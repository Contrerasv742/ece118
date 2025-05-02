#!/bin/bash

# Helper Variables
USB="/run/media/panda/SAMSUNG"

# Ensure Directory Exists
sudo mkdir -p $USB/ece118

# Copy Necessary Files
cp -rv src include $USB/ece118/
