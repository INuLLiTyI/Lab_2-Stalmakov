#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <istream>

class Pipe {
private:
    static int maxId;
    int id;
    std::string name;
    float length;
    int diameter;
    bool inRepair;

public:
    Pipe();
    Pipe(const std::string& name, float length, int diameter, bool inRepair);

    int GetId() const;
    static int GetMaxId();
    static void SetMaxId(int newMaxId);
    std::string GetName() const;
    bool GetState() const;
    float GetLength() const;
    int GetDiameter() const;

    void changeofstate();
    void Edit();
    void Print() const;

    friend std::ostream& operator<<(std::ostream& out, const Pipe& pipe);
    friend std::istream& operator>>(std::istream& in, Pipe& pipe);
    friend std::ifstream& operator>>(std::ifstream& fin, Pipe& p);
    friend std::ofstream& operator<<(std::ofstream& fout, const Pipe& p);
};