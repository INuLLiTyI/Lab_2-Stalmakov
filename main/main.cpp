#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include "pipe.h"
#include "Compressor_Station.h"

using namespace std;

void printMenu();
void clearInput();
void addPipe(Pipe& pipe);
void addCompressorStation(CompressorStation& cs);
void connectPipeToStation(Pipe& pipe, CompressorStation& cs);
void clearDataFile(Pipe& pipe, CompressorStation& cs);

void printMenu() {
    cout << "\n=== Pipeline Management System ===\n";
    cout << "1. Add Pipe\n";
    cout << "2. Add Compressor Station\n";
    cout << "3. View all objects\n";
    cout << "4. Edit Pipe\n";
    cout << "5. Edit Compressor Station\n";
    cout << "6. Save\n";
    cout << "7. Load\n";
    cout << "8. Connect Pipe to Station\n";
    cout << "9. Disconnect Pipe\n";
    cout << "10. Clear File\n";
    cout << "0. Exit\n";
    cout << "Choose option: ";
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void addPipe(Pipe& pipe) {
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

    pipe.SetName(name);
    pipe.SetLength(length);
    pipe.SetDiameter(diameter);
    pipe.SetInRepair(false);

    cout << "Pipe added successfully!\n";
}

void addCompressorStation(CompressorStation& cs) {
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

    cs.SetName(name);
    cs.SetWorkshops(totalWorkshops, workingWorkshops);
    cs.SetEfficiency(efficiency);

    cout << "Compressor Station added successfully!\n";
}

void connectPipeToStation(Pipe& pipe, CompressorStation& cs) {
    if (cs.GetId() != 0) {
        pipe.ConnectToStation(cs.GetId());
        cout << "Pipe connected to station " << cs.GetId() << endl;
    }
    else {
        cout << "Create compressor station first!" << endl;
    }
}

void clearDataFile(Pipe& pipe, CompressorStation& cs) {
    cout << "Are you sure you want to clear data.txt? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        ofstream file("data.txt", ios::trunc);
        if (file) {
            file.close();
            cout << "File data.txt cleared successfully!\n";


            Pipe newPipe;
            CompressorStation newCS;
            pipe = newPipe;
            cs = newCS;
            cout << "Memory data also cleared!\n";
        }
        else {
            cout << "Error clearing file!\n";
        }
    }
    else {
        cout << "Operation cancelled.\n";
    }
}

int main() {
    Pipe pipe;
    CompressorStation cs;
    int choice;

    while (true) {
        printMenu();

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            addPipe(pipe);
            break;
        }
        case 2: {
            addCompressorStation(cs);
            break;
        }
        case 3: {
            cout << "\n=== All Objects ===\n";
            if (pipe.GetName() != "None") {
                cout << "--- Pipe ---\n";
                pipe.Print();
            }
            else {
                cout << "No pipe data available.\n";
            }

            if (cs.GetName() != "None") {
                cout << "\n--- Compressor Station ---\n";
                cs.Print();
            }
            else {
                cout << "No compressor station data available.\n";
            }
            break;
        }
        case 4: {
            if (pipe.GetName() != "None") {
                pipe.Edit();
            }
            else {
                cout << "No pipe to edit! Please add a pipe first.\n";
            }
            break;
        }
        case 5: {
            if (cs.GetName() != "None") {
                int action;
                cout << "1. Start workshop\n2. Stop workshop\nChoose action: ";
                if (cin >> action) {
                    if (action == 1) cs.StartWorkshop();
                    else if (action == 2) cs.StopWorkshop();
                    else cout << "Invalid action!\n";
                }
                else {
                    clearInput();
                    cout << "Invalid input!\n";
                }
            }
            else {
                cout << "No compressor station to edit! Please add a station first.\n";
            }
            break;
        }
        case 6: {
            ofstream out("data.txt");
            if (out) {
                out << pipe << endl << cs;
                cout << "Data saved successfully to data.txt!\n";
            }
            else {
                cout << "Error saving data!\n";
            }
            break;
        }
        case 7: {
            ifstream in("data.txt");
            if (in) {
                in >> pipe >> cs;
                cout << "Data loaded successfully from data.txt!\n";
            }
            else {
                cout << "File data.txt not found! ";
                cout << "Please save data first or create the file manually.\n";

                ofstream create_file("data.txt");
                if (create_file) {
                    cout << "Empty data.txt created. Please save data first.\n";
                }
            }
            break;
        }
        case 8: {
            if (pipe.GetName() != "None" && cs.GetName() != "None") {
                connectPipeToStation(pipe, cs);
            }
            else {
                cout << "Create pipe and station first!" << endl;
            }
            break;
        }
        case 9: {
            if (pipe.IsConnected()) {
                pipe.Disconnect();
                cout << "Pipe disconnected from station" << endl;
            }
            else {
                cout << "Pipe is not connected to any station" << endl;
            }
            break;
        }
        case 10: {
            clearDataFile(pipe, cs);
            break;
        }
        case 0: {
            cout << "Exiting program.\n";
            return 0;
        }
        default: {
            cout << "Invalid choice! Please try again.\n";
            break;
        }
        }
    }
}