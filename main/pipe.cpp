#include <cmath>
#include "pipe.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Tools.h"
using namespace std;

int Pipe::maxId = 0;

Pipe::Pipe()
{
    id = ++maxId;
    name = "None";
    length = 0.0f;
    diameter = 0;
    inRepair = false;
    connectedStationId = 0;
}

int Pipe::GetId() const { return id; }
int Pipe::GetMaxId() { return maxId; }
string Pipe::GetName() const { return name; }
bool Pipe::GetState() const { return inRepair; }
float Pipe::GetLength() const { return length; }
int Pipe::GetDiameter() const { return diameter; }
bool Pipe::IsConnected() const { return connectedStationId != 0; }
int Pipe::GetConnectedStationId() const { return connectedStationId; }

void Pipe::SetName(const string& newName) { name = newName; }
void Pipe::SetLength(float newLength) { length = newLength; }
void Pipe::SetDiameter(int newDiameter) { diameter = newDiameter; }
void Pipe::SetInRepair(bool repairStatus) { inRepair = repairStatus; }

void Pipe::ConnectToStation(int stationId) {
    connectedStationId = stationId;
    inRepair = false;
}

void Pipe::Disconnect() {
    connectedStationId = 0;
    inRepair = true;
}

void Pipe::changeofstate() {
    inRepair = !inRepair;
}

void Pipe::Edit() {
    cout << "Edit pipe (current repair status: " << (inRepair ? "in repair" : "working") << "):\n";
    cout << "Set repair status (0 - working, 1 - in repair): ";
    int status;
    cin >> status;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Status unchanged.\n";
    }
    else {
        inRepair = (status == 1);
    }
}

void Pipe::Print() const {
    cout << "Pipe ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << fixed << setprecision(2);
    cout << "Length: " << length << " km" << endl;
    cout << "Diameter: " << diameter << " mm" << endl;
    cout << "Status: " << (inRepair ? "In repair" : "Operational") << endl;
    cout << "Connected: " << (IsConnected() ? "True" : "False") << endl;
}

ostream& operator<<(ostream& out, const Pipe& pipe) {
    out << pipe.id << endl;
    out << pipe.name << endl;
    out << fixed << setprecision(6);
    out << pipe.length << endl;
    out << pipe.diameter << endl;
    out << pipe.inRepair << endl;
    out << pipe.connectedStationId << endl;
    return out;
}

istream& operator>>(istream& in, Pipe& pipe) {
    in >> pipe.id;
    in.ignore();
    getline(in, pipe.name);
    in >> pipe.length >> pipe.diameter >> pipe.inRepair >> pipe.connectedStationId;
    return in;
}

ifstream& operator>>(ifstream& fin, Pipe& p) {
    fin >> p.id;
    fin >> std::ws;
    getline(fin, p.name);
    fin >> p.length;
    fin >> p.diameter;
    fin >> p.inRepair;
    fin >> p.connectedStationId;
    if (p.id > p.maxId) {
        p.maxId = p.id;
    }
    return fin;
}

ofstream& operator<<(ofstream& fout, const Pipe& p) {
    fout << p.id << endl
        << p.name << endl
        << p.length << endl
        << p.diameter << endl
        << p.inRepair << endl
        << p.connectedStationId << endl;
    return fout;
}