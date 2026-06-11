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
    // The directory for persistent data, same as Unity's
    // Application.persistentDataPath
    static CSTRING PersistentDataPath();
    // The directory for temporary data, same as Unity's Application.tempCachePath
    static CSTRING TemporaryDataPath();

public:
    // Combine two paths to create a longer path, same as C# Path.Combine(string,
    // string)
    static void Combine(STRING_VIEW pathLeft, STRING_VIEW pathRight, char* buffer,
                        SIZE_T bufferSize = PathMax());
    // Combine two paths to create a longer path, same as C# Path.Combine(string,
    // string)
    static STRING Combine(STRING_VIEW pathLeft, STRING_VIEW pathRight);
    // Combine two paths to create a longer path, same as C# Path.Combine(string,
    // string)
    static void Combine(STRING_VIEW pathLeft, STRING_VIEW pathRight, STRING& result);

public:
    // Gets the file part of the path, if no file and it doesn't end in a
    // separator then it returns the top directory
    static void GetFilePart(STRING_VIEW path, char* buffer, SIZE_T bufferSize = PathMax());

    // Gets the file part of the path, if no file and it doesn't end in a
    // separator then it returns the top directory
    static STRING GetFilePart(STRING_VIEW path);

    // Gets the file part of the path, if no file and it doesn't end in a
    // separator then it returns the top directory
    static void GetFilePart(STRING_VIEW path, STRING& result);

    // Gets the directory that the current file or directory is contained within
    static void GetDirectory(STRING_VIEW path, char* buffer, SIZE_T bufferSize = PathMax());

    // Gets the directory that the current file or directory is contained within
    static STRING GetDirectory(STRING_VIEW path);

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
