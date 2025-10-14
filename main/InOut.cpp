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

void PipesPrint(std::unordered_map<int, Pipe>& m) {
    if (m.empty()) {
        std::cout << '\n';
        std::cout << "No any pipes existing!" << std::endl;
        return;
    }
    for (const auto& Pipe : m) {
        std::cout << Pipe.second;
    }
}

void KSPrint(std::unordered_map<int, KS>& m) {
    if (m.empty()) {
        std::cout << "No any CS existing!" << std::endl;
        std::cout << '\n';
        return;
    }
    for (const auto& KS : m) {
        std::cout << KS.second;
    }
}

void Load(std::unordered_map<int, Pipe>& Pipemap, std::unordered_map<int, KS>& KSmap) {
    std::ifstream fin;
    std::string data;

    std::cout << "Input filename: ";
    INPUT_LINE(std::cin, data);

    fin.open(data);

    if (fin.is_open()) {
        int countpipes;
        fin >> countpipes;
        LoadObject(Pipemap, countpipes, fin);
        int countks;
        fin >> countks;
        LoadObject(KSmap, countks, fin);

        std::cout << "Data added succesfully!" << std::endl;
    }
    else {
        std::cout << "Error occured! Please, check if the input format is correct." << std::endl;
    }
    fin.close();
}

void ChangePipe(std::unordered_map<int, Pipe>& Pipemap, std::unordered_set<int>& res) {
    std::string idInput;
    std::cout << "Enter object IDs to modify (space separated): ";
    INPUT_LINE(std::cin, idInput);

    std::istringstream idStream(idInput);
    std::unordered_set<int> ids;
    int id;
    while (idStream >> id) {
        ids.emplace(id);
    }

    for (int id : ids) {
        if (res.find(id) == res.end()) {
            std::cout << "Object with ID " << id << " not found.\n";
            continue;
        }
        Pipemap.at(id).changeofstate();
        std::cout << "Object with ID " << id << " successfully modified\n";
    }
}