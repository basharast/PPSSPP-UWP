// UWP STORAGE MANAGER
// Copyright (c) 2023 Bashar Astifan.
// Email: bashar@astifan.online
// Telegram: @basharastifan
// GitHub: https://github.com/basharast/UWP2Win32

// Functions:
// GetWorkingFolder()
// SetWorkingFolder(std::string location)
// GetInstallationFolder()
// GetLocalFolder()
// GetTempFolder()
// GetPicturesFolder()
// GetVideosFolder()
// GetDocumentsFolder()
// GetMusicFolder()
// GetPreviewPath(std::string path)
//
// CreateFileUWP(std::string path, int accessMode, int shareMode, int openMode)
// CreateFileUWP(std::wstring path, int accessMode, int shareMode, int openMode)
// GetFileStream(std::string path, const char* mode)
// IsValidUWP(std::string path)
// IsExistsUWP(std::string path)
// IsDirectoryUWP(std::string path)
// 
// GetFolderContents(std::string path, T& files)
// GetFolderContents(std::wstring path, T& files)
// GetFileInfoUWP(std::string path, T& info)
//
// GetSizeUWP(std::string path)
// DeleteUWP(std::string path)
// CreateDirectoryUWP(std::string path, bool replaceExisting)
// RenameUWP(std::string path, std::string name)
// CopyUWP(std::string path, std::string name)
// MoveUWP(std::string path, std::string name)
//
// OpenFile(std::string path)
// OpenFolder(std::string path)
// IsFirstStart()
//
// GetLogFile()
// SaveLogs()
// CleanupLogs()

#pragma once 
 
#if defined(_M_ARM) || defined(BUILD14393)
#include <list>
#include <ctime>

#include "StoragePath.h"
#include "StorageInfo.h"
#include "StorageAccess.h"
#include "StoragePickers.h"

// Locations
std::string GetWorkingFolder(); // Where main data is, default is app data
void SetWorkingFolder(std::string location); // Change working location
std::string GetInstallationFolder();
std::string GetLocalFolder();
std::string GetTempFolder();
std::string GetTempFile(std::string name);
std::string GetPicturesFolder(); // Requires 'picturesLibrary' capability
std::string GetVideosFolder(); // Requires 'videosLibrary' capability
std::string GetDocumentsFolder(); // Requires 'documentsLibrary' capability
std::string GetMusicFolder(); // Requires 'musicLibrary' capability
std::string GetPreviewPath(std::string path);
bool isLocalState(std::string path);

// Management
HANDLE CreateFileUWP(std::string path, int accessMode = GENERIC_READ, int shareMode = FILE_SHARE_READ, int openMode = OPEN_EXISTING);
HANDLE CreateFileUWP(std::wstring path, int accessMode = GENERIC_READ, int shareMode = FILE_SHARE_READ, int openMode = OPEN_EXISTING);
FILE* GetFileStream(std::string path, const char* mode);
// `GetFileStreamFromApp` Will use Windows UWP API, use it instead of fopen..etc
FILE* GetFileStreamFromApp(std::string path, const char* mode); 
bool IsValidUWP(std::string path, bool allowForAppData = false);
bool IsExistsUWP(std::string path);
bool IsDirectoryUWP(std::string path);

std::list<ItemInfoUWP> GetFolderContents(std::string path, bool deepScan = false);
std::list<ItemInfoUWP> GetFolderContents(std::wstring path, bool deepScan = false);
ItemInfoUWP GetItemInfoUWP(std::string path);

// Basics
int64_t GetSizeUWP(std::string path);
bool DeleteUWP(std::string path);
bool CreateDirectoryUWP(std::string path, bool replaceExisting = true);
bool RenameUWP(std::string path, std::string name);
// Add file name to destination path
bool CopyUWP(std::string path, std::string dest);
// Add file name to destination path
bool MoveUWP(std::string path, std::string dest);

// Helpers
bool OpenFile(std::string path);
bool OpenFolder(std::string path);
bool IsFirstStart();
std::string ResolvePathUWP(std::string path);
bool IsContainsAccessibleItems(std::string path);
bool IsRootForAccessibleItems(std::string path);
// 'checkIfContainsFutureAccessItems' for listing purposes not real access, 'driveName' like C:
bool CheckDriveAccess(std::string driveName, bool checkIfContainsFutureAccessItems);
bool GetDriveFreeSpace(PathUWP path, int64_t& space);

// Log helpers
std::string GetLogFile();
bool SaveLogs(); // With picker
void CleanupLogs();
#else


#include <list>
#include <set>

#include "Common/File/DirListing.h"

#include "StorageAccess.h"
#include "StoragePickers.h"

// Locations
std::string GetWorkingFolder(); // Where main data is, default is app data
std::string GetInstallationFolder();
std::string GetLocalFolder();
std::string GetTempFolder();
std::string GetTempFile(std::string name);
std::string GetPicturesFolder(); // Requires 'picturesLibrary' capability
std::string GetVideosFolder(); // Requires 'videosLibrary' capability
std::string GetDocumentsFolder(); // Requires 'documentsLibrary' capability
std::string GetMusicFolder(); // Requires 'musicLibrary' capability
std::string GetPreviewPath(std::string path);
bool isLocalState(std::string path);

// Management
// `GetFileStreamFromApp` Will use Windows UWP API, use it instead of fopen..etc
FILE* GetFileStreamFromApp(std::string path, const char* mode);

// 'driveName' like C:
bool CheckDriveAccess(std::string driveName);
bool GetFakeFolders(Path path, std::vector<File::FileInfo>* files, const char* filter, std::set<std::string> filters);
bool IsRootForAccessibleItems(std::string path);

// Helpers
bool OpenFile(std::string path);
bool OpenFolder(std::string path);
bool IsFirstStart();
std::string ResolvePathUWP(std::string path);
bool GetDriveFreeSpace(Path path, int64_t& space);

// Log helpers
std::string GetLogFile();

#endif
