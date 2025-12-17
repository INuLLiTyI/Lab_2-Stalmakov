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

    Pipe newPipe;
    cin >> newPipe;

    int newId = newPipe.GetId();
    pipes[newId] = newPipe;

    cout << "Pipe added successfully! ID: " << newId << "\n";
}

void addCompressorStation(unordered_map<int, CompressorStation>& stations) {
    cout << "\n=== Add New Compressor Station ===\n";

    CompressorStation newStation;
    cin >> newStation;

    int newId = newStation.GetId();
    stations[newId] = newStation;

    cout << "Compressor Station added successfully! ID: " << newId << "\n";
}

void viewAllObjects(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CompressorStation>& stations) {
    cout << "\n=== All Objects ===\n";

    if (pipes.empty() && stations.empty()) {
        cout << "No objects available.\n";
        return;
    }

    if (!pipes.empty()) {
        cout << "--- Pipes (" << pipes.size() << ") ---\n";
        for (const auto& [id, pipe] : pipes) {
            cout << "\nPipe ID: " << id << "\n";
            pipe.Print();
        }
    }

    if (!stations.empty()) {
        cout << "\n--- Compressor Stations (" << stations.size() << ") ---\n";
        for (const auto& [id, station] : stations) {
            cout << "\nCompressor Station ID: " << id << "\n";
            station.Print();
        }
    }
}

void saveToFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CompressorStation>& stations) {
    string filename;
    cout << "Enter filename: ";
    getline(cin >> ws, filename);
    logger.log(filename);

    ofstream out(filename);
    if (out) {
        out << pipes.size() << endl;
        for (const auto& [id, pipe] : pipes) {
            out << pipe << endl;
        }

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
    getline(cin >> ws, filename);
    logger.log(filename);

    ifstream in(filename);
    if (in) {
        pipes.clear();
        stations.clear();

        int pipeCount, stationCount;

        in >> pipeCount;
        for (int i = 0; i < pipeCount; i++) {
            Pipe pipe;
            in >> pipe;
            pipes[pipe.GetId()] = pipe;
        }

        in >> stationCount;
        for (int i = 0; i < stationCount; i++) {
            CompressorStation station;
            in >> station;
            stations[station.GetId()] = station;
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
    cout << "5. Delete Pipes\n";
    cout << "6. Delete Stations\n";
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
        getline(cin >> ws, name);
        logger.log(name);

        auto foundPipes = FindPipeFilter(pipes, checknamepipe, name);
        if (!foundPipes.empty()) {
            cout << "Found " << foundPipes.size() << " pipes\n";

            for (int id : foundPipes) {
                cout << "\nPipe ID " << id << ":\n";
                pipes.at(id).Print();

                char answer;
                cout << "Change repair status? (y/n): ";
                cin >> answer;
                logger.log(string(1, answer));

                if (answer == 'y' || answer == 'Y') {
                    pipes.at(id).changeofstate();
                    cout << "Pipe ID " << id << " status changed.\n";
                }
            }
        }
        else {
            cout << "No pipes found with name: " << name << endl;
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
        logger.log(to_string(status));

        auto foundPipes = FindPipeFilter(pipes, checkstate, status);
        if (!foundPipes.empty()) {
            cout << "Found " << foundPipes.size() << " pipes\n";

            for (int id : foundPipes) {
                cout << "\nPipe ID " << id << ":\n";
                pipes.at(id).Print();

                char answer;
                cout << "Change repair status? (y/n): ";
                cin >> answer;
                logger.log(string(1, answer));

                if (answer == 'y' || answer == 'Y') {
                    pipes.at(id).changeofstate();
                    cout << "Pipe ID " << id << " status changed.\n";
                }
            }
        }
        else {
            cout << "No pipes found with specified status\n";
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
        getline(cin >> ws, name);
        logger.log(name);

        auto foundStations = FindKSFilter(stations, checknameks, name);
        if (!foundStations.empty()) {
            cout << "Found " << foundStations.size() << " stations\n";

            for (int id : foundStations) {
                cout << "\nStation ID " << id << ":\n";
                stations.at(id).Print();

                char answer;
                cout << "Change number of working workshops? (y/n): ";
                cin >> answer;
                logger.log(string(1, answer));

                if (answer == 'y' || answer == 'Y') {
                    int change;
                    cout << "Enter new number of working workshops (current: "
                        << stations.at(id).GetWorkshopsInUse() << "): ";
                    cin >> change;
                    logger.log(to_string(change));

                    if (stations.at(id).UpdateWorkshopsInUse(change - stations.at(id).GetWorkshopsInUse())) {
                        cout << "Station ID " << id << " workshops updated to " << change << ".\n";
                    }
                    else {
                        cout << "Invalid number! Must be between 0 and "
                            << stations.at(id).GetWorkshops() << ".\n";
                    }
                }
            }
        }
        else {
            cout << "No stations found with name: " << name << endl;
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
        logger.log(to_string(minWorkshops));

        auto foundStations = FindKSFilter(stations, workshops, minWorkshops);
        if (!foundStations.empty()) {
            cout << "Found " << foundStations.size() << " stations\n";

            for (int id : foundStations) {
                cout << "\nStation ID " << id << ":\n";
                stations.at(id).Print();

                char answer;
                cout << "Change number of working workshops? (y/n): ";
                cin >> answer;
                logger.log(string(1, answer));

                if (answer == 'y' || answer == 'Y') {
                    int change;
                    cout << "Enter new number of working workshops (current: "
                        << stations.at(id).GetWorkshopsInUse() << "): ";
                    cin >> change;
                    logger.log(to_string(change));

                    if (stations.at(id).UpdateWorkshopsInUse(change - stations.at(id).GetWorkshopsInUse())) {
                        cout << "Station ID " << id << " workshops updated to " << change << ".\n";
                    }
                    else {
                        cout << "Invalid number! Must be between 0 and "
                            << stations.at(id).GetWorkshops() << ".\n";
                    }
                }
            }
        }
        else {
            cout << "No stations found with " << minWorkshops << " or more workshops\n";
        }
        break;
    }
    case 5: {
        if (pipes.empty()) {
            cout << "No pipes available.\n";
            break;
        }
        cout << "All pipes:\n";
        for (const auto& [id, pipe] : pipes) {
            cout << "ID: " << id << " - Name: " << pipe.GetName() << endl;
        }

        string ids;
        cout << "Enter pipe IDs to delete (space separated): ";
        getline(cin >> ws, ids);
        logger.log("Delete pipes: " + ids);

        istringstream idStream(ids);
        int id;
        int deletedCount = 0;

        while (idStream >> id) {
            auto it = pipes.find(id);
            if (it != pipes.end()) {
                pipes.erase(it);
                cout << "Pipe ID " << id << " deleted.\n";
                deletedCount++;
            }
            else {
                cout << "Pipe ID " << id << " not found.\n";
            }
        }

        cout << "Deleted " << deletedCount << " pipes.\n";
        break;
    }
    case 6: {
        if (stations.empty()) {
            cout << "No compressor stations available.\n";
            break;
        }
        cout << "All stations:\n";
        for (const auto& [id, station] : stations) {
            cout << "ID: " << id << " - Name: " << station.GetName() << endl;
        }

        string ids;
        cout << "Enter station IDs to delete (space separated): ";
        getline(cin >> ws, ids);
        logger.log("Delete stations: " + ids);

        istringstream idStream(ids);
        int id;
        int deletedCount = 0;

        while (idStream >> id) {
            auto it = stations.find(id);
            if (it != stations.end()) {
                stations.erase(it);
                cout << "Station ID " << id << " deleted.\n";
                deletedCount++;
            }
            else {
                cout << "Station ID " << id << " not found.\n";
            }
        }

        cout << "Deleted " << deletedCount << " stations.\n";
        break;
    }
    case 0:
        return;
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
        logger.log(to_string(choice));

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