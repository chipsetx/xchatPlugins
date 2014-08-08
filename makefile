
all:
	gcc -shared -fPIC `pkg-config --cflags --libs libnotify` xchatNotify.c -o libnotify_hilight.so

install:
	mkdir -p ~/.xchat2/
	cp libnotify_hilight.so ~/.xchat2/

clean:
	rm libnotify_hilight.so
