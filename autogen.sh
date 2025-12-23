#!/bin/sh
# Run this to generate all the initial makefiles, etc.

set -e

# Check for required tools
missing_tools=""
for tool in autoreconf automake libtool; do
    if ! command -v "$tool" >/dev/null 2>&1; then
        missing_tools="$missing_tools $tool"
    fi
done

if [ -n "$missing_tools" ]; then
    echo "Error: Missing required tools:$missing_tools"
    echo "Please install autotools (autoreconf, automake, libtool)"
    exit 1
fi

# Check if 7zip submodule is initialized
if [ ! -f "third_party/7zip/CPP/7zip/Archive/IArchive.h" ]; then
    echo "Error: 7zip submodule not initialized."
    echo "Please run: git submodule update --init --recursive"
    exit 1
fi

echo "Running autoreconf..."
autoreconf --force --install --verbose

echo ""
echo "lib7zip has been successfully bootstrapped."
echo "You can now run:"
echo "  ./configure"
echo "  make"
echo "  make install"
