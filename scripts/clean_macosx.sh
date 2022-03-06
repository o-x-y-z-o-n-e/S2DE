#!/bin/bash

[ ! -d "scripts" ] && cd ..

[ -d "bin" ] && rm -r "bin"
[ -d "tmp" ] && rm -r "tmp"

[ -f "Makefile" ] && rm "Makefile"
[ -f "S2DE/Makefile" ] && rm "S2DE/Makefile"
[ -f "Example/Makefile" ] && rm "Example/Makefile"