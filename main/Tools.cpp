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

bool checknamepipe(const Pipe& p, const std::string param)
{
    return p.Getname().find(param) != std::string::npos;
}
bool checkstate(const Pipe& p, bool param)
{
    return p.Getstate() == param;
}

bool checknameks(const KS& g, std::string param)
{
    return g.Getname().find(param) != std::string::npos;
}
bool workshops(const KS& g, int param)
{
    return g.Getworkshops() >= param;
}