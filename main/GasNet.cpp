#include "GasNet.h"
#include "Tools.h"
#include "KS.h"
#include <stack>

void GasNet::DeletePipe(std::unordered_set <int> res)
{
    std::string idInput;
    std::cout << "������� ID �������� ��� �������� (����� ������): ";
    INPUT_LINE(std::cin, idInput);
    std::istringstream idStream(idInput);
    std::unordered_set<int> ids;
    int id;
    while (idStream >> id) {
        ids.emplace(id);
    }


    for (int id : ids) {
        auto it = Pipes.find(id);
        if (res.find(id) == res.end()) {
            std::cout << "������ � ID " << id << " �� ������\n";
            continue;
        }
        if (it != Pipes.end()) {

            if (Pipes.at(id).GetLeftKs() != 0) {
                std::cout << "���� �� ������� ����� � id "
                    << id << "���� ����� ��������!" << std::endl;
                std::cout << "�� �������?: ";
                if (GetCorrectNumber(0, 1) == 0) {
                    continue;
                }

            }

            Pipes.erase(it);
            std::cout << "������ � ID " << id << " ������� �����.\n";
        }
    }

}


void GasNet::DeleteKS(std::unordered_set <int> res)
{
    std::string idInput;
    std::cout << "������� ID �������� ��� �������� (����� ������): ";
    INPUT_LINE(std::cin, idInput);
    std::istringstream idStream(idInput);
    std::unordered_set<int> ids;
    int id;
    while (idStream >> id) {
        ids.emplace(id);
    }

    for (int id : ids) {

        auto it = Ks.find(id);
        if (res.find(id) == res.end()) {
            std::cout << "������ � ID " << id << " �� ������\n";
            continue;
        }
        if (it != Ks.end()) {

            int tmpid = IsInNet(id);

            if (tmpid != 0) {
                std::cout << "���� �� ������� �� � id "
                    << id << "���� ����� ��������������!" << std::endl;
                std::cout << "�� �������?: ";
                if (GetCorrectNumber(0, 1) == 1) {
                    Disconnect(Pipes.at(tmpid).GetLeftKs(), Pipes.at(tmpid).GetRightKs());
                }
                else {
                    continue;
                }

            }

            Ks.erase(it);
            std::cout << "������ � ID " << id << " ������� �����.\n";
        }
    }

}

void GasNet::PipesCreate()
{
    Pipe p;
    std::cin >> p;
    Pipes.emplace(p.GetId(), p);
}

void GasNet::KSCreate()
{
    KS g;
    std::cin >> g;
    Ks.emplace(g.GetId(), g);
}

void GasNet::PipesPrint()
{
    if (Pipes.empty()) {
        std::cout << '\n';
        std::cout << "���� ���" << std::endl;
        return;
    }
    for (const auto& Pipe : Pipes) {
        std::cout << Pipe.second;
    }

}

void GasNet::KSPrint()
{
    if (Ks.empty()) {
        std::cout << "�� ���" << std::endl;
        std::cout << '\n';
        return;
    }
    for (const auto& KS : Ks) {
        std::cout << KS.second;
    }
}



void GasNet::Load()
{
    std::ifstream fin;
    std::string data;

    std::cout << "������� ��� �����: ";
    INPUT_LINE(std::cin, data);

    fin.open(data);

    if (fin.is_open()) {
        int countpipes;
        fin >> countpipes;
        LoadObject(Pipes, countpipes, fin);
        int countks;
        fin >> countks;
        LoadObject(Ks, countks, fin);

        std::cout << "������ ������� ���������" << std::endl;
    }
    else {
        std::cout << "��������� ������. ���������� � ��������� ��� ���������� �����." << std::endl;
    }
    fin.close();

}

void GasNet::ChangePipe(std::unordered_set <int> res)
{
    std::string idInput;
    std::cout << "������� ID �������� ��� ��������� (����� ������): ";
    INPUT_LINE(std::cin, idInput);
    std::istringstream idStream(idInput);
    std::unordered_set<int> ids;
    int id;
    while (idStream >> id) {
        ids.emplace(id);
    }


    for (int id : ids) {
        if (res.find(id) == res.end()) {
            std::cout << "������ � ID " << id << " �� ������.\n";
            continue;
        }
        Pipes.at(id).changeofstate();
        std::cout << "������ � ID " << id << " ������� ��������\n";
    }

}

