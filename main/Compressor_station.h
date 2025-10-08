#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <unordered_map>
#include <unordered_set>

class CompressorStation {

private:
    static int maxId;
    int id;
    std::string Name;
    int AmountOfWorkshops;
    int WorkshopsInWork;
    int EfficiencyLevel;

public:
    CompressorStation();


    int GetId() const;
    static int GetMaxId();
    std::string GetName() const;
    int GetPercent() const;

    void SetName(const std::string& name);
    void SetWorkshops(int total, int working);
    void SetEfficiency(int efficiency);
    void StartWorkshop();
    void StopWorkshop();
    void Print() const;

    // Friend functions for I/O
    friend std::ostream& operator<<(std::ostream& out, const CompressorStation& cs);
    friend std::istream& operator>>(std::istream& in, CompressorStation& cs);

};