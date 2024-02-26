#ifndef RAND_NUM_GEN_H
#define RAND_NUM_GEN_H
#include <iostream>
#include <cassert>
using namespace std;
namespace coen79_lab2 {
    //custom class for creating random numbers
    class rand_gen
    {
    public:
        rand_gen(int seed, int multiplier, int increment, int modulus);
        int next();
        void set_seed(int newSeed);
        void print_info();

    private:
        int seed;
        int multiplier;
        int increment;
        int modulus;
    };
}
#endif
