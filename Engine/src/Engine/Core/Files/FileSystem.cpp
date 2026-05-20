#if defined(_WIN32) || defined(_WIN64) // Windows
#define WINDOWS 1
#endif

// I've noticed I've made my life much harder by not using c++17 but oh well
// ig this gives me some practice
#include "FileSystem.h"
#include "config.h"
#include "Logging/Log.h"
#include <codecvt>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h> // POSIX header but is included with basic functionality on Windows :)
#include <sys/types.h>

#if WINDOWS
#include <ShlObj_core.h>
#include <windows.h>
#define PATH_MAX MAX_PATH
#define SEPARATOR '\\'
#define SEPARATOR_STR "\\"
#if UNICODE
#include <codecvt>
#define buffer_t wchar_t
#define string_t std::wstring
#define FROM_STRING(string) std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(string)
#define TO_STRING(wstring) std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wstring)
#else
#define buffer_t char
#define string_t STRING
#define FROM_STRING(string) STRING(string)
#define TO_STRING(string) string
#endif
#else // Linux, MacOS, etc.
#include <limits.h>
#include <unistd.h>
#define SEPARATOR '/'
#define SEPARATOR_STR "/"
#define buffer_t char
#define string_t STRING
#define FROM_STRING(string) STRING(string)
#define TO_STRING(string) string
#endif

static bool s_bInitialised = false;

static STRING s_ExecutablePath;
static STRING s_PersistentDataPath;
static STRING s_TemporaryDataPath;

bool FileSystem::IsInitialized() { return s_bInitialised; }

static void FindExecutablePath()
{
	buffer_t pathBuffer[PATH_MAX];
#if WINDOWS
	GetModuleFileName(nullptr, pathBuffer, PATH_MAX);
#else
	ssize_t len = readlink("/proc/self/exe", pathBuffer, sizeof(pathBuffer) - 1);
	if (len != -1) pathBuffer[len] = '\0';
#endif
	s_ExecutablePath = FileSystem::GetDirectory(TO_STRING(string_t(pathBuffer)));
}

static void FindPersistentDataPath()
{
	char pathBuffer[PATH_MAX];
#if WINDOWS
	PWSTR path = nullptr;
	HRESULT result = SHGetKnownFolderPath(FOLDERID_LocalAppDataLow, 0, nullptr, &path);
	if (SUCCEEDED(result))
	{
		std::wcstombs(pathBuffer, path, PATH_MAX);
		CoTaskMemFree(path);
	}
	if (strlen(pathBuffer) == 0) // Failed to get LocalLow
	{
		CSTRING userPath = std::getenv("USERPROFILE");
		if (strlen(userPath) > 0)
		{
			FileSystem::Combine(userPath, "AppData", pathBuffer);
			FileSystem::Combine(pathBuffer, "LocalLow", pathBuffer);
		}
	}
	if (strlen(pathBuffer) == 0) // Still failed to find
	{
		std::strcpy(pathBuffer, "C:");
		FileSystem::Combine(pathBuffer, "Users", pathBuffer);
		FileSystem::Combine(pathBuffer, "Default", pathBuffer);
		FileSystem::Combine(pathBuffer, "AppData", pathBuffer);
		FileSystem::Combine(pathBuffer, "Local", pathBuffer);
	}
	FileSystem::Combine(pathBuffer, COMPANY_NAME, pathBuffer);
	FileSystem::Combine(pathBuffer, PRODUCT_NAME, pathBuffer);
#elif defined(__APPLE__)
	CSTRING home = std::getenv("HOME");
	FileSystem::Combine(home, "Library", pathBuffer);
	FileSystem::Combine(pathBuffer, "Application Support", pathBuffer);
	FileSystem::Combine(pathBuffer, "com", pathBuffer);
	std::strcpy(pathBuffer + strlen(pathBuffer), ".");
	std::strcpy(pathBuffer + strlen(pathBuffer), COMPANY_NAME);
	std::strcpy(pathBuffer + strlen(pathBuffer), ".");
	std::strcpy(pathBuffer + strlen(pathBuffer), PRODUCT_NAME);
#else // Linux
	CSTRING configHome = std::getenv("XDG_CONFIG_HOME");
	std::strcpy(pathBuffer, configHome);
	if (strlen(pathBuffer) == 0)
	{
		CSTRING home = std::getenv("HOME");
		std::strcpy(pathBuffer, home);
	}
	FileSystem::Combine(pathBuffer, COMPANY_NAME, pathBuffer);
	FileSystem::Combine(pathBuffer, PRODUCT_NAME, pathBuffer);
#endif
	s_PersistentDataPath = pathBuffer;
}

