#!/bin/sh

# make entr watch for changes in the current directory and subdirectories

find . -type f | entr -c sh -c 'make sofle:odon-mac && cp sofle_rev1_odon.hex ~/keyboard/keyboard.hex'
