// TestExtractDir.cpp : Extract archive to directory
//

#include "stdafx.h"
#include "lib7zip.h"
#include <iostream>
#include <string>
#include <filesystem>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#define mkdir _mkdir
#define access _access
#define F_OK 0
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

class TestInStream : public C7ZipInStream
{
private:
	FILE * m_pFile;
	std::string m_strFileName;
	wstring m_strFileExt;
	int m_nFileSize;
public:
	TestInStream(std::string fileName) :
		m_strFileName(fileName),
		m_strFileExt(L"7z")
	{

		wprintf(L"fileName.c_str(): %s\n", fileName.c_str());
		m_pFile = fopen(fileName.c_str(), "rb");
		if (m_pFile) {
			fseek(m_pFile, 0, SEEK_END);
			m_nFileSize = ftell(m_pFile);
			fseek(m_pFile, 0, SEEK_SET);

			auto pos = m_strFileName.find_last_of(".");

			if (pos != m_strFileName.npos) {
#ifdef _WIN32
				std::string tmp = m_strFileName.substr(pos + 1);
				int nLen = MultiByteToWideChar(CP_ACP, 0, tmp.c_str(), -1, nullptr, 0);
				LPWSTR lpszW = new WCHAR[nLen];
				MultiByteToWideChar(CP_ACP, 0,
									tmp.c_str(), -1, lpszW, nLen);
				m_strFileExt = lpszW;
				// free the string
				delete[] lpszW;
#else
				m_strFileExt = L"7z";
#endif
			}
			wprintf(L"Ext:%ls\n", m_strFileExt.c_str());
		}
		else {
			wprintf(L"fileName.c_str(): %s cant open\n", fileName.c_str());
		}
	}

	virtual ~TestInStream()
	{
		fclose(m_pFile);
	}

public:
	virtual wstring GetExt() const
	{
		wprintf(L"GetExt:%ls\n", m_strFileExt.c_str());
		return m_strFileExt;
	}

	virtual int Read(void *data, unsigned int size, unsigned int *processedSize)
	{
		if (!m_pFile)
			return 1;

		int count = fread(data, 1, size, m_pFile);
		wprintf(L"Read:%d %d\n", size, count);

		if (count >= 0) {
			if (processedSize != NULL)
				*processedSize = count;

			return 0;
		}

		return 1;
	}

	virtual int Seek(__int64 offset, unsigned int seekOrigin, UInt64 *newPosition)
	{
		if (!m_pFile)
			return 1;

		int result = fseek(m_pFile, (long)offset, seekOrigin);

		if (!result) {
			if (newPosition)
				*newPosition = ftell(m_pFile);

			return 0;
		}

		return result;
	}

	virtual int GetSize(UInt64 * size)
	{
		if (size)
			*size = m_nFileSize;
		return 0;
	}
};

class DirExtractOutStream : public C7ZipOutStream
{
private:
	FILE * m_pFile;
	std::string m_strOutputDir;
	std::string m_strFullPath;
	wstring m_strFileExt;
	int m_nFileSize;
public:
	DirExtractOutStream(std::string outputDir, std::string relativePath) :
		m_strOutputDir(outputDir),
		m_strFileExt(L"")
	{
		// Create full output path
		m_strFullPath = outputDir + "/" + relativePath;

		// Create directory structure if needed
		CreateDirectoriesForFile(m_strFullPath);

		wprintf(L"Extracting to: %s\n", m_strFullPath.c_str());

		m_pFile = fopen(m_strFullPath.c_str(), "wb");
		m_nFileSize = 0;
	}

	virtual ~DirExtractOutStream()
	{
		if (m_pFile)
			fclose(m_pFile);
	}

	void CreateDirectoriesForFile(const std::string& filePath)
	{
		std::filesystem::path p(filePath);
		std::filesystem::path dir = p.parent_path();

		if (!dir.empty() && !std::filesystem::exists(dir)) {
			std::filesystem::create_directories(dir);
			wprintf(L"Created directory: %s\n", dir.string().c_str());
		}
	}

public:
	int GetFileSize() const
	{
		return m_nFileSize;
	}

	std::string GetFullPath() const
	{
		return m_strFullPath;
	}

	virtual int Write(const void *data, unsigned int size, unsigned int *processedSize)
	{
		if (!m_pFile)
			return 1;

		int count = fwrite(data, 1, size, m_pFile);

		if (count >= 0)
		{
			if (processedSize != NULL)
				*processedSize = count;

			m_nFileSize += count;
			return 0;
		}

		return 1;
	}

