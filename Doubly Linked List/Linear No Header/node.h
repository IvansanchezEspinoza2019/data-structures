#ifndef NODE_H
#define NODE_H
#include<iostream>

template <class T>
class Node{
private:
    T data;
    Node<T>* next;
    Node<T>* prev;
    
public:
    Node();
    Node(const T&);

    T getData() const;
    Node<T>* getNext();
    Node<T>* getPrev();
    void setData(const T&);
    void setNext(Node<T>*);
    void setPrev(Node<T>*);
    
};

using namespace std;

template<class T>
Node<T>::Node() : next(nullptr), prev(nullptr){
}

template<class T>
Node<T>::Node(const T &e) :data(e), next(nullptr), prev(nullptr){

}

template<class T>
T Node<T>::getData() const
{
    return data;
}

template<class T>
Node<T>* Node<T>::getNext()
{
    return next;
}
template<class T>
Node<T>* Node<T>::getPrev()
{
    return prev;
}


template<class T>
void Node<T>::setData(const T &e)
{
    data = e;
}

template<class T>
void Node<T>::setNext(Node<T> *p)
{
    next = p;
}
template<class T>
void Node<T>::setPrev(Node<T> *p)
{
    prev = p;
}



#endif // NODE_H

