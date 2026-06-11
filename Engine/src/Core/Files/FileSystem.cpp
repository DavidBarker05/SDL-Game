#if defined(_WIN32) || defined(_WIN64) // Windows
#define WINDOWS 1
#endif

// I've noticed I've made my life much harder by not using c++17 but oh well
// ig this gives me some practice
#include "FileSystem.h"
#include "Logging/Log.h"
#include "Math/Math.h"
#include <codecvt>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#if WINDOWS
#include <ShlObj_core.h>
#include <windows.h>
#define PATH_MAX MAX_PATH
#if UNICODE
#include <codecvt>
#endif
#else // Linux, MacOS, etc.
#include <limits.h>
#include <unistd.h>
#endif

static bool s_bInitialised = false;

static STRING s_ExecutablePath;
static STRING s_PersistentDataPath;
static STRING s_TemporaryDataPath;

bool FileSystem::IsInitialized() { return s_bInitialised; }

static void FindExecutablePath()
{
    char pathBuffer[PATH_MAX] = {};
#if WINDOWS
#if UNICODE
    wchar_t wideBuffer[PATH_MAX];
    GetModuleFileNameW(nullptr, wideBuffer, PATH_MAX);
    std::wstring_convert<std::codecvt_utf8<wchar_t>>()
        .to_bytes(wideBuffer)
        .copy(pathBuffer, PATH_MAX);
#else
    GetModuleFileNameA(nullptr, pathBuffer, PATH_MAX);
#endif // UNICODE
#else
    ssize_t len = readlink("/proc/self/exe", pathBuffer, sizeof(pathBuffer) - 1);
    if (len != -1) pathBuffer[len] = '\0';
#endif
    s_ExecutablePath = FileSystem::GetDirectory(pathBuffer);
}

static void FindPersistentDataPath(STRING_VIEW companyName, STRING_VIEW productName)
{
    char pathBuffer[PATH_MAX] = {};
#if WINDOWS
    PWSTR path = nullptr;
    HRESULT result = SHGetKnownFolderPath(FOLDERID_LocalAppDataLow, 0, nullptr, &path);
    if (SUCCEEDED(result))
    {
        std::wcstombs(pathBuffer, path, PATH_MAX);
        CoTaskMemFree(path);
    }
    if (std::strlen(pathBuffer) == 0) // Failed to get LocalLow
    {
        CSTRING userPath = std::getenv("USERPROFILE");
        if (userPath && std::strlen(userPath) > 0)
        {
            FileSystem::Combine(userPath, "AppData", pathBuffer);
            FileSystem::Combine(pathBuffer, "LocalLow", pathBuffer);
        }
    }
    if (std::strlen(pathBuffer) == 0) // Still failed to find
    {
        FileSystem::Combine("C:", "Users", pathBuffer);
        FileSystem::Combine(pathBuffer, "Default", pathBuffer);
        FileSystem::Combine(pathBuffer, "AppData", pathBuffer);
        FileSystem::Combine(pathBuffer, "Local", pathBuffer);
    }
    FileSystem::Combine(pathBuffer, companyName, pathBuffer);
    FileSystem::Combine(pathBuffer, productName, pathBuffer);
#elif defined(__APPLE__)
    CSTRING home = std::getenv("HOME");
    FileSystem::Combine(home, "Library", pathBuffer);
    FileSystem::Combine(pathBuffer, "Application Support", pathBuffer);
    FileSystem::Combine(pathBuffer, "com", pathBuffer);
    std::strcpy(pathBuffer + std::strlen(pathBuffer), ".");
    std::strcpy(pathBuffer + std::strlen(pathBuffer), COMPANY_NAME);
    std::strcpy(pathBuffer + std::strlen(pathBuffer), ".");
    std::strcpy(pathBuffer + std::strlen(pathBuffer), PRODUCT_NAME);
#else // Linux
    CSTRING home = std::getenv("XDG_CONFIG_HOME");
    if (!home || std::strlen(home) == 0) home = std::getenv("HOME");
    FileSystem::Combine(home, COMPANY_NAME, pathBuffer);
    FileSystem::Combine(pathBuffer, PRODUCT_NAME, pathBuffer);
#endif
    s_PersistentDataPath = pathBuffer;
}

static void FindTemporaryDataPath(STRING_VIEW companyName, STRING_VIEW productName)
{
    char pathBuffer[PATH_MAX] = {};
#if WINDOWS
    CSTRING localPath = std::getenv("LOCALAPPDATA");
    std::strcpy(pathBuffer, localPath);
    if (std::strlen(pathBuffer) == 0) // Failed to get LocalLow
    {
        CSTRING userPath = std::getenv("USERPROFILE");
        if (!userPath || std::strlen(userPath) > 0)
        {
            FileSystem::Combine(userPath, "AppData", pathBuffer);
            FileSystem::Combine(pathBuffer, "Local", pathBuffer);
        }
    }
    if (std::strlen(pathBuffer) == 0) // Still failed to find
    {
        FileSystem::Combine("C:", "Users", pathBuffer);
        FileSystem::Combine(pathBuffer, "Default", pathBuffer);
        FileSystem::Combine(pathBuffer, "AppData", pathBuffer);
        FileSystem::Combine(pathBuffer, "Local", pathBuffer);
    }
    FileSystem::Combine(pathBuffer, "Temp", pathBuffer);
    FileSystem::Combine(pathBuffer, companyName, pathBuffer);
    FileSystem::Combine(pathBuffer, productName, pathBuffer);
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
    if (std::strlen(pathBuffer) == 0)
    {
        FileSystem::Combine("", "var", pathBuffer);
        FileSystem::Combine(pathBuffer, "tmp", pathBuffer);
    }
    FileSystem::Combine(pathBuffer, COMPANY_NAME, pathBuffer);
    FileSystem::Combine(pathBuffer, PRODUCT_NAME, pathBuffer);
#endif
    s_TemporaryDataPath = pathBuffer;
}

