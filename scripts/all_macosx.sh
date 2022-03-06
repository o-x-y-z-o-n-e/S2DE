#!/bin/bash

[ -d "scripts" ] && cd scripts

./clean_macosx.sh
./gen_macosx.sh
./build_macosx.sh
./run_macosx.sh