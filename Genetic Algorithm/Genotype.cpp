#include "stdafx.h"
#include "Genotype.h"

Genotype::Genotype()
{
	fitness = 0;
	output = "";
}

Genotype::Genotype(const Genotype& g) : fitness(g.fitness), output(g.output)
{
	chromosome = std::bitset<CHROMOSOME_SIZE>(g.chromosome);
}

Genotype::~Genotype()
{
	
}

Genotype Genotype::operator=(const Genotype& g)
{
	fitness = g.fitness;
	output = g.output;
	chromosome = std::bitset<CHROMOSOME_SIZE>(g.chromosome);
	return *this;
}

void Genotype::mutate(double chance)
{
	for (int bit = 0; bit < CHROMOSOME_SIZE; bit++)
	{
		double rchance = (double)rand() / (RAND_MAX + 1);
		if (rchance < chance)
			chromosome.flip(bit);
	}
}

void Genotype::crossover(Genotype& a)
{
	int rnd = rand() % (CHROMOSOME_SIZE - 1);
	for (int i = rnd; i < CHROMOSOME_SIZE; i++)
	{
		bool tmp = chromosome[i];
		chromosome[i] = a.chromosome[i];
		a.chromosome[i] = tmp;
	}
}

void Genotype::populate()
{
	for (int bit = 0; bit < CHROMOSOME_SIZE; bit++){
		chromosome[bit] = rand() % 2;
	}
}

std::string Genotype::to_string()
{
	return std::to_string(fitness) + " : " + chromosome.to_string();
}