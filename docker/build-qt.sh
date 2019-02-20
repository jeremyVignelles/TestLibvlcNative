#!/bin/bash

#Fail on error
set -e

export QT_VERSION=5.12.1
export QT_PATH=/qt
export INSTALL_PATH=/opt/qt

case "$TARGET_PLATFORM" in
  "win32")
    export arch="x86"
    export os="Windows"
    export HOST_COMPILER="i686-w64-mingw32"
    export PATH="/opt/gcc-$HOST_COMPILER/bin:$PATH"
    ;;
  "win64")
    export arch="x64"
    export os="Windows"
    export HOST_COMPILER="x86_64-w64-mingw32"
    export PATH="/opt/gcc-$HOST_COMPILER/bin:$PATH"
  ;;
  *)
    echo "TARGET_PLATFORM is unspecified"
  return 1;
esac

mkdir -p $QT_PATH
mkdir -p $INSTALL_PATH

#Download the source
cd $QT_PATH
wget https://download.qt.io/official_releases/qt/5.12/$QT_VERSION/submodules/qtbase-everywhere-src-$QT_VERSION.tar.xz

#Extract the source
tar xf qtbase-everywhere-src-$QT_VERSION.tar.xz
rm -rf qtbase-everywhere-src-$QT_VERSION.tar.xz
cd $QT_PATH/qtbase-everywhere-src-$QT_VERSION/

#Configure and build QT
./configure -xplatform win32-g++ -device-option CROSS_COMPILE=${HOST_COMPILER}- --prefix=$INSTALL_PATH -opensource -confirm-license \
	-no-sql-sqlite -no-gif -qt-libjpeg -no-openssl -no-opengl -no-dbus \
	-no-sql-odbc -no-pch \
  -no-compile-examples -nomake examples

make -j4
make install
rm -rf /qt
