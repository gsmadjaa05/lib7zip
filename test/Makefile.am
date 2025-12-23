AM_CPPFLAGS = \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/$(SEVENZIP_SOURCE_DIR) \
	-I$(top_srcdir)/$(SEVENZIP_SOURCE_DIR)/CPP \
	-I$(top_srcdir)/$(SEVENZIP_SOURCE_DIR)/CPP/Common \
	-I$(top_srcdir)/$(SEVENZIP_SOURCE_DIR)/CPP/Windows \
	-I$(top_srcdir)/$(SEVENZIP_SOURCE_DIR)/C \
	-I$(top_srcdir)/includes

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

if BUILD_TESTS
noinst_PROGRAMS =

# Common sources used by all test programs
common_sources = \
	stdafx.cpp \
	stdafx.h

# List of test programs to build
test_programs = \
	Test7Zip \
	Test7Zip2 \
	Test7ZipCryptFileName \
	Test7ZipDmg \
	Test7ZipMulti \
	Test7ZipRar5 \
	Test7ZipSignature \
	test_archive \
	TestExtractDir \
	TestExtractDirPassword

# Add each test program
Test7Zip_SOURCES = Test7Zip.cpp $(common_sources)
Test7Zip_LDADD = $(top_builddir)/src/lib7zip.la $(DL_LIBS)

Test7Zip2_SOURCES = Test7Zip2.cpp $(common_sources)
Test7Zip2_LDADD = $(top_builddir)/src/lib7zip.la $(DL_LIBS)

Test7ZipCryptFileName_SOURCES = Test7ZipCryptFileName.cpp $(common_sources)
Test7ZipCryptFileName_LDADD = $(top_builddir)/src/lib7zip.la $(DL_LIBS)

Test7ZipDmg_SOURCES = Test7ZipDmg.cpp $(common_sources)
Test7ZipDmg_LDADD = $(top_builddir)/src/lib7zip.la $(DL_LIBS)

Test7ZipMulti_SOURCES = Test7ZipMulti.cpp $(common_sources)
Test7ZipMulti_LDADD = $(top_builddir)/src/lib7zip.la $(DL_LIBS)

Test7ZipRar5_SOURCES = Test7ZipRar5.cpp $(common_sources)
Test7ZipRar5_LDADD = $(top_builddir)/src/lib7zip.la $(DL_LIBS)

Test7ZipSignature_SOURCES = Test7ZipSignature.cpp $(common_sources)
Test7ZipSignature_LDADD = $(top_builddir)/src/lib7zip.la $(DL_LIBS)

test_archive_SOURCES = test_archive.cpp $(common_sources)
test_archive_LDADD = $(top_builddir)/src/lib7zip.la $(DL_LIBS)

TestExtractDir_SOURCES = TestExtractDir.cpp $(common_sources)
TestExtractDir_LDADD = $(top_builddir)/src/lib7zip.la $(DL_LIBS)

TestExtractDirPassword_SOURCES = TestExtractDirPassword.cpp $(common_sources)
TestExtractDirPassword_LDADD = $(top_builddir)/src/lib7zip.la $(DL_LIBS)

# Add all test programs to noinst_PROGRAMS
noinst_PROGRAMS += $(test_programs)
endif

# Clean up generated files
CLEANFILES = *.o
