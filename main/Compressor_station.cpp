#include "Compressor_station.h"
#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include "Tools.h"
using namespace std;

int CompressorStation::maxId = 0;

CompressorStation::CompressorStation() {
    id = ++maxId;
    name = "";
    workshops = 0;
    workshopsInWork = 0;
    efficiency = 0;
}

CompressorStation::CompressorStation(const string& name, int workshops, int workshopsInWork, int efficiency) {
    id = ++maxId;
    this->name = name;
    this->workshops = workshops;
    this->workshopsInWork = workshopsInWork;
    this->efficiency = efficiency;
}

int CompressorStation::GetId() const {
    return id;
}

int CompressorStation::GetMaxId() {
    return maxId;
}

void CompressorStation::SetMaxId(int newMaxId) {
    maxId = newMaxId;
}

string CompressorStation::GetName() const {
    return name;
}

int CompressorStation::GetWorkshops() const {
    return workshops;
}

int CompressorStation::GetWorkshopsInUse() const {
    return workshopsInWork;
}

int CompressorStation::GetPercent() const {
    if (workshops == 0) return 0;
    return (workshopsInWork * 100) / workshops;
}

void CompressorStation::StartWorkshop() {
    if (workshopsInWork < workshops) {
        workshopsInWork++;
    }
}

void CompressorStation::StopWorkshop() {
    if (workshopsInWork > 0) {
        workshopsInWork--;
    }
}

bool CompressorStation::UpdateWorkshopsInUse(int change) {
    int newValue = workshopsInWork + change;
    if (newValue >= 0 && newValue <= workshops) {
        workshopsInWork = newValue;
        return true;
    }
    return false;
}

void CompressorStation::Print() const {
    cout << format("Name: {}\n", name);
    cout << format("  Total workshops: {}\n", workshops);
    cout << format("  Workshops in work: {}\n", workshopsInWork);
    cout << format("  Efficiency: {}\n", efficiency);

    if (workshops > 0) {
        double percentage = (static_cast<double>(workshopsInWork) / workshops) * 100;
        cout << format("  Percentage of workshops in work: {:.2f}%\n", percentage);
    }
}

ostream& operator<<(ostream& out, const CompressorStation& cs) {
    out << "Compressor Station [ID: " << cs.id << "]: " << cs.name << "\n";
    out << "  Workshops: " << cs.workshopsInWork << "/" << cs.workshops << " in use\n";
    out << "  Efficiency: " << cs.efficiency << "\n";
    return out;
}

istream& operator>>(istream& in, CompressorStation& cs) {
    string name;
    int workshops, workshopsInWork, efficiency;

    cout << "Enter compressor station name: ";
    getline(in >> ws, name);

    cout << "Enter total number of workshops: ";
    while (!(in >> workshops) || workshops <= 0) {
        cout << "Invalid input! Enter positive number: ";
        in.clear();
        in.ignore(10000, '\n');
    }

    cout << "Enter number of workshops in work: ";
    while (!(in >> workshopsInWork) || workshopsInWork < 0 || workshopsInWork > workshops) {
        cout << "Invalid input! Enter number between 0 and " << workshops << ": ";
        in.clear();
        in.ignore(10000, '\n');
    }

    cout << "Enter efficiency: ";
    while (!(in >> efficiency) || efficiency <= 0) {
        cout << "Invalid input! Enter positive number: ";
        in.clear();
        in.ignore(10000, '\n');
    }

    cs = CompressorStation(name, workshops, workshopsInWork, efficiency);
    return in;
}

ifstream& operator>>(ifstream& fin, CompressorStation& cs) {
    int id;
    string name;
    int workshops, workshopsInWork, efficiency;

    fin >> id;
    getline(fin >> ws, name);
    fin >> workshops;
    fin >> workshopsInWork;
    fin >> efficiency;

    cs = CompressorStation(name, workshops, workshopsInWork, efficiency);
    const_cast<int&>(cs.id) = id;
    CompressorStation::maxId = max(CompressorStation::maxId, id);

    return fin;
}

ofstream& operator<<(ofstream& fout, const CompressorStation& cs) {
    fout << cs.id << "\n";
    fout << cs.name << "\n";
    fout << cs.workshops << "\n";
    fout << cs.workshopsInWork << "\n";
    fout << cs.efficiency << "\n";
    return fout;
}