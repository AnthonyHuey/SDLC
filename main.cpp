// Anthony Huey - 10/30/2026 - COMSC 210 - Lab 29: SDLC
// designa a project that meets the requirements in the proposal.
/*Project Overview:
Track the populaton of various species overtime and the influence they have on
each other. 

Implementation:
A std::map to store which type of animal, herbivore & carnivore, which is categorized 
into 3 seperate pools of young, adult, or old. each category will conatain 
the species and age of various animals. 
The type of animal will be the map's key.
The array with the categorized animals will be the map's value.

Simulated events:
Simulation will focus on predation, and repoduction and how each type of animals
population influences the other's. As well as how weather or other natural events
influence both. */

// Include, map,list,array,fstream,iostream,string and anything else

// function defs for display, and probably time simulation/interval.
    // funcs for removing/adding animals

// states for extreme weather, drought, flooding, blizzard, etc.
    // influences starvation, reproduction of certain animals.


// Main
    // Initialize map, stores animall type, and the array for the list of animals
        // animal object will contain  - sspecies and age.
    // Fill the map with data from file, animal species, age, etc. 
        // give an error if fail to open
        // close file

    // Begin the simulation, 
        // every x amount of time go through each type of animal
            // decide if anyone starves/dies of old age. remove them. 
                // for herbivors, decide if they are also predated
            // decide if anyone reproduces
                // generate a new animal add it to the list
            
        // output the changes.
        
    // decide if any special events occur.
        // migration, extreame weather.
    
    // the population of one animal influence the other is the main idea,
    // more herbivore's leads to more carnivores, which leads to less herbivores
        // a cylcle the balances itself is the idea.
        // the balance is influence by natural events, 
            // see if balance can return from such events.
        
// End
