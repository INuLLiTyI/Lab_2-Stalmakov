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
    CompressorStation(const std::string& name, int workshops, int workshopsInWork, int efficiency);

    int GetId() const;
    static int GetMaxId();
    static void SetMaxId(int newMaxId);
    std::string GetName() const;
    int GetWorkshops() const;
    int GetWorkshopsInUse() const;
    int GetPercent() const;

    void StartWorkshop();
    void StopWorkshop();
    bool UpdateWorkshopsInUse(int change);

    void Print() const;

    friend std::ostream& operator<<(std::ostream& out, const CompressorStation& cs);
    friend std::istream& operator>>(std::istream& in, CompressorStation& cs);
    friend std::ifstream& operator>>(std::ifstream& fin, CompressorStation& g);
    friend std::ofstream& operator<<(std::ofstream& fout, const CompressorStation& g);
};