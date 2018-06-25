#!/bin/bash

INSTALL_DIR=/usr/local/bin
OUTDIR=$TRAVIS_BUILD_DIR/bin/$HOST
mkdir -p $OUTDIR

ARCHIVE_CMD="zip"

if [[ $HOST = "i686-w64-mingw32" ]]; then
    ARCHIVE_NAME="windows-x86.zip"
elif [[ $HOST = "x86_64-w64-mingw32" ]]; then
    ARCHIVE_NAME="windows-x64.zip"
elif [[ $HOST = "arm-linux-gnueabihf" ]]; then
    ARCHIVE_NAME="arm-x86.tar.gz"
    ARCHIVE_CMD="tar -czf"
elif [[ $HOST = "aarch64-linux-gnu" ]]; then
    ARCHIVE_NAME="arm-x64.tar.gz"
    ARCHIVE_CMD="tar -czf"
elif [[ $HOST = "x86_64-unknown-linux-gnu" ]]; then
    ARCHIVE_NAME="linux-x64.tar.gz"
    ARCHIVE_CMD="tar -czf"
elif [[ $HOST = "x86_64-apple-darwin11" ]]; then
    ARCHIVE_NAME="osx-x64.zip"
fi

cp $INSTALL_DIR/methuselah-qt $OUTDIR || cp $INSTALL_DIR/methuselah-qt.exe $OUTDIR || echo "no QT Wallet"
cp $INSTALL_DIR/methuselahd $OUTDIR || cp $INSTALL_DIR/methuselahd.exe $OUTDIR
cp $INSTALL_DIR/methuselah-cli $OUTDIR || cp $INSTALL_DIR/methuselah-cli.exe $OUTDIR
strip "$OUTDIR"/* || echo "nothing to strip"
ls -lah $OUTDIR

cd $OUTDIR
ARCHIVE_CMD="$ARCHIVE_CMD $ARCHIVE_NAME *"
eval $ARCHIVE_CMD

mkdir -p $OUTDIR/zip
mv $ARCHIVE_NAME $OUTDIR/zip

echo "Install: $INSTALL"
echo ls $INSTALL
echo "Output: $OUTDIR"
echo ls $OUTDIR
echo "Archives: $OUTDIR/zip"
echo ls $OUTDIR/zip

sleep $[ ( $RANDOM % 6 )  + 1 ]s