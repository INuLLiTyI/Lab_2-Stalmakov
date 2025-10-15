#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <istream>

class Pipe {
private:
    static int maxId;
    int id;
    std::string name;
    float length;
    int diameter;
    bool inRepair;
    int connectedStationId;

public:
    Pipe();

    // Getters
    int GetId() const;
    static int GetMaxId();
    std::string GetName() const;
    bool GetState() const;
    float GetLength() const;
    int GetDiameter() const;
    bool IsConnected() const;
    int GetConnectedStationId() const;

    // Setters
    void SetName(const std::string& name);
    void SetLength(float length);
    void SetDiameter(int diameter);
    void SetInRepair(bool inRepair);
    void ConnectToStation(int stationId);
    void Disconnect();

    void changeofstate();
    void Edit();
    void Print() const;

    // Friend functions for I/O
    friend std::ostream& operator<<(std::ostream& out, const Pipe& pipe);
    friend std::istream& operator>>(std::istream& in, Pipe& pipe);
    friend std::ifstream& operator>>(std::ifstream& fin, Pipe& p);
    friend std::ofstream& operator<<(std::ofstream& fout, const Pipe& p);
};