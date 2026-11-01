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
// realized this isn't actually that usefull, oh well.
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
const int MAX = 3, MONTHS = 12, E_MAX = 100; // Array, time loop, event roll
bool drought = 0, flooding = 0, blizzard = 0, // weather
bool herbPop = 0, carnPop = 0; // iss herb/carnivore overpopulated?
bool cont = 0; // for the simulation loop.

// function dislpay, add, delete, count.
void addAnimal(map<string, array<list<Animal>, MAX>> &pop,
                                                 string t, string s, int a)
{ 
    int stage = (a < 3) ? YOUNG : (a < 8) ? ADULT : OLD; 
    pop[t][stage].push_back(Animal(s, a));
}

int countTotalAnimal(const map<string, array<list<Animal>, MAX>> pop, string type)
{ // return the amount of animals of a type (hrebivore/carnivore)
    // this is for the random events weighting.
    auto it = pop.find(type); // search herb or carn
    
    int total = 0;
    for (const auto& stage : it->second) // each list in array
        total += stage.size();
    return total;
}

int countAnimal(const map<string, array<list<Animal>, MAX>> pop, string type, int age)
{
    auto it = pop.find(type); // search herb or carn
    return it->second[age].size(); // return size of that specific age group
}

void display(map<string, array<list<Animal>, MAX>> pop)
{

    cout << "\n\t\tYOUNG \tADULT \tOLD";
    cout << "\nHERBIVORE|";
    cout << "\t" << countAnimal(pop, "herbivore", YOUNG);
    cout << "\t" << countAnimal(pop, "herbivore", ADULT);
    cout << "\t" << countAnimal(pop, "herbivore", OLD);
    cout << "\nCARNIVORE|";
    cout << "\t" << countAnimal(pop, "carnivore", YOUNG);
    cout << "\t" << countAnimal(pop, "carnivore", ADULT);
    cout << "\t" << countAnimal(pop, "carnivore", OLD);
}
int main()
{
    srand(time(0)); // for the random event rolls
    map<string, array<list<Animal>, MAX>> population;
    const array<string, MAX> herb = {"Zebra", "Giraffe", "Gazelle"};
    const array<string, MAX> carn = {"Lion", "Crocodile", "Hippopotamus"};
       
    // Fill the map with data from file, animal species, age, etc. 
        // give an error if fail to open
        // close file
    ifstream fin;
    fin.open("animals.txt");
    if (fin.good())
    {
        string type;
        string species;
        int age;
        while (fin >> type >> species >> age)
            addAnimal(population, type, species, age);
        fin.close();    
    }
    else
        cout << "File not found!\n";
    // Begin the simulation, user can loop as many times as they want.
        // roll a dice which decides if an event happens,
        // if an even occurs roll again to decide which one.
    // output the changes.
    // don't forget to add a wait at the end to 'simulate' time passing.
    int event = 10;
    while (cont != 1) // outer while loop to let user decide when to end sim
    {
        for(int i = 0; i < MONTHS; i++) // progress by "months"
        {
            cout << "\nMonth " << i << ": ";

// 10% chance per month for event. +10% per miss   
// the event wieghting can be adjusted later, works for now
// i want the population of certain groups to effect the odds.
//      more herbivores means predation is more likely, 
//      less herbivores mean starvation for carnivores is more likely and so on.
// the weather add another push/pull to the odds, can be added later easy.
            if ((rand() % E_MAX) <= event)
            {
                cout << "Got an event!";
                int roll = (rand() % E_MAX);
                cout << "\nDEBUG - Rolled a: " << roll << endl;
                if (roll < 25 )
                {
                    cout << "\nREPRODUCTION\n";
                    // herbivore alwasy reproduce 50/50 for carnivore
                    addAnimal(population, "herbivore", "test", 1);
                    cout << "\nA new herbivore was born!";
                    if ((rand() % E_MAX) <= 50) 
                    {   // make animal random later ------------*
                        addAnimal(population, "carnivore", "test", 1);
                        cout << "\nA new carnivore was born!";
                    }
                }
                else if (roll < 35) 
                { // random amount between 1-3ish
                    cout <<"\nSTARVATION\n";
                    if (rand() % E_MAX < 50) // rough idea
                    { // will prob crash need to validate
                        population["herbivore"][YOUNG].pop_front();
                        population["herbivore"][YOUNG].pop_front();
                        population["herbivore"][YOUNG].pop_front();
                        cout << "\n3 herbivore's died from starvation!";
                    }
                    else
                        population["herbivore"][YOUNG].pop_front();
                        cout << "\nA herbivore died from starvation!";
                }
                else if (roll < 60)
                {
                    cout << "\nPREDATION\n";
                    population["herbivore"][YOUNG].pop_front();
                    cout << "\nA carnivore ate a herbivore!";

                }
                else if (roll < 65)// start a certain weather
                { // these will effect the rolls above
                    cout << "\nWEATHER\n";
                    if (rand() % E_MAX < 33) 
                        drought = 1;
                    else if (rand() % E_MAX < 66)
                        flooding = 1;
                    else if (rand() % E_MAX < 99)
                        blizzard = 1;  
                }
                event = 10; // reset event chance.
            }
            else
            {
                cout << "Nothing occured...";
                event += 10;
            }

        }
        display(population);
        char YN = 'Y';
        cout << "\nWould you like to continue the simulation? (Y/N): ";
        cin >> YN;
        if (YN == 'N' || YN == 'n')
            cont = 1;
    }
    cout << "\nGoodybye!";
}
