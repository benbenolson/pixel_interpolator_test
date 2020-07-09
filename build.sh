#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ${DIR}/deps/cglm
chmod +x autogen.sh
./autogen.sh
./configure --prefix=${DIR}/deps/prefix
make -j5
make install
cd ${DIR}

gcc -lglfw -lGL -lm main.c -I${DIR}/deps/prefix/include -o main
