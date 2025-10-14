﻿#pragma once
#include <iostream>
#include "Pipe.h"
#include "KS.h"
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <format>

#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
						std::cerr << str << std::endl