void FileSystem::Init(STRING_VIEW companyName, STRING_VIEW productName)
{
    FindExecutablePath();
    FindPersistentDataPath(companyName, productName);
    FindTemporaryDataPath(companyName, productName);
    if (Logger::IsInitialized()) LOG_INFO("Initialised the file system");
    s_bInitialised = true;
}

SIZE_T FileSystem::PathMax() { return PATH_MAX; }

CSTRING FileSystem::ExecutablePath() { return s_ExecutablePath.c_str(); }

CSTRING FileSystem::PersistentDataPath() { return s_PersistentDataPath.c_str(); }

CSTRING FileSystem::TemporaryDataPath() { return s_TemporaryDataPath.c_str(); }

void FileSystem::Combine(STRING_VIEW pathLeft, STRING_VIEW pathRight, char* buffer,
                         SIZE_T bufferSize)
{
    std::filesystem::path left(pathLeft);
    std::filesystem::path right(pathRight);
    std::filesystem::path combined = left / right;
    combined.string().copy(buffer, bufferSize);
}

STRING FileSystem::Combine(STRING_VIEW pathLeft, STRING_VIEW pathRight)
{
    std::filesystem::path left(pathLeft);
    std::filesystem::path right(pathRight);
    std::filesystem::path combined = left / right;
    return combined.string();
}

void FileSystem::Combine(STRING_VIEW pathLeft, STRING_VIEW pathRight, STRING& result)
{
    result = Combine(pathLeft, pathRight);
}

void FileSystem::GetFilePart(STRING_VIEW path, char* buffer, SIZE_T bufferSize)
{
    try
    {
        std::filesystem::path(path).filename().string().copy(buffer, bufferSize);
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("%s", e.what());
    }
}

STRING FileSystem::GetFilePart(STRING_VIEW path)
{
    try
    {
        return std::filesystem::path(path).filename().string();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("%s", e.what());
        return static_cast<STRING>(path);
    }
}

void FileSystem::GetFilePart(STRING_VIEW path, STRING& result)
{
    try
    {
        result = std::filesystem::path(path).filename().string();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("%s", e.what());
    }
}

void FileSystem::GetDirectory(STRING_VIEW path, char* buffer, SIZE_T bufferSize)
{
    try
    {
        std::filesystem::path(path).parent_path().string().copy(buffer, bufferSize);
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("%s", e.what());
    }
}

STRING FileSystem::GetDirectory(STRING_VIEW path)
{
    try
    {
        return std::filesystem::path(path).parent_path().string();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("%s", e.what());
        return static_cast<STRING>(path);
    }
}

void FileSystem::GetDirectory(STRING_VIEW path, STRING& result)
{
    try
    {
        result = std::filesystem::path(path).parent_path().string();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("%s", e.what());
    }
}

bool FileSystem::Exists(STRING_VIEW path)
{
    try
    {
        return std::filesystem::exists(std::filesystem::path(path));
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("%s", e.what());
        return false;
    }
}

void FileSystem::Create(STRING_VIEW path)
{
    try
    {
        std::filesystem::create_directories(std::filesystem::path(path));
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("%s", e.what());
    }
}

bool FileSystem::ReadFile(STRING_VIEW path, char* output, SIZE_T bufferSize)
{
    try
    {
        std::ifstream file(static_cast<STRING>(path));
        if (file.is_open())
        {
            std::stringstream buffer;
            buffer << file.rdbuf();
            buffer.str().copy(output, bufferSize);
            return true;
        }
        return false;
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("%s", e.what());
        return false;
    }
}

bool FileSystem::ReadFile(STRING_VIEW path, STRING& output)
{
    try
    {
        std::ifstream file(static_cast<STRING>(path));
        if (file.is_open())
        {
            std::stringstream buffer;
            buffer << file.rdbuf();
            output = buffer.str();
            return true;
        }
        return false;
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("%s", e.what());
        return false;
    }
}

void FileSystem::WriteFile(STRING_VIEW path, STRING_VIEW contents)
{
    try
    {
        STRING dir = GetDirectory(path);
        if (!Exists(dir)) Create(dir);
        std::ofstream file(static_cast<STRING>(path), std::ios::trunc); // Explicit truncation
        file << contents;
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("%s", e.what());
    }
}

void FileSystem::AppendFile(STRING_VIEW path, STRING_VIEW contents)
{
    try
    {
        STRING dir = GetDirectory(path);
        if (!Exists(dir)) Create(dir);
        std::ofstream file(static_cast<STRING>(path), std::ios::app);
        file << contents;
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("%s", e.what());
    }
}
