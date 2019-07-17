#!/bin/bash

cd `dirname "$0"`

VLC_VERSION=4.0.0-20190717-0833
VLC_FOLDER_NAME=vlc-4.0.0-dev

if [[ ! -d $VLC_FOLDER_NAME ]]; then
    wget https://nightlies.videolan.org/build/win64/vlc-$VLC_VERSION/vlc-$VLC_VERSION-dev-win64.7z

    7z x vlc-$VLC_VERSION-dev-win64.7z
fi


if [[ ! -d bin ]]; then
    mkdir bin
    cp $VLC_FOLDER_NAME/libvlc.dll bin
    cp $VLC_FOLDER_NAME/libvlccore.dll bin
    cp -r $VLC_FOLDER_NAME/hrtfs bin
    cp -r $VLC_FOLDER_NAME/locale bin
    cp -r $VLC_FOLDER_NAME/lua bin
    cp -r $VLC_FOLDER_NAME/plugins bin
fi

x86_64-w64-mingw32-g++ d3d11_player.cpp -I/src/$VLC_FOLDER_NAME/sdk/include -L/src/$VLC_FOLDER_NAME/sdk/lib -lvlc -ld3d11 -ld3dcompiler_47 -luuid -o bin/testVlc.exe
