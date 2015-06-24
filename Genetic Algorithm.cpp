
#include "Genotype.h"
#include <time.h>
#include "Population.h"
#include <string>
#include <iostream>

int main()
{
	srand(time(NULL));

	std::cout << "GENETIC ALGORITHM\n";
	Population p;
	p.populate(10);
	// Step 20 generations
	for (int i = 0; i < 100; i++)
	{
		p.printState();
		p.nextPopulation(10);
	}
	p.printState();
	std::cout << p.getMaxFitness();
	return 0;
}

