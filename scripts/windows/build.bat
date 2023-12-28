@echo off



pushd ..

call "Scripts/bin/premake5.exe" vs2022

popd

pause
