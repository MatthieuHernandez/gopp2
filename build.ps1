
cppfront -cwd ./generate ../src/main.cpp2
if (!$?) { Exit $LASTEXITCODE }
cmake -S . -B ./build -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
if (!$?) { Exit $LASTEXITCODE }
ninja -C ./build
if (!$?) { Exit $LASTEXITCODE }
./build/gopp2.exe