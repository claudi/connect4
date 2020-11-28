import numpy as np
import pygad.gann
import subprocess

global matches

# matches = np.loadtxt("matches.txt")

def construct_matches(solution, sol_idx):
    global GANN_instance
    global matches
    
    if sol_idx != 0:
        return
    else:
        population_vectors = pygad.gann.population_as_vectors(population_networks=GANN_instance.population_networks)
        n_individus = 10
        for id in range(n_individus):
            file = open("coefs/" + str(id) + ".dat", "w")
            for gene in population_vectors[id]:
                file.write(str(int(1000*gene)) + "\n")
                print(id)
            file.close()

        output = subprocess.run(["bash", "coefs/match.sh"], stdout=subprocess.PIPE, text=True)
        output = output.stdout.split("\n")[:-1]
        for id in range(len(output)):
            output[id] = output[id].split(" ")

        matches = np.zeros((n_individus, n_individus))
        for result in output:
            matches[int(result[0]), int(result[1])] = int(result[2])
        print(matches)

def get_value(id):
    global matches
    suma = 0
    for i in range(matches.shape[0]):
        if id != i:
            suma += matches[id, i]
            n = matches[i, id]
            if n == 1:
                suma += 1
            if n == 0:
                suma += 3
    return suma

def fitness_func(solution, sol_idx):
    construct_matches(solution, sol_idx)
    print(sol_idx)
    value = get_value(sol_idx)
    maximum_value = 3*(10-1)*2
    fitness = value/maximum_value
    return fitness

def callback_generation(ga_instance):
    global GANN_instance

    population_matrices = pygad.gann.population_as_matrices(population_networks=GANN_instance.population_networks,
                                                            population_vectors=ga_instance.population)
    GANN_instance.update_population_trained_weights(population_trained_weights=population_matrices)

    print("Generation = {generation}".format(generation=ga_instance.generations_completed))
    print("Accuracy   = {fitness}".format(fitness=ga_instance.best_solution()[1]))

num_neurons_input = 1380
num_neurons_output = 1

num_neurons_hidden_layers=[128, 64]

hidden_activations=["relu", "relu"]

num_solutions = 10
GANN_instance = pygad.gann.GANN(num_solutions=num_solutions,
                                num_neurons_input=num_neurons_input,
                                num_neurons_output=num_neurons_output,
                                num_neurons_hidden_layers=num_neurons_hidden_layers,
                                hidden_activations=hidden_activations)

population_vectors = pygad.gann.population_as_vectors(population_networks=GANN_instance.population_networks)

num_generations = 5

num_parents_mating = 3
initial_population = population_vectors.copy()

mutation_percent_genes = 5
ga_instance = pygad.GA(num_generations=num_generations,
                       num_parents_mating=num_parents_mating,
                       initial_population=population_vectors.copy(),
                       fitness_func=fitness_func,
                       mutation_percent_genes=mutation_percent_genes,
                       callback_generation=callback_generation)
ga_instance.run()
ga_instance.plot_result()

solution, solution_fitness, solution_idx = ga_instance.best_solution()

file = open("solution.dat", "w")
for gene in solution:
    file.write(str(gene) + "\n")
file.close()
print(solution)
print(solution_fitness)
print(solution_idx)
print(population_vectors)



