
#include<iostream>
#include <random>
#include <functional>
#include "list.h"   // put your LIST DIRECTORY

int main(){
    List<int, 50> list;  // instance of the static list

    // to generate random numbers
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,100);
    auto random = std::bind( distribution, generator );

    /// adding elements
    for(int i =0; i< 40; i++){
        list.push_back(random());
    }
    std::cout << "Elements added: \n" << list.toString() << std::endl;
    
    /// delete the first 10 elements 
    for(int i = 0; i < 10; i++){
        list.deleteData(0); 
    }
    std::cout << "\nUpdate after deleting: \n" << list.toString() << std::endl;


    // sorting
    list.sortDataMerge();
    
    std::cout << "\nUpdate after sorting: \n" << list.toString() << std::endl;
    
    return 0;
}