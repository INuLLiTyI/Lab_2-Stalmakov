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
#include "InOut.h"

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

    // Генерация ID
    int newId = Pipe::GetMaxId() + 1;
    Pipe newPipe;
    newPipe.SetName(name);
    newPipe.SetLength(length);
    newPipe.SetDiameter(diameter);
    newPipe.SetInRepair(false);

    pipes[newId] = newPipe;

    cout << "Pipe added successfully! ID: " << newId << "\n";
    logger.log("Added pipe ID: " + to_string(newId) + ", Name: " + name);
}

void addCompressorStation(unordered_map<int, CompressorStation>& stations) {
    cout << "\n=== Add New Compressor Station ===\n";

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

    // Генерация ID
    int newId = CompressorStation::GetMaxId() + 1;
    CompressorStation newStation;
    newStation.SetName(name);
    newStation.SetWorkshops(totalWorkshops, workingWorkshops);
    newStation.SetEfficiency(efficiency);

    stations[newId] = newStation;

    cout << "Compressor Station added successfully! ID: " << newId << "\n";
    logger.log("Added compressor station ID: " + to_string(newId) + ", Name: " + name);
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
    logger.log("Viewed all objects");
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
        logger.log("Saved data to file: " + filename);
    }
    else {
        cout << "Error saving data to " << filename << "!\n";
        logger.log("Error saving to file: " + filename);
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
            pipes[pipe.GetId()] = pipe; // Сохраняем с оригинальным ID
        }

        // Загружаем станции
        in >> stationCount;
        for (int i = 0; i < stationCount; i++) {
            CompressorStation station;
            in >> station;
            stations[station.GetId()] = station; // Сохраняем с оригинальным ID
        }

        cout << "Data loaded successfully from " << filename << "!\n";
        logger.log("Loaded data from file: " + filename);
    }
    else {
        cout << "File " << filename << " not found!\n";
        logger.log("File not found: " + filename);
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

        auto foundPipes = FindPipeFilter(pipes, checknamepipe, name);
        if (!foundPipes.empty()) {
            cout << "Found " << foundPipes.size() << " pipes\n";
            ChangePipe(pipes, foundPipes);
            logger.log("Searched pipes by name: " + name + ", found: " + to_string(foundPipes.size()));
        }
        else {
            cout << "No pipes found with name: " << name << endl;
            logger.log("Searched pipes by name: " + name + ", found: 0");
        }
        break;
    }
    case 2: {
        if (pipes.empty()) {
            cout << "No pipes available.\n";
            break;
        }
        cout << "Search pipes by repair status (0 - working, 1 - in repair): ";
        bool status;
        cin >> status;

        auto foundPipes = FindPipeFilter(pipes, checkstate, status);
        if (!foundPipes.empty()) {
            cout << "Found " << foundPipes.size() << " pipes\n";
            ChangePipe(pipes, foundPipes);
            logger.log("Searched pipes by status: " + to_string(status) + ", found: " + to_string(foundPipes.size()));
        }
        else {
            cout << "No pipes found with specified status\n";
            logger.log("Searched pipes by status: " + to_string(status) + ", found: 0");
        }
        break;
    }
    case 3: {
        if (stations.empty()) {
            cout << "No compressor stations available.\n";
            break;
        }
        string name;
        cout << "Enter station name to search: ";
        clearInput();
        getline(cin, name);

        auto foundStations = FindKSFilter(stations, checknameks, name);
        if (!foundStations.empty()) {
            cout << "Found " << foundStations.size() << " stations\n";
            ChangeKS(stations, foundStations);
            logger.log("Searched stations by name: " + name + ", found: " + to_string(foundStations.size()));
        }
        else {
            cout << "No stations found with name: " << name << endl;
            logger.log("Searched stations by name: " + name + ", found: 0");
        }
        break;
    }
    case 4: {
        if (stations.empty()) {
            cout << "No compressor stations available.\n";
            break;
        }
        cout << "Enter minimum number of workshops: ";
        int minWorkshops;
        cin >> minWorkshops;

        auto foundStations = FindKSFilter(stations, workshops, minWorkshops);
        if (!foundStations.empty()) {
            cout << "Found " << foundStations.size() << " stations\n";
            ChangeKS(stations, foundStations);
            logger.log("Searched stations by workshops >= " + to_string(minWorkshops) + ", found: " + to_string(foundStations.size()));
        }
        else {
            cout << "No stations found with " << minWorkshops << " or more workshops\n";
            logger.log("Searched stations by workshops >= " + to_string(minWorkshops) + ", found: 0");
        }
        break;
    }
    case 0:
        return;
    default:
        cout << "Invalid choice!\n";
        logger.log("Invalid search choice: " + to_string(choice));
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
            logger.log("Application exited by user");
            return 0;
        default:
            cout << "Invalid choice! Please try again.\n";
            logger.log("Invalid menu choice: " + to_string(choice));
            break;
        }
    }
}