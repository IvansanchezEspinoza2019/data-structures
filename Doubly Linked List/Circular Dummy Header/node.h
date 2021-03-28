#ifndef NODE_H
#define NODE_H
#include<iostream>
#include <exception>
#include <string>

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

template <class T>
class Node{
private:
    T* dataPtr;
    Node<T>* next;
    Node<T>* prev;

public:
    Node();
    Node(const T&);
    ~Node();

    T* getDataPtr() const;
    T getData() const;
    Node<T>* getNext();
    Node<T>* getPrev();
    void setDataPtr(T*);
    void setData(const T&);
    void setNext(Node<T>*);
    void setPrev(Node<T>*);

};

using namespace std;

template<class T>
Node<T>::Node() : dataPtr(nullptr), next(nullptr), prev(nullptr){
}

template<class T>
Node<T>::Node(const T &e) : next(nullptr), prev(nullptr){
    dataPtr = new T(e);
    if(dataPtr == nullptr){
    throw Exception("No memory available, new Node()");
    }
}

template<class T>
Node<T>::~Node()
{
    delete dataPtr;
    dataPtr = nullptr;
}

template<class T>
T Node<T>::getData() const
{
    if(dataPtr == nullptr){
        throw Exception("No data found, getData()");
    }
    return *dataPtr;    //desreferenciar
}
template<class T>
T* Node<T>::getDataPtr() const
{
    return dataPtr;
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
    if(dataPtr == nullptr){
        if ((dataPtr = new T(e)) == nullptr){
            throw Exception("No memory available, setData()");
        }
    }
    else{
        *dataPtr = e;
    }
}
template<class T>
void Node<T>::setDataPtr(T* e)
{
    dataPtr = e;
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

