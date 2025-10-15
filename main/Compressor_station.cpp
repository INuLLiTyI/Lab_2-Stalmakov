#include "Compressor_station.h"
#include <iostream>
#include <string>
#include <fstream>
#include <format>
using namespace std;

// Инициализация статической переменной
int CompressorStation::maxId = 0;

CompressorStation::CompressorStation()
    : id(0), name(""), workshops(0), workshopsInWork(0), efficiency(0) {
} // id = 0 вместо ++maxId

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
    cout << format("Compressor Station [ID: {}]: {}\n", id, name);
    cout << format("  Total workshops: {}\n", workshops);
    cout << format("  Workshops in work: {}\n", workshopsInWork);
    cout << format("  Efficiency: {}\n", efficiency);

    if (workshops > 0) {
        double percentage = (static_cast<double>(workshopsInWork) / workshops) * 100;
        cout << format("  Percentage of workshops in work: {:.2f}%\n", percentage);
    }
}

// Friend functions for I/O
ostream& operator<<(ostream& out, const CompressorStation& cs) {
    out << "Compressor Station [ID: " << cs.id << "]: " << cs.name << "\n";
    out << "  Workshops: " << cs.workshopsInWork << "/" << cs.workshops << " in use\n";
    out << "  Efficiency: " << cs.efficiency << "\n";
    return out;
}

istream& operator>>(istream& in, CompressorStation& cs) {
    cout << "Enter compressor station name: ";
    getline(in, cs.name);

    cout << "Enter total number of workshops: ";
    in >> cs.workshops;

    cout << "Enter number of workshops in work: ";
    in >> cs.workshopsInWork;

    cout << "Enter efficiency: ";
    in >> cs.efficiency;

    in.ignore(); // очистка буфера
    return in;
}

ifstream& operator>>(ifstream& fin, CompressorStation& cs) {
    fin >> cs.id;
    fin.ignore();
    std::getline(fin, cs.name);
    fin >> cs.workshops;
    fin >> cs.workshopsInWork;
    fin >> cs.efficiency;

    // Обновляем maxId при загрузке
    if (cs.id > CompressorStation::maxId) {
        CompressorStation::maxId = cs.id;
    }
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