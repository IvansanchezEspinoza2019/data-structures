/*
    This is a simple list which has a pre-defined size. When the 
    list is full, then there is no way to reserve more memory to 
    store new elements, so erasing elements is needed.

    Description:
        The list uses <templates> to admit any class or data type 
        (class T). ARRAYSIZE value especify the list lenght.
*/

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <exception>
#include <string>
#include <iostream>

// exception class
class Exception : public std::exception {
    private:
        std::string msg;
    public:
        explicit Exception(const char* message) : msg(message) { }
        explicit Exception(const std::string& message) : msg(message) { }
        virtual ~Exception() throw () { }
        virtual const char* what() const throw () {
            return msg.c_str();
            }
};

template<class T, int ARRAYSIZE=1024> 
class List {
    private:
        T data[ARRAYSIZE];                        // array of class 'T' with 'ARRAYSIZE' lenght
        int last;                                 // the last element position
        bool isValidPos(const int&);
        void copyAll(const List<T,ARRAYSIZE> & s);
        void sortDataMerge(const int&,const int&);   

    public:
        // constructor
        List();                 
        // 2nd constructor       
        List(const List<T,ARRAYSIZE> &);      

        //methods
        bool isEmpty();
        bool isFull();
        void insertData(const int&, const T&);
        void push_back(const T&);
        void deleteData(const int&);
        int getFirst();
        int getLast();
        int getPrevPos(const int&);
        int getNextPos(const int&);
        T retrieve(const int&); 
        void print();
        void deleteAll();
        std::string toString(); 
        
        // search
        int findData(const T&);    // lineal search
        int findDataBin(const T&); // binary search
        //sorting
        void swapData(T &a, T &b); // swap data
        void sortDataMerge();      // merge sort
        void sortDataBubble();     // bubble sort

        // operators
        List<T, ARRAYSIZE>& operator = (const List<T, ARRAYSIZE>&); 
        bool operator <(const T&s);   
    };

#include "list.h"
using namespace std;

template<class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isValidPos(const int &p){  // verify if a given position is valid
    return p>=0 and p<=(last+1); // is in range of the indexes of the list
}

template<class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List(): last(-1){ // initialize le list with last=-1 because there is no elements yet
}

template<class T, int ARRAYSIZE>
List<T,ARRAYSIZE>::List(const List<T, ARRAYSIZE> &s)
{
    copyAll(s);
}
template<class T, int ARRAYSIZE>
List<T, ARRAYSIZE>& List<T,ARRAYSIZE>::operator =(const List<T,ARRAYSIZE>&t)  // copy an entire list
{
    copyAll(t); 
    return *this;
}

template<class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE> ::isEmpty() { //verify if the list is empty
    return last == -1;
}

