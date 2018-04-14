Release Process
====================

* * *

###update (commit) version in sources

	contrib/verifysfbinaries/verify.sh
	doc/README*
	share/setup.nsi
	src/clientversion.h (change CLIENT_VERSION_IS_RELEASE to true)

###tag version in git

	git tag -s v(new version, e.g. 0.8.0)

###write release notes. git shortlog helps a lot, for example:

	git shortlog --no-merges v(current version, e.g. 0.7.2)..v(new version, e.g. 0.8.0)

* * *

##perform gitian builds

 From a directory containing the methuselah source, gitian-builder and gitian.sigs

	export SIGNER=(your gitian key, ie bluematt, sipa, etc)
	export VERSION=(new version, e.g. 0.8.0)
	pushd ./methuselah
	git checkout v${VERSION}
	popd
	pushd ./gitian-builder
        mkdir -p inputs; cd inputs/

 Register and download the Apple SDK (see OSX Readme for details)
	visit https://developer.apple.com/downloads/download.action?path=Developer_Tools/xcode_4.6.3/xcode4630916281a.dmg

 Using a Mac, create a tarball for the 10.7 SDK
	tar -C /Volumes/Xcode/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/ -czf MacOSX10.7.sdk.tar.gz MacOSX10.7.sdk

 Fetch and build inputs: (first time, or when dependency versions change)

	wget 'http://miniupnp.free.fr/files/download.php?file=miniupnpc-1.9.20140701.tar.gz' -O miniupnpc-1.9.20140701.tar.gz
	wget 'https://www.openssl.org/source/openssl-1.0.2g.tar.gz'
	wget 'http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz'
	wget 'http://zlib.net/zlib-1.2.8.tar.gz'
	wget 'ftp://ftp.simplesystems.io/pub/png/src/history/libpng16/libpng-1.6.8.tar.gz'
	wget 'https://fukuchi.io/works/qrencode/qrencode-3.4.3.tar.bz2'
	wget 'https://downloads.sourcefioe.net/project/boost/boost/1.55.0/boost_1_55_0.tar.bz2'
	wget 'https://svn.boost.io/trac/boost/raw-attachment/ticket/7262/boost-mingw.patch' -O \
	     boost-mingw-gas-cross-compile-2013-03-03.patch
	wget 'https://download.qt-project.io/official_releases/qt/5.2/5.2.0/single/qt-everywhere-opensource-src-5.2.0.tar.gz'
	wget 'https://download.qt-project.io/archive/qt/4.6/qt-everywhere-opensource-src-4.6.4.tar.gz'
	wget 'https://protobuf.googlecode.com/files/protobuf-2.5.0.tar.bz2'
	wget 'https://github.com/mingwandroid/toolchain4/archive/10cc648683617cca8bcbeae507888099b41b530c.tar.gz'
	wget 'http://www.opensource.apple.com/tarballs/cctools/cctools-809.tar.gz'
	wget 'http://www.opensource.apple.com/tarballs/dyld/dyld-195.5.tar.gz'
	wget 'http://www.opensource.apple.com/tarballs/ld64/ld64-127.2.tar.gz'
	wget 'http://pkgs.fedoraproject.io/repo/pkgs/cdrkit/cdrkit-1.1.11.tar.gz/efe08e2f3ca478486037b053acd512e9/cdrkit-1.1.11.tar.gz'
	wget 'https://github.com/theuni/libdmg-hfsplus/archive/libdmg-hfsplus-v0.1.tar.gz'
	wget 'http://llvm.io/releases/3.2/clang+llvm-3.2-x86-linux-ubuntu-12.04.tar.gz' -O \
	     clang-llvm-3.2-x86-linux-ubuntu-12.04.tar.gz
        wget 'https://raw.githubusercontent.com/theuni/osx-cross-depends/master/patches/cdrtools/genisoimage.diff' -O \
	     cdrkit-deterministic.patch
	cd ..
	./bin/gbuild ../methuselah/contrib/gitian-descriptors/boost-linux.yml
	mv build/out/boost-*.zip inputs/
	./bin/gbuild ../methuselah/contrib/gitian-descriptors/deps-linux.yml
	mv build/out/methuselah-deps-*.zip inputs/
	./bin/gbuild ../methuselah/contrib/gitian-descriptors/qt-linux.yml
	mv build/out/qt-*.tar.gz inputs/
	./bin/gbuild ../methuselah/contrib/gitian-descriptors/boost-win.yml
	mv build/out/boost-*.zip inputs/
	./bin/gbuild ../methuselah/contrib/gitian-descriptors/deps-win.yml
	mv build/out/methuselah-deps-*.zip inputs/
	./bin/gbuild ../methuselah/contrib/gitian-descriptors/qt-win.yml
	mv build/out/qt-*.zip inputs/
	./bin/gbuild ../methuselah/contrib/gitian-descriptors/protobuf-win.yml
	mv build/out/protobuf-*.zip inputs/
	./bin/gbuild ../methuselah/contrib/gitian-descriptors/gitian-osx-native.yml
	mv build/out/osx-*.tar.gz inputs/
	./bin/gbuild ../methuselah/contrib/gitian-descriptors/gitian-osx-depends.yml
	mv build/out/osx-*.tar.gz inputs/
	./bin/gbuild ../methuselah/contrib/gitian-descriptors/gitian-osx-qt.yml
	mv build/out/osx-*.tar.gz inputs/

 Build methuselahd and methuselah-qt on Linux32, Linux64, and Win32:

	./bin/gbuild --commit methuselah=v${VERSION} ../methuselah/contrib/gitian-descriptors/gitian-linux.yml
	./bin/gsign --signer $SIGNER --release ${VERSION} --destination ../gitian.sigs/ ../methuselah/contrib/gitian-descriptors/gitian-linux.yml
	pushd build/out
	zip -r methuselah-${VERSION}-linux-gitian.zip *
	mv methuselah-${VERSION}-linux-gitian.zip ../../../
	popd
	./bin/gbuild --commit methuselah=v${VERSION} ../methuselah/contrib/gitian-descriptors/gitian-win.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win --destination ../gitian.sigs/ ../methuselah/contrib/gitian-descriptors/gitian-win.yml
	pushd build/out
	zip -r methuselah-${VERSION}-win-gitian.zip *
	mv methuselah-${VERSION}-win-gitian.zip ../../../
	popd
    ./bin/gbuild --commit methuselah=v${VERSION} ../methuselah/contrib/gitian-descriptors/gitian-osx-methuselah.yml
    ./bin/gsign --signer $SIGNER --release ${VERSION}-osx --destination ../gitian.sigs/ ../methuselah/contrib/gitian-descriptors/gitian-osx-methuselah.yml
	pushd build/out
	mv Methuselah-Qt.dmg ../../../
	popd
	popd

  Build output expected:

  1. linux 32-bit and 64-bit binaries + source (methuselah-${VERSION}-linux-gitian.zip)
  2. windows 32-bit and 64-bit binaries + installer + source (methuselah-${VERSION}-win-gitian.zip)
  3. OSX installer (Methuselah-Qt.dmg)
  4. Gitian signatures (in gitian.sigs/${VERSION}[-win|-osx]/(your gitian key)/

repackage gitian builds for release as stand-alone zip/tar/installer exe

**Linux .tar.gz:**

	unzip methuselah-${VERSION}-linux-gitian.zip -d methuselah-${VERSION}-linux
	tar czvf methuselah-${VERSION}-linux.tar.gz methuselah-${VERSION}-linux
	rm -rf methuselah-${VERSION}-linux

**Windows .zip and setup.exe:**

	unzip methuselah-${VERSION}-win-gitian.zip -d methuselah-${VERSION}-win
	mv methuselah-${VERSION}-win/methuselah-*-setup.exe .
	zip -r methuselah-${VERSION}-win.zip methuselah-${VERSION}-win
	rm -rf methuselah-${VERSION}-win

**Mac OS X .dmg:**

	mv Methuselah-Qt.dmg methuselah-${VERSION}-osx.dmg

###Next steps:

Commit your signature to gitian.sigs:

	pushd gitian.sigs
	git add ${VERSION}-linux/${SIGNER}
	git add ${VERSION}-win/${SIGNER}
	git add ${VERSION}-osx/${SIGNER}
	git commit -a
	git push  # Assuming you can push to the gitian.sigs tree
	popd

-------------------------------------------------------------------------

### After 3 or more people have gitian-built and their results match:

- Perform code-signing.

    - Code-sign Windows -setup.exe (in a Windows virtual machine using signtool)

    - Code-sign MacOSX .dmg

  Note: only Gavin has the code-signing keys currently.

- Create `SHA256SUMS.asc` for builds, and PGP-sign it. This is done manually.
  Include all the files to be uploaded. The file has `sha256sum` format with a
  simple header at the top:

```
Hash: SHA256

0060f7d38b98113ab912d4c184000291d7f026eaf77ca5830deec15059678f54  methuselah-x.y.z-linux.tar.gz
...
```

- Upload zips and installers, as well as `SHA256SUMS.asc` from last step, to the methuselahcoin.io server

- Update methuselahcoin.io version

  - Make a pull request to add a file named `YYYY-MM-DD-vX.Y.Z.md` with the release notes
  to https://github.com/bitcoin/bitcoin.io/tree/master/_releases
   ([Example for 0.9.2.1](https://raw.githubusercontent.com/bitcoin/bitcoin.io/master/_releases/2014-06-19-v0.9.2.1.md)).

  - After the pull request is merged, the website will automatically show the newest version, as well
    as update the OS download links. Ping Saivann in case anything goes wrong

- Announce the release:

  - Release sticky on bitcointalk: https://bitcointalk.io/index.php?board=1.0

  - Methuselah-development mailing list

  - Update title of #methuselah on Freenode IRC

  - Optionally reddit /r/Methuselah, ... but this will usually sort out itself

- Notify BlueMatt so that he can start building [https://launchpad.net/~bitcoin/+archive/ubuntu/bitcoin](the PPAs)

- Add release notes for the new version to the directory `doc/release-notes` in git master

- Celebrate
