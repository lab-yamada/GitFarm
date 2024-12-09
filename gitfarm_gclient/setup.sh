#!/bin/bash

OS=$(uname)

if [[ "$OS" == "Darwin" ]]; then
    echo "Running on macOS"
    brew install curl
    echo 'export PATH="/opt/homebrew/opt/curl/bin:$PATH"' >> ~/.zshrc
    source ~/.zshrc
elif [[ "$OS" == "Linux" ]]; then
    echo "Running on Linux"
    apt install curl
    echo 'export PATH="/usr/bin/curl:$PATH"' >> ~/.zshrc
else
    echo "Unknown OS: $OS"
fi
