#!/bin/bash

[ -d "scripts" ] && cd scripts

./gen_macosx.sh
./build_macosx.sh
./run_macosx.sh