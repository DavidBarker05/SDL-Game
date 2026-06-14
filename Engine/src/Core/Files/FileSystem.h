#pragma once

#include "Types.h"
#include <filesystem> // If needed std::filesystem allows for more complex stuff, but this class does make some of the more general common stuff a bit easier

class FileSystem
{
public:
    static bool IsInitialized();
    static void Init(STRING_VIEW companyName, STRING_VIEW productName);

public:
    // The max length of characters a path can be
    static SIZE_T PathMax();

public:
    // The directory the executable is in
    static CSTRING ExecutablePath();
    // The directory for persistent data, same as Unity's Application.persistentDataPath
    static CSTRING PersistentDataPath();
    // The directory for temporary data, same as Unity's Application.tempCachePath
    static CSTRING TemporaryDataPath();

public:
    // Combine paths to create a longer path same ase C# Path.Combine()
    static void Combine(PARAMS<STRING_VIEW> paths, char* buffer, SIZE_T bufferSize = PathMax());
    // Combine paths to create a longer path same ase C# Path.Combine()
    [[nodiscard]] static STRING Combine(PARAMS<STRING_VIEW> paths);
    // Combine paths to create a longer path same ase C# Path.Combine()
    static void Combine(PARAMS<STRING_VIEW> paths, STRING& output);

public:
    // Gets the file part of the path, if no file and it doesn't end in a
    // separator then it returns the top directory
    static void GetFilePart(STRING_VIEW path, char* buffer, SIZE_T bufferSize = PathMax());

    // Gets the file part of the path, if no file and it doesn't end in a
    // separator then it returns the top directory
    [[nodiscard]] static STRING GetFilePart(STRING_VIEW path);

    // Gets the file part of the path, if no file and it doesn't end in a
    // separator then it returns the top directory
    static void GetFilePart(STRING_VIEW path, STRING& result);

    // Gets the directory that the current file or directory is contained within
    static void GetDirectory(STRING_VIEW path, char* buffer, SIZE_T bufferSize = PathMax());

    // Gets the directory that the current file or directory is contained within
    [[nodiscard]] static STRING GetDirectory(STRING_VIEW path);

    // Gets the directory that the current file or directory is contained within
    static void GetDirectory(STRING_VIEW path, STRING& result);

public:
    // Whether or not a file exists
    static bool Exists(STRING_VIEW path);

    // Create a directory if it doesn't exist
    static void Create(STRING_VIEW path);

public:
    // Read data from a file, returns true if the file exists
    static bool ReadFile(STRING_VIEW path, char* output, SIZE_T bufferSize);
    // Read data from a file, returns true if the file exists
    static bool ReadFile(STRING_VIEW path, STRING& output);

    // Write data to a file, clears all existing content in the file if it exists
    // and creates it if the file doesn't exist
    static void WriteFile(STRING_VIEW path, STRING_VIEW contents);

    // Append data to the end of a file, creates the file if it doesn't exist
    static void AppendFile(STRING_VIEW path, STRING_VIEW contents);
};
