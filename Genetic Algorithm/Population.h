#pragma once
#include <vector>
#include "Genotype.h"

class Population
{
public:
	static const double CROSSOVER_CHANCE;
	static const double MUTATION_CHANCE;
	static const int MAX_ROULETTE_ATTEMPTS;

	Population();
	~Population();
	void populate(int amt);
	void evalFitness();
	void nextPopulation(int newSize);

	double getTotalFitness();
	double getAvgFitness();
private:
	int roulette(double prop[], int populationSize, double totalFitness);
};

