#!/usr/bin/env bash

VERSION=${1:-latest}

# TODO get the latest version following https://github.com/zeromq/cppzmq/releases/latest
#   hardcode it for the moment
if [ ${VERSION} = "latest" ]; then
    VERSION="4.7.1"
fi

TMPDIR=$(mktemp -d)

curl -sL https://github.com/zeromq/cppzmq/archive/refs/tags/v${VERSION}.tar.gz | tar xz --directory=${TMPDIR}

SOURCE_DIR=${TMPDIR}/cppzmq-${VERSION}
BUILD_DIR=${SOURCE_DIR}/build

cmake -S ${SOURCE_DIR} -B ${BUILD_DIR} -DCMAKE_BUILD_TYPE=Release -DCPPZMQ_BUILD_TESTS=OFF
cmake --build ${BUILD_DIR} --target install

rm -rf ${SOURCE_DIR}
rmdir ${TMPDIR}
