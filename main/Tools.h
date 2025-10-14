﻿#pragma once
#include <iostream>
#include "Pipe.h"
#include "KS.h"
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <format>

#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
						std::cerr << str << std::endl
void fix();

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

bool checknameks(const KS& g, std::string param);
bool workshops(const KS& g, int param);
void edit(std::unordered_map<int, Pipe>& Pipemap, std::unordered_set <int> res);
void delet(std::unordered_map<int, Pipe>& Pipemap, std::unordered_set <int> res);

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
using filterks = bool(*)(const KS& g, T param);

template<typename T>
std::unordered_set<int> FindKSFilter(const std::unordered_map<int, KS>& KSmap, filterks<T> f, T param)
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