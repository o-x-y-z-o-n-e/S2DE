@echo off

if not exist cd ..
"vendor/premake/bin/windows-x86_64/premake5" vs2022

PAUSE