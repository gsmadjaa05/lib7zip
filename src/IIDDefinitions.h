// IIDDefinitions.h
// COM Interface ID definitions for 7-Zip interfaces

#ifndef LIB7ZIP_IID_DEFINITIONS_H
#define LIB7ZIP_IID_DEFINITIONS_H

#include <guiddef.h>

// 7-Zip GUID constants from IDecl.h
#define k_7zip_GUID_Data1 0x23170F69
#define k_7zip_GUID_Data2 0x40C1
#define k_7zip_GUID_Data3_Common 0x278A

// Stream interfaces (groupId=3)
DEFINE_GUID(IID_IInStream, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0, 0, 0, 3, 0, 3, 0, 0);
DEFINE_GUID(IID_IOutStream, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0, 0, 0, 3, 0, 4, 0, 0);
DEFINE_GUID(IID_IStreamGetSize, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0, 0, 0, 3, 0, 6, 0, 0);

// Archive interfaces (groupId=6)
DEFINE_GUID(IID_IInArchive, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0, 0, 0, 6, 0, 0, 0, 0);
DEFINE_GUID(IID_IInArchiveGetStream, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0, 0, 0, 6, 0, 1, 0, 0);
DEFINE_GUID(IID_IArchiveOpenVolumeCallback, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0, 0, 0, 6, 0, 2, 0, 0);
DEFINE_GUID(IID_IArchiveOpenSetSubArchiveName, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0, 0, 0, 6, 0, 3, 0, 0);

// Password interface (groupId=5, subId=16 from IPassword.h)
DEFINE_GUID(IID_ICryptoGetTextPassword, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0, 0, 0, 5, 0, 16, 0, 0);

// Codec interfaces
DEFINE_GUID(IID_ICompressCodecsInfo, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0, 0, 0, 4, 0, 3, 0, 0);
DEFINE_GUID(IID_ISetCompressCodecsInfo, k_7zip_GUID_Data1, k_7zip_GUID_Data2, k_7zip_GUID_Data3_Common, 0, 0, 0, 4, 0, 4, 0, 0);

#endif // LIB7ZIP_IID_DEFINITIONS_H
