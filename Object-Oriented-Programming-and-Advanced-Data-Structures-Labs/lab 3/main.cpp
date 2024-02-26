#include "sequence1.h"
#include <iostream>
using namespace coen79_lab3;

//Prints the numbers currently in the sequence
void printSequence(sequence &seq){
    std::cout << "Contents:";
    for(int i = 0; i < seq.size(); i++){
        std::cout << " " << seq[i];
    }
    std::cout << std::endl;
    std::cout << "-----------------------------" << std::endl;
}

//prints the mean, standard deviation, and sum of the sequence
void printStats(sequence &seq){
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Mean: " << seq.mean() << std::endl;
    std::cout << "StdDev: " << seq.standardDeviation() << std::endl;
    std::cout << "Sum: " << summation(seq) << std::endl;
}

//tests for code
int main(){
    sequence test1;
    test1.insert(1);
    test1.insert(2);
    test1.insert(3);
    printStats(test1);
    printSequence(test1);

    sequence test2;
    test2.insert(2);
    test2.insert(3);
    test2.insert(4);
    printStats(test2);
    printSequence(test2);
    
    sequence test3;
    std::cout << "tester 3 :" << std::endl;
    test3 = test1 + test2;
    printStats(test3);
    printSequence(test3);
    std::cout << "tester 3 functions :" << std::endl;
    test3.advance();
    printStats(test3);
    printSequence(test3);
    test3.advance();
    printStats(test3);
    printSequence(test3);
    test3.remove_front();
    printStats(test3);
    printSequence(test3);
    test3.advance();
    printStats(test3);
    printSequence(test3);
    test3.remove_front();
    printStats(test3);
    printSequence(test3);
    test3.retreat();
    printStats(test3);
    printSequence(test3);
    test3.remove_current();
    printStats(test3);
    printSequence(test3);
    test3.attach_back(14);
    printStats(test3);
    printSequence(test3);
}