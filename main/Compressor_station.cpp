#include "Compressor_station.h"
#include <iostream>
#include <fstream>
#include "Tools.h"
using namespace std;

int CompressorStation::maxId = 0;

CompressorStation::CompressorStation()
{
    id = ++maxId;
    Name = "None";
    AmountOfWorkshops = 0;
    WorkshopsInWork = 0;
    EfficiencyLevel = 0;
}


int CompressorStation::GetId() const { return id; }
int CompressorStation::GetMaxId() { return maxId; }
string CompressorStation::GetName() const { return Name; }
int CompressorStation::GetWorkshops() const { return AmountOfWorkshops; }
int CompressorStation::GetWorkshopsInUse() const { return WorkshopsInWork; }
int CompressorStation::GetPercent() const {
    return (AmountOfWorkshops > 0) ? (WorkshopsInWork * 100 / AmountOfWorkshops) : 0;
}

void CompressorStation::SetName(const string& name) { Name = name; }
void CompressorStation::SetWorkshops(int total, int working) {
    AmountOfWorkshops = total;
    WorkshopsInWork = working;
}
void CompressorStation::SetEfficiency(int efficiency) { EfficiencyLevel = efficiency; }

void CompressorStation::StartWorkshop() {
    if (WorkshopsInWork < AmountOfWorkshops) {
        WorkshopsInWork++;
        cout << "Workshop started. Now working: " << WorkshopsInWork << "/" << AmountOfWorkshops << endl;
    }
    else {
        cout << "All workshops are already working!\n";
    }
}

void CompressorStation::StopWorkshop() {
    if (WorkshopsInWork > 0) {
        WorkshopsInWork--;
        cout << "Workshop stopped. Now working: " << WorkshopsInWork << "/" << AmountOfWorkshops << endl;
    }
    else {
        cout << "No workshops are working!\n";
    }
}

bool CompressorStation::UpdateWorkshopsInUse(int change) {
    int new_workshops_work = WorkshopsInWork + change;
    if (new_workshops_work >= 0 && new_workshops_work <= AmountOfWorkshops) {
        WorkshopsInWork = new_workshops_work;
        return true;
    }
    else {
        cout << "Error: number of working workshops must be between 0 and " << AmountOfWorkshops << ".\n";
        return false;
    }
}

void CompressorStation::Print() const {
    cout << "Compressor Station ID: " << id << endl;
    cout << "Name: " << Name << endl;
    cout << "Workshops: " << WorkshopsInWork << "/" << AmountOfWorkshops << " working" << endl;
    cout << "Efficiency Level: " << EfficiencyLevel << endl;
    cout << "Utilization: " << GetPercent() << "%" << endl;
}

ostream& operator<<(ostream& out, const CompressorStation& cs) {
    out << cs.id << endl;
    out << cs.Name << endl;
    out << cs.AmountOfWorkshops << endl;
    out << cs.WorkshopsInWork << endl;
    out << cs.EfficiencyLevel << endl;
    return out;
}

istream& operator>>(istream& in, CompressorStation& cs) {
    in >> cs.id;
    in.ignore();
    getline(in, cs.Name);
    in >> cs.AmountOfWorkshops >> cs.WorkshopsInWork >> cs.EfficiencyLevel;
    return in;
}

ifstream& operator>>(ifstream& fin, CompressorStation& g) {
    fin >> g.id;
    fin >> ws;
    getline(fin, g.Name);
    fin >> g.AmountOfWorkshops;
    fin >> g.WorkshopsInWork;
    fin >> g.EfficiencyLevel;
    if (g.id > g.maxId) {
        g.maxId = g.id;
    }
    return fin;
}

ofstream& operator<<(ofstream& fout, const CompressorStation& g) {
    fout << g.id << endl << g.Name << endl << g.AmountOfWorkshops << endl << g.WorkshopsInWork << endl << g.EfficiencyLevel << endl;
    return fout;
}