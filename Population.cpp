#include "Population.h"
#include <windows.h>
#include <iostream>

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
	// Generate "amt" new members of the population
	for (int gtype = 0; gtype < amt; gtype++)
	{
		Genotype g;
		g.populate();
		pop.push_back(g);
	}
	// Reevaluate fitness
	evalFitness();
}

void Population::nextPopulation(int newSize)
{
	const int POPULATION_SIZE = pop.size();
	double totalFitness = getTotalFitness();
	double* prop = new double[POPULATION_SIZE];
	*prop = pop[0].fitness / totalFitness;
	// Generate a pseudo roulette wheel to choose genotypes, with probability based on fitness
	for (int p = 1; p < POPULATION_SIZE; p++)
		prop[p] = prop[p - 1] + pop[p].fitness / totalFitness;
	std::vector<Genotype> next;
	// Generate the next new population based on roulette chosen offspring
	for (int i = 0; i < newSize; i++)
	{
		// Roulette two "different" [will only try MAX_ROULETTE_ATTEMPTS times]
		// members of the population, based on fitness
		int c1 = roulette(prop, POPULATION_SIZE, totalFitness);
		int c2 = c1;
		for (int t = 0; t < MAX_ROULETTE_ATTEMPTS && c2 == c1; t++)
			c2 = roulette(prop, POPULATION_SIZE, totalFitness);
		// Copy the genotypes out
		Genotype a (pop[c1]);
		Genotype b (pop[c2]);
		// Crossover the chromosomes if applicable
		if ((double) rand() / (RAND_MAX + 1) < CROSSOVER_CHANCE)
			a.crossover(b);
		// Mutate the child by the defined chance
		a.mutate(MUTATION_CHANCE);
		// Push the child onto the population stack
		next.push_back(a);
	}
	// Shift the new population onto the stack
	pop = next;
	delete[] prop; // NEVER EVER DELETE THIS OR MEMORY LEAKS
	// Reevaluate the fitness of the new population
	evalFitness();
	generation++;
}

void Population::evalFitness()
{
	// Evaluate the "fitness" function of every genotype in the population
	for (int gtype = 0; gtype < pop.size(); gtype++)
	{
		// Here, the fitness is just the sum of the bits
		Genotype g = pop[gtype];
		int sum = 0;
		for (int b = 0; b < Genotype::CHROMOSOME_SIZE; b++)
			sum += g.chromosome[b];
		pop[gtype].fitness = sum;
	}
}

void Population::printState()
{
	// Prints the current state of the population
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int maxIdx = getMaxFitnessIndex();
	SetConsoleTextAttribute(hConsole, 0x0f);
	std::cout << "//:: generation: " << generation << std::endl;
	for (int gtype = 0; gtype < pop.size(); gtype++)
	{
		if (gtype == maxIdx)
			SetConsoleTextAttribute(hConsole, 0x0a);
		else
			SetConsoleTextAttribute(hConsole, 0x07);
		std::cout << pop[gtype].to_string() + '\n';
	}
}

int Population::roulette(double*& prop, int populationSize, double totalFitness)
{
	double rnd = (double) rand() / (RAND_MAX + 1);
	// Loop through the probabilities until it is less
	// than the random value, thus simulating a roulette wheel
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

int Population::getMaxFitnessIndex()
{
	int idx = 0;
	for (int i = 1; i < pop.size(); i++)
		if (pop[i].fitness > pop[idx].fitness)
			idx = i;
	return idx;
}

double Population::getMaxFitness()
{
	return pop[getMaxFitnessIndex()].fitness;
}

int Population::getMinFitnessIndex()
{
	int idx = 0;
	for (int i = 1; i < pop.size(); i++)
		if (pop[i].fitness < pop[idx].fitness)
			idx = i;
	return idx;
}

double Population::getMinFitness()
{
	return pop[getMinFitnessIndex()].fitness;
}
