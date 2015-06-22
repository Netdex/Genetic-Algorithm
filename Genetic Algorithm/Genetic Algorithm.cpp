// Genetic Algorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Genotype.h"
#include <time.h>
#include "Population.h"
#include <string>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	Population p;
	p.populate(10);
	for (int i = 0; i < 10; i++)
	{
		std::cout << p.to_string();
		p.nextPopulation(10);
		
	}
	std::cout << p.getMaxFitness();
	std::cin.ignore();
	return 0;
}

