#pragma once
#include "Pipe.h"
#include "KS.h"
#include <unordered_map>
#include <sstream> 
#include <vector>
#include "Tools.h"

std::unordered_map<int, KS> KSCreate(std::unordered_map<int, KS>& m);
std::unordered_map<int, Pipe> PipesCreate(std::unordered_map<int, Pipe>& m);
void PipesPrint(std::unordered_map<int, Pipe>& m);
void KSPrint(std::unordered_map<int, KS>& m);

template <typename T>
std::unordered_map<int, T> LoadObject(std::unordered_map<int, T>& Object, int count, std::ifstream& fin) {
    for (int i = 0; i < count; i++) {
        T obj{};
        fin >> obj;
        Object.emplace(obj.GetId(), obj);
    }
    return Object;
}