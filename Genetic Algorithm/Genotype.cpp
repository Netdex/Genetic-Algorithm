#include "stdafx.h"
#include "Genotype.h"
#include <cstdlib>

const int Genotype::CHROMOSOME_SIZE = 9;

Genotype::Genotype()
{
	fitness = 0;
	output = "";
	chromosome = new char[CHROMOSOME_SIZE];
}

Genotype::Genotype(const Genotype& g) : fitness(g.fitness), output(g.output)
{
	chromosome = new char[CHROMOSOME_SIZE];
	for (int i = 0; i < CHROMOSOME_SIZE; i++)
		chromosome[i] = g.chromosome[i];
}

Genotype::~Genotype()
{
	delete[] chromosome;
}

Genotype Genotype::operator=(const Genotype& g)
{
	fitness = g.fitness;
	output = g.output;
	delete[] chromosome;
	chromosome = new char[CHROMOSOME_SIZE];
	for (int i = 0; i < CHROMOSOME_SIZE; i++)
		chromosome[i] = g.chromosome[i];
	return *this;
}
void Genotype::mutate(double chance)
{
	for (int word = 0; word < CHROMOSOME_SIZE; word++)
	{
		for (int bit = 0; bit < sizeof(chromosome); bit++)
		{
			double rchance = (double) rand() / (RAND_MAX + 1);
			if (rchance < chance)
				chromosome[word] ^= 1 << bit;
		}
	}
}

void Genotype::crossover(Genotype a)
{
	int rnd = rand() % (CHROMOSOME_SIZE - 1);
	for (int i = rnd; i < CHROMOSOME_SIZE; i++)
	{
		char tmp = chromosome[i];
		chromosome[i] = a.chromosome[i];
		a.chromosome[i] = tmp;
	}
}

void Genotype::populate()
{
	for (int word = 0; word < CHROMOSOME_SIZE; word++)
		chromosome[word] = (char)(rand() % 255);
}
