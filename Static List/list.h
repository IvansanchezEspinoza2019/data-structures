#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <exception>
#include <string>
#include <iostream>

template<class T, int ARRAYSIZE=1024>
class List {
    private:
        T data[ARRAYSIZE];
        int last;
        bool isValidPos(const int&);
        void copyAll(const List<T,ARRAYSIZE> & s);
        //mezcla
        void sortDataMerge(const int&,const int&);
    public:
        List(); //constructor
        List(const List<T,ARRAYSIZE> &); //constructor copia
        //clase Exception anidada
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
        //operaciones de la lista
        bool isEmpty();
        bool isFull();
        void insertData(const int&, const T&);
        void deleteData(const int&);
        int getFirst();
        int getLast();
        int getPrevPos(const int&);
        int getNextPos(const int&);
        T retrieve(const int&); //retorna un valor de tipo T
        void print();
        void deleteAll();
        std::string toString(); //convierte un objeto en cadena
        void sortDataBubble(); //ordenamiento burbuja
        void swapData(T &a, T &b); //intercambia dos datos de tipo T
        int findData(const T&);//busqueda lineal
        int findDataBin(const T&); //busqueda binaria
        //mezclas
        void sortDataMerge();

        List<T, ARRAYSIZE>& operator = (const List<T, ARRAYSIZE>&); //operador de asignacion
        bool operator <(const T&s);
    };

#include "list.h"
using namespace std;

template<class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isValidPos(const int &p){
return p>=0 and p<=(last+1);
}
template<class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List(): last(-1){
}

template<class T, int ARRAYSIZE>
List<T,ARRAYSIZE>::List(const List<T, ARRAYSIZE> &s)
{
    copyAll(s);
}
template<class T, int ARRAYSIZE>
List<T, ARRAYSIZE>& List<T,ARRAYSIZE>::operator =(const List<T,ARRAYSIZE>&t)
{
    copyAll(t); //llama al metodo copiar
    return *this;
}

template<class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE> ::isEmpty() {
    return last == -1;
}

template<class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE> ::isFull() {
    return last == ARRAYSIZE - 1;
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE> ::insertData(const int &p, const T &e) {
    if(isFull()) {
        throw Exception("Desbordamiento de datos, Lista llena, insertData");
        }
    if(!isValidPos(p)){
            throw Exception("Posicion invalida, insertData");
        }

    int i(last+1);
    while(i>p) {
        data[i]= data[i-1];
        i--;
        }
    data[p] = e;
    last++;
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE> ::deleteData(const int&p) {
    if(isEmpty()) {
        throw Exception("Insuficiencia de datos, deleteData");
        return;
        }
    if(!(p>=0 and p<=last)) {
        throw Exception("Posicion invalida, deleteData");
        }

    int i(p);
    while(i < last) {
        data[i] = data[i+1];
        i++;
        }
    last--;
    }

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE> ::getFirst() {
    if(isEmpty()) {
        return -1;
        }
    return 0;
    }

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE> ::getLast() {
    return last;
    }

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE> ::getPrevPos(const int&p) {
    if(isEmpty() or p<1 or p>last) {
        return -1;
        }
    return p-1;
    }

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE> ::getNextPos(const int&p) {
    if(isEmpty() or p < 0 or p>last-1) {
        return -1;
        }
    return p+1;
    }

template<class T, int ARRAYSIZE>
T List<T, ARRAYSIZE> ::retrieve(const int&p) {
    if(isEmpty()) {
        throw Exception("Insuficiencia de datos, retrieve");
        }
    if(p<0 or p>last){
        throw Exception("Posicion invalida, retrieve");
    }
    return data[p];
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE> ::print() {

    int i(0);
    while(i<=last){
        cout << i+1<<". "<<data[i] << endl;
        i++;
    }
}

template<class T, int ARRAYSIZE>
void List<T,ARRAYSIZE> ::deleteAll() {
    last = -1;
}

template<class T, int ARRAYSIZE>
void List<T,ARRAYSIZE>::copyAll(const List<T,ARRAYSIZE> & s){
    int i(0);
    while(i<=s.getLast()){
        this->data[i] = s.data[i];
        i++;
    }
    this->last = s.last;
}

//to string
template<class T, int ARRAYSIZE>
string List<T,ARRAYSIZE>::toString()
{
    string result;

    int i= 0;
    while (i<= last) {
        result += data[i].toString() + "\n";
        i++;
    }

    return result;
}
template<class T, int ARRAYSIZE>
void List<T,ARRAYSIZE>::swapData(T& a, T& b){
T aux(a);
a = b;
b = aux;
}
//busqueda lineal
template<class T, int ARRAYSIZE>
int List<T,ARRAYSIZE>::findData(const T& e){
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
void List<T,ARRAYSIZE>::sortDataBubble() //ordenamiento burbuja
{
    int i(last), j;
    bool flag = false;
    do{
        flag = false;
        j=0;
        while (i<j) {
            if(data[j]>data[j+1]){
                flag = true;
                swapData(data[j],data[j+1]);
            }
            j++;
        }
        i--;
    }while(flag==true);
}
template<class T, int ARRAYSIZE>
int List<T,ARRAYSIZE>::findDataBin(const T &e){
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
    template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE> ::sortDataMerge(const int& leftEdge,const int& rightEdge)() {
    if(leftEdge>= rightEdge){	//criterio de paro
    	return;
    }
    int m((leftEdge+rightEdge)/2);
    //divide y venceras
    sortDataMerge(leftEdge,m); //ordena lado izquierdo(recursivo)
    sortDataMerge(m+1,rightEdge);//ordena lado derecho(recursvo)
    
    //intercalacion
    static T temp[ARRAYSIZE];
    for(int z(leftEdge); z<= rightEdge; z++){
    	temp[z]= data[z];
    }
    
    int i(leftEdge), j(m+1), x(leftEdge);
    while(i<=m and j<= rightEdge){
    	
    	while(i<= m and temp[i]<=temp[j]){
    		data[x++]= temp[i++];
    	}
    	
    	if(i<=m){
    		while(j<= righEdge and temp[j]<= temp[i]){
    			data[x++]= temp[j++];
    		}
    	}
    }
    	//
    	while(i<= m){
    		data[x++]= temp[i++];
    	}
    	while(j<= righEdge){
    			data[x++]= temp[j++];
    		}  
    }

#endif // LIST_H_INCLUDED
