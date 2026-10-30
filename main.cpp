// Anthony Huey - 10/30/2026 - COMSC 210 - Lab 29: SDLC
// design a project that meets the requirements in the proposal.

// Include, map,list,array,fstream,iostream,string and anything else
#include <map>
#include <string>
#include <list>
#include <array>
#include <iostream>
#include <fstream>

using namespace std;

//class for animals, species and age
class Animal
{
private:
    string species;
    int age;

public:
 Animal(string s, int a) : species(s), age(a) {}

 void ageUp() {age++;}

 int getAge() const {return age;}
 void setAge(int a) {age = a;} 
 string getSpecies() const {return species;}
 void setSpecies(string s) {species = s;}

};
enum Stage {YOUNG, ADULT, OLD}; // easier to code with
const int MAX = 3; // eventually set MAX & MIN for each type of animal

// function defs for display, and probably time simulation/interval.
    // funcs for removing/adding animals
void display(map<string, array<list<Animal>, MAX>> pop)
{
    cout << pop["herbivore"][YOUNG].front().getSpecies();
    cout << " (age: " << pop["herbivore"][YOUNG].front().getAge() << ")";
}

// states for extreme weather, drought, flooding, blizzard, etc.
    // influences starvation, reproduction of certain animals.
bool drought, flooding, blizzard = 0;


// Main
    // Initialize map, stores animall type, and the array for the list of animals
int main()
{
    map<string, array<list<Animal>, MAX>> population;
    population["herbivore"][YOUNG].push_back(Animal("Zebra", 1));
    population["carnivore"][ADULT].push_back(Animal("Lion", 12));
   
    display(population);
 

}
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
