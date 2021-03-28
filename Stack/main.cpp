#include<iostream>
#include"stack.h" //import the stack.h file

int main(){
    // instance of a stack
    Stack<int> stack; 
    
    std::cout <<"\t .: PUSH :."<<std::endl;
    // pushing elements into the stack
    for(int i=0; i < 10; i++){
        std::cout <<i<<"-";
        stack.push(i); 
    }
    
    // creating a copy of the stack
    Stack<int> stackCopy(stack);
    

    std::cout <<"\n\n\t .: POP :."<<std::endl;
    // pop elements from the original stack 
    while (!stack.isEmpty()){
       std::cout <<stack.pop() << "-";
    }
    std::cout << "\nStack empty!"<<std::endl;

    
    std::cout <<"\n\t .: Stack copy size :."<<std::endl;
    std::cout << stackCopy.size() << std::endl;

    stackCopy.~Stack(); // deleting all elements

    return 0;
}