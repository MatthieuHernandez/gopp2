param (
    [ValidateSet("Debug", "Release")]
    [string]$BuildType = "Debug",
    [string]$Run = "run"
)
$BuildDir = "./build/$BuildType"
$DebugArg = ""
if ($BuildType -eq "Debug") { $DebugArg = "-d" }

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
cppfront -cwd ./generate ../src/game.h2 -import-std $DebugArg |
cppfront -cwd ./generate ../src/main.cpp2 -import-std $DebugArg

# Move files used for debugging to the build folder.
if ($BuildType -eq "Debug") {
    New-Item -Force -Path "$BuildDir/" -Name "src" -ItemType "directory"
    Copy-Item -Force -Path "./src/*.h2" -Destination "$BuildDir/src/"
    Copy-Item -Force -Path "./src/*.cpp2" -Destination "$BuildDir/src/"
    Move-Item -Force -Path "./src/*.h2-*" -Destination "$BuildDir/src/"
    Move-Item -Force -Path "./src/*.cpp2-*" -Destination "$BuildDir/src/"
}

if (!$?) { Exit $LASTEXITCODE }
cmake -S . -B $BuildDir -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE="$BuildType"
if (!$?) { Exit $LASTEXITCODE }
ninja -C $BuildDir
if (!$?) { Exit $LASTEXITCODE }
if ($Run -eq "norun") { Exit 0 }
$ExecutablePath = "$BuildDir/gopp2.exe"
& $ExecutablePath