template<class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE> ::isFull() { // verify if the list is full
    return last == ARRAYSIZE - 1;
}
template<clas T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::push_back(const T &e){
    insertData(last+1, e);
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE> ::insertData(const int &p, const T &e) { // inserts data to the list
    if(isFull()) {      // if full list
        throw Exception("Data overflow: the list is full in insertData()");
    }
    if(!isValidPos(p)){ //if the position is invalid
            throw Exception("Invalid position, insertData()");
    }

    int i(last+1);          // init an auxiliar iterator with the last element position+1
    while(i>p) {            // until i reaches the position when we want to insert
        /*
            scrolls the elements one positioon forward begining
            from 'p+1' to last+1 beacause we need to store a new one 
            element.
        */
        data[i]= data[i-1]; 
        i--;
    }
    data[p] = e; // override the actual element(already moved forward) with the new one
    last++; // increment the amount of elements
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE> ::deleteData(const int&p) { // delete an element from the list
    if(isEmpty()) {
        throw Exception("Empty list, deleteData()");
        return;
    }
    if(!(p>=0 and p<=last)) {
        throw Exception("Invalid position, deleteData()");
    }

    int i(p);       
    while(i < last) {  
        /*
            scrolls the elements one position back begining
            from the position we want to delete.
        */
        data[i] = data[i+1];
        i++;
        }
    last--; // erase the amount of elements
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE> ::getFirst() {  // get the index of the first element
    if(isEmpty()) {
        return -1;
        }
    return 0;
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE> ::getLast() { // get the index of last element
    return last;
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE> ::getPrevPos(const int&p) { // get the index of the previos element
    if(isEmpty() or p<1 or p>last) {
        return -1;
        }
    return p-1;
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE> ::getNextPos(const int&p) { // get the index of the next element
    if(isEmpty() or p < 0 or p>last-1) {
        return -1;
        }
    return p+1;
}

template<class T, int ARRAYSIZE>
T List<T, ARRAYSIZE> ::retrieve(const int&p) { // get the data from an index
    if(isEmpty()) {
        throw Exception("Empty List, retrieve()");
        }
    if(p<0 or p>last){
        throw Exception("Invalid position, retrieve()");
    }
    return data[p]; // return the element
}

template<class T, int ARRAYSIZE>
void List<T,ARRAYSIZE> ::deleteAll() { // delete everything
// just with this line because al data is going to be override when inserting
    last = -1; 
}

template<class T, int ARRAYSIZE>
void List<T,ARRAYSIZE>::copyAll(const List<T,ARRAYSIZE> & s){  // copy all elements from a list
    int i(0);
    while(i<=s.getLast()){
        this->data[i] = s.data[i];
        i++;
    }
    this->last = s.last;
}

template<class T, int ARRAYSIZE>
string List<T,ARRAYSIZE>::toString() // to_string() method
{
    string result;

    int i= 0;
    while (i<= last) {
        result += data[i].toString() + "-";
        i++;
    }

    return result;
}
template<class T, int ARRAYSIZE>
void List<T,ARRAYSIZE>::swapData(T& a, T& b){  // used to swap data from to positions
    T aux(a);
    a = b;
    b = aux;
}

template<class T, int ARRAYSIZE>
int List<T,ARRAYSIZE>::findData(const T& e){ // lineal search
    int i(0);
    while(i<=last){
        if(data[i]==e){
            return i;
        }
        i++;
    }
    return -1;
}

template<class T, int ARRAYSIZE>
void List<T,ARRAYSIZE>::sortDataBubble() //bubble sorting
{
    int i(last), j;
    bool flag = false;   // just to do it more eficient
    do{
        flag = false;
        j=0;
        while (j < i) {
            if(data[j]>data[j+1]){   
                flag = true;
                swapData(data[j],data[j+1]); // order
            }
            j++;
        }
        i--;
    }while(flag==true); // while at least one element swap with other  
}
template<class T, int ARRAYSIZE>
int List<T,ARRAYSIZE>::findDataBin(const T &e){ // binary search, needs the list to be sorted first
    int i(0), j(last), mid;

    while(i<=j){
        mid = (i+j)/2;

        if(data[mid]==e){
            return mid;
        }
        if(data[mid]>e){
            j = mid-1;
        }
        else{
            i = mid+1;
        }
    }
    return -1;
}
template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE> ::sortDataMerge() {
    sorDataMerge(0, last);
}

template<class T, int ARRAYSIZE>     // merge sort
int List<T, ARRAYSIZE> ::sortDataMerge(const int& leftEdge,const int& rightEdge)() {
    if(leftEdge>= rightEdge){	        // stoping step
    	return;
    }
    int m((leftEdge+rightEdge)/2);      // split the actual array, m is the middle of the array
   
    sortDataMerge(leftEdge,m);          //sort the left side(recursive)
    sortDataMerge(m+1,rightEdge);       //osort the right side(recursive)
    
    
    static T temp[ARRAYSIZE];           // temp array

    for(int z(leftEdge); z<= rightEdge; z++){  // copy the elements without sorting
    	temp[z]= data[z];
    }
    // init the begininig, middle and the end of the array
    int i(leftEdge), j(m+1), x(leftEdge);

    while(i<=m and j<= rightEdge){  
        /*  here is comparing the values of the two 'splited' arrays.
            The first part is from i(leftEdge) index to m(middle), second from j(m+1) to 
            the end of the array(tightEdge).
        */
    	
        while(i<= m and temp[i]<=temp[j]){
            /*
            puts the elems if the first array(i index) are smaller than
            the second array(j index)
            */
    	    data[x++]= temp[i++];
        }
    	
        if(i<=m){
            /*
            here is doing the other case, when the second array(j index) is 
            smaller than the first one(i index).
            */
    	    while(j<= righEdge and temp[j]<= temp[i]){
    		    data[x++]= temp[j++]; //  so puts the value of the elem in j index
    	    }
        }
    }

    /*
        Here do just the same as above but with the remaining elements
    */
    while(i<= m){ 
        // means that were not selected because of the 2nd array had smaller values
    	data[x++]= temp[i++];
    }
    while(j<= righEdge){  
        // means that were not selectd because of 1st array had smaller values
    	data[x++]= temp[j++];
    }  
}

#endif // LIST_H_INCLUDED
