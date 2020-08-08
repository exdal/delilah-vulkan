@echo off
pushd %~dp0\..\
call premake5.exe xcode4
popd
PAUSE