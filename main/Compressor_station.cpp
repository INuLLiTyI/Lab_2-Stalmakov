#include "Compressor_station.h"
#include <iostream>
#include <string>
#include <fstream>
#include <format>

// Инициализация статической переменной
int CompressorStation::maxId = 0;

CompressorStation::CompressorStation() 
    : id(++maxId), name(""), workshops(0), workshopsInWork(0), efficiency(0) {}

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
    return fout;
}