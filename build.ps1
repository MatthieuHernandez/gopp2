cppfront -cwd ./generate ../src/color.h2 |
cppfront -cwd ./generate `
    ../src/stone.h2 `
    ../src/goban.h2 `
    ../src/move.h2 `
    ../src/game.h2 `
    ../src/engine.h2 `
    ../src/io.h2 `
    ../src/main.cpp2 `
    -import-std
if (!$?) { Exit $LASTEXITCODE }
cmake -S . -B ./build -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
if (!$?) { Exit $LASTEXITCODE }
ninja -C ./build
if (!$?) { Exit $LASTEXITCODE }
./build/gopp2.exe