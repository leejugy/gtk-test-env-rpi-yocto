GTK_CFLAGS = $(shell $(PKG_CONFIG) --cflags gtk+-3.0)
GTK_LIBS = $(shell $(PKG_CONFIG) --libs gtk+-3.0)

all:
	$(CC) $(LDFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)