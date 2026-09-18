#if defined(_WIN32) || defined(_WIN64) // Windows
#define WINDOWS 1
#endif

#include "FileSystem.h"
#include "Logging/Log.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static bool s_bInitialised = false;

static STRING s_ExecutablePath;
static STRING s_PersistentDataPath;
static STRING s_TemporaryDataPath;

bool FileSystem::IsInitialized() { return s_bInitialised; }

static void FindPersistentDataPath(STRING_VIEW companyName, STRING_VIEW productName)
{
#if WINDOWS
    CSTRING localPath = std::getenv("LOCALAPPDATA");
    if (localPath && std::strlen(localPath) != 0)
    {
        FileSystem::Combine({localPath, companyName, productName}, s_PersistentDataPath);
        return;
    }
    CSTRING userPath = std::getenv("USERPROFILE");
    if (userPath && std::strlen(userPath) > 0)
    {
        FileSystem::Combine({userPath, "AppData", "Local", companyName, productName}, s_PersistentDataPath);
        return;
    }
    FileSystem::Combine({"C:", "Users", "Default", "AppData", "Local", companyName, productName}, s_PersistentDataPath);
#elif defined(__APPLE__)
    CSTRING home = std::getenv("HOME");
    s_PersistentDataPath = FileSystem::Combine({home, "Library", "Application Support", "com"}) + "." +
                           static_cast<STRING>(companyName) + "." + static_cast<STRING>(productName);
#else // Linux
    CSTRING home = std::getenv("XDG_CONFIG_HOME");
    if (!home || std::strlen(home) == 0) home = std::getenv("HOME");
    FileSystem::Combine({home, companyName, productName}, s_PersistentDataPath);
#endif
}

static void FindTemporaryDataPath(STRING_VIEW companyName, STRING_VIEW productName)
{
#if WINDOWS
    CSTRING localPath = std::getenv("LOCALAPPDATA");
    if (localPath && std::strlen(localPath) != 0)
    {
        FileSystem::Combine({localPath, "Temp", companyName, productName}, s_TemporaryDataPath);
        return;
    }
    CSTRING userPath = std::getenv("USERPROFILE");
    if (userPath && std::strlen(userPath) > 0)
    {
        FileSystem::Combine({userPath, "AppData", "Local", "Temp", companyName, productName}, s_TemporaryDataPath);
        return;
    }
    FileSystem::Combine({"C:", "Users", "Default", "AppData", "Local", "Temp", companyName, productName},
                        s_TemporaryDataPath);
#elif defined(__APPLE__)
    CSTRING home = std::getenv("HOME");
    s_TemporaryDataPath = FileSystem::Combine({home, "Library", "Caches", "com"}) + "." +
                          static_cast<STRING>(companyName) + "." + static_cast<STRING>(productName);
#else // Linux
    CSTRING tmp = std::getenv("TMPDIR");
    if (tmp && std::strlen(tmp) != 0)
    {
        FileSystem::Combine({tmp, companyName, productName}, s_TemporaryDataPath);
        return;
    }
    FileSystem::Combine({std::filesystem::current_path().root_name().string(), "var", "tmp", companyName, productName},
                        s_TemporaryDataPath);
#endif
}

void FileSystem::Init(STRING_VIEW executablePath, STRING_VIEW companyName, STRING_VIEW productName)
{
    s_ExecutablePath = executablePath;
    FindPersistentDataPath(companyName, productName);
    FindTemporaryDataPath(companyName, productName);
    if (Logger::IsInitialized()) LOG_INFO("Initialised the file system");
    s_bInitialised = true;
}

CSTRING FileSystem::ExecutablePath() { return s_ExecutablePath.c_str(); }

CSTRING FileSystem::PersistentDataPath() { return s_PersistentDataPath.c_str(); }

CSTRING FileSystem::TemporaryDataPath() { return s_TemporaryDataPath.c_str(); }

STRING FileSystem::Combine(PARAMS<STRING_VIEW> paths)
{
    if (!paths.size())
    {
        LOG_ERROR("No paths to combine");
        return STRING();
    }
    std::filesystem::path path;
    for (auto it = paths.begin(); it != paths.end(); ++it) path.append(*it);
    return path.string();
}

void FileSystem::Combine(PARAMS<STRING_VIEW> paths, STRING& output)
{
    if (!paths.size())
    {
        LOG_ERROR("No paths to combine");
        return;
    }
    std::filesystem::path path;
    for (auto it = paths.begin(); it != paths.end(); ++it) path.append(*it);
    output = path.string();
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
