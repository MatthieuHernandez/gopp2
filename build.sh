#!/bin/bash

set -e  # Arrêter l'exécution en cas d'erreur

BUILD_TYPE="Debug"
RUN="run"

# Vérifier les arguments
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

cppfront -cwd ./generate ../src/color.h2 $DebugArg |
cppfront -cwd ./generate ../src/stone.h2 -import-std $DebugArg |
cppfront -cwd ./generate ../src/move.h2 -import-std $DebugArg |
cppfront -cwd ./generate ../src/goban.h2  -import-std $DebugArg |
cppfront -cwd ./generate ../src/engine.h2 -import-std $DebugArg |
cppfront -cwd ./generate ../src/io.h2 -import-std $DebugArg |
cppfront -cwd ./generate ../src/player.h2 -import-std $DebugArg |
cppfront -cwd ./generate ../src/human.h2 -import-std $DebugArg |
cppfront -cwd ./generate ../src/dumb.h2 -import-std $DebugArg |
cppfront -cwd ./generate ../src/random.h2 -import-std $DebugArg |
cppfront -cwd ./generate ../src/ai.h2 -import-std $DebugArg |
cppfront -cwd ./generate ../src/itself.h2 -import-std $DebugArg |
cppfront -cwd ./generate ../src/game.h2 -import-std $DebugArg |
cppfront -cwd ./generate ../src/main.cpp2 -import-std $DebugArg

# Déplacer les fichiers de debug si nécessaire
if [[ "$BUILD_TYPE" == "Debug" ]]; then
    mkdir -p "$BUILD_DIR/src"
    cp -f ./src/*.h2 "$BUILD_DIR/src/"
    cp -f ./src/*.cpp2 "$BUILD_DIR/src/"
    mv -f ./src/*.h2-* "$BUILD_DIR/src/" 2>/dev/null || true
    mv -f ./src/*.cpp2-* "$BUILD_DIR/src/" 2>/dev/null || true
fi

# Configurer et compiler avec CMake et Ninja
cmake -S . -B $BUILD_DIR -G"Unix Makefiles" -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
make -C $BUILD_DIR

# Exécuter le binaire si demandé
if [[ "$RUN" != "norun" ]]; then
    "$BUILD_DIR/gopp2.exe"
fi
