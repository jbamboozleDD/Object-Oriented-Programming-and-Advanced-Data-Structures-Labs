#include "mystring.h"
#include <iostream>
#include <cassert>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <cctype>

namespace coen79_lab5
{
    string::string(const char str[]){
        size_t i = strlen(str);   //ensures precondition and gets size of str
        allocated = 0;
        current_length = 0;
        reserve(i);
        std::copy(str, str + i, characters);
        current_length = i;
    }

    string::string(char c){
        allocated = 0;
        current_length = 0;
        reserve(2);
        characters[0] = c;
        characters[1] = '\0';   //need this so other functions can identify when the string ends
        current_length = 1;
    }

    string::string(const string& source){   //copy constructor
        current_length = 0;
        allocated = 0;
        reserve(source.allocated);
        std::copy(source.characters, source.characters + source.current_length, characters);
        current_length = source.current_length;
    }

    string:: ~string( ){    //deconstructor
        delete []characters;
        allocated = 0;
        current_length = 0; 
    }

    void string::reserve(size_t n){
        if(n == allocated ){    //if n is same as previous allocation, do nothing
            return;
        }
        if (n < current_length + 1){    //if n is less than previous allocation, set n to real size of string
            n = current_length+1;
        }
        char* temp = new char[n];   //creates array for characters pointer
        if(current_length != 0){    //error when trying to copy something of 0 length
            std::copy(characters, characters + current_length, temp);
            delete []characters;
        }
        characters = temp;
        allocated = n;
        return;
   }

    void string::operator +=(const string& addend){
        reserve(allocated + addend.allocated);
        int k = 0;
        for(int i = length(); i < (length() + addend.length()); i++){   //need seperate iterator for different characters functions
            characters[i] = addend.characters[k];
            k++;
        }
        current_length = length() + addend.length();
    }

    void string::operator +=(const char addend[ ]){
        size_t i = strlen(addend);  //makes sure addend is valid string and gets its length
        reserve(allocated + i);
        int k = 0;
        for(int j = length(); j < (length() + i); j++){
            characters[j] = addend[k];
            k++;
        }
        current_length = length() + i;
    }

    void string::operator +=(char addend){
        reserve(allocated + 1);
        characters[length()] = addend;
        current_length = length() + 1;
        characters[length()] = '\0';    //imporant for other functions to work right
    }
    
    string& string::operator =(const string& source){
        reserve(source.allocated);
        std::copy(source.characters, source.characters + source.length(), characters);
        current_length = source.length();   //everything gets copied
    }

    //don't need to worry about stuff before position, put string in at position, then add half originally behind
    //poistion to end
    void string::insert(const string& source, unsigned int position){
        size_t len = length();
        reserve(source.allocated + allocated);
        char temp[len - position];
        std::strncpy(temp, characters + position, len - position);
        std::strncpy(characters + position, source.characters, source.length());
        std::strncpy(characters + position + 1, temp, len - position);
        current_length = len + source.current_length;
        return;
    }

    //copy stuff from after position + num over onto position and reset current length to ignore leftovers
    void string::dlt(unsigned int position, unsigned int num){
        assert(position + num <= length());
        size_t len = length();
        char temp[len - position - num];
        std::strncpy(temp, characters + position + num, len - position - num);
        std::strncpy(characters + position, temp, len - position - num);
        current_length = len - num;
        reserve(len - num);
        return;
    }

    
    void string::replace(char c, unsigned int position){
        assert(position <= length());
        this->characters[position] = c;
        return;
    }

    void string::replace(const string& source, unsigned int position){
        assert(source.length() + position <= length());
        int k = 0;
        for(int i = position; i < position + source.length(); i++){     //need different iterators for each characters array
            characters[i] = source.characters[k];
            k++;
        }
        return;
    }

    // CONSTANT MEMBER FUNCTIONS
    //size_t length( ) const { return current_length; }

    char string::operator[](size_t position) const{
        assert(position < length());
        return characters[position];
    }

    int string::search(char c) const{
        for(int i = 0; i < length(); i++){
            if(characters[i] == c)
                return i;
        }
        return -1;
    }

    int string::search(const string& substring) const{
        int flag = -1;
        int subitr;
        for(int i = 0; i < (length() - substring.length())+1; i++){  
            if(substring.characters[0] == characters[i]){         //loops through string looking for beginning of substring
                flag = i;
                subitr = 0;
                for(int j = i; j < (i + substring.length()); j++){       //if beginning of substring is found, then checks if following
                    if(characters[j] != substring.characters[subitr]){   //letters match the substring
                        flag = -1;  //flag made -1 if substring doesn't match
                    }
                    subitr++; 
                }
            }
            if(flag != -1)
                return flag;
        }
        return -1;
    }

    unsigned int string::count(char c) const{
        unsigned int cntr = 0;
        for(int i = 0; i < length(); i++){
            if(characters[i] == c)
                cntr++;
        }
        return cntr;
    }

    // FRIEND FUNCTIONS
    std::ostream& operator <<(std::ostream& outs, const string& source){
        for(int i = 0; i < source.length(); i++){
            outs << source.characters[i];
        }
        return outs;
    }

    bool operator ==(const string& s1, const string& s2){
        if(strcmp(s1.characters, s2.characters) == 0)
            return true;
        return false;
    }

    bool operator !=(const string& s1, const string& s2){
        return !(s1 == s2);
    }

    bool operator > (const string& s1, const string& s2){
        if(strcmp(s1.characters, s2.characters) > 0)
            return true;
        return false;
    }

    bool operator < (const string& s1, const string& s2){
        if(strcmp(s1.characters, s2.characters) < 0)
            return true;
        return false;
    }

    bool operator >=(const string& s1, const string& s2){
        if(strcmp(s1.characters, s2.characters) >= 0)
            return true;
        return false;
    }

    bool operator <=(const string& s1, const string& s2){
        if(strcmp(s1.characters, s2.characters) <= 0)
            return true;
        return false;
    }

    string operator +(const string& s1, const string& s2){
        string temp;
        temp.reserve(s1.length() + s2.length());
        temp += s1;
        temp += s2;
        return temp;
    }

    string operator +(const string& s1, const char addend[]){
        string temp;
        temp.reserve(s1.length() + strlen(addend));
        temp += s1;
        temp += addend;
        return temp;
    }

    std::istream& operator >>(std::istream& ins, string& target){
        char t;
        string temp;
        ins.get(t);     //gets one character at a time
        while(isspace(t) != 0){     //isspace checks if character is ' ', /n, etc...
            ins.get(t);             //skips over all white spaces
        }
        while(isspace(t) == 0 && t != '\0'){    //adds one character at a time until end of string or new whitespace
            temp+=t;
            ins.get(t);
        }
        target = temp;
        return ins;
    }
}