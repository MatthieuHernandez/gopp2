param (
    [ValidateSet("Debug", "Release")]
    [string]$BuildType = "Debug"
)
$BuildDir = "./build/$BuildType"

cppfront -cwd ./generate ../src/color.h2 |
cppfront -cwd ./generate ../src/stone.h2 -import-std |
cppfront -cwd ./generate ../src/move.h2 -import-std |
cppfront -cwd ./generate ../src/goban.h2  -import-std |
cppfront -cwd ./generate ../src/engine.h2 -import-std |
cppfront -cwd ./generate ../src/io.h2 -import-std |
cppfront -cwd ./generate ../src/player.h2 -import-std |
cppfront -cwd ./generate ../src/human.h2 -import-std |
cppfront -cwd ./generate ../src/random.h2 -import-std |
cppfront -cwd ./generate ../src/ai.h2 -import-std |
cppfront -cwd ./generate ../src/game.h2 -import-std |
cppfront -cwd ./generate ../src/main.cpp2 -import-std
if (!$?) { Exit $LASTEXITCODE }
cmake -S . -B $BuildDir -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE="$BuildType"
if (!$?) { Exit $LASTEXITCODE }
ninja -C $BuildDir
if (!$?) { Exit $LASTEXITCODE }
$ExecutablePath = "$BuildDir/gopp2.exe"
& $ExecutablePath