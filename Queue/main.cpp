#include<iostream>
#include <random>
#include <functional>
#include"queue.h"   

int main(){

     // to generate random numbers
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0,1000);
    auto random = std::bind( distribution, generator );

    // queue object
    Queue<double> queue;

    std::cout << "Inserting elements... "<<std::endl;
    for(int i= 0; i < 10; i++){
        queue.enqueue(random()); // inserts at the end
    }

    // queue size
    std::cout << "Queue size: "<<queue.size() << std::endl;

    // sumatory
    double sum = 0.0;
    while(!queue.isEmpty()){
        sum+=queue.dequeue(); // return and deletes the front of the queue
    }

    std::cout << "\nSumatory of elemens: "<< sum << std::endl;

    return 0;
}