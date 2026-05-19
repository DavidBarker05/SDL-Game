#pragma once

#include "Types.h"

class FileSystem
{

public:
	static bool IsInitialized();
	static void Init();

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
	// Combine two paths to create a longer path, same as C# Path.Combine(string, string)
	static void Combine(CSTRING pathLeft, CSTRING pathRight, char* buffer,
						SIZE_T bufferSize = PathMax());
	// Combine two paths to create a longer path, same as C# Path.Combine(string, string)
	static void Combine(const STRING& pathLeft, CSTRING pathRight, char* buffer,
						SIZE_T bufferSize = PathMax());
	// Combine two paths to create a longer path, same as C# Path.Combine(string, string)
	static void Combine(CSTRING pathLeft, const STRING& pathRight, char* buffer,
						SIZE_T bufferSize = PathMax());
	// Combine two paths to create a longer path, same as C# Path.Combine(string, string)
	static void Combine(const STRING& pathLeft, const STRING& pathRight, char* buffer,
						SIZE_T bufferSize = PathMax());

	// Combine two paths to create a longer path, same as C# Path.Combine(string, string)
	static STRING Combine(CSTRING pathLeft, CSTRING pathRight);
	// Combine two paths to create a longer path, same as C# Path.Combine(string, string)
	static STRING Combine(const STRING& pathLeft, CSTRING pathRight);
	// Combine two paths to create a longer path, same as C# Path.Combine(string, string)
	static STRING Combine(CSTRING pathLeft, const STRING& pathRight);
	// Combine two paths to create a longer path, same as C# Path.Combine(string, string)
	static STRING Combine(const STRING& pathLeft, const STRING& pathRight);

	// Combine two paths to create a longer path, same as C# Path.Combine(string, string)
	static void Combine(CSTRING pathLeft, CSTRING pathRight, STRING& result);
	// Combine two paths to create a longer path, same as C# Path.Combine(string, string)
	static void Combine(STRING pathLeft, CSTRING pathRight, STRING& result);
	// Combine two paths to create a longer path, same as C# Path.Combine(string, string)
	static void Combine(CSTRING pathLeft, STRING pathRight, STRING& result);
	// Combine two paths to create a longer path, same as C# Path.Combine(string, string)
	static void Combine(STRING pathLeft, STRING pathRight, STRING& result);

public:
	// Gets the file part of the path, if no file and it doesn't end in a separator then it returns
	// the top directory
	static void GetFilePart(CSTRING path, char* buffer, SIZE_T bufferSize = PathMax());
	// Gets the file part of the path, if no file and it doesn't end in a separator then it returns
	// the top directory
	static void GetFilePart(const STRING& path, char* buffer, SIZE_T bufferSize = PathMax());

	// Gets the file part of the path, if no file and it doesn't end in a separator then it returns
	// the top directory
	static STRING GetFilePart(CSTRING path);
	// Gets the file part of the path, if no file and it doesn't end in a separator then it returns
	// the top directory
	static STRING GetFilePart(const STRING& path);

	// Gets the file part of the path, if no file and it doesn't end in a separator then it returns
	// the top directory
	static void GetFilePart(CSTRING path, STRING& result);
	// Gets the file part of the path, if no file and it doesn't end in a separator then it returns
	// the top directory
	static void GetFilePart(const STRING& path, STRING& result);

	// Gets the directory that the current file or directory is contained within
	static void GetDirectory(CSTRING path, char* buffer, SIZE_T bufferSize = PathMax());
	// Gets the directory that the current file or directory is contained within
	static void GetDirectory(const STRING& path, char* buffer, SIZE_T bufferSize = PathMax());

	// Gets the directory that the current file or directory is contained within
	static STRING GetDirectory(CSTRING path);
	// Gets the directory that the current file or directory is contained within
	static STRING GetDirectory(const STRING& path);

	// Gets the directory that the current file or directory is contained within
	static void GetDirectory(CSTRING path, STRING& result);
	// Gets the directory that the current file or directory is contained within
	static void GetDirectory(const STRING& path, STRING& result);

public:
	// Whether or not a file exists
	static bool FileExists(CSTRING file);
	// Whether or not a file exists
	static bool FileExists(const STRING& file);

	// Whether or not a directory exists
	static bool DirectoryExists(CSTRING directory);
	// Whether or not a directory exists
	static bool DirectoryExists(const STRING& directory);

public:
	// Create a directory if it doesn't exist
	static void MakeDirectory(CSTRING directory);
	// Create a directory if it doesn't exist
	static void MakeDirectory(const STRING& directory);

public:
	// Read data from a file, returns true if the file exists
	static bool ReadFile(CSTRING path, char* output, SIZE_T bufferSize);
	// Read data from a file, returns true if the file exists
	static bool ReadFile(CSTRING path, STRING& output);

	// Read data from a file, returns true if the file exists
	static bool ReadFile(const STRING& path, char* output, SIZE_T bufferSize);
	// Read data from a file, returns true if the file exists
	static bool ReadFile(const STRING& path, STRING& output);

	// Write data to a file, clears all existing content in the file if it exists and creates it if
	// the file doesn't exist
	static void WriteFile(CSTRING path, CSTRING contents);
	// Write data to a file, clears all existing content in the file if it
	// exists and creates it if the file doesn't exist
	static void WriteFile(CSTRING path, const STRING& contents);

	// Write data to a file, clears all existing content in the file if it
	// exists and creates it if the file doesn't exist
	static void WriteFile(const STRING& path, CSTRING contents);
	// Write data to a file, clears all existing content in the file if it
	// exists and creates it if the file doesn't exist
	static void WriteFile(const STRING& path, const STRING& contents);

	// Append data to the end of a file, creates the file if it doesn't exist
	static void AppendFile(CSTRING path, CSTRING contents);
	// Append data to the end of a file, creates the file if it doesn't exist
	static void AppendFile(CSTRING path, const STRING& contents);

	// Append data to the end of a file, creates the file if it doesn't exist
	static void AppendFile(const STRING& path, CSTRING contents);
	// Append data to the end of a file, creates the file if it doesn't exist
	static void AppendFile(const STRING& path, const STRING& contents);
};