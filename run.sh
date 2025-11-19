#! /usr/bin/env bash

cmake -S$PWD -Bbuild-artifacts -DCMAKE_CXX_COMPILER=/usr/local/bin/g++ -DCMAKE_RUNTIME_OUTPUT_DIRECTORY:PATH=$PWD --preset=user --log-level=NOTICE
cmake --build build-artifacts -t demoscene
$PWD/demoscene
