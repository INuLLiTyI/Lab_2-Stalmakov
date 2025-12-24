#include <string>
#include <fstream>
#include "Pipe.h"
#include "KS.h"
#include "GasNet.h"
#include "Tools.h"
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <format>



void PrintMainMenu();
void Printaddmenu();
void MainMenu(GasNet);
void fix();


int main()
{
    GasNet gasnet;
    redirect_output_wrapper cerr_out(std::cerr);
    std::string time = std::format("{:%d_%m_%Y %H_%M_%OS}", std::chrono::system_clock::now());
    std::ofstream logfile("log_" + time + ".txt");
    if (logfile)
        cerr_out.redirect(logfile);
    setlocale(LC_ALL, "RU");
    MainMenu(gasnet);

}




void PrintMainMenu() {
    std::cout <<
        "1. Добавить трубу" << "\n"
        "2. Добавить КС" << "\n"
        "3. Просмотр всех объектов" << "\n"
        "4. Сохранить" << "\n"
        "5. Загрузить" << "\n"
        "6. Поиск" << "\n"
        "7. Соединить в станцию" << "\n"
        "8. Топологическая сортировка" << "\n"
        "0. Выход" << "\n" << "\n";
}
void Printaddmenu() {
    std::cout << "1.Поиск трубы по имени" << std::endl;
    std::cout << "2.Поиск трубы по состоянию" << std::endl;
    std::cout << "3.Поиск КС по имени" << std::endl;
    std::cout << "4.Поиск КС по цехам" << std::endl;
    std::cout << "0.Выход в основное меню" << std::endl << std::endl;
}
void PrintChois() {
    std::cout << "1.Изменить" << std::endl << "2.Удалить" << std::endl;
}
void savepipe(std::ofstream& fout, std::unordered_map<int, Pipe>& Pipemap) {

    for (auto& p : Pipemap) {
        fout << p.second;
    }

}
void saveks(std::ofstream& fout, std::unordered_map<int, KS>& KSmap) {
    for (auto& g : KSmap) {
        fout << g.second;
    }
}




void MainMenu(GasNet n) {
    std::string data;
    int usernumber;
    std::string name;
    bool state;
    int work;
    int chois;
    std::unordered_set <int> res;
    while (1) {
        PrintMainMenu();
        usernumber = GetCorrectNumber(0, 8);
        switch (usernumber) {
        case 1:
            n.PipesCreate();
            break;
        case 2:
            n.KSCreate();
            break;
        case 3:
            n.KSPrint();
            n.PipesPrint();
            break;
        case 4: {
            std::ofstream fout;
            std::cout << "Ведите имя файла ";
            INPUT_LINE(std::cin, data);
            fout.open(data, std::ios::out);
            if (fout.is_open()) {
                fout << n.GetPipes().size() << std::endl;
                savepipe(fout, n.GetPipes());
                fout << n.GetKS().size() << std::endl;
                saveks(fout, n.GetKS());
                std::cout << "Сохранение прошло успешно" << std::endl;
            }
            else {
                std::cout << "Не удолось произвести запись в файл." << std::endl;
            }
            break;
        }
        case 5: {
            n.Load();
            break;
        case 6: {
            bool exitSubMenu = false;
            while (!exitSubMenu) {
                Printaddmenu();
                usernumber = GetCorrectNumber(0, 4);
                switch (usernumber) {
                case 1:
                    if (n.GetPipes().empty()) {
                        std::cout << "Обектов нет" << std::endl;
                        break;
                    }
                    else {
                        std::cout << "Введите имя для поиска ";
                        INPUT_LINE(std::cin, name);
                        res = FindPipeFilter(n.GetPipes(), checknamepipe, name);
                        PrintChois();
                        chois = GetCorrectNumber(1, 2);
                        if (chois == 1) {
                            n.ChangePipe(res);
                        }
                        if (chois == 2) {
                            n.DeletePipe(res);
                        }
                    }
                    break;
                case 2:
                    if (n.GetPipes().empty()) {
                        std::cout << "Обектов нет" << std::endl;
                        break;
                    }
                    else {
                        std::cout << "Введите состояние для поиска ";
                        state = GetCorrectNumber(0, 1);
                        res = FindPipeFilter(n.GetPipes(), checkstate, state);
                        PrintChois();
                        chois = GetCorrectNumber(1, 2);
                        if (chois == 1) {
                            n.ChangePipe(res);
                        }
                        if (chois == 2) {
                            n.DeletePipe(res);
                        }
                    }
                    break;
                case 3:
                    if (n.GetPipes().empty()) {
                        std::cout << "Обектов нет" << std::endl;
                        break;
                    }
                    else {
                        std::cout << "Введите имя для поиска ";
                        INPUT_LINE(std::cin, name);
                        res = FindKSFilter(n.GetKS(), checknameks, name);
                        PrintChois();
                        chois = GetCorrectNumber(1, 2);
                        if (chois == 1) {
                            n.ChangeKS(res);
                        }
                        if (chois == 2) {
                            n.DeleteKS(res);
                            break;
                        }
                        break;
                    }
                    break;
                case 4:
                    if (n.GetKS().empty()) {
                        std::cout << "Обектов нет" << std::endl;
                        break;
                    }
                    else {
                        std::cout << "Введите цехи для поиска ";
                        work = GetCorrectNumber(0, 100);
                        res = FindKSFilter(n.GetKS(), workshops, work);
                        PrintChois();
                        chois = GetCorrectNumber(1, 2);
                        if (chois == 1) {
                            n.ChangeKS(res);
                        }
                        if (chois == 2) {
                            n.DeleteKS(res);
                        }
                    }
                    break;
                case 0:
                    exitSubMenu = true;
                    break;
                default:
                    std::cout << "Некорректный ввод. Повторите попытку.\n";
                    break;
                }
            }
            break;
        }
        case 7:
        {
            std::cout << "Введите id левой кс: ";
            int id = GetCorrectNumber(1, 100000);
            std::cout << "Введите id правой кс: ";
            int id1 = GetCorrectNumber(1, 100000);
            if (id == id1) {
                std::cout << "Вы пытайтесь соединить одну и ту же кс! " << std::endl;
                break;
            }
            std::cout << "Введите диаметр трубы: ";
            int dm = GetCorrectNumber(1, 1400);
            if (!n.Connect(id, id1, dm)) {
                std::cout << "Неверные id " << std::endl;
                break;
            }
            std::cout << "Станция успешно создана! " << std::endl;
            break;
        }
        case 8: {
            std::vector<int> v = n.Sort();
            if (v.empty()) {
                std::cout << "Данных нет!" << std::endl;
                break;
            }
            std::cout << "Результат топологической сортировки" << std::endl;
            for (auto& i : v) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            break;
        }
        case 0:
            return;
        }
        }
    }
}