static void FindTemporaryDataPath()
{
	char pathBuffer[PATH_MAX];
#if WINDOWS
	CSTRING localPath = std::getenv("LOCALAPPDATA");
	std::strcpy(pathBuffer, localPath);
	if (strlen(pathBuffer) == 0) // Failed to get LocalLow
	{
		CSTRING userPath = std::getenv("USERPROFILE");
		if (strlen(userPath) > 0)
		{
			FileSystem::Combine(userPath, "AppData", pathBuffer);
			FileSystem::Combine(pathBuffer, "Local", pathBuffer);
		}
	}
	if (strlen(pathBuffer) == 0) // Still failed to find
	{
		std::strcpy(pathBuffer, "C:");
		FileSystem::Combine(pathBuffer, "Users", pathBuffer);
		FileSystem::Combine(pathBuffer, "Default", pathBuffer);
		FileSystem::Combine(pathBuffer, "AppData", pathBuffer);
		FileSystem::Combine(pathBuffer, "Local", pathBuffer);
	}
	FileSystem::Combine(pathBuffer, "Temp", pathBuffer);
	FileSystem::Combine(pathBuffer, COMPANY_NAME, pathBuffer);
	FileSystem::Combine(pathBuffer, PRODUCT_NAME, pathBuffer);
#elif defined(__APPLE__)
	CSTRING home = std::getenv("HOME");
	FileSystem::Combine(home, "Library", pathBuffer);
	FileSystem::Combine(pathBuffer, "Caches", pathBuffer);
	FileSystem::Combine(pathBuffer, "com", pathBuffer);
	std::strcpy(pathBuffer + strlen(pathBuffer), ".");
	std::strcpy(pathBuffer + strlen(pathBuffer), COMPANY_NAME);
	std::strcpy(pathBuffer + strlen(pathBuffer), ".");
	std::strcpy(pathBuffer + strlen(pathBuffer), PRODUCT_NAME);
#else // Linux
	CSTRING tmp = std::getenv("TMPDIR");
	std::strcpy(pathBuffer, tmp);
	if (strlen(pathBuffer) == 0)
	{
		FileSystem::Combine("", "var", pathBuffer);
		FileSystem::Combine(pathBuffer, "tmp", pathBuffer);
	}
	FileSystem::Combine(pathBuffer, COMPANY_NAME, pathBuffer);
	FileSystem::Combine(pathBuffer, PRODUCT_NAME, pathBuffer);
#endif
	s_TemporaryDataPath = pathBuffer;
}

void FileSystem::Init()
{
	FindExecutablePath();
	FindPersistentDataPath();
	FindTemporaryDataPath();
	if (Logger::IsInitialized()) LOG_INFO("Initialised the file system");
	s_bInitialised = true;
}

SIZE_T FileSystem::PathMax() { return PATH_MAX; }

CSTRING FileSystem::ExecutablePath() { return s_ExecutablePath.c_str(); }

CSTRING FileSystem::PersistentDataPath() { return s_PersistentDataPath.c_str(); }

CSTRING FileSystem::TemporaryDataPath() { return s_TemporaryDataPath.c_str(); }

void FileSystem::Combine(CSTRING pathLeft, CSTRING pathRight, char* buffer, SIZE_T bufferSize)
{
	std::strncpy(buffer, pathLeft, bufferSize);
	std::strncpy(buffer + strlen(buffer), SEPARATOR_STR, bufferSize - strlen(buffer));
	std::strncpy(buffer + strlen(buffer), pathRight, bufferSize - strlen(buffer));
}

