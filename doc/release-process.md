Release Process
====================

* Update translations (ping wumpus, Diapolo or tcatm on IRC) see [translation_process.md](https://github.com/drivercoin/drivercoin/blob/master/doc/translation_process.md#syncing-with-transifex)
* Update [bips.md](bips.md) to account for changes since the last release.

* * *

###First time / New builders 
Check out the source code in the following directory hierarchy.

	cd /path/to/your/toplevel/build
	git clone https://github.com/drivercoin/gitian.sigs.git
	git clone https://github.com/drivercoin/drivercoin-detached-sigs.git
	git clone https://github.com/devrandom/gitian-builder.git
	git clone https://github.com/drivercoin/drivercoin.git

###Drivercoin maintainers/release engineers, update (commit) version in sources

	pushd ./drivercoin
	contrib/verifysfbinaries/verify.sh
	doc/README*
	share/setup.nsi
	src/clientversion.h (change CLIENT_VERSION_IS_RELEASE to true)

	# tag version in git

	git tag -s v(new version, e.g. 0.8.0)

	# write release notes. git shortlog helps a lot, for example:

	git shortlog --no-merges v(current version, e.g. 0.7.2)..v(new version, e.g. 0.8.0)
	popd

* * *

###Setup and perform gitian builds

 Setup gitian descriptors:
  
	pushd ./drivercoin
	export SIGNER=(your gitian key, ie bluematt, sipa, etc)
	export VERSION=(new version, e.g. 0.8.0)
	git checkout v${VERSION}
	popd

  Ensure your gitian.sigs are up-to-date if you wish to gverify your builds against other gitian signatures.

	pushd ./gitian.sigs
	git pull
	popd

  Ensure gitian-builder is up-to-date to take advantage of new caching features (`e9741525c` or later is recommended).

	pushd ./gitian-builder
	git pull

###Fetch and create inputs: (first time, or when dependency versions change)
 
	mkdir -p inputs
	wget -P inputs https://drivercoincore.org/cfields/osslsigncode-Backports-to-1.7.1.patch
	wget -P inputs http://downloads.sourceforge.net/project/osslsigncode/osslsigncode/osslsigncode-1.7.1.tar.gz

 Register and download the Apple SDK: see [OSX readme](README_osx.txt) for details.
 
 https://developer.apple.com/devcenter/download.action?path=/Developer_Tools/xcode_6.1.1/xcode_6.1.1.dmg
 
 Using a Mac, create a tarball for the 10.9 SDK and copy it to the inputs directory:
 
	tar -C /Volumes/Xcode/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/ -czf MacOSX10.9.sdk.tar.gz MacOSX10.9.sdk

###Optional: Seed the Gitian sources cache and offline git repositories

By default, gitian will fetch source files as needed. To cache them ahead of time:

	make -C ../drivercoin/depends download SOURCES_PATH=`pwd`/cache/common

Only missing files will be fetched, so this is safe to re-run for each build.

NOTE: Offline builds must use the --url flag to ensure gitian fetches only from local URLs. For example: 
```
./bin/bguild --url drivercoin=/path/to/drivercoin,signature=/path/to/sigs {rest of arguments}
```
The gbuild invocations below <b>DO NOT DO THIS</b> by default.

###Build (and optionally verify) Drivercoin Core for Linux, Windows, and OS X:
  
	./bin/gbuild --commit drivercoin=v${VERSION} ../drivercoin/contrib/gitian-descriptors/gitian-linux.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-linux --destination ../gitian.sigs/ ../drivercoin/contrib/gitian-descriptors/gitian-linux.yml
	./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-linux ../drivercoin/contrib/gitian-descriptors/gitian-linux.yml
	mv build/out/drivercoin-*.tar.gz build/out/src/drivercoin-*.tar.gz ../

	./bin/gbuild --commit drivercoin=v${VERSION} ../drivercoin/contrib/gitian-descriptors/gitian-win.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win-unsigned --destination ../gitian.sigs/ ../drivercoin/contrib/gitian-descriptors/gitian-win.yml
	./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-win-unsigned ../drivercoin/contrib/gitian-descriptors/gitian-win.yml
	mv build/out/drivercoin-*-win-unsigned.tar.gz inputs/drivercoin-win-unsigned.tar.gz
	mv build/out/drivercoin-*.zip build/out/drivercoin-*.exe ../

	./bin/gbuild --commit drivercoin=v${VERSION} ../drivercoin/contrib/gitian-descriptors/gitian-osx.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-osx-unsigned --destination ../gitian.sigs/ ../drivercoin/contrib/gitian-descriptors/gitian-osx.yml
	./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-osx-unsigned ../drivercoin/contrib/gitian-descriptors/gitian-osx.yml
	mv build/out/drivercoin-*-osx-unsigned.tar.gz inputs/drivercoin-osx-unsigned.tar.gz
	mv build/out/drivercoin-*.tar.gz build/out/drivercoin-*.dmg ../
	popd

  Build output expected:

  1. source tarball (drivercoin-${VERSION}.tar.gz)
  2. linux 32-bit and 64-bit dist tarballs (drivercoin-${VERSION}-linux[32|64].tar.gz)
  3. windows 32-bit and 64-bit unsigned installers and dist zips (drivercoin-${VERSION}-win[32|64]-setup-unsigned.exe, drivercoin-${VERSION}-win[32|64].zip)
  4. OSX unsigned installer and dist tarball (drivercoin-${VERSION}-osx-unsigned.dmg, drivercoin-${VERSION}-osx64.tar.gz)
  5. Gitian signatures (in gitian.sigs/${VERSION}-<linux|{win,osx}-unsigned>/(your gitian key)/

###Next steps:

Commit your signature to gitian.sigs:

	pushd gitian.sigs
	git add ${VERSION}-linux/${SIGNER}
	git add ${VERSION}-win-unsigned/${SIGNER}
	git add ${VERSION}-osx-unsigned/${SIGNER}
	git commit -a
	git push  # Assuming you can push to the gitian.sigs tree
	popd

  Wait for Windows/OSX detached signatures:

	Once the Windows/OSX builds each have 3 matching signatures, they will be signed with their respective release keys.
	Detached signatures will then be committed to the [drivercoin-detached-sigs](https://github.com/drivercoin/drivercoin-detached-sigs) repository, which can be combined with the unsigned apps to create signed binaries.

  Create (and optionally verify) the signed OSX binary:

	pushd ./gitian-builder
	./bin/gbuild -i --commit signature=v${VERSION} ../drivercoin/contrib/gitian-descriptors/gitian-osx-signer.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-osx-signed --destination ../gitian.sigs/ ../drivercoin/contrib/gitian-descriptors/gitian-osx-signer.yml
	./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-osx-signed ../drivercoin/contrib/gitian-descriptors/gitian-osx-signer.yml
	mv build/out/drivercoin-osx-signed.dmg ../drivercoin-${VERSION}-osx.dmg
	popd

  Create (and optionally verify) the signed Windows binaries:

	pushd ./gitian-builder
	./bin/gbuild -i --commit signature=v${VERSION} ../drivercoin/contrib/gitian-descriptors/gitian-win-signer.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win-signed --destination ../gitian.sigs/ ../drivercoin/contrib/gitian-descriptors/gitian-win-signer.yml
	./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-win-signed ../drivercoin/contrib/gitian-descriptors/gitian-win-signer.yml
	mv build/out/drivercoin-*win64-setup.exe ../drivercoin-${VERSION}-win64-setup.exe
	mv build/out/drivercoin-*win32-setup.exe ../drivercoin-${VERSION}-win32-setup.exe
	popd

Commit your signature for the signed OSX/Windows binaries:

	pushd gitian.sigs
	git add ${VERSION}-osx-signed/${SIGNER}
	git add ${VERSION}-win-signed/${SIGNER}
	git commit -a
	git push  # Assuming you can push to the gitian.sigs tree
	popd

-------------------------------------------------------------------------

### After 3 or more people have gitian-built and their results match:

- Create `SHA256SUMS.asc` for the builds, and GPG-sign it:
```bash
sha256sum * > SHA256SUMS
gpg --digest-algo sha256 --clearsign SHA256SUMS # outputs SHA256SUMS.asc
rm SHA256SUMS
```
(the digest algorithm is forced to sha256 to avoid confusion of the `Hash:` header that GPG adds with the SHA256 used for the files)
Note: check that SHA256SUMS itself doesn't end up in SHA256SUMS, which is a spurious/nonsensical entry.

- Upload zips and installers, as well as `SHA256SUMS.asc` from last step, to the drivercoin.org server
  into `/var/www/bin/drivercoin-core-${VERSION}`

- Update drivercoin.org version

  - First, check to see if the Drivercoin.org maintainers have prepared a
    release: https://github.com/drivercoin-dot-org/drivercoin.org/labels/Releases

      - If they have, it will have previously failed their Travis CI
        checks because the final release files weren't uploaded.
        Trigger a Travis CI rebuild---if it passes, merge.

  - If they have not prepared a release, follow the Drivercoin.org release
    instructions: https://github.com/drivercoin-dot-org/drivercoin.org#release-notes

  - After the pull request is merged, the website will automatically show the newest version within 15 minutes, as well
    as update the OS download links. Ping @saivann/@harding (saivann/harding on Freenode) in case anything goes wrong

- Announce the release:

  - Release sticky on drivercointalk: https://drivercointalk.org/index.php?board=1.0

  - Drivercoin-development mailing list

  - Update title of #drivercoin on Freenode IRC

  - Optionally reddit /r/Drivercoin, ... but this will usually sort out itself

- Notify BlueMatt so that he can start building [https://launchpad.net/~drivercoin/+archive/ubuntu/drivercoin](the PPAs)

- Add release notes for the new version to the directory `doc/release-notes` in git master

- Celebrate
