#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <map>
#include <string>
#include <any>
#include <queue>
#include <chrono>

//#TODO: When going cross platform make sure to wrap this in a platform check
#include <cassert>
#define SFM_ASSERT assert 

//Entt specific - used during resource loading.
#include <entt/entt.hpp>

#include <entt/core/hashed_string.hpp>
#include <entt/resource/handle.hpp>
#include <entt/resource/loader.hpp>
#include <entt/resource/cache.hpp>

using namespace entt::literals;