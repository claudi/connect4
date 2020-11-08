import random
import subprocess

POPULATION_SIZE = 100
GENES = range(46080)
GENES_SIZE = 1380

class Individual(object):
    chromosome = None
    fitness = -1

    def __init__(self, chromosome):
        self.chromosome = chromosome
    
    @classmethod
    def mutated_gene(self):
        '''
        Create random genes for mutation
        '''
        global GENES
        gene = random.choice(GENES)
        return gene
    
    @classmethod
    def create_genome(self):
        '''
        Create chromosome
        '''
        global GENES_SIZE
        return [self.mutated_gene() for _ in range(GENES_SIZE)]
    
    def mate(self, par2):
        '''
        Perform matin and produce new offspring
        '''

        # chromosome for offspring
        child_chromosome = []
        for gp1, gp2 in zip(self.chromosome, par2.chromosome):
            prob = random.random()

            if prob < 0.45:
                child_chromosome.append(gp1)
            
            elif prob < 0.90:
                child_chromosome.append(gp2)

            else:
                child_chromosome.append(self.mutated_gene())

        return Individual(child_chromosome)
    
    def calculate_fitness(self, population):
        self.fitness = 0

        for rival in population:
            self.fitness += 1
            # self.fitness += self.match(rival)
        
        return self.fitness
    
    def match(self, rival):
        score = 0
        for chr1, chr2 in zip(self.chromosome, rival.chromosome):
            if chr1 > chr2:
                score += 1
            elif chr1 < chr2:
                score -= 1

        return score

def runGames(population):
    POPULATION_SIZE = 10

    for id in range(len(population)):
        file = open("gen/coefs/" + str(id) + ".dat", "w")
        for gene in population[id].chromosome:
            file.write(str(gene) + "\n")
    
    output = subprocess.run(["bash", "gen/match.sh", str(POPULATION_SIZE)], stdout=subprocess.PIPE, text=True)
    output = output.stdout.split("\n")[:-1]
    for id in range(len(output)):
        output[id] = output[id].split(" ")

    matches = [ [ None for _ in range(POPULATION_SIZE) ] for _ in range(POPULATION_SIZE) ]
    for result in output:
        matches[int(result[0])][int(result[1])] = result[2]

    print(matches)
    return matches

def main():
    population = []
    global POPULATION_SIZE

    generation = 1

    found = False

    for _ in range(POPULATION_SIZE):
        genome = Individual.create_genome()
        population.append(Individual(genome))
    
    while not found:
        results = runGames(population)
        
        for gp1 in population:
            gp1.calculate_fitness(population)
        
        found = True

if __name__ == '__main__':
    main()

