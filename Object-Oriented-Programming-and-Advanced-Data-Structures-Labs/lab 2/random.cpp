#include <cassert>
#include <iostream>
#include "random.h"

using namespace std;
namespace coen79_lab2
{
    //constructor to create new instance of a rand_gen object
    rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus)
    {
        this->seed = seed;
        this->multiplier = multiplier;
        this->increment = increment;
        this->modulus = modulus;
    }
    //gets the result of the random number equation and returns it while updating the seed
    int rand_gen::next()
    {
        seed = (multiplier * seed + increment) % modulus;
        return seed;
    }
    //allows user to change the seed being used
    void rand_gen::set_seed(int newSeed)
    {
        seed = newSeed;
    }
    //prints out all the info
    void rand_gen::print_info()
    {
        cout << "Seed: " << seed << endl;
        cout << "Multiplier: " << multiplier << endl;
        cout << "Increment: " << increment << endl;
        cout << "Modulus: " << modulus << endl;
        cout << "Next: " << next() << endl;
    }
}