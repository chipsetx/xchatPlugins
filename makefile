
all:
	gcc -shared -fPIC `pkg-config --cflags --libs libnotify` xchatNotify.c -o libnotify_hilight.so

install:
	cp libnotify_hilight.so $(DESTDIR)/usr/lib/xchat/plugins/

clean:
	rm libnotify_hilight.so
