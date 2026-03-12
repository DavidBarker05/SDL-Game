#ifndef DATATYPES_H
#define DATATYPES_H

#include <cstddef>
#include <cstdint>

#define NULL 0

#define FALSE 0
#define TRUE 1

using SIZE_T = std::size_t;

using PVOID = void*;

using CHAR8 = char;
using PCHAR8 = char*;
using CSTRING = const char*;

using INT8 = std::int8_t;
using UINT8 = std::uint8_t;

using INT16 = std::int16_t;
using UINT16 = std::uint16_t;

using INT32 = std::int32_t;
using UINT32 = std::uint32_t;

using INT64 = std::int64_t;
using UINT64 = std::uint64_t;

using FLOAT32 = float;

using FLOAT64 = double;

#endif // !DATATYPES_H
