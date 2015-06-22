#pragma once
#include <string>
#include <bitset>
#include <cstdlib>

class Genotype
{
public:
	static const size_t CHROMOSOME_SIZE = 8;
	double fitness;
	std::string output;

	std::bitset<CHROMOSOME_SIZE> chromosome;

	Genotype();
	Genotype(const Genotype& g);
	~Genotype();
	Genotype operator=(const Genotype& g);
	void crossover(Genotype& a);
	void mutate(double chance);
	void populate();
	std::string to_string();
};

