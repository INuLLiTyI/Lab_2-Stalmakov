#pragma once
#include <iostream>
#include "pipe.h"
#include "Compressor_station.h"
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <format>
#include <fstream>

#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
                        std::cerr << str << std::endl
void fix();

// Logger for writing user inputes
class Logger {
private:
    std::ofstream logFile;
public:
    Logger() {
        logFile.open("pipeline_log.txt", std::ios::app);
        log("=== Application started ===");
    }

    void log(const std::string& action) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        char timeStr[100];
        ctime_s(timeStr, sizeof(timeStr), &time);
        timeStr[24] = '\0'; // удаляем перевод строки
        logFile << timeStr << " - " << action << std::endl;
    }

    ~Logger() {
        log("=== Application closed ===");
        if (logFile.is_open()) {
            logFile.close();
        }
    }
};

extern Logger logger;

class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;
public:
    redirect_output_wrapper(std::ostream& src)
        :old_buf(src.rdbuf()), stream(src)
    {
    }
    ~redirect_output_wrapper() {
        stream.rdbuf(old_buf);
    }
    void redirect(std::ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};

bool checknamepipe(const Pipe& p, std::string param);
bool checkstate(const Pipe& p, bool param);

bool checknameks(const CompressorStation& g, std::string param);
bool workshops(const CompressorStation& g, int param);
void edit(std::unordered_map<int, Pipe>& Pipemap, std::unordered_set <int> res);

template<typename T>
using filterpipe = bool(*)(const Pipe& p, T param);

template<typename T>
std::unordered_set<int> FindPipeFilter(const std::unordered_map<int, Pipe>& Pipemap, filterpipe<T> f, T param)
{
    std::unordered_set <int> res;
    for (auto& p : Pipemap)
    {
        if (f(p.second, param)) {
            res.emplace(p.first);
            std::cout << p.second;
        }
    }
    return res;
}

template<typename T>
using filterks = bool(*)(const CompressorStation& g, T param);

template<typename T>
std::unordered_set<int> FindKSFilter(const std::unordered_map<int, CompressorStation>& KSmap, filterks<T> f, T param)
{
    std::unordered_set <int> res;
    for (auto& g : KSmap)
    {
        if (f(g.second, param)) {
            res.emplace(g.first);
            std::cout << g.second;
        }
    }
    return res;
}

template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((std::cin >> x).fail()
        || std::cin.peek() != '\n'
        || x < min || x > max)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a correct value: ";
    }
    std::cerr << x << std::endl;
    return x;
}