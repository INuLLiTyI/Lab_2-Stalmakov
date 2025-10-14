#include "Tools.h"
#include <iostream>
#include "InOut.h"
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <string>
#include <limits>

void fix() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool checknamepipe(const Pipe& p, const std::string param)
{
    return p.GetName().find(param) != std::string::npos;
}

bool checkstate(const Pipe& p, bool param)
{
    return p.GetState() == param;
}

bool checknameks(const CompressorStation& g, std::string param)
{
    return g.GetName().find(param) != std::string::npos;
}

bool workshops(const CompressorStation& g, int param)
{
    return g.GetWorkshops() >= param;
}

void edit(std::unordered_map<int, Pipe>& Pipemap, std::unordered_set<int> res) {
    std::string idInput;
    std::cout << "Enter object IDs to change state (space separated): ";
    std::getline(std::cin >> std::ws, idInput);

    std::istringstream idStream(idInput);
    int id;
    bool foundAny = false;

    while (idStream >> id) {
        if (res.find(id) != res.end()) {
            Pipemap.at(id).changeofstate();
            foundAny = true;
            std::cout << "State of pipe with ID " << id << " changed." << std::endl;
        }
        else {
            std::cout << "ID " << id << " not found in filtered set." << std::endl;
        }
    }

    if (!foundAny) {
        std::cout << "No IDs found to change state." << std::endl;
    }
}