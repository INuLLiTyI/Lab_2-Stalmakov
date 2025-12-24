#pragma once 
#include <iostream>
#include <unordered_map>
#include "KS.h"
#include "Pipe.h"
#include <unordered_set>
#include "Tools.h"

class GasNet {
private:
    std::unordered_map<int, KS> Ks;
    std::unordered_map <int, Pipe> Pipes;
    std::vector<std::vector<int>> Graph;

public:
    void DeletePipe(std::unordered_set <int> res);
    void DeleteKS(std::unordered_set <int> res);
    void PipesCreate();
    void KSCreate();
    void PipesPrint();
    void KSPrint();
    void Load();
    void ChangePipe(std::unordered_set <int> res);
    void ChangeKS(std::unordered_set <int> res);
    std::unordered_map <int, Pipe>& GetPipes();
    std::unordered_map<int, KS>& GetKS();
    std::vector<int> Sort();
    bool Connect(int KSin, int KSout, int diameter);
    bool CreateGraph();
    bool Disconnect(int KSin, int KSout);
    int IsInNet(int Ksid);
};

template <typename T>
std::unordered_map<int, T> LoadObject(std::unordered_map<int, T>& Object, int count, std::ifstream& fin) {
    for (int i = 0; i < count; i++) {
        T obj{};
        fin >> obj;
        Object.emplace(obj.GetId(), obj);
    }
    return Object;
}
