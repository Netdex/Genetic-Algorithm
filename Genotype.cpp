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
	// Loop through the chromosome, and mutate randomly as necessary
	for (int bit = 0; bit < CHROMOSOME_SIZE; bit++)
	{
		double rchance = (double)rand() / (RAND_MAX + 1);
		if (rchance < chance)
			chromosome.flip(bit);
	}
}

void Genotype::crossover(Genotype& a)
{
	// Crossover two chromosomes of two genotypes at a random location
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
	// Randomly populate the genotype's chromosome
	for (int bit = 0; bit < CHROMOSOME_SIZE; bit++){
		chromosome[bit] = rand() % 2;
	}
}

std::string Genotype::to_string()
{
	std::string csome = chromosome.to_string();
	int len = 7 + 3 + 1 + csome.length(); // max len, extra formatting, buffer space, csome length
	char* ret = new char[len];
	sprintf(ret, "%7.3f : %s", fitness, csome.c_str());
	std::string retstr(ret);
	delete[] ret;
	return retstr;
}
