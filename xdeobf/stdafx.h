#pragma once

#pragma warning(push)
#pragma warning(disable:4244)
#pragma warning(disable:4267)
#include <ida.hpp>
#include <hexrays.hpp>
#pragma warning(pop)

#include <map>

#include "Config.h"

#if VERBOSE
#define dbg msg
#else
#define dbg
#endif

#include "InsnMatcher.h"
#include "InsnOptimizer.h"
