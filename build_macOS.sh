#!/bin/bash

"vendor/premake/bin/macosx-ARM64/premake5" gmake2

make

cd Example
"./../bin/debug-macosx-ARM64/Example/Example"