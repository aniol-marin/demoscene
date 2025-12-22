#! /usr/bin/env bash

echo "preparing demo..."
cmake -S$PWD -Bbuild-artifacts -DCMAKE_RUNTIME_OUTPUT_DIRECTORY:PATH=$PWD --preset=user --log-level=NOTICE

echo "building demo..."
cmake --build build-artifacts -t demoscene

echo "running demo..."
$PWD/demoscene
