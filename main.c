#include <gtk/gtk.h> // GTK 라이브러리 헤더
#include <time.h>    // 시간 관련 함수 (time, localtime, strftime)
#include <stdio.h>   // 표준 입출력 함수 (printf 등)
#include <glib.h>    // G_TRUE, G_FALSE 등 GLib 매크로 및 타입 정의

// 시간 업데이트를 위한 함수
// 이 함수는 g_timeout_add_seconds에 의해 주기적으로 호출됩니다.
gboolean update_time(gpointer user_data) {
    // user_data는 GtkLabel 포인터로 전달되므로, GtkLabel로 캐스팅합니다.
    GtkLabel *time_label = GTK_LABEL(user_data); 
    time_t raw_time;       // 현재 시간을 초 단위로 저장할 변수
    struct tm *info;       // 시간을 년, 월, 일, 시, 분, 초 등으로 분해한 구조체 포인터
    char buffer[80];       // 포맷팅된 시간을 저장할 문자열 버퍼

    // 현재 시스템 시간을 가져옵니다.
    time(&raw_time); 
    // 가져온 시간을 지역 시간으로 변환합니다.
    info = localtime(&raw_time); 

    // 시간을 "HH:MM:SS" 형식으로 버퍼에 포맷팅합니다.
    // strftime 함수는 C 표준 라이브러리에 포함되어 있습니다.
    strftime(buffer, sizeof(buffer), "%H:%M:%S", info);

    // GtkLabel 위젯의 텍스트를 업데이트합니다.
    gtk_label_set_text(time_label, buffer);

    // 이 함수가 g_timeout_add_seconds에 의해 계속 호출되도록 G_TRUE를 반환합니다.
    return TRUE; 
}

// 애플리케이션이 활성화(실행)될 때 호출되는 콜백 함수
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;      // 메인 애플리케이션 윈도우
    GtkWidget *grid;        // 위젯 배치를 위한 그리드 컨테이너
    GtkWidget *time_label;  // 현재 시간을 표시할 레이블 위젯

    // 1. 새 GtkApplicationWindow를 생성합니다.
    window = gtk_application_window_new(app);
    // 윈도우 제목을 설정합니다.
    gtk_window_set_title(GTK_WINDOW(window), "linux date timer"); 
    // 윈도우의 기본 크기를 300x300 픽셀로 설정합니다.
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300); 
    // 윈도우 크기 조절을 비활성화합니다.
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE); 

    // 2. GtkGrid 위젯을 생성합니다. (레이블 중앙 정렬을 위해 사용)
    grid = gtk_grid_new();
    // GTK3에서는 gtk_container_add를 사용하여 윈도우에 자식 위젯을 추가합니다.
    gtk_container_add(GTK_CONTAINER(window), grid); 

    // 3. 시간 표시용 GtkLabel 위젯을 생성하고 초기 텍스트를 설정합니다.
    time_label = gtk_label_new("00:00:00"); 

    // 4. 레이블의 폰트 크기와 굵기를 CSS를 통해 설정합니다.
    // GtkCssProvider를 생성합니다.
    GtkCssProvider *provider = gtk_css_provider_new();
    // CSS 데이터를 로드합니다. GTK3에서는 length 인자가 필요합니다.
    const char *css_data = "label { font-size: 48px; font-weight: bold; }";
    gtk_css_provider_load_from_data(provider, css_data, -1, NULL); // -1은 문자열 길이를 자동으로 계산, NULL은 에러 처리용
    
    // 레이블의 스타일 컨텍스트에 CSS 프로바이더를 추가합니다.
    gtk_style_context_add_provider(gtk_widget_get_style_context(time_label),
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    // CSS 프로바이더 객체를 더 이상 사용하지 않으므로 참조 카운트를 감소시킵니다.
    g_object_unref(provider);

    // 5. 그리드에 레이블을 추가하고 중앙에 정렬합니다.
    // gtk_grid_attach(그리드, 위젯, 왼쪽 열, 위쪽 행, 너비, 높이)
    gtk_grid_attach(GTK_GRID(grid), time_label, 0, 0, 1, 1);
    // 수평 중앙 정렬
    gtk_widget_set_halign(time_label, GTK_ALIGN_CENTER);
    // 수직 중앙 정렬
    gtk_widget_set_valign(time_label, GTK_ALIGN_CENTER);

    // 6. 1초(1000밀리초)마다 update_time 함수를 호출하도록 타이머를 설정합니다.
    // update_time 함수에 time_label 위젯을 인자로 전달합니다.
    g_timeout_add_seconds(1, update_time, time_label);

    // 7. 생성된 윈도우를 화면에 표시합니다.
    gtk_widget_show_all(window); // GTK3에서는 show_all이 일반적입니다.
}

// 프로그램의 메인 함수
int main(int argc, char **argv) {
    GtkApplication *app; // GTK 애플리케이션 객체
    int status;          // 애플리케이션 실행 상태 코드

    // 1. 새 GtkApplication 인스턴스를 생성합니다.
    // GTK3에서는 G_APPLICATION_DEFAULT_FLAGS 사용하거나 0을 직접 전달합니다.
    app = gtk_application_new("org.gtk.timertest", G_APPLICATION_DEFAULT_FLAGS); 

    // 2. 애플리케이션의 "activate" 시그널에 activate 함수를 연결합니다.
    // 애플리케이션이 활성화될 때 activate 함수가 호출됩니다.
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // 3. 애플리케이션을 실행합니다.
    status = g_application_run(G_APPLICATION(app), argc, argv);
    
    // 4. 애플리케이션 리소스를 해제합니다.
    g_object_unref(app);

    return status; // 프로그램 종료 상태 반환
}

