#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <istream>

class CompressorStation {
private:
    static int maxId;
    int id;
    std::string name;
    int workshops;
    int workshopsInWork;
    int efficiency;

public:
    CompressorStation();

    // Getters
    int GetId() const;
    static int GetMaxId();
    std::string GetName() const;
    int GetWorkshops() const;
    int GetWorkshopsInUse() const;
    int GetPercent() const;

    // Setters
    void SetName(const std::string& name);
    void SetWorkshops(int total, int working);
    void SetEfficiency(int efficiency);

    // Workshop management
    void StartWorkshop();
    void StopWorkshop();
    bool UpdateWorkshopsInUse(int change);

    void Print() const;

    // Friend functions for I/O
    friend std::ostream& operator<<(std::ostream& out, const CompressorStation& cs);
    friend std::istream& operator>>(std::istream& in, CompressorStation& cs);
    friend std::ifstream& operator>>(std::ifstream& fin, CompressorStation& g);
    friend std::ofstream& operator<<(std::ofstream& fout, const CompressorStation& g);
};