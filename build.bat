@echo off

if not exist %~dp0build goto no_build

cmake --build %~dp0build --config Debug
goto :eof

:no_build
echo no build directory
