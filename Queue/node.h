#ifndef SmartNode_H
#define SmartNode_H
#include<iostream>
#include <exception>
#include <string>

class NodeException : public std::exception {
    private:
        std::string msg;
    public:
        explicit NodeException(const char* message) : msg(message) { }
        explicit NodeException(const std::string& message) : msg(message) { }
        virtual ~NodeException() throw () { }
        virtual const char* what() const throw () {
            return msg.c_str();
        }
};

template <class T>
class SmartNode{
private:
    T* dataPtr;
    SmartNode<T>* next;
    SmartNode<T>* prev;

public:
    SmartNode();
    SmartNode(const T&);
    ~SmartNode();

    

    T* getDataPtr() const;
    T getData() const;
    SmartNode<T>* getNext();
    SmartNode<T>* getPrev();
    void setDataPtr(T*);
    void setData(const T&);
    void setNext(SmartNode<T>*);
    void setPrev(SmartNode<T>*);

};

using namespace std;

template<class T>
SmartNode<T>::SmartNode() : dataPtr(nullptr), next(nullptr), prev(nullptr){
}

template<class T>
SmartNode<T>::SmartNode(const T &e) : next(nullptr), prev(nullptr){
    dataPtr = new T(e);
    if(dataPtr == nullptr){
        throw NodeException("No memory available, new Node()");
    }
}

template<class T>
SmartNode<T>::~SmartNode()
{
    delete dataPtr;
    dataPtr = nullptr;
}

template<class T>
T SmartNode<T>::getData() const
{
    if(dataPtr == nullptr){
        throw NodeException("No data found, Node::getData()");
    }
    return *dataPtr;    
}
template<class T>
T* SmartNode<T>::getDataPtr() const
{
    return dataPtr;
}

template<class T>
SmartNode<T>* SmartNode<T>::getNext()
{
    return next;
}
template<class T>
SmartNode<T>* SmartNode<T>::getPrev()
{
    return prev;
}
template<class T>
void SmartNode<T>::setData(const T &e)
{
    if(dataPtr == nullptr){
        if ((dataPtr = new T(e)) == nullptr){
            throw NodeException("No memory available, Node::setData()");
        }
    }
    else{
        *dataPtr = e;
    }
}
template<class T>
void SmartNode<T>::setDataPtr(T* e)
{
    dataPtr = e;
}


template<class T>
void SmartNode<T>::setNext(SmartNode<T> *p)
{
    next = p;
}
template<class T>
void SmartNode<T>::setPrev(SmartNode<T> *p)
{
    prev = p;
}



#endif // SmartNode_H

