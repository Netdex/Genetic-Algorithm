#include "stdafx.h"
#include "Population.h"

const double Population::CROSSOVER_CHANCE = 0.7;
const double Population::MUTATION_CHANCE = 0.007;
const int Population::MAX_ROULETTE_ATTEMPTS = 100;

std::vector<Genotype> pop;

Population::Population()
{
	generation = 0;
}

Population::~Population()
{

}

void Population::populate(int amt)
{
	pop.clear();
	for (int gtype = 0; gtype < amt; gtype++)
	{
		Genotype g;
		g.populate();
		pop.push_back(g);
	}
	evalFitness();
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
	generation++;
}

void Population::evalFitness()
{	
	for (int gtype = 0; gtype < pop.size(); gtype++)
	{
		Genotype g = pop[gtype];
		int sum = 0;
		for (int b = 0; b < Genotype::CHROMOSOME_SIZE; b++)
			sum += g.chromosome[b];
		pop[gtype].fitness = sum;
	}
}

int Population::roulette(double*& prop, int populationSize, double totalFitness)
{
	double rnd = (double) rand() / (RAND_MAX + 1);
	for (int j = 0; j < populationSize; j++)
		if (rnd < prop[j])
			return j;
	return populationSize - 1;
}

std::string Population::to_string()
{
	std::string ret = "//:: generation: " + std::to_string(generation) + std::string("\n");
	for (int gtype = 0; gtype < pop.size(); gtype++)
	{
		ret += pop[gtype].to_string() + '\n';
	}
	return ret;
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

double Population::getMaxFitnessIndex()
{
	int idx = 0;
	for (int i = 1; i < pop.size(); i++)
	{
		if (pop[i].fitness > pop[idx].fitness)
			idx = i;
	}
	return idx;
}

double Population::getMaxFitness()
{
	return pop[getMaxFitnessIndex()].fitness;
}

double Population::getMinFitnessIndex()
{
	int idx = 0;
	for (int i = 1; i < pop.size(); i++)
	{
		if (pop[i].fitness < pop[idx].fitness)
			idx = i;
	}
	return idx;
}

double Population::getMinFitness()
{
	return pop[getMinFitnessIndex()].fitness;
}
