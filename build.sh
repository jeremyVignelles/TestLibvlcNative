#!/bin/bash

cd `dirname "$0"`

VLC_VERSION=3.0.4

if [[ ! -d vlc-$VLC_VERSION ]]; then
    wget https://get.videolan.org/vlc/$VLC_VERSION/win64/vlc-$VLC_VERSION-win64.7z

    7z x vlc-$VLC_VERSION-win64.7z
fi


if [[ ! -d bin ]]; then
    mkdir bin
    cp vlc-$VLC_VERSION/libvlc.dll bin
    cp vlc-$VLC_VERSION/libvlccore.dll bin
    cp -r vlc-$VLC_VERSION/hrtfs bin
    cp -r vlc-$VLC_VERSION/locale bin
    cp -r vlc-$VLC_VERSION/lua bin
    cp -r vlc-$VLC_VERSION/plugins bin
fi

x86_64-w64-mingw32-gcc main.c -I/src/vlc-$VLC_VERSION/sdk/include -L/src/vlc-$VLC_VERSION/sdk/lib -lvlccore -lvlc -o bin/testVlc.exe