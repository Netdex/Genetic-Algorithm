#include "stdafx.h"
#include "Population.h"
#include <vector>
#include <cstdlib>

const double Population::CROSSOVER_CHANCE = 0.7;
const double Population::MUTATION_CHANCE = 0.007;
const int Population::MAX_ROULETTE_ATTEMPTS = 100;

std::vector<Genotype> pop;

Population::Population()
{
	
}

Population::~Population()
{
	
}

void Population::populate(int amt)
{
	pop.clear();
	pop.resize(amt);
	for (int gtype = 0; gtype < amt; gtype++)
	{
		Genotype g;
		g.populate();
		pop.push_back(g);
	}
}

void Population::nextPopulation(int newSize)
{
	const int POPULATION_SIZE = pop.size();
	double totalFitness = getTotalFitness();
	double* prop = new double[POPULATION_SIZE];
	*prop = pop[0].fitness;
	for (int p = 1; p < POPULATION_SIZE; p++)
		prop[p] = prop[p - 1] + pop[p].fitness / totalFitness;
	std::vector<Genotype> next;
	for (int i = 0; i < newSize; i++)
	{
		int c1 = roulette(prop, POPULATION_SIZE, totalFitness);
		int c2 = c1;
		for (int t = 0; t < MAX_ROULETTE_ATTEMPTS && c2 == c1; t++)
			c2 = roulette(prop, POPULATION_SIZE, totalFitness);
		Genotype a (pop[c1]);
		Genotype b (pop[c2]);
		if ((double) rand() / (RAND_MAX + 1) < CROSSOVER_CHANCE)
			a.crossover(b);
		a.mutate(MUTATION_CHANCE);
		next.push_back(a);
	}
	pop = next;
	delete[] prop;
	evalFitness();
}

void Population::evalFitness()
{
	for (int i = 0; i < pop.size(); i++)
	{
		pop[i].fitness = 1;
	}
}

int Population::roulette(double* prop, int populationSize, double totalFitness)
{
	double rnd = (double) rand() / (RAND_MAX + 1);
	for (int j = 0; j < populationSize; j++)
		if (rnd < prop[j])
			return j;
	return populationSize - 1;
}

double Population::getTotalFitness()
{
	double total = 0;
	for (int gtype = 0; gtype < pop.size(); gtype++)
		total += pop[gtype].fitness;
	return total;
}

double Population::getAvgFitness()
{
	return getTotalFitness() / pop.size();
}
