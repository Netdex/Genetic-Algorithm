#pragma once
#include <string>

class Genotype
{
public:
	static const int CHROMOSOME_SIZE;
	double fitness;
	std::string output;

	char* chromosome;

	Genotype();
	Genotype(const Genotype& g);
	~Genotype();
	Genotype operator=(const Genotype& g);
	void crossover(Genotype a);
	void mutate(double chance);
	void populate();
};

