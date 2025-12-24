#include <iostream>
#include "KS.h"
#include "Tools.h"
#include "InOut.h"

int KS::maxid = 0;

KS::KS()
{
    name = "None";
    workshops = 0;
    workshops_work = 0;
    efficiency = 0;

}

std::string KS::Getname() const
{
    return name;
}


int KS::GetId()
{
    return id;
}

int KS::Getworkshops() const
{
    return workshops;
}

std::ifstream& operator>>(std::ifstream& fin, KS& g)
{
    fin >> g.id;
    fin >> std::ws;
    getline(fin, g.name);
    fin >> g.workshops;
    fin >> g.workshops_work;
    fin >> g.efficiency;
    g.maxid = g.id;
    return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const KS& g)
{
    fout << g.id << std::endl << g.name << std::endl << g.workshops << std::endl << g.workshops_work << std::endl << g.efficiency << std::endl;
    return fout;
}

std::istream& operator>>(std::istream& in, KS& g)
{
    std::cout << "\n";
    std::cout << "Введите имя: ";
    INPUT_LINE(in, g.name);
    g.id = ++g.maxid;
    std::cout << "Введите количесвто цехов: ";
    g.workshops = GetCorrectNumber(1, 10000);
    std::cout << "Введит количество цехов в работе: ";
    g.workshops_work = GetCorrectNumber(0, g.workshops);
    std::cout << "Введите эффективность: ";
    g.efficiency = GetCorrectNumber(1, 100);
    std::cout << std::endl;
    return in;
}

std::ostream& operator<<(std::ostream& out, const KS& g)
{
    if (g.name == "") {
        std::cout << "Нет данных для вывода" << "\n";
    }
    else {
        if (g.name != "") {
            out << "\n";
            out << "id: " << g.id << std::endl;
            out << "Название: " << g.name << std::endl;
            out << "Количество цехов: " << g.workshops << std::endl;
            out << "Количество цехов в работе: " << g.workshops_work << std::endl;
            out << "Эффективность: " << g.efficiency << std::endl << std::endl;
        }
    }
    return out;
}