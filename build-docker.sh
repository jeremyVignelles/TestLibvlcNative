#!/bin/bash

cd `dirname "$0"`
docker run -it --rm --mount type=bind,src=$(pwd),dst=//src registry.videolan.org:5000/vlc-debian-win64:20201106143728 //src/build.sh