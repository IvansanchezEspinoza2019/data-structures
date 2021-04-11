/*
    This node has two pointers: one for the left children and 
    one for the right children.
*/

#ifndef Node_H
#define Node_H

#include <iostream>
#include "string.h"
#include "exception"

using namespace std;

// exception class
class NodeException : public std::exception
{
private:
    std::string msg;
public:
    NodeException();
    explicit NodeException(const char* message) : msg(message) { }
    explicit NodeException(const std::string& message) : msg(message) { }
    virtual ~NodeException() throw () { }
    virtual const char* what() const throw () {
        return msg.c_str();
    }
};

// node definition
template <class T>
class Node
{
private:
    T* dataPtr;
    Node <T>* left;     // left child
    Node <T>* right;    // right child

public:
    // constructors
    Node();
    Node(const T&e);
    ~Node();

    // methods
    T getData() const;
    void setData(const T &value);

    Node<T> *&getRight();
    void setRight(Node<T> *&value);

    Node<T> *&getLeft();
    void setLeft(Node<T> *&value);

    T *getDataPtr() const;
    void setDataPtr(T *value);
};

/*
    Implementation of Main methods 
*/

template <class T>
Node<T>::Node(): dataPtr(nullptr), left(nullptr), right(nullptr){}

template <class T>
Node<T>::Node(const T & e): left(nullptr), right(nullptr){

    dataPtr = new T(e);

    if (dataPtr == nullptr) {
        throw NodeException("No memory available, creating Node");
    }
}

template <class T>
Node<T>::~Node(){
    delete dataPtr;
}

template <class T>
T Node<T>::getData() const
{
    if (dataPtr == nullptr) {
        throw NodeException("No data, Node::getData()");
    }

    return *dataPtr;
}

template <class T>
void Node<T>::setData(const T &value)
{
    if (dataPtr == nullptr) {
        if ((dataPtr = new T(value)) == nullptr) {
            throw NodeException("No memory available, Node::setData()");
        }
    }
    else {
        *dataPtr = value;
    }
}

template <class T>
Node<T> *&Node<T>::getRight()
{
    return right;
}

template <class T>
void Node<T>::setRight(Node<T> *&value)
{
    right = value;
}

template <class T>
Node<T> *&Node<T>::getLeft()
{
    return left;
}

template <class T>
void Node<T>::setLeft(Node<T> *&value)
{
    left = value;
}

template <class T>
T *Node<T>::getDataPtr() const
{
    return dataPtr;
}

template <class T>
void Node<T>::setDataPtr(T *value)
{
    dataPtr = value;
}

#endif // Node_H
