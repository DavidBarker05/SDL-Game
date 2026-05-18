#pragma once

#include "Types.h"

class FileSystem
{
public:
    static SIZE_T PathMax();

public:
    static CSTRING ExecutablePath();
    static CSTRING PersistentDataPath();
    static CSTRING TemporaryDataPath();

public:
    static bool IsInitialized();
    static void Init();

public:
    static void Combine(CSTRING pathLeft, CSTRING pathRight, char* buffer);
    static void Combine(CSTRING pathLeft, CSTRING pathRight, char** pBuffer);

public:
    static bool ReadFile(CSTRING path, char* output);
    static void WriteFile(CSTRING path, CSTRING contents);
    static void AppendLine(CSTRING path, CSTRING contents);
};