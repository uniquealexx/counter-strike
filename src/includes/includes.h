#pragma once

// standard thread library includes
#include <Windows.h>
#include <winternl.h>

#include <thread>
#include <memory>
#include <vector>
#include <format>
#include <cstdint>
#include <optional>
#include <iostream>
#include <string_view>

// dependencies includes
#include "../../dependencies/include/MinHook.h"
#include "../../dependencies/src/buffer.h"

// project includes
#include "../core/core.h"
#include "../utils/utils.h"

#include "../core/hooks/hooks.h"

