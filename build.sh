#!/bin/bash

#Fail on error
set -e

cd `dirname "$0"`

VLC_VERSION=3.0.6

case "$TARGET_PLATFORM" in
  "win32")
    export HOST_COMPILER="i686-w64-mingw32"
    export PATH="/opt/gcc-$HOST_COMPILER/bin:$PATH"
    ;;
  "win64")
    export HOST_COMPILER="x86_64-w64-mingw32"
    export PATH="/opt/gcc-$HOST_COMPILER/bin:$PATH"
  ;;
  *)
    echo "TARGET_PLATFORM is unspecified"
  return 1;
esac

if [[ ! -d bin ]]; then
    if [[ ! -f vlc-$VLC_VERSION-$TARGET_PLATFORM.7z ]]; then
      wget https://get.videolan.org/vlc/$VLC_VERSION/$TARGET_PLATFORM/vlc-$VLC_VERSION-$TARGET_PLATFORM.7z
    fi

    7z x vlc-$VLC_VERSION-win64.7z
    mv vlc-$VLC_VERSION/ bin

    # Change prefix root of package config files
    sed -i -e "s+^prefix=.*+prefix=$(pwd)/bin/sdk+" bin/sdk/lib/pkgconfig/*.pc

    cp /opt/qt/bin/{Qt5Core,Qt5Gui,Qt5Widgets}.dll bin
    mkdir bin/platforms
    cp /opt/qt/plugins/platforms/qwindows.dll bin/platforms/

    # This is important for the bug to happen
    rm -rf bin/plugins/audio_output/libmmdevice_plugin.dll
fi

cd bin
cmake -DCMAKE_TOOLCHAIN_FILE=/Toolchain.$HOST_COMPILER.cmake ..
make