import numpy
import pygad
import pygad.nn
import pygad.gann
import subprocess

def fitness_func(solution, sol_idx):
    global GANN_instance, data_inputs, data_outputs

    predictions = pygad.nn.predict(last_layer=GANN_instance.population_networks[sol_idx],
                                   data_inputs=data_inputs)
    correct_predictions = numpy.where(predictions == data_outputs)[0].size
    solution_fitness = (correct_predictions/data_outputs.size)*100

    return solution_fitness

def callback_generation(ga_instance):
    global GANN_instance

    population_matrices = pygad.gann.population_as_matrices(population_networks=GANN_instance.population_networks, 
                                                            population_vectors=ga_instance.population)

    GANN_instance.update_population_trained_weights(population_trained_weights=population_matrices)

    print("Generation = {generation}".format(generation=ga_instance.generations_completed))
    print("Accuracy   = {fitness}".format(fitness=ga_instance.best_solution()[1]))

data_inputs = numpy.array([[1, 1],
                           [1, 0],
                           [0, 1],
                           [0, 0]])

data_outputs = numpy.array([0, 
                            1, 
                            1, 
                            0])

GANN_instance = pygad.gann.GANN(num_solutions=5,
                                num_neurons_input=2,
                                num_neurons_hidden_layers=[2],
                                num_neurons_output=2,
                                hidden_activations=["relu"],
                                output_activation="softmax")

population_vectors = pygad.gann.population_as_vectors(population_networks=GANN_instance.population_networks)

ga_instance = pygad.GA(num_generations=50, 
                       num_parents_mating=3, 
                       initial_population=population_vectors.copy(),
                       fitness_func=fitness_func,
                       mutation_percent_genes=5,
                       callback_generation=callback_generation)

ga_instance.run()

ga_instance.plot_result()

solution, solution_fitness, solution_idx = ga_instance.best_solution()
print(solution)
print(solution_fitness)
print(solution_idx)

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

