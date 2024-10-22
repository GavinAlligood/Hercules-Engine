#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "Hercules/Core/Log/Log.h"

#ifdef HC_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // HC_PLATFORM_WINDOWS