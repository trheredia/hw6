#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {}; // store the substrings here
        int group = 4; // start filling from the last group index 
        int i = k.length() - 1; // starting index in the string
        while(i >= 0){
          unsigned long long value = 0; // value for current group
          unsigned long long power = 1; // to start the powers of 36
          int count = 0; // count for the characters in the group
          while(i >= 0 && count < 6){ // loop through all the characters
            char current = k[i]; // get the current character
            value += letterDigitToNumber(current) * power; // add the numerical value
            power *= 36; // get the next power
            i--; // move to previous letter
            count++; // increase the character count
          }
          w[group] = value; // store the groups value
          group--; // move to the next group
        }
        return (rValues[0]*w[0]) + (rValues[1]*w[1]) + (rValues[2]*w[2]) + (rValues[3]*w[3]) + (rValues[4]*w[4]);

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter >= 'A' && letter <= 'Z'){ // first convert any upper case
          letter = letter - 'A' + 'a';
        }
       
        if(letter >= 'a' && letter <= 'z'){ // index lower case numbers
          return letter - 'a';
        }
        else if(letter >= '0' && letter <= '9'){ // index any other characters
          return 26 + (letter - '0');
        }
    
        return 0; // otherwise return 0
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
