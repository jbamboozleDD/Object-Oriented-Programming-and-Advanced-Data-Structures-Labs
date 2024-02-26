//partner is Arran
#include <iostream>
#include "random.h"

using namespace coen79_lab2;

int main()
{
    rand_gen num(1, 40, 725, 729);  //creates new rand_num object

    for(int i = 0; i < 5; i++)  //produces 5 random numbers with seed starting at 1
    {
        num.print_info();
    }
    std::cout<<endl;

    num.set_seed(1);
    for(int i = 0; i < 5; i++)  //produces 5 random numbers with seed starting at 1
    {
        num.print_info();
    }
    std::cout<<endl;
    
    num.set_seed(15);   //produces 5 random numbers with seed starting at 15
    for(int i = 0; i < 5; i++)
    {
        num.print_info();
    }
    std::cout<<endl;
    
    rand_gen newNum(14, 85, 637, 1947); //creates new rand_num object
    for(int i = 0; i < 5; i++)  //produces 5 random numbers with seed starting at 14
    {
        newNum.print_info();
    }
    std::cout<<endl;
    
    newNum.set_seed(14);
    for(int i = 0; i < 5; i++)  //produces 5 random numbers with seed starting at 14
    {
        newNum.print_info();
    }

    return 0;
}