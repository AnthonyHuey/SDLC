// Anthony Huey - 10/30/2026 - COMSC 210 - Lab 29: SDLC
// design a project that meets the requirements in the proposal.
// Include, map,list,array,fstream,iostream,string and anything else
#include <map>
#include <string>
#include <list>
#include <array>
#include <iostream>
#include <fstream>

#include <thread> // to make it seem like etime is passing.
#include <chrono>

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
bool drought = 0, flooding = 0, blizzard = 0; // weather
bool herbPop = 0, carnPop = 0; // is herb/carnivore overpopulated?
bool cont = 0; // for the simulation loop.

// function dislpay, add, delete, count.
void addAnimal(map<string, array<list<Animal>, MAX>> &pop,
                                                 string t, string s, int a)
{ 
    int stage = (a < 3) ? YOUNG : (a < 12) ? ADULT : OLD; 
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

void ageAnimal(map<string, array<list<Animal>, MAX>> &pop)
{ // ages up all the animal, might aswell use that class i made.
    for (auto& type : pop )
        for (auto& stage : type.second)
            for (Animal& a : stage)
                a.ageUp();
}

void deadAnimal(map<string, array<list<Animal>, MAX>> &pop, string food)
{
    int stage = rand() % MAX; // select a random stage
   
    if (!pop[food][stage].empty()) // avoid killing adults, i think?
        if (stage != ADULT)
            pop[food][stage].pop_front();
        else if (!pop[food][stage - 1].empty())
            pop[food][stage - 1].pop_front();
        else if (!pop[food][stage + 1].empty())
            pop[food][stage + 1].pop_front();
}

void moveAnimal(map<string, array<list<Animal>, MAX>> &pop)
{
    for (auto& type : pop) // gets the herbivore/carnivore. adult -> old
    {
        auto& stage = type.second; // for array/lists
        // scroll through the list
        for (auto it = stage[ADULT].begin(); it != stage[ADULT].end();)
        {
            if (it->getAge() >= 16) // condition to move lists
            { // easier than splice, for me.
                cout << "\n" << it->getSpecies() << " is now old!";
                stage[OLD].push_back(*it); // copy the it to the new list/
                it = stage[ADULT].erase(it); // delete from old and get next.
            }
            else
                it++;
        }
    }

    for (auto& type : pop) // gets the herbivore/carnivore. adult -> old
    {
        auto& stage = type.second; // for array/lists
        // scroll through the list
        for (auto it = stage[YOUNG].begin(); it != stage[YOUNG].end();)
        {
            if (it->getAge() >= 16) // condition to move lists
            { 
                cout << "\n" << it->getSpecies() << " is now an adult!";
                stage[ADULT].push_back(*it); 
                it = stage[YOUNG].erase(it);
            }
            else
                it++;
        }
    }

    
}

int main()
{
    srand(time(0)); // for the random event rolls
    map<string, array<list<Animal>, MAX>> population;
    const array<string, MAX> herb = {"Zebra", "Giraffe", "Gazelle"};
    const array<string, MAX> carn = {"Lion", "Crocodile", "Leopard"};
       
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
    int event = 15; // 15% chance per month for event. +10% per miss  
    while (cont != 1) // outer while loop to let user to decide when to end sim
    {
        for(int i = 0; i < MONTHS; i++) // progress by "months"
        {
            cout << "\nMonth " << i + 1 << ": ";
 
            if ((rand() % E_MAX) <= event)
            {
                cout << "Got an event!";
                int roll = (rand() % E_MAX);
                //cout << "\nDEBUG - Rolled a: " << roll;
                if (roll < 35 )
                {
                    cout << "\nREPRODUCTION: ";
                    // herbivore alwasy reproduce, 50/50 for carnivore
                    addAnimal(population, "herbivore", herb[rand()%MAX], 1);
                    addAnimal(population, "herbivore", herb[rand()%MAX], 1);
                    cout << "A new set of herbivore was born!";
                    if ((rand() % E_MAX) <= 50) 
                    {   
                        addAnimal(population, "carnivore", carn[rand()%MAX], 1);
                        cout << " And a new carnivore was born!";
                    }
                }
                else if (roll < 50 || ((drought || blizzard) && roll < 90)) 
                {
                    cout <<"\nDEATH: ";
                    if (drought || blizzard) 
                    {
                        cout << "Herbivore's couldn't find any food, "
                             << " a herbivore died from starvation...";
                        deadAnimal(population, "herbivore"); 
                    }
                    if (countTotalAnimal(population, "herbivore") < 10)
                    {
                        cout << "Carnivore's couldn't find any herbivore's, "
                             << "3 carnivore's died from starvation...";
                        for (int i = 0; i < MAX; i++)
                            deadAnimal(population, "carnivore");        
                    }
                }
                if (roll < 30 && !drought && !blizzard && !flooding)
                {  
                    cout << "\nWEATHER: ";
                    if (rand() % E_MAX < 33) 
                    {
                        drought = 1;
                        cout << "A drought has started!";
                    }
                    else if (rand() % E_MAX < 66)
                    {
                        flooding = 1;
                        cout << "A flood has started!";
                    }
                    else if (rand() % E_MAX < 100)
                    {
                        blizzard = 1;  
                        cout << "A bliizard has started!";
                    }
                }
                else if (drought || blizzard || flooding)
                {
                    drought = 0;
                    blizzard = 0;
                    flooding = 0;
                    cout << "\nThe weather has returned to normal...";
                }
                if (roll < 25 || (!blizzard && !flooding && roll < 50)) 
                { // independant from the rolls above.
                    cout << "\nPREDATION: ";
                    deadAnimal(population, "herbivore");
                    cout << "A carnivore ate a herbivore!";
                }
                if (herbPop)
                {
                    cout << "\ncarnivore's ate an excess of herbivore's!";
                    deadAnimal(population, "herbivore");
                    deadAnimal(population, "herbivore");
                    deadAnimal(population, "herbivore");
                }
                if (carnPop)
                {
                    cout << "\nToo many carnivore's, some go hungry...";
                    deadAnimal(population, "carnivore");
                }
                if (countAnimal(population, "herbivore", OLD) > 3)
                {
                    cout << "\nSome herbivore's die of old age...";
                    population["herbivore"][OLD].pop_front();
                }
                if (countAnimal(population, "carnivore", OLD) > 3)
                {
                    cout << "\nSome carnivore's die of old age...";
                    population["carnivore"][OLD].pop_front();
                }
              
                event = 10; // reset event chance.
            }
            else
            {
                cout << "Nothing occured...";
                event += 10;
            }
            this_thread::sleep_for(chrono::seconds(1)); // "simulate" time passing

        }
        display(population);
        // check if a certain pop is overpopulated.
        if (countTotalAnimal(population, "herbivore") > 50)
        {
            herbPop = 1;
             cout << "\nHerbivore population is quite large!";
        }
        else 
        {
            herbPop = 0;
            cout << "\nHerbivore population is normal.";
        }
        if (countTotalAnimal(population, "carnivore") > 35)
        {
            carnPop = 1;
            cout << "\nCarnivore population is quite large!";
        }
        else
        {
            carnPop = 0;
            cout << "\nCarnivore population is normal.";
        }

        char YN = 'Y';
        cout << "\nWould you like to continue the simulation? (Y/N): ";
        cin >> YN;
        if (YN == 'N' || YN == 'n')
            cont = 1;
    ageAnimal(population); // increase all animals age by 1
    moveAnimal(population); // check if any should move age brackets.
    cout << endl;
    }
    cout << "\nGoodybye!";
}
