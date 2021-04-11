/*
    Binary Search Tree

    This tree uses a node with two pointers: one points to a left node
    and the other points to the right node.

    At insertion, always put the new element in its correct position,
    that is, search through the tree and for every node position verify
    if the new element value is smaller or bigger, if its smaller, then
    inserts to the left of that node, otherwise inserts to the right.
*/

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include<exception>
#include<string>
#include "node.h"  // binary tree node

// for throwing exceptions
class Exception : public std::exception
{
private:
    std::string msg;
public:
    Exception();
    explicit Exception(const char* message) : msg(message) { }
    explicit Exception(const std::string& message) : msg(message) { }
    virtual ~Exception() throw () { }
    virtual const char* what() const throw () {
        return msg.c_str();
    }
};

// class definition
template <class T>
class BTree
{
private:
    Node <T>* root;
    void copyAll(Node<T> *);
    void deleteAll(Node<T>*&);
    Node<T>*& deleteData(Node<T>*&, const T &);
    void insertData(Node<T>*&, const T&);
    Node<T>*& findData(Node<T>*&,const T&);
    Node<T>*& getLowest(Node<T>*&);
    Node<T>*& getHighest(Node<T>*&);
    unsigned getHeight(Node<T>*&);
    void parsePreOrder(Node<T>*&);
    void parseInOrder(Node<T>*&);
    void parsePostOrder(Node<T>*&);

public:
    // constructurs
    BTree();
    BTree(const BTree<T>&);
    ~BTree();

    // main Binary Tree methods
    void deleteAll();
    bool isEmpty();
    bool isLeaf(Node<T>*&);
    void insertData(const T&);
    void deleteData(const T &);
    Node<T>*& getLowest();
    Node<T>*& getHighest();
    unsigned getHeight();
    Node<T>*& findData(const T&);
    Node<T>*& getRoot();

    // print first father, then left and finally the right node
    void parsePreOrder();
    // print first left node, then father and finally the right node
    void parseInOrder();
    // print first left, then right and finally the father node
    void parsePostOrder();

    BTree<T>& operator = (const BTree<T> &);
};

////// private methods ////
template<class T>
void BTree<T>::copyAll(Node<T> *a)         // copy method
{
  if(a!= nullptr){
      insertData(a->getData());
      copyAll(a->getLeft());
      copyAll(a->getRight());
  }
}
template<class T>
void BTree<T>::deleteAll(){              // delete all nodes
    deleteAll(root);
}

template<class T>
void BTree<T>::deleteAll(Node<T>*& x)
{
    if(x!=nullptr){                     // while there are elements
        deleteAll(x->getLeft());
        deleteAll(x->getRight());
        delete x;
        x = nullptr;
    }
}

template<class T>
void BTree<T>::insertData(Node<T> *& r, const T & e)    // inserts elements 
{
    /*
        This insert function adds elements in order in the tree, so
        first look where the data belongs in the tree as they arrive.
    */
    if (r == nullptr) {
        if((r = new Node<T>(e)) == nullptr){
            throw Exception("No memory available, BTree::insertData()");
        }
    }
    else{                               // inserts the elements in order, if e is smaller thar actual node, the added to its left
        if(e < r->getData())
            insertData(r->getLeft(),e);
        else{                           // otherwise, added to the right
            insertData(r->getRight(),e);
        }
    }
}

template<class T>
Node<T> *&BTree<T>::getLowest(Node<T> *& r)        // get the lowest element
{
    if (r == nullptr) {
        return r;
    }

    if (r->getLeft() == nullptr) {
        return r;
    }

    return getLowest(r->getLeft());    // the lowest is always int the left part of the tree
}

template<class T>
Node<T>*& BTree<T>::getHighest(Node<T> *& r)      // the bigger element
{
    if(r == nullptr or r->getRight() == nullptr){
        return r;
    }

    return getHighest(r->getRight());  // alwasy is in the right part
}

template<class T>
unsigned BTree<T>::getHeight(Node<T> *& r)     // height from root to the deepest leaf
{
    if (r == nullptr) {
        return 0;
    }

    unsigned lH(getHeight(r->getLeft()));
    unsigned rH(getHeight(r->getRight()));

    return 1 + (lH > rH ? lH : rH);

}

