#include <cmath>
#include "pipe.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Tools.h"
using namespace std;

int Pipe::maxId = 0;

Pipe::Pipe() {
    id = 0;
    name = "";
    length = 0.0f;
    diameter = 0;
    inRepair = false;
}

Pipe::Pipe(const string& name, float length, int diameter, bool inRepair) {
    id = ++maxId;
    this->name = name;
    this->length = length;
    this->diameter = diameter;
    this->inRepair = inRepair;
}

int Pipe::GetId() const { return id; }
int Pipe::GetMaxId() { return maxId; }
void Pipe::SetMaxId(int newMaxId) { maxId = newMaxId; }
string Pipe::GetName() const { return name; }
bool Pipe::GetState() const { return inRepair; }
float Pipe::GetLength() const { return length; }
int Pipe::GetDiameter() const { return diameter; }

void Pipe::changeofstate() {
    inRepair = !inRepair;
}

void Pipe::Edit() {
    cout << "Edit pipe (current repair status: " << (inRepair ? "in repair" : "working") << "):\n";
    cout << "Set repair status (0 - working, 1 - in repair): ";
    int status;
    cin >> status;
    cerr << status << endl;

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
    cout << "Name: " << name << endl;
    cout << fixed << setprecision(2);
    cout << "Length: " << length << " km" << endl;
    cout << "Diameter: " << diameter << " mm" << endl;
    cout << "Status: " << (inRepair ? "In repair" : "Operational") << endl;
}

ostream& operator<<(ostream& out, const Pipe& pipe) {
    out << pipe.id << endl;
    out << pipe.name << endl;
    out << fixed << setprecision(6);
    out << pipe.length << endl;
    out << pipe.diameter << endl;
    out << pipe.inRepair << endl;
    return out;
}

istream& operator>>(istream& in, Pipe& pipe) {
    string name;
    float length;
    int diameter;

    cout << "Enter pipe name: ";
    INPUT_LINE(in, name);

    cout << "Enter length (km): ";
    while (!(in >> length) || length <= 0) {
        cout << "Invalid input! Enter positive number: ";
        in.clear();
        in.ignore(10000, '\n');
    }
    cerr << length << endl;

    cout << "Enter diameter (mm): ";
    while (!(in >> diameter) || diameter <= 0) {
        cout << "Invalid input! Enter positive number: ";
        in.clear();
        in.ignore(10000, '\n');
    }
    cerr << diameter << endl;

    pipe.id = ++Pipe::maxId;
    pipe.name = name;
    pipe.length = length;
    pipe.diameter = diameter;
    pipe.inRepair = false;

    return in;
}

ifstream& operator>>(ifstream& fin, Pipe& p) {
    int id;
    string name;
    float length;
    int diameter;
    bool inRepair;

    fin >> id;
    getline(fin >> ws, name);
    fin >> length;
    fin >> diameter;
    fin >> inRepair;

    p.id = id;
    p.name = name;
    p.length = length;
    p.diameter = diameter;
    p.inRepair = inRepair;

    Pipe::maxId = max(Pipe::maxId, id);

    return fin;
}

ofstream& operator<<(ofstream& fout, const Pipe& p) {
    fout << p.id << endl
        << p.name << endl
        << p.length << endl
        << p.diameter << endl
        << p.inRepair << endl;
    return fout;
}