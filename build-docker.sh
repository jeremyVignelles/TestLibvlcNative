#!/bin/bash

cd `dirname "$0"`
docker run --rm -it --mount type=bind,src=$(pwd),dst=/src test-libvlc-native /src/build.sh