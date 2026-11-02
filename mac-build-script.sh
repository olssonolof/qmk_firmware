#!/bin/sh

# make entr watch for changes in the current directory and subdirectories

#find . -type f | entr -c sh -c 'make sofle:odon-mac && cp sofle_rev1_odon.hex ~/keyboard/keyboard.hex'
#find . -type f | entr -c sh -c 'make sofle:odon-mac && cp ./.build/sofle_rev1_odon-mac.hex ~/keyboard/keyboard.hex'
make sofle:odon-mac && cp sofle_rev1_odon-mac.hex ~/keyboard/keyboard.hex
