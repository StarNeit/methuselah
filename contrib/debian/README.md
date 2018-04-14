
Debian
====================
This directory contains files used to package methuselahd/methuselah-qt
for Debian-based Linux systems. If you compile methuselahd/methuselah-qt yourself, there are some useful files here.

## methuselah: URI support ##


methuselah-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install methuselah-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your methuselah-qt binary to `/usr/bin`
and the `../../share/pixmaps/methuselah128.png` to `/usr/share/pixmaps`

methuselah-qt.protocol (KDE)

