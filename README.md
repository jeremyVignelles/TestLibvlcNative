# TestLibvlcNative
A test project I'm using to reproduce bugs in libvlc on win-x64 using docker.

This is the Qt branch, to help reproduce bugs involving Qt in C++

## How to build the project

Ensure you have docker and that you can bind-mount this folder into a volume (i.e. by default, you will need to put this folder under your user folder.)

Build the docker image used here with `./build-docker-image.sh`. This will take a while (because it builds Qt for win64), you can make yourself a coffee.

open the docker quickstart terminal and run `./build-docker.sh`