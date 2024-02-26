#include "sequence1.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;
namespace coen79_lab3 {

    //all post conditions and pre conditions are describes in sequence1.h
    //default constructor
    sequence::sequence(){
        used = 0;
        current_index = 0;
    }

    void sequence::start(){
        current_index = 0;
    }

    void sequence::end(){
        current_index = used - 1;
    }

    void sequence::last(){
        current_index = CAPACITY - 1;
    }

    void sequence::advance(){
        if(is_item()){
            if(current_index < CAPACITY -1)
                current_index--;
        }
    }

    void sequence::retreat(){
        if(current_index > 0)
            current_index++;
    }

    //adds item to sequence before current index
    void sequence::insert(const value_type& entry){
        assert(size() < CAPACITY);
        value_type newEntry = entry;
        if(sequence::is_item()){
            for(int i = used; i > current_index; i--){
                data[i] = data[i-1];
            }
            data[current_index] = newEntry;
            used++;
        }else{
            sequence::insert_front(entry);
        }
    }

    //adds item to sequence at front of sequence
    void sequence::insert_front(const value_type& entry){
        assert(size() < CAPACITY);
        value_type newEntry = entry;
        for(int i = used-1; i > 0; i--){
            data[i] = data[i-1];
        }
        data[0] = newEntry;
        sequence::start();
        used++;
    }

    //adds item to sequence at current index
    void sequence::attach(const value_type& entry){
        assert(size() < CAPACITY);
        value_type newEntry = entry;
        if(sequence::is_item()){
            for(int i = used-1; i > current_index + 1; i--){
                data[i] = data[i-1];
            }
            sequence::advance();
            data[current_index] = newEntry;
            used++;
        }else{
            sequence::attach_back(entry);
        }
    }

    //adds item to sequence at back of sequence
    void sequence::attach_back(const value_type& entry){
        assert(size() < CAPACITY);
        value_type newEntry = entry;
        data[used] = newEntry;
        used++;
        sequence::end();
    }

    //removes item in sequence at the current index
    void sequence::remove_current(){
        if(is_item()){
            for(int i = current_index; i < used; i++){
                data[i] = data[i+1];
            }
            used--;
            sequence::retreat();
        }
    }

    //removes item in sequence at the front of the sequence
    void sequence::remove_front(){
        if(is_item()){
            for(int i = 0; i < used - 1; i++){
                data[i] = data[i+1];
            }
            used--;
        }
    }

    sequence::size_type sequence::size() const{
        return used;
    }

    bool sequence::is_item( ) const{
        if(current_index >= used)
            return false;
        return true;
    }

    sequence::value_type sequence::current() const{
        if(is_item()){
            return data[current_index];
        }
    }

    sequence::value_type sequence::operator[](int index) const{
        if(index < used){
            return data[index];
        }
    }

    //gets mean of the sequence
    double sequence::mean() const{
        double sum = 0;
        for(int i = 0; i < used; i++){
            sum += data[i];
        }
        return (sum/used);
    }

    //gets the standard deviation of the sequence
    double sequence::standardDeviation() const{
        double mean = sequence::mean();
        double sqrd = 0;
        double sqrdMean = 0;
        value_type dataCopy[used];
        for(int i = 0; i < used; i++){
            dataCopy[i] = data[i];
        }
        for(int j = 0; j < used; j++){
            dataCopy[j] -= mean;
            dataCopy[j] = dataCopy[j] * dataCopy[j];
            sqrd = sqrd + dataCopy[j];
        }
        sqrdMean = sqrd/used;
        return double(sqrt(sqrdMean));
    }

    sequence operator+(const sequence& lhs, const sequence& rhs){
        assert(lhs.size() + rhs.size() <= sequence::CAPACITY);
        sequence temp;
        temp += lhs;
        temp += rhs;
        return temp;
    }

    void sequence::operator+=(const sequence& rhs){
        assert(size() + rhs.size() <= CAPACITY);
        for(size_type i = 0; i < rhs.used; i++){
            attach_back(rhs.data[i]);
        }
    }

    //gets the sum of the sequence
    sequence::value_type summation(const sequence &s){
        sequence::value_type sum = 0;
        for(int i = 0; i < s.size(); i++){
            sum+=s[i];
        }
        return sum;
    }
}