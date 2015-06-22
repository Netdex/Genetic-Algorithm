// Genetic Algorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Genotype.h"
#include <time.h>
#include "Population.h"

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	Population p;
	p.populate(100);
	p.nextPopulation(100);
	
	return 0;
}

