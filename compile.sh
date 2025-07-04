source /opt/rpi-4.0b/environment-setup-cortexa72-poky-linux
export TARGET="gtk"
export SRC="*.c"
export CPPFLAGS=""
export CXXFLAGS=""
export LDFLAGS=" \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/gtk-3.0 \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/pango-1.0 \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/glib-2.0 \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/glib-2.0/include/ \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/lib/glib-2.0/include/ \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/harfbuzz -I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/freetype2 \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/libpng16 \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/libmount \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/blkid \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/fribidi \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/uuid \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/cairo \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/pixman-1 \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/gdk-pixbuf-2.0 \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/x86_64-linux-gnu \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/gio-unix-2.0 \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/atk-1.0 \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/at-spi2-atk/2.0 \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/dbus-1.0 \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/lib/x86_64-linux-gnu/dbus-1.0/include \
-I/opt/rpi-4.0b/sysroots/cortexa72-poky-linux//usr/include/at-spi-2.0 \
-lpthread \
-lgtk-3 \
-lgdk-3 \
-lpangocairo-1.0 \
-lpango-1.0 \
-lharfbuzz \
-latk-1.0 \
-lcairo-gobject \
-lcairo \
-lgdk_pixbuf-2.0 \
-lgio-2.0 \
-lgobject-2.0 \
-lglib-2.0 "

make -j$(cat /proc/cpuinfo | grep -c processor)