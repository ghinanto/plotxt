#!/usr/bin/env bash

gcc --version

VERSION=${1:-latest}

# TODO get the latest version following https://github.com/libssh2/libssh2/releases/latest
#   hardcode it for the moment
if [ ${VERSION} = "latest" ]; then
    VERSION="1.9.0"
fi

TMPDIR=$(mktemp -d)

curl -sL https://github.com/libssh2/libssh2/releases/download/libssh2-${VERSION}/libssh2-${VERSION}.tar.gz | tar xz --directory=${TMPDIR}

SOURCE_DIR=${TMPDIR}/libssh2-${VERSION}
BUILD_DIR=${SOURCE_DIR}/build

cmake -S ${SOURCE_DIR} -B ${BUILD_DIR} -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DBUILD_EXAMPLES=OFF -DBUILD_TESTING=OFF
cmake --build ${BUILD_DIR} --target install

rm -rf ${SOURCE_DIR}
rmdir ${TMPDIR}
