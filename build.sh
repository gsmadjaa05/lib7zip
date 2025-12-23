#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")" && pwd)"
JOBS="${JOBS:-$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)}"

case "${ENABLE_TESTS:-0}" in
  1|true|yes|on|ENABLE)
    CONFIGURE_TEST_FLAG="--enable-tests"
    ;;
  *)
    CONFIGURE_TEST_FLAG="--disable-tests"
    ;;
esac

build_target() {
  local name="$1"
  local host="$2"
  local prefix="$3"
  local build_dir="${ROOT}/build_${name}_autotools"

  echo "==> Building for ${name} (host=${host}, prefix=${prefix})"
  rm -rf "${build_dir}"
  mkdir -p "${build_dir}"
  pushd "${build_dir}" >/dev/null
  "${ROOT}/configure" --host="${host}" --prefix="${prefix}" "${CONFIGURE_TEST_FLAG}"
  make -j"${JOBS}"
  make install
  popd >/dev/null
}

autoreconf -fi

build_target mingw32 i686-w64-mingw32 /mingw32
build_target mingw64 x86_64-w64-mingw32 /mingw64

echo "Build completed. Installed into /mingw32 and /mingw64."

