#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <fstream>
#include "pipe.h"
#include "Compressor_station.h"
#include <unordered_map>
#include <unordered_set>

#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
                        std::cerr << str << std::endl

#define PRINT_PARAM(out, x) out<< #x << "=" << x << std::endl

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

template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((std::cin >> x).fail()    // check type
        || std::cin.peek() != '\n'    // is buffer empty (int/float check)
        || x < min || x > max)        // check range
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Type number (" << min << "-" << max << "):";
    }
    std::cerr << x << std::endl;
    return x;
}

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
        }
    }
    return res;
}