#include "Tools.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

bool checknamepipe(const Pipe& p, const string param)
{
    return p.GetName().find(param) != string::npos;
}

bool checkstate(const Pipe& p, bool param)
{
    return p.GetState() == param;
}

bool checknameks(const CompressorStation& g, string param)
{
    return g.GetName().find(param) != string::npos;
}

bool workshops(const CompressorStation& g, int param)
{
    return g.GetWorkshops() >= param;
}

void edit(unordered_map<int, Pipe>& Pipemap, unordered_set<int> res) {
    string idInput;
    cout << "Enter object IDs to change state (space separated): ";
    INPUT_LINE(cin, idInput);

    istringstream idStream(idInput);
    int id;
    bool foundAny = false;

    while (idStream >> id) {
        if (res.find(id) != res.end()) {
            Pipemap.at(id).changeofstate();
            foundAny = true;
            cout << "State of pipe with ID " << id << " changed." << endl;
        }
        else {
            cout << "ID " << id << " not found in filtered set." << endl;
        }
    }

    if (!foundAny) {
        cout << "No IDs found to change state." << endl;
    }
}