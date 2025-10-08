#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <unordered_map>

class Pipe {
private:
    static int maxId;
    int id;
    std::string Name;
    float Length;
    int Diameter;
    bool InRepair;
    int connectedStationId;

public:
    Pipe();

    // Getters
    int GetId() const;
    static int GetMaxId();
    std::string GetName() const;
    bool GetStatement() const;
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

    void Edit();
    void Print() const;

    // Friend functions for I/O
    friend std::ostream& operator<<(std::ostream& out, const Pipe& pipe);
    friend std::istream& operator>>(std::istream& in, Pipe& pipe);
};