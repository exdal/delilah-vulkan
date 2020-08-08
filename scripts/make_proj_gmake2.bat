@echo off
pushd %~dp0\..\
call premake5.exe gmake2
popd
PAUSE