#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <string>
#include "pipe.h"
#include "Compressor_station.h"
#include "Tools.h"

using namespace std;

// Объявления функций
void printMenu();
void clearInput();
void addPipe(unordered_map<int, Pipe>& pipes);
void addCompressorStation(unordered_map<int, CompressorStation>& stations);
void viewAllObjects(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CompressorStation>& stations);
void saveToFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CompressorStation>& stations);
void loadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, CompressorStation>& stations);
void searchAndEdit(unordered_map<int, Pipe>& pipes, unordered_map<int, CompressorStation>& stations);

// Вспомогательные функции для поиска
template<typename T>
unordered_set<int> findPipesByFilter(const unordered_map<int, Pipe>& pipes, bool(*filter)(const Pipe&, T), T param);
template<typename T>
unordered_set<int> findStationsByFilter(const unordered_map<int, CompressorStation>& stations, bool(*filter)(const CompressorStation&, T), T param);

void printMenu() {
    cout << "\n=== Pipeline Management System ===\n";
    cout << "1. Add Pipe\n";
    cout << "2. Add Compressor Station\n";
    cout << "3. View all objects\n";
    cout << "4. Search and Edit\n";
    cout << "5. Save\n";
    cout << "6. Load\n";
    cout << "0. Exit\n";
    cout << "Choose option: ";
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void addPipe(unordered_map<int, Pipe>& pipes) {
    cout << "\n=== Add New Pipe ===\n";

    Pipe newPipe;
    string name;
    float length;
    int diameter;

    cout << "Enter pipe name: ";
    clearInput();
    getline(cin, name);

    cout << "Enter length (km): ";
    while (!(cin >> length) || length <= 0) {
        cout << "Invalid input! Enter positive number: ";
        clearInput();
    }

    cout << "Enter diameter (mm): ";
    while (!(cin >> diameter) || diameter <= 0) {
        cout << "Invalid input! Enter positive number: ";
        clearInput();
    }

    newPipe.SetName(name);
    newPipe.SetLength(length);
    newPipe.SetDiameter(diameter);
    newPipe.SetInRepair(false);

    // Генерация ID (можно улучшить)
    static int nextPipeId = 1;
    pipes[nextPipeId] = newPipe;

    cout << "Pipe added successfully! ID: " << nextPipeId << "\n";
    nextPipeId++;
}

void addCompressorStation(unordered_map<int, CompressorStation>& stations) {
    cout << "\n=== Add New Compressor Station ===\n";

    CompressorStation newStation;
    string name;
    int totalWorkshops, workingWorkshops, efficiency;

    cout << "Enter station name: ";
    clearInput();
    getline(cin, name);

    cout << "Enter total number of workshops: ";
    while (!(cin >> totalWorkshops) || totalWorkshops <= 0) {
        cout << "Invalid input! Enter positive number: ";
        clearInput();
    }

    cout << "Enter number of working workshops: ";
    while (!(cin >> workingWorkshops) || workingWorkshops < 0 || workingWorkshops > totalWorkshops) {
        cout << "Invalid input! Enter number between 0 and " << totalWorkshops << ": ";
        clearInput();
    }

    cout << "Enter efficiency level: ";
    while (!(cin >> efficiency) || efficiency <= 0) {
        cout << "Invalid input! Enter positive number: ";
        clearInput();
    }

    newStation.SetName(name);
    newStation.SetWorkshops(totalWorkshops, workingWorkshops);
    newStation.SetEfficiency(efficiency);

    // Генерация ID
    static int nextStationId = 1;
    stations[nextStationId] = newStation;

    cout << "Compressor Station added successfully! ID: " << nextStationId << "\n";
    nextStationId++;
}

void viewAllObjects(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CompressorStation>& stations) {
    cout << "\n=== All Objects ===\n";

    if (pipes.empty()) {
        cout << "No pipes available.\n";
    }
    else {
        cout << "--- Pipes (" << pipes.size() << ") ---\n";
        for (const auto& [id, pipe] : pipes) {
            cout << "ID: " << id << " - ";
            pipe.Print();
        }
    }

    if (stations.empty()) {
        cout << "No compressor stations available.\n";
    }
    else {
        cout << "\n--- Compressor Stations (" << stations.size() << ") ---\n";
        for (const auto& [id, station] : stations) {
            cout << "ID: " << id << " - ";
            station.Print();
        }
    }
}

void saveToFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CompressorStation>& stations) {
    string filename;
    cout << "Enter filename: ";
    clearInput();
    getline(cin, filename);

    ofstream out(filename);
    if (out) {
        // Сохраняем количество труб
        out << pipes.size() << endl;
        for (const auto& [id, pipe] : pipes) {
            out << pipe << endl;
        }

        // Сохраняем количество станций
        out << stations.size() << endl;
        for (const auto& [id, station] : stations) {
            out << station << endl;
        }

        cout << "Data saved successfully to " << filename << "!\n";
    }
    else {
        cout << "Error saving data to " << filename << "!\n";
    }
}

void loadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, CompressorStation>& stations) {
    string filename;
    cout << "Enter filename: ";
    clearInput();
    getline(cin, filename);

    ifstream in(filename);
    if (in) {
        pipes.clear();
        stations.clear();

        int pipeCount, stationCount;

        // Загружаем трубы
        in >> pipeCount;
        for (int i = 0; i < pipeCount; i++) {
            Pipe pipe;
            in >> pipe;
            // Здесь нужно получить ID из pipe или генерировать новый
            static int nextId = 1;
            pipes[nextId++] = pipe;
        }

        // Загружаем станции
        in >> stationCount;
        for (int i = 0; i < stationCount; i++) {
            CompressorStation station;
            in >> station;
            static int nextId = 1;
            stations[nextId++] = station;
        }

        cout << "Data loaded successfully from " << filename << "!\n";
    }
    else {
        cout << "File " << filename << " not found!\n";
    }
}

void searchAndEdit(unordered_map<int, Pipe>& pipes, unordered_map<int, CompressorStation>& stations) {
    int choice;
    cout << "\n=== Search and Edit ===\n";
    cout << "1. Search Pipes by Name\n";
    cout << "2. Search Pipes by Repair Status\n";
    cout << "3. Search Stations by Name\n";
    cout << "4. Search Stations by Workshop Count\n";
    cout << "0. Back to Main Menu\n";
    cout << "Choose option: ";

    cin >> choice;

    switch (choice) {
    case 1: {
        if (pipes.empty()) {
            cout << "No pipes available.\n";
            break;
        }
        string name;
        cout << "Enter pipe name to search: ";
        clearInput();
        getline(cin, name);

        // Здесь должна быть реализация поиска по имени
        // и дальнейшее редактирование/удаление
        break;
    }
          // Аналогично для других случаев поиска
    default:
        cout << "Invalid choice!\n";
    }
}

int main() {
    unordered_map<int, Pipe> pipes;
    unordered_map<int, CompressorStation> stations;
    int choice;

    while (true) {
        printMenu();

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            addPipe(pipes);
            break;
        case 2:
            addCompressorStation(stations);
            break;
        case 3:
            viewAllObjects(pipes, stations);
            break;
        case 4:
            searchAndEdit(pipes, stations);
            break;
        case 5:
            saveToFile(pipes, stations);
            break;
        case 6:
            loadFromFile(pipes, stations);
            break;
        case 0:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }
    }
}