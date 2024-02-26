#include "poly.h"
#include <iostream>
#include <iomanip>

using namespace coen79_lab4;

void printTest(){
    polynomial p1, p2;
    std::cout << p1 << std::endl;

    p1.assign_coef(5, 2);
    std::cout << p1 << std::endl;

    p1.assign_coef(3,0);
    p1.assign_coef(-4,1);
    std::cout << p1 << std::endl;

    p2.assign_coef(8,1);
    //std::cout << "flag" << std::endl;
    p1 = p1 + p2;
    std::cout << p1 << std::endl;

    p2.clear();
    p1.assign_coef(-2.5,3);
    std::cout << p1 << std::endl;

    p2.assign_coef(-7.2,0);
    std::cout << p2 << std::endl;

    p2.assign_coef(-3,5);
    std::cout << p2 << std::endl;
}

int main(){
    std::cout << "Testing Printing Function" << std::endl;
    printTest();

    std::cout << "Constructor Tests" << std::endl;
    polynomial p1, temp;
    polynomial p2(5.2,0);
    polynomial p3(3.7,29);
    polynomial p4(4.6,13);
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
    std::cout << p4 << std::endl;

    std::cout << "Assignment Tests" << std::endl;
    p1.clear();
    p2.clear();
    p1.assign_coef(9,0);
    p1.assign_coef(8,1);
    p1.assign_coef(7,17);
    p1.assign_coef(6,28);
    p1.assign_coef(5,29);
    std::cout << p1 << std::endl;
    std::cout << "Degree: " << p1.degree() << std::endl;

    p2.assign_coef(-4,0);
    p2.assign_coef(-3.5,1);
    p2.assign_coef(-3,17);
    p2.assign_coef(-2.5,28);
    p2.assign_coef(-2,29);
    std::cout << p2 << std::endl;

    std::cout << "Add To Tests" << std::endl;
    temp.assign_coef(12,0);
    p1 = p1 - temp;
    temp.clear();
    temp.assign_coef(4,29);
    p2 = p2 + temp;
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;

    std::cout << "Next Term Tests" << std::endl;
    std::cout << "Next term after 29 is " << p1.next_term(29) << std::endl;
    std::cout << "Next term after 20 is " << p1.next_term(20) << std::endl;
    std::cout << "Term before 20 is " << p1.previous_term(20) << std::endl;
    std::cout << "Next term after 5 is " << p1.next_term(5) << std::endl;
    std::cout << "Term before 5 is " << p1.previous_term(5) << std::endl;
    std::cout << "Term before 0 is " << p1.previous_term(0) << std::endl;

    std::cout << "Is Zero Test" << std::endl;
    if(p1.is_zero())
        std::cout << p1 << " is zero." << std::endl;
    else
        std::cout << p1 << " is not zero." << std::endl;
    p1.clear();
    if(p1.is_zero())
        std::cout << p1 << " is zero." << std::endl;
    else
        std::cout << p1 << " is not zero." << std::endl;

    std::cout << "Math Tests" << std::endl;
    p1.clear();
    p1.assign_coef(3,0);
    p1.assign_coef(4,1);
    p1.assign_coef(5,2);
    std::cout << p1 << std::endl;
    std::cout << std::fixed << std::setprecision(0) << "If x=4, f(x)=" << p1.eval(4) << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "If x=2.5, f(x)=" << p1.eval(2.5) << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "If x=-3.7, f(x)=" << p1.eval(-3.7) << std::endl;
    std::cout << "Derivate: " << p1.derivative() << std::endl;
    std::cout << "Antiderivative: " << p1.antiderivative() << std::endl;
    std::cout << std::fixed << std::setprecision(3) << "DefInt(f) from 0 to 5.7: " << p1.definite_integral(0,5.7) << std::endl;
    
    std::cout << "Math Operator Tests" << std::endl;
    p2.clear();
    p2.assign_coef(7.2,2);
    p2.assign_coef(-11.3,1);
    std::cout << "(" << p1 << ")" << " + " << "(" << p2 << ") = " << (p1+p2) << std::endl;
    std::cout << "(" << p1 << ")" << " - " << "(" << p2 << ") = " << (p1-p2) << std::endl;
    std::cout << "(" << p1 << ")" << " * " << "(" << p2 << ") = " << (p1*p2);
}