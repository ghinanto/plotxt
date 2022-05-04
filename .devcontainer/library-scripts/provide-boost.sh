#!/usr/bin/env bash

VERSION=${1:-latest}

if [ ${VERSION} = "latest" ]; then
    VERSION="1.75.0"
fi
VERSION=$(echo ${VERSION} | tr '.' '_')

TMPDIR=$(mktemp -d)

curl -sL https://www.cnaf.infn.it/~giaco/boost_${VERSION}.tar.gz | tar xz --directory=${TMPDIR}

SOURCE_DIR=${TMPDIR}/boost_${VERSION}
cd ${SOURCE_DIR}
./bootstrap.sh --with-libraries=system,log,filesystem,random,program_options,thread,regex,chrono --without-icu
./b2 install

cd -
rm -rf ${SOURCE_DIR}
rmdir ${TMPDIR}
