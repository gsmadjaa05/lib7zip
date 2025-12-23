# Automake file for lib7zip
SUBDIRS = src

if BUILD_TESTS
SUBDIRS += test
endif

# Install pkg-config file
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = lib7zip.pc

# Data files to distribute
EXTRA_DIST = \
	cmake/toolchains/mingw32.cmake \
	cmake/toolchains/mingw64.cmake \
	third_party/7zip/README.md \
	AUTHORS \
	COPYING \
	README.md

# Clean up generated files
CLEANFILES = *.o *.lo

# Remove build artifacts
MAINTAINERCLEANFILES = \
	Makefile.in \
	aclocal.m4 \
	configure \
	config.h.in \
	config.h.in~ \
	stamp-h1 \
	lib7zip-*.tar.gz

# Documentation
dist_doc_DATA = README.md

.PHONY: check-valgrind
check-valgrind:
	@echo "Running tests under valgrind..."
	@for test in $(noinst_PROGRAMS); do \
		if [ -x "$$test" ]; then \
			echo "Testing $$test..."; \
			valgrind --leak-check=full --error-exitcode=1 ./$$test || exit 1; \
		fi; \
	done
