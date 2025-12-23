# Common sources for the library
lib7zip_sources = \
	7ZipArchive.cpp \
	7ZipArchiveItem.cpp \
	7ZipArchiveOpenCallback.cpp \
	7ZipArchiveOpenCallback.h \
	7ZipCodecInfo.cpp \
	7ZipCodecInfo.h \
	7ZipCompressCodecsInfo.cpp \
	7ZipCompressCodecsInfo.h \
	7ZipDllHandler.cpp \
	7ZipDllHandler.h \
	7ZipFormatInfo.cpp \
	7ZipFormatInfo.h \
	7ZipFunctions.h \
	7ZipInStreamWrapper.cpp \
	7ZipInStreamWrapper.h \
	7ZipObjectPtrArray_stub.cpp \
	7ZipObjectPtrArray.cpp \
	7ZipOpenArchive.cpp \
	7zipLibrary.cpp \
	HelperFuncs.cpp \
	HelperFuncs.h \
	lib7zip.h \
	compat.h \
	OSFunctions_OS2.cpp \
	OSFunctions_OS2.h \
	OSFunctions_UnixLike.cpp \
	OSFunctions_UnixLike.h \
	OSFunctions_Win32.cpp \
	OSFunctions_Win32.h \
	OSFunctions.h \
	$(top_srcdir)/$(SEVENZIP_SOURCE_DIR)/CPP/Common/MyString.cpp \
	$(top_srcdir)/$(SEVENZIP_SOURCE_DIR)/CPP/Common/MyWindows.cpp \
	$(top_srcdir)/$(SEVENZIP_SOURCE_DIR)/CPP/Windows/PropVariant.cpp

# Build library with libtool (produces static by default, shared when enabled)
lib_LTLIBRARIES = lib7zip.la
lib7zip_la_SOURCES = $(lib7zip_sources)
lib7zip_la_LDFLAGS = -version-info 4:0:0 $(DL_LIBS)
lib7zip_la_LIBADD = $(WIN_OLE_LIBS)

AM_CPPFLAGS = \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/$(SEVENZIP_SOURCE_DIR) \
	-I$(top_srcdir)/$(SEVENZIP_SOURCE_DIR)/CPP \
	-I$(top_srcdir)/$(SEVENZIP_SOURCE_DIR)/CPP/Common \
	-I$(top_srcdir)/$(SEVENZIP_SOURCE_DIR)/CPP/Windows \
	-I$(top_srcdir)/$(SEVENZIP_SOURCE_DIR)/C \
	-I$(top_srcdir)/includes

# Compiler flags
AM_CXXFLAGS = \
	-fPIC \
	-Wall \
	-Wextra \
	-Werror \
	-Wno-unused-parameter \
	-Wno-cast-function-type

if MINGW
AM_CPPFLAGS += -DUNICODE -D_UNICODE
endif

# Install headers
include_HEADERS = lib7zip.h compat.h

# Clean up generated files
CLEANFILES = *.o *.lo
