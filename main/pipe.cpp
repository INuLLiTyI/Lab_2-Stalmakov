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
    Name = "None";
    Length = 0.0f;
    Diameter = 0;
    InRepair = false;
    connectedStationId = 0;
}

int Pipe::GetId() const { return id; }
int Pipe::GetMaxId() { return maxId; }
string Pipe::GetName() const { return Name; }
bool Pipe::GetState() const { return InRepair; }
float Pipe::GetLength() const { return Length; }
int Pipe::GetDiameter() const { return Diameter; }
bool Pipe::IsConnected() const { return connectedStationId != 0; }
int Pipe::GetConnectedStationId() const { return connectedStationId; }

void Pipe::SetName(const string& name) { Name = name; }
void Pipe::SetLength(float length) { Length = length; }
void Pipe::SetDiameter(int diameter) { Diameter = diameter; }
void Pipe::SetInRepair(bool inRepair) { InRepair = inRepair; }

void Pipe::ConnectToStation(int stationId) {
    connectedStationId = stationId;
    InRepair = false;
}

void Pipe::Disconnect() {
    connectedStationId = 0;
    InRepair = true;
}

void Pipe::changeofstate() {
    InRepair = !InRepair;
}

void Pipe::Edit() {
    cout << "Edit pipe (current repair status: " << (InRepair ? "in repair" : "working") << "):\n";
    cout << "Set repair status (0 - working, 1 - in repair): ";
    int status;
    cin >> status;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Status unchanged.\n";
    }
    else {
        InRepair = (status == 1);
    }
}

void Pipe::Print() const {
    cout << "Pipe ID: " << id << endl;
    cout << "Name: " << Name << endl;
    cout << fixed << setprecision(2);
    cout << "Length: " << Length << " km" << endl;
    cout << "Diameter: " << Diameter << " mm" << endl;
    cout << "Status: " << (InRepair ? "In repair" : "Operational") << endl;
    cout << "Connected: " << (IsConnected() ? "True" : "False") << endl;
}

ostream& operator<<(ostream& out, const Pipe& pipe) {
    out << pipe.id << endl;
    out << pipe.Name << endl;
    out << fixed << setprecision(6);
    out << pipe.Length << endl;
    out << pipe.Diameter << endl;
    out << pipe.InRepair << endl;
    out << pipe.connectedStationId << endl;
    return out;
}

istream& operator>>(istream& in, Pipe& pipe) {
    in >> pipe.id;
    in.ignore();
    getline(in, pipe.Name);
    in >> pipe.Length >> pipe.Diameter >> pipe.InRepair >> pipe.connectedStationId;
    return in;
}

ifstream& operator>>(ifstream& fin, Pipe& p) {
    fin >> p.id;
    fin >> std::ws;
    getline(fin, p.Name);
    fin >> p.Length;
    fin >> p.Diameter;
    fin >> p.InRepair;
    fin >> p.connectedStationId;
    if (p.id > p.maxId) {
        p.maxId = p.id;
    }
    return fin;
}

ofstream& operator<<(ofstream& fout, const Pipe& p) {
    fout << p.id << endl
        << p.Name << endl
        << p.Length << endl
        << p.Diameter << endl
        << p.InRepair << endl
        << p.connectedStationId << endl;
    return fout;
}