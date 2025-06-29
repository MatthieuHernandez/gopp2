param (
    [ValidateSet("Debug", "Release")]
    [string]$BuildType = "Debug",
    [string]$Run = "run",
    [string]$ProgArg = ""
)
$BuildDir = ".\build\$BuildType"
$DebugArg = ""

if ($BuildType -eq "Debug") { $DebugArg = "-d" }

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
if ($BuildType -eq "Debug") {
    New-Item -Force -Path "$BuildDir" -Name "src" -ItemType "directory"
    New-Item -Force -Path "$BuildDir\src" -Name "cpp2" -ItemType "directory"
    Move-Item -Force -Path ".\src\cpp2\*.h2-*" -Destination "$BuildDir\src\cpp2"
    Move-Item -Force -Path ".\src\cpp2\*.cpp2-*" -Destination "$BuildDir\src\cpp2"
}

if (!$?) { Exit $LASTEXITCODE }

cmake -S . -B $BuildDir -G Ninja `
    -DCMAKE_PREFIX_PATH="C:\Programming\Qt\6.8.2\msvc2022_64\lib\cmake\Qt6" `
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON `
    -DCMAKE_CXX_COMPILER=clang++ `
    -DCMAKE_C_COMPILER=clang `
    -DCMAKE_BUILD_TYPE="$BuildType"

if (!$?) { Exit $LASTEXITCODE }

ninja -C $BuildDir

if (!$?) { Exit $LASTEXITCODE }

if (!(Test-Path "$BuildDir\bin\images")) {
    New-Item -Path "$BuildDir\bin" -Name "images" -ItemType "directory"
}
Copy-Item -Force -Recurse "resources\images\*" -Destination "$BuildDir\bin\images"

if (!(Test-Path "$BuildDir\bin\snn_models")) {
    cmd /c mklink /d "$BuildDir\bin\snn_models" "..\..\..\snn_models"
}

if (!(Test-Path "$BuildDir\bin\platforms")) {
    New-Item -Path "$BuildDir\bin" -Name "platforms" -ItemType "directory"
}
if ($BuildType -eq "Debug") {
    Copy-Item -Force "C:\Programming\Qt\6.8.2\msvc2022_64\plugins\platforms\qwindowsd.dll" -Destination "$BuildDir\bin\platforms"
    Copy-Item -Force "C:\Programming\Qt\6.8.2\msvc2022_64\bin\Qt6Cored.dll" -Destination "$BuildDir\bin"
    Copy-Item -Force "C:\Programming\Qt\6.8.2\msvc2022_64\bin\Qt6Guid.dll" -Destination "$BuildDir\bin"
    Copy-Item -Force "C:\Programming\Qt\6.8.2\msvc2022_64\bin\Qt6Widgetsd.dll" -Destination "$BuildDir\bin"
    Copy-Item -Force "C:\Programming\Qt\6.8.2\msvc2022_64\bin\Qt6Widgetsd.dll" -Destination "$BuildDir\bin"
    Copy-Item -Force "C:\Programming\Qt\6.8.2\msvc2022_64\bin\Qt6Concurrentd.dll" -Destination "$BuildDir\bin"
}
else {
    Copy-Item -Force "C:\Programming\Qt\6.8.2\msvc2022_64\plugins\platforms\qwindows.dll" -Destination "$BuildDir\bin\platforms"
    Copy-Item -Force "C:\Programming\Qt\6.8.2\msvc2022_64\bin\Qt6Core.dll" -Destination "$BuildDir\bin"
    Copy-Item -Force "C:\Programming\Qt\6.8.2\msvc2022_64\bin\Qt6Gui.dll" -Destination "$BuildDir\bin"
    Copy-Item -Force "C:\Programming\Qt\6.8.2\msvc2022_64\bin\Qt6Widgets.dll" -Destination "$BuildDir\bin"
    Copy-Item -Force "C:\Programming\Qt\6.8.2\msvc2022_64\bin\Qt6Widgets.dll" -Destination "$BuildDir\bin"
    Copy-Item -Force "C:\Programming\Qt\6.8.2\msvc2022_64\bin\Qt6Concurrent.dll" -Destination "$BuildDir\bin"
}
Move-Item -Force "$BuildDir\gopp2.exe" -Destination "$BuildDir\bin"

if (!$?) { Exit $LASTEXITCODE }

if ($Run -eq "norun") { Exit 0 }

Push-Location "$BuildDir\bin\"
& .\gopp2.exe $ProgArg
Pop-Location
