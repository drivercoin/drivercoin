
Debian
====================
This directory contains files used to package drivercoind/drivercoin-qt
for Debian-based Linux systems. If you compile drivercoind/drivercoin-qt yourself, there are some useful files here.

## drivercoin: URI support ##


drivercoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install drivercoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your drivercoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/drivercoin128.png` to `/usr/share/pixmaps`

drivercoin-qt.protocol (KDE)

