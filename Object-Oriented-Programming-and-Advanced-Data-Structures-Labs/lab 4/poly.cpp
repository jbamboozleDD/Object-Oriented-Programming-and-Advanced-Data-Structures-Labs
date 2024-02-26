#include "poly.h"
#include <iostream>
#include <cmath>
#include <cassert>
#include <climits>
#include <iomanip>

using namespace std;
namespace coen79_lab4{

    //loops backwards through coefficent array until finds a nonzero value, that value is the highest degree so
    //its index is made the current degree and the loop breaks
    void polynomial::update_current_degree(){
        current_degree = 0;
        for(int i = MAXIMUM_DEGREE; i > 0; i--){
            if(coef[i] != 0){
                current_degree = i;
                break;
            }
        }
    }

    //constructor for polynomial, assigns all values zero except for given coefficient at given exponent
    polynomial::polynomial(double c, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        for(int i = 0; i <= MAXIMUM_DEGREE; i++){
            coef[i] = 0.0;
        }
        coef[exponent] = c;
        this->update_current_degree();
    }

    //assigns coefficient at exponent value 
    void polynomial::assign_coef(double coefficient, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        coef[exponent] = coefficient;
        this->update_current_degree();
    }

    //adds value to current coefficient at give exponent
    void polynomial::add_to_coef(double amount, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        coef[exponent] = amount;
        this->update_current_degree();
    }

    //clears out coefficient array
    void polynomial::clear( ){
        for(int i = 0; i <= MAXIMUM_DEGREE; i++){
            coef[i] = 0.0;
        }
        this->update_current_degree();
    }

    //takes the indefinite integral of the polynomial
    polynomial polynomial::antiderivative( ) const{
        assert(degree() < MAXIMUM_DEGREE);
        polynomial temp;
        for(int i = current_degree + 1; i > 0; i--){
            temp.coef[i] = coef[i-1]/i;
        }
        temp.update_current_degree();
        return temp;
    }

    //gets coeffienct value
    double polynomial::coefficient(unsigned int exponent) const{
        return coef[exponent];
    }

    //takes the definite integral of the polynomial between the two give values
    double polynomial::definite_integral(double x0, double x1) const{
        polynomial temp = antiderivative();
        return temp.eval(x1) - temp.eval(x0);
    }

 // 	unsigned int polynomial::degree() const {}

    //takes teh derivative of the polynomial
   	polynomial polynomial::derivative() const{
        polynomial temp;
        for(int i = 0; i <= current_degree; i++){
            temp.coef[i] = coef[i+1]*(i+1);
        }
        temp.update_current_degree();
        return temp;
    }

    //returns value if you plugged x into the polynomial
   	double polynomial::eval(double x) const{
        double sum = 0;
        for(int i = 0; i <= current_degree; i++){
            sum += coef[i] * pow(x, i);
        }
        return sum;
    }

    //returns true if all coefficients are zero
    bool polynomial::is_zero() const{
        for(int i = 0; i <= MAXIMUM_DEGREE; i++){
            if(coef[i] != 0)
                return false;
        }
        return true;
    }

    //finds the next higher non-zero term
   	unsigned int polynomial::next_term(unsigned int e) const{
        for(int i = e + 1; i < current_degree; i++){
            if(coef[i] != 0)
            return i;
        }
        return 0;
    }

    //finds the next lower non-zero term
   	unsigned int polynomial::previous_term(unsigned int e) const{
        for(int i = e - 1; i > 0; i--){
            if(coef[i] != 0)
            return i;
        }
        return UINT_MAX;
    }

   // double polynomial::operator() (double x) const { return eval(x); }

    //adds the coeffients of both polynomials together
    polynomial operator+(const polynomial& p1, const polynomial& p2){
        polynomial temp;
        for(int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++){
            temp.coef[i] = p1.coef[i] + p2.coef[i];
        }
        temp.update_current_degree();
        return temp;
    }

    //subtracts coefficients of one polynomial from another
    polynomial operator-(const polynomial& p1, const polynomial& p2){
        polynomial temp;
        for(int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++){
            temp.coef[i] = p1.coef[i] - p2.coef[i];
        }
        temp.update_current_degree();
        return temp;
    }

    //multiplies cofficients and adds degrees of polynomials
    polynomial operator*(const polynomial& p1, const polynomial& p2){
        assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
        polynomial temp;
        for(int i = 0; i <= p1.degree(); i++){
            for(int j = 0; j <= p2.degree(); j++){
                temp.coef[i+j] += p1.coef[i] * p2.coef[j];
            }
        }
        temp.update_current_degree();
        return temp;
    }

    ostream& operator<<(ostream& out, const polynomial& p){
        if(p.is_zero()){
            out << "0.0";
            return out;
        }

        string sign;
        double temp;

        if(p.coef[p.current_degree] < 0){
            sign = "-";
            temp = p.coef[p.current_degree]*(-1);
        }else{
            sign = "";
            temp = p.coef[p.current_degree];
        }

        if(p.current_degree > 1){                                        //prints out first element since it is a unique case
            out << fixed << setprecision(1) << sign << temp << "x^" << p.current_degree;
        }
        if(p.current_degree == 1){
            out << fixed << setprecision(1) << sign << temp << "x";
        }
        if(p.current_degree == 0){
            out << fixed << setprecision(1) << sign << temp;
        }

        for(int i = p.current_degree - 1; i >= 0; i--){                 //prints out rest of elements if they exist
            if(p.coef[i] != 0){
                if(p.coef[i] > 0){
                    sign = '+';
                    temp = p.coef[i];
                }else{
                    sign = '-';
                    temp = p.coef[i]*(-1);
                }

                if(i > 1){
                    out << " " << fixed << setprecision(1) << sign << " " << temp << "x^" << i;
                }
                if(i == 1){
                    out << " " << fixed << setprecision(1) << sign << " " << temp << "x";
                }
                if(i == 0){
                    out << " " << fixed << setprecision(1) << sign << " " << temp;
                }
            }
        }
        return out;
    }
}