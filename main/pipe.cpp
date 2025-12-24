#include <iostream>
#include "Pipe.h"
#include "Tools.h"
#include "InOut.h"


int Pipe::maxid = 0;


Pipe::Pipe()
{
    name = "None";
    length = 0;
    diameter = 0;
    state = 0;
    ksleftid = 0;
    ksrightid = 0;
}

Pipe::Pipe(std::string name, int length, int diameter, bool state, int ksleftid, int ksrightid) {
    this->name = name;
    this->length = length;
    this->diameter = diameter;
    this->state = state;
    this->id = ++maxid;
    this->ksleftid = ksleftid;
    this->ksrightid = ksrightid;
}



bool Pipe::Getstate() const
{
    return state;
}

void Pipe::changeofstate()
{
    state = !state;
}

int Pipe::GetDiameter()
{
    return diameter;
}

int Pipe::GetLeftKs()
{
    return ksleftid;
}

int Pipe::GetRightKs()
{
    return ksrightid;
}

std::ifstream& operator>>(std::ifstream& fin, Pipe& p)
{
    fin >> p.id;
    fin >> p.ksleftid;
    fin >> p.ksrightid;
    fin >> std::ws;
    getline(fin, p.name);
    fin >> p.length;
    fin >> p.diameter;
    fin >> p.state;
    p.maxid = p.id;
    return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const Pipe& p)
{
    fout << p.id << std::endl << p.ksleftid << std::endl << p.ksrightid << std::endl << p.name << std::endl << p.length << std::endl << p.diameter << std::endl << p.state << std::endl;
    return fout;
}

std::istream& operator>>(std::istream& in, Pipe& p)
{
    std::cout << "Введите имя трубы: ";
    INPUT_LINE(in, p.name);
    p.id = ++p.maxid;
    std::cout << "Введите длину: ";
    p.length = GetCorrectNumber(1, 10000);
    std::cout << "Введите диаметр: ";
    p.diameter = GetCorrectNumber(1, 10000);
    std::cout << "Введите состояние: ";
    p.state = GetCorrectNumber(0, 1);
    p.ksleftid = 0;
    p.ksrightid = 0;
    std::cout << std::endl;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Pipe& p)
{
    out << "\n";
    out << "id: " << p.id << std::endl;
    if (!(p.ksleftid == 0 && p.ksrightid == 0)) {
        out << "id левой кс: " << p.ksleftid << std::endl;
        out << "id правой кс: " << p.ksrightid << std::endl;
    }
    out << "Имя трубы: " << p.name << std::endl;
    out << "Длина: " << p.length << std::endl;
    out << "Диаметр: " << p.diameter << std::endl;
    out << "Состояние: " << (p.state ? "Исправна" : "В ремонте") << std::endl << std::endl;
    return out;

}

int Pipe::GetId()
{
    return id;
}

std::string Pipe::Getname() const
{
    return name;
}

void Pipe::SetKs(int LeftKs, int RightKs) {
    ksleftid = LeftKs;
    ksrightid = RightKs;
}

void Pipe::SetDiameter(int diameter) {
    this->diameter = diameter;
}pe::Getname() const
{
    return name;
}

void Pipe::SetKs(int LeftKs, int RightKs) {
    ksleftid = LeftKs;
    ksrightid = RightKs;
}

void Pipe::SetDiameter(int diameter) {
    this->diameter = diameter;
}st;
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