void GasNet::ChangeKS(std::unordered_set <int> res)
{
    std::string idInput;
    std::cout << "������� ID �������� ��� ��������� (����� ������): ";
    INPUT_LINE(std::cin, idInput);

    std::istringstream idStream(idInput);
    std::unordered_set<int> ids;
    int id;
    while (idStream >> id) {
        ids.emplace(id);
    }
    int change;
    std::cout << "������� ���������� ����� ";
    change = GetCorrectNumber(0, 100);

    for (int id : ids) {
        if (res.find(id) == res.end()) {
            std::cout << "������ � ID " << id << " �� ������.\n";
            continue;
        }

        if (Ks.at(id).UpdateWorkshopsInUse(change)) {
            std::cout << "������ � ID" << id << " ������� ��������\n";
        }
        else {
            std::cout << "������ � �������� ��������� �������" << std::endl;
        }
    }
}

std::unordered_map<int, Pipe>& GasNet::GetPipes()
{
    return Pipes;
}

std::unordered_map<int, KS>& GasNet::GetKS()
{
    return Ks;
}


static void topologicalSortUtil(int v, const std::vector<std::vector<int>>& adjMatrix, std::vector<bool>& visited, std::vector<int>& Stack) {
    visited[v] = true;


    for (size_t i = 0; i < adjMatrix.size(); ++i) {
        if (adjMatrix[v][i] && !visited[i]) {
            topologicalSortUtil(i, adjMatrix, visited, Stack);
        }
    }


    Stack.push_back(v + 1);
}


std::vector<int> GasNet::Sort() {
    if (!(this->CreateGraph())) {
        return std::vector<int>();
    }
    int n = Graph.size();
    std::vector<bool> visited(n, false);
    std::vector<int> Vector;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            topologicalSortUtil(i, Graph, visited, Vector);
        }
    }
    std::reverse(Vector.begin(), Vector.end());
    return Vector;
}


bool GasNet::Connect(int KSin, int KSout, int diameter)
{

    if (Ks.find(KSin) == Ks.end()) {
        return false;
    }

    if (Ks.find(KSout) == Ks.end()) {
        return false;
    }

    for (auto& i : Pipes) {
        if (i.second.GetDiameter() == diameter &&
            i.second.GetLeftKs() == 0
            && i.second.GetRightKs() == 0
            && i.second.Getstate()) {

            i.second.SetKs(KSin, KSout);

            return true;
        }
    }
    std::cout << "����� �� �������!" << std::endl;
    std::string name;
    std::cout << "������� ��� �����: ";
    INPUT_LINE(std::cin, name);
    std::cout << "������� ������ �����: ";
    int length = GetCorrectNumber(1, 10000);
    Pipe p(name, length, diameter, true, KSin, KSout);
    Pipes.emplace(p.GetId(), p);
    return true;

}

bool GasNet::CreateGraph() {
    Graph = std::vector<std::vector<int>>(Ks.size(), std::vector<int>(Ks.size()));
    int left = 0;
    int right = 0;
    bool flag = false;
    for (auto& i : Pipes) {
        left = i.second.GetLeftKs();
        right = i.second.GetRightKs();
        if (left != 0 && right != 0) {
            flag = true;
            Graph[left - 1][right - 1] = i.second.GetDiameter();
        }
    }
    return flag;
}

bool GasNet::Disconnect(int KSin, int KSout)
{
    for (auto& i : Pipes) {
        if (i.second.GetLeftKs() == KSin && i.second.GetRightKs() == KSout ||
            i.second.GetRightKs() == KSin && i.second.GetLeftKs() == KSout) {

            i.second.SetKs(0, 0);
            return true;
        }

    }
    return false;
}

int GasNet::IsInNet(int Ksid)
{
    for (auto& i : Pipes) {
        if (i.second.GetLeftKs() == Ksid ||
            i.second.GetRightKs() == Ksid) {
            return i.second.GetId();
        }
    }
    return 0;
}