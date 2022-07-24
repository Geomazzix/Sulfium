#pragma once

//C++
#include <memory>
#include <any>
#include <functional>
#include <algorithm>
#include <optional>
#include <unordered_map>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <set>
#include <chrono>

//C
#include <cstdio>
#include <cassert>
#include <cstdint>

//Core includes
#include <Core/Printer/Printer.h>

//D3D specific.
#define WIN32_LEAN_AND_MEAN
#include <Windows.h> //HResult

#include <d3d12.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

//Utility from the DirectX headers github: https://github.com/microsoft/DirectX-Headers/blob/main/include/directx/d3dx12.h
//Must be updated by hand.
#include <D3D12Renderer/Utility/d3dx12.h>

using namespace Microsoft::WRL;
using namespace DirectX;