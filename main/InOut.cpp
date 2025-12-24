#include <iostream>
#include "InOut.h"
#include <string>
#include <fstream>
#include "Tools.h"
#include <unordered_map>


std::unordered_map<int, Pipe> PipesCreate(std::unordered_map<int, Pipe>& m) {
    Pipe p;
    std::cin >> p;
    m.emplace(p.GetId(), p);
    return m;
}

std::unordered_map<int, KS> KSCreate(std::unordered_map<int, KS>& m) {
    KS g;
    std::cin >> g;
    m.emplace(g.GetId(), g);
    return m;
}


void PipesPrint(std::unordered_map<int, Pipe>& m) {
    if (m.empty()) {
        std::cout << '\n';
        std::cout << "Труб нет" << std::endl;
        return;
    }
    for (const auto& Pipe : m) {
        std::cout << Pipe.second;
    }
}

void KSPrint(std::unordered_map<int, KS>& m) {
    if (m.empty()) {
        std::cout << "КС нет" << std::endl;
        std::cout << '\n';
        return;
    }
    for (const auto& KS : m) {
        std::cout << KS.second;
    }
}

void Load(std::unordered_map<int, Pipe>& Pipemap, std::unordered_map<int, KS>& KSmap) {
    std::ifstream fin;
    std::string data;

    std::cout << "Введите имя файла: ";
    INPUT_LINE(std::cin, data);

    fin.open(data);

    if (fin.is_open()) {
        int countpipes;
        fin >> countpipes;
        LoadObject(Pipemap, countpipes, fin);
        int countks;
        fin >> countks;
        LoadObject(KSmap, countks, fin);

        std::cout << "Данные успешно загружены" << std::endl;
    }
    else {
        std::cout << "Произошла ошибка. Обратитесь в поддержку или попробуйте снова." << std::endl;
    }
    fin.close();
}

void ChangePipe(std::unordered_map<int, Pipe>& Pipemap, std::unordered_set <int>& res) {
    std::string idInput;
    std::cout << "Введите ID объектов для изменения (через пробел): ";
    INPUT_LINE(std::cin, idInput);
    std::istringstream idStream(idInput);
    std::unordered_set<int> ids;
    int id;
    while (idStream >> id) {
        ids.emplace(id);
    }


    for (int id : ids) {
        if (res.find(id) == res.end()) {
            std::cout << "Объект с ID " << id << " не найден.\n";
            continue;
        }
        Pipemap.at(id).changeofstate();
        std::cout << "Объект с ID " << id << " успешно изменены\n";
    }
}

void ChangeKS(std::unordered_map<int, KS>& KSmap, std::unordered_set <int>& res) {
    std::string idInput;
    std::cout << "Введите ID объектов для изменения (через пробел): ";
    INPUT_LINE(std::cin, idInput);

    std::istringstream idStream(idInput);
    std::unordered_set<int> ids;
    int id;
    while (idStream >> id) {
        ids.emplace(id);
    }
    int change;
    std::cout << "Введите количество цехов ";
    change = GetCorrectNumber(0, 100);

    for (int id : ids) {
        if (res.find(id) == res.end()) {
            std::cout << "Объект с ID " << id << " не найден.\n";
            continue;
        }

        if (KSmap.at(id).UpdateWorkshopsInUse(change)) {
            std::cout << "Объект с ID" << id << " успешно изменены\n";
        }
        else {
            std::cout << "Ошибка в процессе изменения объекта" << std::endl;
        }
    }
}