void FileSystem::Combine(const STRING& pathLeft, CSTRING pathRight, char* buffer, SIZE_T bufferSize)
{
	Combine(pathLeft.c_str(), pathRight, buffer, bufferSize);
}

void FileSystem::Combine(CSTRING pathLeft, const STRING& pathRight, char* buffer, SIZE_T bufferSize)
{
	Combine(pathLeft, pathRight.c_str(), buffer, bufferSize);
}

void FileSystem::Combine(const STRING& pathLeft, const STRING& pathRight, char* buffer,
						 SIZE_T bufferSize)
{
	Combine(pathLeft.c_str(), pathRight.c_str(), buffer, bufferSize);
}

STRING FileSystem::Combine(CSTRING pathLeft, CSTRING pathRight)
{
	CSTRING buffer = (CSTRING)alloca(PATH_MAX);
	Combine(pathLeft, pathRight, const_cast<char*>(buffer));
	return STRING(buffer);
}

STRING FileSystem::Combine(const STRING& pathLeft, CSTRING pathRight)
{
	return Combine(pathLeft.c_str(), pathRight);
}

STRING FileSystem::Combine(CSTRING pathLeft, const STRING& pathRight)
{
	return Combine(pathLeft, pathRight.c_str());
}

STRING FileSystem::Combine(const STRING& pathLeft, const STRING& pathRight)
{
	return Combine(pathLeft.c_str(), pathRight.c_str());
}

void FileSystem::Combine(CSTRING pathLeft, CSTRING pathRight, STRING& result)
{
	result = Combine(pathLeft, pathRight);
}

void FileSystem::Combine(STRING pathLeft, CSTRING pathRight, STRING& result)
{
	result = Combine(pathLeft, pathRight);
}

void FileSystem::Combine(CSTRING pathLeft, STRING pathRight, STRING& result)
{
	result = Combine(pathLeft, pathRight);
}

void FileSystem::Combine(STRING pathLeft, STRING pathRight, STRING& result)
{
	result = Combine(pathLeft, pathRight);
}

void FileSystem::GetFilePart(CSTRING path, char* buffer, SIZE_T bufferSize)
{
	CSTRING pLastSeparator = std::strrchr(path, SEPARATOR);
	pLastSeparator ? std::strncpy(buffer, &path[pLastSeparator - path + 1], bufferSize) :
					 std::strncpy(buffer, path, bufferSize);
}

void FileSystem::GetFilePart(const STRING& path, char* buffer, SIZE_T bufferSize)
{
	GetFilePart(path.c_str(), buffer, bufferSize);
}

STRING FileSystem::GetFilePart(CSTRING path)
{
	STRING output(path);
	output = output.substr(output.find_last_of(SEPARATOR_STR) + 1);
	return output;
}

STRING FileSystem::GetFilePart(const STRING& path)
{
	STRING output(path);
	output = output.substr(output.find_last_of(SEPARATOR_STR) + 1);
	return output;
}

void FileSystem::GetFilePart(CSTRING path, STRING& result)
{
	result = path;
	result = result.substr(result.find_last_of(SEPARATOR_STR) + 1);
}

void FileSystem::GetFilePart(const STRING& path, STRING& result)
{
	result = path;
	result = result.substr(result.find_last_of(SEPARATOR_STR) + 1);
}

void FileSystem::GetDirectory(CSTRING path, char* buffer, SIZE_T bufferSize)
{
	CSTRING pLastSeparator = std::strrchr(path, SEPARATOR);
	SIZE_T count = pLastSeparator ?
					   (pLastSeparator - path < bufferSize ? pLastSeparator - path : bufferSize) :
					   bufferSize;
	std::strncpy(buffer, path, count);
}

void FileSystem::GetDirectory(const STRING& path, char* buffer, SIZE_T bufferSize)
{
	GetDirectory(path.c_str(), buffer, bufferSize);
}

STRING FileSystem::GetDirectory(CSTRING path)
{
	STRING output(path);
	output = output.substr(0, output.find_last_of(SEPARATOR_STR));
	return output;
}

