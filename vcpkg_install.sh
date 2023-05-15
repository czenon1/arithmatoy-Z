#!/bin/bash

VCPKG_VERSION=2022.03.10 # Change vcpkg version here
VCPKG_PATH=.local/vcpkg

set -e

if [ ! -e $VCPKG_PATH/.git ]; then
  git clone https://github.com/microsoft/vcpkg $VCPKG_PATH
  $VCPKG_PATH/bootstrap-vcpkg.sh -useSystemBinaries
fi

pushd $VCPKG_PATH

git checkout $VCPKG_VERSION
./vcpkg upgrade --no-dry-run

# Add dependencies here
./vcpkg install cmocka

popd
