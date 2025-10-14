#include "Compressor_station.h"
#include <iostream>
<<<<<<< HEAD
#include <fstream>
#include "Tools.h"
using namespace std;

int CompressorStation::maxId = 0;

CompressorStation::CompressorStation()
{
    id = ++maxId;
    Name = "None";
    AmountOfWorkshops = 0;
    WorkshopsInWork = 0;
    EfficiencyLevel = 0;
}


int CompressorStation::GetId() const { return id; }
int CompressorStation::GetMaxId() { return maxId; }
string CompressorStation::GetName() const { return Name; }
int CompressorStation::GetWorkshops() const { return AmountOfWorkshops; }
int CompressorStation::GetWorkshopsInUse() const { return WorkshopsInWork; }
int CompressorStation::GetPercent() const {
    return (AmountOfWorkshops > 0) ? (WorkshopsInWork * 100 / AmountOfWorkshops) : 0;
}

void CompressorStation::SetName(const string& name) { Name = name; }
void CompressorStation::SetWorkshops(int total, int working) {
    AmountOfWorkshops = total;
    WorkshopsInWork = working;
}
void CompressorStation::SetEfficiency(int efficiency) { EfficiencyLevel = efficiency; }

void CompressorStation::StartWorkshop() {
    if (WorkshopsInWork < AmountOfWorkshops) {
        WorkshopsInWork++;
        cout << "Workshop started. Now working: " << WorkshopsInWork << "/" << AmountOfWorkshops << endl;
    }
    else {
        cout << "All workshops are already working!\n";
=======
#include <string>
#include <fstream>
#include <format>

// Инициализация статической переменной
int CompressorStation::maxId = 0;

CompressorStation::CompressorStation()
    : id(++maxId), name(""), workshops(0), workshopsInWork(0), efficiency(0) {
}

// Getters
int CompressorStation::GetId() const {
    return id;
}

int CompressorStation::GetMaxId() {
    return maxId;
}

std::string CompressorStation::GetName() const {
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

// Setters
void CompressorStation::SetName(const std::string& newName) {
    name = newName;
}

void CompressorStation::SetWorkshops(int total, int working) {
    workshops = total;
    workshopsInWork = working;
    if (workshopsInWork > workshops) {
        workshopsInWork = workshops;
    }
}

void CompressorStation::SetEfficiency(int newEfficiency) {
    efficiency = newEfficiency;
}

// Workshop management
void CompressorStation::StartWorkshop() {
    if (workshopsInWork < workshops) {
        workshopsInWork++;
>>>>>>> 3323d9974e07d2145f6e6e28374ffa222fb0faf7
    }
}

void CompressorStation::StopWorkshop() {
<<<<<<< HEAD
    if (WorkshopsInWork > 0) {
        WorkshopsInWork--;
        cout << "Workshop stopped. Now working: " << WorkshopsInWork << "/" << AmountOfWorkshops << endl;
    }
    else {
        cout << "No workshops are working!\n";
=======
    if (workshopsInWork > 0) {
        workshopsInWork--;
>>>>>>> 3323d9974e07d2145f6e6e28374ffa222fb0faf7
    }
}

bool CompressorStation::UpdateWorkshopsInUse(int change) {
<<<<<<< HEAD
    int new_workshops_work = WorkshopsInWork + change;
    if (new_workshops_work >= 0 && new_workshops_work <= AmountOfWorkshops) {
        WorkshopsInWork = new_workshops_work;
        return true;
    }
    else {
        cout << "Error: number of working workshops must be between 0 and " << AmountOfWorkshops << ".\n";
        return false;
    }
}

void CompressorStation::Print() const {
    cout << "Compressor Station ID: " << id << endl;
    cout << "Name: " << Name << endl;
    cout << "Workshops: " << WorkshopsInWork << "/" << AmountOfWorkshops << " working" << endl;
    cout << "Efficiency Level: " << EfficiencyLevel << endl;
    cout << "Utilization: " << GetPercent() << "%" << endl;
}

ostream& operator<<(ostream& out, const CompressorStation& cs) {
    out << cs.id << endl;
    out << cs.Name << endl;
    out << cs.AmountOfWorkshops << endl;
    out << cs.WorkshopsInWork << endl;
    out << cs.EfficiencyLevel << endl;
    return out;
}

istream& operator>>(istream& in, CompressorStation& cs) {
    in >> cs.id;
    in.ignore();
    getline(in, cs.Name);
    in >> cs.AmountOfWorkshops >> cs.WorkshopsInWork >> cs.EfficiencyLevel;
    return in;
}

ifstream& operator>>(ifstream& fin, CompressorStation& g) {
    fin >> g.id;
    fin >> ws;
    getline(fin, g.Name);
    fin >> g.AmountOfWorkshops;
    fin >> g.WorkshopsInWork;
    fin >> g.EfficiencyLevel;
    if (g.id > g.maxId) {
        g.maxId = g.id;
    }
    return fin;
}

ofstream& operator<<(ofstream& fout, const CompressorStation& g) {
    fout << g.id << endl << g.Name << endl << g.AmountOfWorkshops << endl << g.WorkshopsInWork << endl << g.EfficiencyLevel << endl;
=======
    int newValue = workshopsInWork + change;
    if (newValue >= 0 && newValue <= workshops) {
        workshopsInWork = newValue;
        return true;
    }
    return false;
}

void CompressorStation::Print() const {
    std::cout << std::format("Compressor Station [ID: {}]: {}\n", id, name);
    std::cout << std::format("  Total workshops: {}\n", workshops);
    std::cout << std::format("  Workshops in work: {}\n", workshopsInWork);
    std::cout << std::format("  Efficiency: {}\n", efficiency);

    if (workshops > 0) {
        double percentage = (static_cast<double>(workshopsInWork) / workshops) * 100;
        std::cout << std::format("  Percentage of workshops in work: {:.2f}%\n", percentage);
    }
}

// Friend functions for I/O
std::ostream& operator<<(std::ostream& out, const CompressorStation& cs) {
    out << "Compressor Station [ID: " << cs.id << "]: " << cs.name << "\n";
    out << "  Workshops: " << cs.workshopsInWork << "/" << cs.workshops << " in use\n";
    out << "  Efficiency: " << cs.efficiency << "\n";
    return out;
}

std::istream& operator>>(std::istream& in, CompressorStation& cs) {
    std::cout << "Enter compressor station name: ";
    std::getline(in, cs.name);

    std::cout << "Enter total number of workshops: ";
    in >> cs.workshops;

    std::cout << "Enter number of workshops in work: ";
    in >> cs.workshopsInWork;

    std::cout << "Enter efficiency: ";
    in >> cs.efficiency;

    in.ignore(); // очистка буфера
    return in;
}

std::ifstream& operator>>(std::ifstream& fin, CompressorStation& cs) {
    fin >> cs.id;
    fin.ignore();
    std::getline(fin, cs.name);
    fin >> cs.workshops;
    fin >> cs.workshopsInWork;
    fin >> cs.efficiency;
    return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const CompressorStation& cs) {
    fout << cs.id << "\n";
    fout << cs.name << "\n";
    fout << cs.workshops << "\n";
    fout << cs.workshopsInWork << "\n";
    fout << cs.efficiency << "\n";
>>>>>>> 3323d9974e07d2145f6e6e28374ffa222fb0faf7
    return fout;
}