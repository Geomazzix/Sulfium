#pragma once

//Containers
#include <vector>
#include <string>
#include <memory>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>

//C
#include <cstdint>
#include <cstdio>
#include <cassert>

//C++
#include <algorithm>
#include <any>
#include <optional>

//String utility.
#include <regex>
#include <sstream>
#include <iomanip>
#include <iosfwd>
#include <fstream>

//Windows specific utility.
#if defined(WIN32) || defined(WIN64)
#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#endif
#include <windows.h>
#endif