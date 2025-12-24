#pragma once
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <istream>


class Pipe {
private:
    std::string name;
    int length;
    int diameter;
    bool state;
    int id;
    int ksleftid;
    int ksrightid;
    static int maxid;
public:
    Pipe();
    Pipe(std::string name, int length, int diameter, bool state, int ksleftid, int ksrightid);
    int GetId();
    std::string Getname() const;
    void SetKs(int LeftKs, int RightKs);
    void SetDiameter(int diameter);
    bool Getstate() const;
    void SetState(bool newState) { state = newState; }
    void changeofstate();
    int GetDiameter();
    int GetLeftKs();
    int GetRightKs();

    friend std::ifstream& operator >> (std::ifstream& fin, Pipe& p);
    friend std::ofstream& operator << (std::ofstream& fout, const Pipe& p);

    friend std::istream& operator >> (std::istream& in, Pipe& p);
    friend std::ostream& operator << (std::ostream& out, const Pipe& p);
};