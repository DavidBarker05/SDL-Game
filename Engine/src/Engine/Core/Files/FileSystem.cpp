#if defined(_WIN32) || defined(_WIN64) // Windows
#define WINDOWS 1
#endif

#include "FileSystem.h"
#include "Logging/Log.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include "config.h"
#if WINDOWS
#include <windows.h>
#include <ShlObj_core.h>
#define PATH_MAX MAX_PATH
#define SEPARATOR '\\'
#define SEPARATOR_STR "\\"
#if UNICODE
#include <codecvt>
#define buffer_t wchar_t
#define string_t std::wstring
#define TO_STRING(wstring) std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wstring)
#else
#define buffer_t char
#define string_t std::string
#define TO_CHARBUFF(src, dst, size) std::memcpy(dst, src, size)
#define TO_STRING(string) string
#endif
#else // Linux, MacOS, etc.
#include <unistd.h>
#include <limits.h>
#define SEPARATOR '/'
#define SEPARATOR_STR "/"
#define buffer_t char
#define string_t std::string
#define TO_STRING(string) string
#endif

static bool s_bInitialised = false;

static CSTRING s_ExecutablePath;
static CSTRING s_PersistentDataPath;
static CSTRING s_TemporaryDataPath;

SIZE_T FileSystem::PathMax()
{
    return PATH_MAX;
}

CSTRING FileSystem::ExecutablePath()
{
    return s_ExecutablePath;
}

CSTRING FileSystem::PersistentDataPath()
{
    return s_PersistentDataPath;
}

CSTRING FileSystem::TemporaryDataPath()
{
    return s_TemporaryDataPath;
}

bool FileSystem::IsInitialized()
{
    return s_bInitialised;
}

static void FindExecutablePath()
{
    buffer_t pathBuffer[PATH_MAX];
    std::string output;
#if WINDOWS
	GetModuleFileName(nullptr, pathBuffer, PATH_MAX);
#else
	ssize_t len = readlink("/proc/self/exe", pathBuffer, sizeof(pathBuffer) - 1);
	if (len != -1) pathBuffer[len] = '\0';
#endif
    output = TO_STRING(string_t(pathBuffer));
	std::size_t lastPos = output.find_last_of(SEPARATOR);
	output = output.substr(0, lastPos);
    std::strcpy(const_cast<char*>(s_ExecutablePath), output.c_str());
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
    std::strcpy(const_cast<char*>(s_PersistentDataPath), pathBuffer);
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
    std::strcpy(const_cast<char*>(s_TemporaryDataPath), pathBuffer);
}

void FileSystem::Init()
{
    s_ExecutablePath = (CSTRING)alloca(PATH_MAX);
    s_PersistentDataPath = (CSTRING)alloca(PATH_MAX);
    s_TemporaryDataPath = (CSTRING)alloca(PATH_MAX);
    FindExecutablePath();
    FindPersistentDataPath();
    FindTemporaryDataPath();
    if (Logger::IsInitialized())
    {
        LOG_INFO("%s", s_TemporaryDataPath);
        LOG_INFO("Initialised the file system");
    }
    s_bInitialised = true;
}

void FileSystem::Combine(CSTRING pathLeft, CSTRING pathRight, char* buffer)
{
    std::strcpy(buffer, pathLeft);
    std::strcpy(buffer + strlen(buffer), SEPARATOR_STR);
    std::strcpy(buffer + strlen(buffer), pathRight);
}

void FileSystem::Combine(CSTRING pathLeft, CSTRING pathRight, char** pBuffer)
{
    *pBuffer = (char*)malloc(PATH_MAX);
    std::strcpy(*pBuffer, pathLeft);
    std::strcpy(*pBuffer + strlen(*pBuffer), SEPARATOR_STR);
    std::strcpy(*pBuffer + strlen(*pBuffer), pathRight);
}

bool FileSystem::ReadFile(CSTRING path, char* output)
{
    // TODO Read file
    return false;
}

void FileSystem::WriteFile(CSTRING path, CSTRING contents)
{
    // TODO Write to file
}

void FileSystem::AppendLine(CSTRING path, CSTRING contents)
{
    // TODO Append line to file
}
