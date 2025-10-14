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
<<<<<<< HEAD
    Name = "None";
    Length = 0.0f;
    Diameter = 0;
    InRepair = false;
=======
    name = "None";
    length = 0.0f;
    diameter = 0;
    inRepair = false;
>>>>>>> 3323d9974e07d2145f6e6e28374ffa222fb0faf7
    connectedStationId = 0;
}

int Pipe::GetId() const { return id; }
int Pipe::GetMaxId() { return maxId; }
<<<<<<< HEAD
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
=======
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
>>>>>>> 3323d9974e07d2145f6e6e28374ffa222fb0faf7
}

void Pipe::Disconnect() {
    connectedStationId = 0;
<<<<<<< HEAD
    InRepair = true;
}

void Pipe::changeofstate() {
    InRepair = !InRepair;
}

void Pipe::Edit() {
    cout << "Edit pipe (current repair status: " << (InRepair ? "in repair" : "working") << "):\n";
=======
    inRepair = true;
}

void Pipe::changeofstate() {
    inRepair = !inRepair;
}

void Pipe::Edit() {
    cout << "Edit pipe (current repair status: " << (inRepair ? "in repair" : "working") << "):\n";
>>>>>>> 3323d9974e07d2145f6e6e28374ffa222fb0faf7
    cout << "Set repair status (0 - working, 1 - in repair): ";
    int status;
    cin >> status;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Status unchanged.\n";
    }
    else {
<<<<<<< HEAD
        InRepair = (status == 1);
=======
        inRepair = (status == 1);
>>>>>>> 3323d9974e07d2145f6e6e28374ffa222fb0faf7
    }
}

void Pipe::Print() const {
    cout << "Pipe ID: " << id << endl;
<<<<<<< HEAD
    cout << "Name: " << Name << endl;
    cout << fixed << setprecision(2);
    cout << "Length: " << Length << " km" << endl;
    cout << "Diameter: " << Diameter << " mm" << endl;
    cout << "Status: " << (InRepair ? "In repair" : "Operational") << endl;
=======
    cout << "Name: " << name << endl;
    cout << fixed << setprecision(2);
    cout << "Length: " << length << " km" << endl;
    cout << "Diameter: " << diameter << " mm" << endl;
    cout << "Status: " << (inRepair ? "In repair" : "Operational") << endl;
>>>>>>> 3323d9974e07d2145f6e6e28374ffa222fb0faf7
    cout << "Connected: " << (IsConnected() ? "True" : "False") << endl;
}

ostream& operator<<(ostream& out, const Pipe& pipe) {
    out << pipe.id << endl;
<<<<<<< HEAD
    out << pipe.Name << endl;
    out << fixed << setprecision(6);
    out << pipe.Length << endl;
    out << pipe.Diameter << endl;
    out << pipe.InRepair << endl;
=======
    out << pipe.name << endl;
    out << fixed << setprecision(6);
    out << pipe.length << endl;
    out << pipe.diameter << endl;
    out << pipe.inRepair << endl;
>>>>>>> 3323d9974e07d2145f6e6e28374ffa222fb0faf7
    out << pipe.connectedStationId << endl;
    return out;
}

istream& operator>>(istream& in, Pipe& pipe) {
    in >> pipe.id;
    in.ignore();
<<<<<<< HEAD
    getline(in, pipe.Name);
    in >> pipe.Length >> pipe.Diameter >> pipe.InRepair >> pipe.connectedStationId;
=======
    getline(in, pipe.name);
    in >> pipe.length >> pipe.diameter >> pipe.inRepair >> pipe.connectedStationId;
>>>>>>> 3323d9974e07d2145f6e6e28374ffa222fb0faf7
    return in;
}

ifstream& operator>>(ifstream& fin, Pipe& p) {
    fin >> p.id;
    fin >> std::ws;
<<<<<<< HEAD
    getline(fin, p.Name);
    fin >> p.Length;
    fin >> p.Diameter;
    fin >> p.InRepair;
=======
    getline(fin, p.name);
    fin >> p.length;
    fin >> p.diameter;
    fin >> p.inRepair;
>>>>>>> 3323d9974e07d2145f6e6e28374ffa222fb0faf7
    fin >> p.connectedStationId;
    if (p.id > p.maxId) {
        p.maxId = p.id;
    }
    return fin;
}

ofstream& operator<<(ofstream& fout, const Pipe& p) {
    fout << p.id << endl
<<<<<<< HEAD
        << p.Name << endl
        << p.Length << endl
        << p.Diameter << endl
        << p.InRepair << endl
=======
        << p.name << endl
        << p.length << endl
        << p.diameter << endl
        << p.inRepair << endl
>>>>>>> 3323d9974e07d2145f6e6e28374ffa222fb0faf7
        << p.connectedStationId << endl;
    return fout;
}