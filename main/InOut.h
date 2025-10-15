#pragma once
#include "pipe.h"
#include "Compressor_station.h"
#include <unordered_map>
#include <sstream> 
#include <vector>
#include "Tools.h"

std::unordered_map<int, CompressorStation> KSCreate(std::unordered_map<int, CompressorStation>& m);
std::unordered_map<int, Pipe> PipesCreate(std::unordered_map<int, Pipe>& m);
void PipesPrint(std::unordered_map<int, Pipe>& m);
void KSPrint(std::unordered_map<int, CompressorStation>& m);

template <typename T>
std::unordered_map<int, T> LoadObject(std::unordered_map<int, T>& Object, int count, std::ifstream& fin) {
    for (int i = 0; i < count; i++) {
        T obj{};
        fin >> obj;
        Object.emplace(obj.GetId(), obj);
    }
    return Object;
}

void Load(std::unordered_map<int, Pipe>& Pipemap, std::unordered_map<int, CompressorStation>& KSmap);

template <typename T>
void DeleteObjectById(std::unordered_map<int, T>& objects, std::unordered_set<int>& res) {
    std::string idInput;
    std::cout << "Enter object IDs for deletion (space separated): ";
    INPUT_LINE(std::cin, idInput);

    std::istringstream idStream(idInput);
    std::unordered_set<int> ids;
    int id;
    while (idStream >> id) {
        ids.emplace(id);
    }

    for (int id : ids) {
        auto it = objects.find(id);
        if (res.find(id) == res.end()) {
            std::cout << "Object with ID " << id << " not found.\n";
            continue;
        }
        if (it != objects.end()) {
            objects.erase(it);
            std::cout << "Object with ID " << id << " successfully deleted.\n";
        }
    }
}

void ChangePipe(std::unordered_map<int, Pipe>& Pipemap, std::unordered_set<int>& res);
void ChangeKS(std::unordered_map<int, CompressorStation>& KSmap, std::unordered_set<int>& res);