	virtual int Seek(__int64 offset, unsigned int seekOrigin, UInt64 *newPosition)
	{
		if (!m_pFile)
			return 1;

		int result = fseek(m_pFile, (long)offset, seekOrigin);

		if (!result)
		{
			if (newPosition)
				*newPosition = ftell(m_pFile);

			return 0;
		}

		return result;
	}

	virtual int SetSize(UInt64 size)
	{
		wprintf(L"SetFileSize:%ld\n", size);
		return 0;
	}
};

const wchar_t * index_names[] = {
	L"kpidPackSize", //(Packed Size)
	L"kpidAttrib", //(Attributes)
	L"kpidCTime", //(Created)
	L"kpidATime", //(Accessed)
	L"kpidMTime", //(Modified)
	L"kpidSolid", //(Solid)
	L"kpidEncrypted", //(Encrypted)
	L"kpidUser", //(User)
	L"kpidGroup", //(Group)
	L"kpidComment", //(Comment)
	L"kpidPhySize", //(Physical Size)
	L"kpidHeadersSize", //(Headers Size)
	L"kpidChecksum", //(Checksum)
	L"kpidCharacts", //(Characteristics)
	L"kpidCreatorApp", //(Creator Application)
	L"kpidTotalSize", //(Total Size)
	L"kpidFreeSpace", //(Free Space)
	L"kpidClusterSize", //(Cluster Size)
	L"kpidVolumeName", //(Label)
	L"kpidPath", //(FullPath)
	L"kpidIsDir", //(IsDir)
};

int main(int argc, char * argv[])
{
	if (argc < 3) {
		wprintf(L"Usage: TestExtractDir [archive file] [output directory]\n");
		wprintf(L"Example: TestExtractDir Test7Zip.7z extracted_files\n");
		return 1;
	}

	C7ZipLibrary lib;

	if (!lib.Initialize()) {
		wprintf(L"initialize fail!\n");
		return 1;
	}

	WStringArray exts;

	if (!lib.GetSupportedExts(exts)) {
		wprintf(L"get supported exts fail\n");
		return 1;
	}

	C7ZipArchive * pArchive = NULL;

	std::string archivePath = argv[1];
	std::string outputDir = argv[2];

	// Create output directory if it doesn't exist
	std::filesystem::path outDir(outputDir);
	if (!std::filesystem::exists(outDir)) {
		std::filesystem::create_directories(outDir);
		wprintf(L"Created output directory: %s\n", outputDir.c_str());
	}

	TestInStream stream(archivePath);

	if (lib.OpenArchive(&stream, &pArchive)) {
		unsigned int numItems = 0;

		pArchive->GetItemCount(&numItems);

		wprintf(L"Archive contains %d items\n", numItems);

		for(unsigned int i = 0; i < numItems; i++) {
			C7ZipArchiveItem * pArchiveItem = NULL;

			if (pArchive->GetItemInfo(i, &pArchiveItem)) {
				wstring fullPath = pArchiveItem->GetFullPath();
				bool isDir = pArchiveItem->IsDir();

				wprintf(L"Item %d: %ls (isDir: %d)\n", i, fullPath.c_str(), isDir);

				if (!isDir) {
					// Extract file
					std::string relativePath = std::string(fullPath.begin(), fullPath.end());
					DirExtractOutStream outStream(outputDir, relativePath);

					wprintf(L"Extracting file: %ls\n", fullPath.c_str());

					if (pArchive->Extract(pArchiveItem, &outStream)) {
						wprintf(L"Successfully extracted: %ls (%d bytes)\n",
							   fullPath.c_str(), outStream.GetFileSize());
					} else {
						wprintf(L"Failed to extract: %ls\n", fullPath.c_str());
					}
				} else {
					// Create directory
					std::string dirPath = outputDir + "/" + std::string(fullPath.begin(), fullPath.end());
					std::filesystem::path dir(dirPath);

					if (!std::filesystem::exists(dir)) {
						std::filesystem::create_directories(dir);
						wprintf(L"Created directory: %s\n", dirPath.c_str());
					}
				}
			}
		}
	}
	else {
		wprintf(L"open archive %s fail\n", archivePath.c_str());
	}

	if (pArchive != NULL)
		delete pArchive;

	wprintf(L"Extraction completed!\n");
	return 0;
}
