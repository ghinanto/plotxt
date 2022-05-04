#!/usr/bin/env bash

VERSION=${1:-latest}

# TODO get the latest version following https://github.com/Kitware/CMake/releases/latest
#   hardcode it for the moment
if [ ${VERSION} = "latest" ]; then
    VERSION="3.20.0"
fi

curl -sL https://github.com/Kitware/CMake/releases/download/v${VERSION}/cmake-${VERSION}-linux-x86_64.tar.gz | tar xz --directory=/usr/local --strip-components=1
