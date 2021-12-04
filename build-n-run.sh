#!/usr/bin/env bash

make clean && make -j $(nproc --all) && time ./chess
