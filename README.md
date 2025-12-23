# lib7zip

lib7zip is a C++ wrapper library for accessing 7-Zip archives programmatically. This version is aligned with **7-Zip 25.0** and now builds exclusively with **GNU Autotools** (no alternate build system).

## 🚀 Quick Start (Autotools)

```bash
# From repo root
git submodule update --init --recursive

# Regenerate build system (when building from a fresh checkout)
./autogen.sh   # or: autoreconf -fi

# Configure (examples)
./configure --prefix=/usr/local
# cross for MinGW 64-bit:
# ./configure --host=x86_64-w64-mingw32 --prefix=/mingw64
# enable tests if desired:
# ./configure --enable-tests

# Build & install
make -j4
make install
```

### Convenience cross-build script

`./build.sh` will:
- regen autotools
- build and install for `/mingw32` (host `i686-w64-mingw32`) and `/mingw64` (host `x86_64-w64-mingw32`)
- set `ENABLE_TESTS=1` to include the test programs (off by default)
- set `JOBS=N` to control parallelism

## ✨ Features

- **Modern 7-Zip 25.0 Compatibility**: Updated COM interfaces and API
- **Autotools-only build**: Static library by default; shared when `--enable-shared`
- **Cross-Platform Ready**: Builds on Linux/macOS; cross-compiles to Windows via MinGW
- **Optional Tests**: Build with `--enable-tests` (disabled by default)

## 📋 Requirements

- **7-Zip 25.0 Source**: Git submodule at `third_party/7zip/`
- **Tooling**: autoconf, automake, libtool, pkg-config
- **Compiler**: GCC 8+ or Clang 10+ with C++17 support
- **Windows cross**: MinGW-w64 toolchains (`mingw-w64-{i686,x86_64}-gcc`) and matching binutils
- **System Libraries**: pthread, dl (on Unix-like platforms)

## 🔧 Key Modernizations

This version includes comprehensive updates for 7-Zip 25.0 compatibility:

| Component | Changes Made |
|-----------|--------------|
| **COM Interfaces** | Updated `MY_UNKNOWN_IMP*` → `Z7_COM_UNKNOWN_IMP_*` macros |
| **Data Types** | Fixed `unsigned __int64` → `UInt64` throughout codebase |
| **Method Signatures** | Added proper `throw()` exception specifications |
| **Include Paths** | Updated for new 7-Zip 25.0 directory structure |
| **Build System** | Autotools-only; optional tests gated by `--enable-tests` |

## 📦 Generated Artifacts

- `src/.libs/lib7zip.a` - Static library (default)
- `src/.libs/lib7zip.dll.a` + `src/.libs/lib7zip.dll` - Shared (if `--enable-shared` and supported)

## 💻 Usage Example

```cpp
#include "lib7zip.h"

int main() {
    // Initialize library
    C7ZipLibrary lib;
    if (!lib.Initialize()) return -1;

    // Open archive
    C7ZipArchive* archive = lib.OpenArchive(L"example.7z");
    if (!archive) return -1;

    // List contents
    printf("Archive contains %d items\n", archive->GetItemCount());
    
    // Extract all files
    for (int i = 0; i < archive->GetItemCount(); ++i) {
        archive->ExtractItem(i, L"output_dir/");
    }

    lib.CloseArchive(archive);
    return 0;
}
```

### Compilation

```bash
# Static linking
g++ -std=c++17 app.cpp -I./third_party/7zip -L./src/.libs -l7zip -ldl -lpthread

# Shared linking  
g++ -std=c++17 app.cpp -I./third_party/7zip -L./src/.libs -l7zip -ldl -lpthread
export LD_LIBRARY_PATH=./src/.libs:$LD_LIBRARY_PATH
```

## 🎯 Project Status

| Component | Status | Notes |
|-----------|--------|-------|
| **Core Library** | ✅ **Ready** | Fully functional with 7-Zip 25.0 |
| **Static Library** | ✅ **Ready** | Built via autotools |
| **Shared Library** | ✅ **Ready** | `--enable-shared` when supported by toolchain |
| **COM Interfaces** | ✅ **Ready** | Updated for 7-Zip 25.0 |
| **API Compatibility** | ✅ **Ready** | Backward compatible API maintained |
| **Test Programs** | ⚠️ **Optional** | Build with `--enable-tests` |

## 📚 Documentation

- **[Original Documentation](https://github.com/stonewell/lib7zip)** - Historical reference
- **7-Zip Official**: [7-zip.org](https://www.7-zip.org/) for format specifications

## 🛠️ Development Notes

### Runtime Requirements
- **Linux/Unix**: Requires 7-Zip installation with 7z.so available
- **Windows**: Requires 7z.dll in application directory or PATH
- **macOS**: Requires 7-Zip installation via Homebrew or similar

### Path Configuration
```bash
# Linux: Find 7z.so location
find /usr -name "7z.so" 2>/dev/null
export LD_LIBRARY_PATH=/usr/lib/p7zip:$LD_LIBRARY_PATH

# Windows: Copy 7z.dll to application directory
cp "C:\\Program Files\\7-Zip\\7z.dll" .
```

## 🤝 Contributing

This project has been fully modernized for 7-Zip 25.0. The core library is production-ready and actively maintained. Contributions for test program updates or additional features are welcome.

## 🙏 Acknowledgments

* Many thanks to _Joe_ who provided so many great patches
* Many thanks to _Christoph_ who gave so many great advises and patches
* Many thanks to _Christoph Thielecke_ for providing great patches for OS2 and dynamic library
* This project is made from https://github.com/celyrin/lib7zip
* Thanks to the 7-Zip team for maintaining the excellent compression library

## 🔗 Related Projects

* Python Binding created by Mark: http://github.com/harvimt/pylib7zip

## 📄 License

This project maintains compatibility with 7-Zip's licensing terms. Please refer to the original 7-Zip license documentation for complete usage terms and conditions.

## 📝 Version History

### 4.0.0 (2025) - 7-Zip 25.0 Modernization
- **Major API Update**: Full compatibility with 7-Zip 25.0
- **Build System Overhaul**: Autotools-only; legacy alternate build removed
- **COM Interface Modernization**: Updated all interfaces to current 7-Zip standards
- **Performance Improvements**: Optimized library builds
- **Cross-Platform Ready**: Enhanced Linux, Windows, macOS support

### 3.0.0 (Previous)
- Introduced an alternate build system (now removed)
- Fix bug when do signature detect for dmg files
- Fix bug of memory leaking when deal with sub archive

### 2.0.0 (Previous)
- Library compatibility with p7zip 15.9.0 and 7zip 15.10.0
- Bug fixes in test programs

*For complete historical changelog, see git history or previous README versions.*

---

**Status**: ✅ **Production Ready** - Core library fully functional with 7-Zip 25.0