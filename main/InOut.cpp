#include <iostream>
#include "InOut.h"
#include <string>
#include <fstream>

using namespace std;

unordered_map<int, Pipe> PipesCreate(unordered_map<int, Pipe>& m) {
    Pipe p;
    cin >> p;
    m.emplace(p.GetId(), p);
    return m;
}

unordered_map<int, CompressorStation> KSCreate(unordered_map<int, CompressorStation>& m) {
    CompressorStation g;
    cin >> g;
    m.emplace(g.GetId(), g);
    return m;
}

void PipesPrint(unordered_map<int, Pipe>& m) {
    if (m.empty()) {
        cout << '\n';
        cout << "No any pipes existing!" << endl;
        return;
    }
    for (const auto& Pipe : m) {
        cout << Pipe.second;
    }
}

void KSPrint(unordered_map<int, CompressorStation>& m) {
    if (m.empty()) {
        cout << "No any CS existing!" << endl;
        cout << '\n';
        return;
    }
    for (const auto& KS : m) {
        cout << KS.second;
    }
}

void Load(unordered_map<int, Pipe>& Pipemap, unordered_map<int, CompressorStation>& KSmap) {
    ifstream fin;
    string data;

    cout << "Input filename: ";
    INPUT_LINE(cin, data);

    fin.open(data);

    if (fin.is_open()) {
        int countpipes;
        fin >> countpipes;
        LoadObject(Pipemap, countpipes, fin);
        int countks;
        fin >> countks;
        LoadObject(KSmap, countks, fin);

        cout << "Data added succesfully!" << endl;
    }
    else {
        cout << "Error occured! Please, check if the input format is correct." << endl;
    }
    fin.close();
}

void ChangePipe(unordered_map<int, Pipe>& Pipemap, unordered_set<int>& res) {
    for (int id : res) {
        Pipemap.at(id).changeofstate();
        cout << "Object with ID " << id << " successfully modified\n";
    }
}

void ChangeKS(unordered_map<int, CompressorStation>& KSmap, unordered_set<int>& res) {
    int change;
    cout << "Enter number of workshops to change: ";
    change = GetCorrectNumber(-100, 100);

    for (int id : res) {
        if (KSmap.at(id).UpdateWorkshopsInUse(change)) {
            cout << "Object with ID " << id << " successfully modified\n";
        }
        else {
            cout << "Object modification error." << endl;
        }
    }
}