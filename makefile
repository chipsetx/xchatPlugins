
all:
	gcc -shared -fPIC `pkg-config --cflags --libs libnotify` xchatNotify.c -o libnotify_hilight.so

install:
	install -d libnotify_hilight.so $(DESTDIR)/usr/lib/xchat/plugins/

clean:
	rm libnotify_hilight.so