STRING FileSystem::GetDirectory(const STRING& path)
{
	STRING output(path);
	output = output.substr(0, output.find_last_of(SEPARATOR_STR));
	return output;
}

void FileSystem::GetDirectory(CSTRING path, STRING& result) { result = GetDirectory(path); }

void FileSystem::GetDirectory(const STRING& path, STRING& result) { result = GetDirectory(path); }

bool FileSystem::FileExists(CSTRING file) { return std::ifstream(file).good(); }

bool FileSystem::FileExists(const STRING& file) { return std::ifstream(file).good(); }

bool FileSystem::DirectoryExists(CSTRING directory)
{
	struct stat info;
	return (!stat(directory, &info)) && (info.st_mode & S_IFDIR);
}

bool FileSystem::DirectoryExists(const STRING& directory)
{
	return DirectoryExists(directory.c_str());
}

void FileSystem::MakeDirectory(CSTRING directory)
{
	// Sadly no universal way to do this pre c++17 :(
#if WINDOWS
	CreateDirectory(FROM_STRING(directory).c_str(), nullptr);
#else
	mkdir(directory, 0777);
#endif
}

void FileSystem::MakeDirectory(const STRING& directory) { MakeDirectory(directory.c_str()); }

bool FileSystem::ReadFile(CSTRING path, char* output, SIZE_T bufferSize)
{
	if (FILE* pFile = fopen(path, "r"))
	{
		std::fread(output, sizeof(char), bufferSize, pFile);
		fclose(pFile);
		return true;
	}
	return false;
}

bool FileSystem::ReadFile(CSTRING path, STRING& output)
{
	std::ifstream file(path);
	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		output = buffer.str();
		return true;
	}
	return false;
}

bool FileSystem::ReadFile(const STRING& path, char* output, SIZE_T bufferSize)
{
	return ReadFile(path.c_str(), output, bufferSize);
}

bool FileSystem::ReadFile(const STRING& path, STRING& output)
{
	return ReadFile(path.c_str(), output);
}

void FileSystem::WriteFile(CSTRING path, CSTRING contents)
{
	STRING dir = GetDirectory(path);
	if (!DirectoryExists(dir)) MakeDirectory(dir);
	std::ofstream file(path, std::ios::trunc); // Explicit truncation
	file << contents;
}

void FileSystem::WriteFile(CSTRING path, const STRING& contents)
{
	STRING dir = GetDirectory(path);
	if (!DirectoryExists(dir)) MakeDirectory(dir);
	std::ofstream file(path, std::ios::trunc); // Explicit truncation
	file << contents;
}

void FileSystem::WriteFile(const STRING& path, CSTRING contents)
{
	STRING dir = GetDirectory(path);
	if (!DirectoryExists(dir)) MakeDirectory(dir);
	std::ofstream file(path, std::ios::trunc); // Explicit truncation
	file << contents;
}

void FileSystem::WriteFile(const STRING& path, const STRING& contents)
{
	STRING dir = GetDirectory(path);
	if (!DirectoryExists(dir)) MakeDirectory(dir);
	std::ofstream file(path, std::ios::trunc); // Explicit truncation
	file << contents;
}

void FileSystem::AppendFile(CSTRING path, CSTRING contents)
{
	STRING dir = GetDirectory(path);
	if (!DirectoryExists(dir)) MakeDirectory(dir);
	std::ofstream file(path, std::ios::app);
	file << contents;
}

void FileSystem::AppendFile(CSTRING path, const STRING& contents)
{
	STRING dir = GetDirectory(path);
	if (!DirectoryExists(dir)) MakeDirectory(dir);
	std::ofstream file(path, std::ios::app);
	file << contents;
}

void FileSystem::AppendFile(const STRING& path, CSTRING contents)
{
	STRING dir = GetDirectory(path);
	if (!DirectoryExists(dir)) MakeDirectory(dir);
	std::ofstream file(path, std::ios::app);
	file << contents;
}

void FileSystem::AppendFile(const STRING& path, const STRING& contents)
{
	STRING dir = GetDirectory(path);
	if (!DirectoryExists(dir)) MakeDirectory(dir);
	std::ofstream file(path, std::ios::app);
	file << contents;
}
