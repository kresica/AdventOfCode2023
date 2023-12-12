#!/bin/bash

[ ! -d day$1 ] && {
    mkdir day$1
    mkdir day$1/src
    mkdir day$1/hdr
    mkdir day$1/data \
    && echo "Successfully created Day $1"
} || echo "Day $1 not created!"
