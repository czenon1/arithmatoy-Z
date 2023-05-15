LOCAL_PATH=.local
VCPKG_PATH=$LOCAL_PATH/vcpkg
CMAKE_OUT=$LOCAL_PATH/cmake
CMAKE_BUILD=$CMAKE_OUT/build
CMAKE_DIST=$CMAKE_OUT/dist

setup() {
  bash vcpkg_install.sh
  cmake_prepare
}

clean() {
  cmake_clean
  vcpkg_clean
}

cmake_clean() {
  rm -rf $CMAKE_OUT
}

cmake_prepare() {
  # Note: $@ forwards argument so you can add additional arguments
  # e.g: cmake_prepare -DCMAKE_BUILD_TYPE=Release to configure the build solution in release mode with gcc
  cmake -DCMAKE_TOOLCHAIN_FILE=$VCPKG_PATH/scripts/buildsystems/vcpkg.cmake \
    -S . \
    -B $CMAKE_BUILD \
    -DCMAKE_INSTALL_PREFIX=$CMAKE_DIST \
    -DBUILD_TESTING=1 \
    "$@"
}

cmake_prepare_release() {
  cmake_prepare -DCMAKE_BUILD_TYPE=Release "$@"
}

cmake_prepare_debug() {
  cmake_prepare -DCMAKE_BUILD_TYPE=Debug "$@"
}

cmake_build() {
  # Note: $@ forwards argument so you can add additional arguments
  # e.g: cmake_build --config release to build in release mode with Visual Studio Compiler
  cmake --build $CMAKE_BUILD -j "$@"
}

cmake_build_release() {
  cmake_build --config Release "$@"
}

cmake_build_debug() {
  cmake_build --config Debug "$@"
}

cmake_install() {
  # Note: $@ forwards argument so you can add additional arguments
  # e.g: cmake_install --config release to build in release mode, then install, with Visual Studio Compiler
  cmake --build $CMAKE_BUILD -j --target install "$@"
}

cmake_install_release() {
  cmake_install --config Release
}

cmake_install_debug() {
  cmake_install --config Debug
}

ctest_release() {
  cmake_build_release
  ctest --test-dir $CMAKE_BUILD -C Release -V
}

ctest_debug() {
  cmake_build_debug
  ctest --test-dir $CMAKE_BUILD -C Debug -V
}

vcpkg_export_dependencies() {
  $VCPKG_PATH/vcpkg export --x-all-installed --zip --output=precompiled-third-party
}

vcpkg_clean() {
  rm -rf $VCPKG_PATH
}
