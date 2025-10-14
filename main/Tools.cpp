#include "Tools.h"
#include <iostream>
#include "InOut.h"
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <string>
#include <limits>

void fix() {
    std::cin.clear(); // Reset stream state
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}