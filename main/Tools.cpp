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

void edit(std::unordered_map<int, Pipe>& Pipemap, std::unordered_set<int> res) {

    std::string idInput;
    std::cout << "Enter object IDs to change state (space separated): ";
    std::getline(std::cin >> std::ws, idInput);

    std::istringstream idStream(idInput);
    int id;
    bool foundAny = false;

    while (idStream >> id) {
        // Check if this ID is in the filtered set
        if (res.find(id) != res.end()) {
            Pipemap.at(id).changeofstate(); // Change state of pipe with given ID
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