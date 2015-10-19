Drivercoin Core 0.11.99
=====================

Setup
---------------------
[Drivercoin Core](http://drivercoin.org/en/download) is the original Drivercoin client and it builds the backbone of the network. However, it downloads and stores the entire history of Drivercoin transactions (which is currently several GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

Running
---------------------
The following are some helpful notes on how to run Drivercoin on your native platform. 

### Unix

You need the Qt4 run-time libraries to run Drivercoin-Qt. On Debian or Ubuntu:

	sudo apt-get install libqtgui4

Unpack the files into a directory and run:

- bin/32/drivercoin-qt (GUI, 32-bit) or bin/32/drivercoind (headless, 32-bit)
- bin/64/drivercoin-qt (GUI, 64-bit) or bin/64/drivercoind (headless, 64-bit)



### Windows

Unpack the files into a directory, and then run drivercoin-qt.exe.

### OSX

Drag Drivercoin-Qt to your applications folder, and then run Drivercoin-Qt.

### Need Help?

* See the documentation at the [Drivercoin Wiki](https://en.drivercoin.it/wiki/Main_Page)
for help and more information.
* Ask for help on [#drivercoin](http://webchat.freenode.net?channels=drivercoin) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=drivercoin).
* Ask for help on the [DrivercoinTalk](https://drivercointalk.org/) forums, in the [Technical Support board](https://drivercointalk.org/index.php?board=4.0).

Building
---------------------
The following are developer notes on how to build Drivercoin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OSX Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The Drivercoin repo's [root README](https://github.com/drivercoin/drivercoin/blob/master/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/drivercoin/doxygen/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)

### Resources
* Discuss on the [DrivercoinTalk](https://drivercointalk.org/) forums, in the [Development & Technical Discussion board](https://drivercointalk.org/index.php?board=6.0).
* Discuss project-specific development on #drivercoin-core-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=drivercoin-core-dev).
* Discuss general Drivercoin development on #drivercoin-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=drivercoin-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
Distributed under the [MIT software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
