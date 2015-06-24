#pragma once
#include <vector>
#include "Genotype.h"
#include <string>
#include <cstdlib>

class Population
{
public:
	static const double CROSSOVER_CHANCE;
	static const double MUTATION_CHANCE;
	static const int MAX_ROULETTE_ATTEMPTS;

	int generation;

	Population();
	~Population();
	void populate(int amt);
	void evalFitness();
	void nextPopulation(int newSize);

	double getTotalFitness();
	double getAvgFitness();
	int getMaxFitnessIndex();
	double getMaxFitness();
	int getMinFitnessIndex();
	double getMinFitness();
	void printState();
private:
	int roulette(double*& prop, int populationSize, double totalFitness);
};

