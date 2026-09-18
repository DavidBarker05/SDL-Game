#pragma once

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <string>
#include <string_view>

using SIZE_T = std::size_t;

using CSTRING = const char*;
using STRING = std::string;
using STRING_VIEW = std::string_view;

using INT8 = std::int_fast8_t;
using UINT8 = std::uint_fast8_t;

using INT16 = std::int_fast16_t;
using UINT16 = std::uint_fast16_t;

using INT32 = std::int_fast32_t;
using UINT32 = std::uint_fast32_t;

using INT64 = std::int64_t;
using UINT64 = std::uint64_t;

using FLOAT32 = float;
using FLOAT64 = double;

template<typename T>
using PARAMS = std::initializer_list<T>;
