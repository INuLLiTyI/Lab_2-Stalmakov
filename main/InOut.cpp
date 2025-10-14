#include <iostream>
#include "InOut.h"
#include <string>
#include <fstream>
#include "Tools.h"
#include <unordered_map>

std::unordered_map<int, Pipe> PipesCreate(std::unordered_map<int, Pipe>& m) {
    Pipe p;
    std::cin >> p;
    m.emplace(p.GetId(), p);
    return m;
}

std::unordered_map<int, KS> KSCreate(std::unordered_map<int, KS>& m) {
    KS g;
    std::cin >> g;
    m.emplace(g.GetId(), g);
    return m;
}