template<class T>
void BTree<T>::parsePreOrder(Node<T> *& r)      
{
    if (r == nullptr) {
        return;
    }
    cout << r->getData() << " ";

    parsePreOrder(r->getLeft());

    parsePreOrder(r->getRight());
}

template<class T>
void BTree<T>::parseInOrder(Node<T> *& r)
{
    if (r == nullptr) {
        return;
    }

    parseInOrder(r->getLeft());

    cout << r->getData() << " ";

    parseInOrder(r->getRight());
}

template<class T>
void BTree<T>::parsePostOrder(Node<T> *& r)
{
    if (r == nullptr) {
        return;
    }

    parsePostOrder(r->getLeft());

    parsePostOrder(r->getRight());

    cout << r->getData() << " ";
}

///// public methods 

template<class T>
BTree<T>::BTree(): root(nullptr){}    // initialize the tree root

template<class T>
BTree<T>::BTree(const BTree<T> &r)    // initialize this tree with other tree
{
    deleteAll(this->root);
    copyAll(r.root);
}

template<class T>
BTree<T>::~BTree()             // destructor
{
    deleteAll(root);
}

template<class T>
bool BTree<T>::isEmpty()       // empty tree
{
    return root == nullptr;
}

template<class T>
bool BTree<T>::isLeaf(Node<T> *& r)   // if a node does not have left and right childrens (nodes)
{
    return r->getLeft() == r->getRight();
}

template<class T>                       // inserts begining from the root
void BTree<T>::insertData(const T & e)
{
    insertData(root, e);
}

template<class T>
void BTree<T>::deleteData(const T&e){    // delete data  
    deleteData(root, e);
}

template<class T>
Node<T>*& BTree<T>::deleteData(Node<T>*& pos, const T& e)  // deletes data and make the linking process
{
    if(pos == nullptr){                                 // invalid position
        throw Exception("No data available, BTree::deleteData()");
    }
    else if(e < pos->getData()){                        // search on left side
        pos->setLeft(deleteData(pos->getLeft(),e));
    }
    else if(e> pos->getData()){                         // search on right side
        pos->setRight(deleteData(pos->getRight(),e));
    }
    else{
        if(pos->getLeft() == nullptr && pos->getRight() == nullptr){ // if is leaf
            delete pos;
            pos = nullptr;
        }
        else if(pos->getLeft() == nullptr){  
            Node<T>* aux = pos;
            pos = pos->getRight();
            delete aux;
        }
        else if(pos->getRight() == nullptr){
            Node<T>* aux = pos;
            pos = pos->getLeft();
            delete aux;
        }
        else{
            Node<T>* aux = getLowest(pos->getRight());
            pos->setData(aux->getData());
            pos->setRight(deleteData(pos->getRight(),aux->getData()));
        }
    }
    return pos;
}

template<class T>
Node<T>*& BTree<T>::findData(Node<T>*& r, const T &e)   // find a certain data in the tree
{
    if(r == nullptr){
        return r;
    }
    else{
        if((e == r->getData())){
            return r;
        }
        else{
            if(e < r->getData()){
               return  findData(r->getLeft(),e);
            }
            else{
               return findData(r->getRight(),e);
            }
        }
    }
}

template<class T>
Node<T>*& BTree<T>::getLowest()  // min value on the tree
{
    return getLowest(root);
}

template<class T>
Node<T>*& BTree<T>::getHighest()  // max value
{
    return getHighest(root);
}

template<class T>
unsigned BTree<T>::getHeight()   
{
    return getHeight(root);
}

template<class T>
Node<T>*& BTree<T>::findData(const T &e)
{
    return findData(root,e);
}

template<class T>
Node<T>*& BTree<T>::getRoot()
{
    return root;
}

template<class T>
void BTree<T>::parsePreOrder()
{
    parsePreOrder(root);
}

template<class T>
void BTree<T>::parseInOrder()
{
    parseInOrder(root);
}

template<class T>
void BTree<T>::parsePostOrder()
{
    parsePostOrder(root);
}

template<class T>
BTree<T>& BTree<T>::operator =(const BTree<T> &e)   // copy constructor
{
    deleteAll(this->getRoot());
    copyAll(e.root);
    return *this;
}

#endif // BTREE_H
