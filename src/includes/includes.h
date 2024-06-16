#pragma once

// standard thread library includes
#include <Windows.h>
#include <winternl.h>
#include <wrl/client.h>

#include <thread>
#include <memory>
#include <vector>
#include <format>
#include <cstdint>
#include <optional>
#include <iostream>
#include <string_view>

// dependencies includes
#include "../../dependencies/minhook/include/MinHook.h"
#include "../../dependencies/minhook/src/buffer.h"

#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_impl_dx11.h"
#include "../../dependencies/imgui/imgui_impl_win32.h"

// other libs include
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

// memory include
#include "../utils/memory/memory.h"

// sdk includes
#include "../sdk/interfaces/appsystem.h"
#include "../sdk/interfaces/source2client.h"
#include "../sdk/interfaces/source2engine.h"
#include "../sdk/interfaces/renderdevicedx11.h"

// project includes
#include "../core/displacement/displacement.h"

#include "../utils/console/console.h"

#include "../sdk/interfaces.h"

#include "../utils/render/render.h"

#include "../core/input/input.h"
#include "../core/hooks/hooks.h"
#include "../core/core.h"




