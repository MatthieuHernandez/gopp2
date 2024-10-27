cppfront -cwd ./generate ../src/color.h2 |
cppfront -cwd ./generate ../src/stone.h2 -import-std |
cppfront -cwd ./generate ../src/move.h2 -import-std |
cppfront -cwd ./generate ../src/goban.h2  -import-std |
cppfront -cwd ./generate ../src/engine.h2 -import-std |
cppfront -cwd ./generate ../src/io.h2 -import-std |
cppfront -cwd ./generate ../src/player.h2 -import-std |
cppfront -cwd ./generate ../src/game.h2 -import-std |
cppfront -cwd ./generate ../src/main.cpp2 -import-std
if (!$?) { Exit $LASTEXITCODE }
cmake -S . -B ./build -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
if (!$?) { Exit $LASTEXITCODE }
ninja -C ./build
if (!$?) { Exit $LASTEXITCODE }
./build/gopp2.exe