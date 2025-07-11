#!/bin/bash

set -e

BUILD_TYPE="Debug"
RUN="run"
PROG_ARG="$3"

if [[ "$1" == "Release" ]]; then
    BUILD_TYPE="Release"
fi
if [[ "$2" == "norun" ]]; then
    RUN="norun"
fi

BUILD_DIR="./build/$BUILD_TYPE"
DEBUG_ARG=""
if [[ "$BUILD_TYPE" == "Debug" ]]; then
    DEBUG_ARG="-d"
fi

cppfront -cwd ./src/generated ../cpp2/transformation.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/color.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/stone.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/move.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/goban.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/engine.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/io.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/cli.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/player.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/human.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/dumb.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/random.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/ai.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/itself.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/game.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/interface.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/cli_interface.h2 -pure-cpp2 $DebugArg |
cppfront -cwd ./src/generated ../cpp2/gui_interface.h2 -import-std $DebugArg |
cppfront -cwd ./src/generated ../cpp2/main.cpp2 -import-std $DebugArg

# Move files used for debugging to the build folder.
if [[ "$BUILD_TYPE" == "Debug" ]]; then
    mkdir -p "$BUILD_DIR/src"
    mkdir -p "$BUILD_DIR/src/cpp2"
    cp -f ./src/*.h2 "$BUILD_DIR/src/"
    cp -f ./src/*.cpp2 "$BUILD_DIR/src/"
    mv -f ./src/cpp2/*.h2-* "$BUILD_DIR/src/cpp2/" 2>/dev/null || true
    mv -f ./src/cpp2/*.cpp2-* "$BUILD_DIR/src/cpp2/" 2>/dev/null || true
fi

mkdir -p "$BUILD_DIR/bin/images"
cp -f ./resources/images/*  "$BUILD_DIR/bin/images"

ln -sfn "$(realpath --relative-to="$BUILD_DIR/bin" ./snn_models)" "$BUILD_DIR/bin/snn_models"

cmake -S . -B $BUILD_DIR -G"Unix Makefiles" \
    -DCMAKE_CXX_COMPILER=g++-14 \
    -DCMAKE_C_COMPILER=gcc-14 \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
make -C $BUILD_DIR

mv -f "$BUILD_DIR/gopp2" "$BUILD_DIR/bin/" 2>/dev/null || true

if [[ "$RUN" != "norun" ]]; then
    cd "$BUILD_DIR/bin"
    ./gopp2 "$PROG_ARG"
    cd ../../..
fi
