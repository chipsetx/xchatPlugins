XChat Plugins
=============

This repo serves as a holder for the libnotify xchat plugin.

I wrote this for personal usage: it is not production code in that there's no
way to configure the messages sent. It is a good base to build a custom XChat
LibNotify plugin from, hence I'm sharing it here.

I recommend using <a href="https://github.com/knopwob/dunst">Dunst</a>, a
lightweight notification daemon.

Compilation
===========
Pretty simple, just run `make` and then `make install` to compile and install
as the current user.

Usage
=====
XChat will automatically load the plugin when starting up.

Author
=======
-Harry van Haaren, 2013
harryhaaren@gmail.com

