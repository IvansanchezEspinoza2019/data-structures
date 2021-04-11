#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include<exception>
#include<string>

#include "node.h"

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

    BTree();
    BTree(const BTree<T>&);
    ~BTree();

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

    void parsePreOrder();
    void parseInOrder();
    void parsePostOrder();

    BTree<T>& operator = (const BTree<T> &);
};

//privados
template<class T>
void BTree<T>::copyAll(Node<T> *a)
{
  if(a!= nullptr){
      insertData(a->getData());
      copyAll(a->getLeft());
      copyAll(a->getRight());
  }
}
template<class T>
void BTree<T>::deleteAll(){
    deleteAll(root);
}

template<class T>
void BTree<T>::deleteAll(Node<T>*& x)
{
    if(x!=nullptr){
        deleteAll(x->getLeft());
        deleteAll(x->getRight());
        delete x;
        x = nullptr;
    }
}

template<class T>
void BTree<T>::insertData(Node<T> *& r, const T & e)
{
    if (r == nullptr) {
        if((r = new Node<T>(e)) == nullptr){
            throw Exception("Error reservando memoria, insertData()");
        }
    }
    else{
        if(e < r->getData())
            insertData(r->getLeft(),e);
        else{
            insertData(r->getRight(),e);
        }
    }
}

template<class T>
Node<T> *&BTree<T>::getLowest(Node<T> *& r)
{
    if (r == nullptr) {
        return r;
    }

    if (r->getLeft() == nullptr) {
        return r;
    }

    return getLowest(r->getLeft());
}

template<class T>
Node<T>*& BTree<T>::getHighest(Node<T> *& r)
{
    if(r == nullptr or r->getRight() == nullptr){
        return r;
    }

    return getHighest(r->getRight());
}

template<class T>
unsigned BTree<T>::getHeight(Node<T> *& r)
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

//Publicos

template<class T>
BTree<T>::BTree(): root(nullptr){}

template<class T>
BTree<T>::BTree(const BTree<T> &r)
{
    deleteAll(this->root);
    copyAll(r.root);
}

template<class T>
BTree<T>::~BTree()
{
    deleteAll(root);
}

template<class T>
bool BTree<T>::isEmpty()
{
    return root == nullptr;
}

template<class T>
bool BTree<T>::isLeaf(Node<T> *& r)
{
    return r->getLeft() == r->getRight();
}

template<class T>
void BTree<T>::insertData(const T & e)
{
    insertData(root, e);
}

template<class T>
void BTree<T>::deleteData(const T&e){
    deleteData(root,e);
}

template<class T>
Node<T>*& BTree<T>::deleteData(Node<T>*& pos, const T& e)
{
    if(pos == nullptr){
        throw Exception("Insuficiencia de datos, deleteData()");
    }
    else if(e < pos->getData()){
        pos->setLeft(deleteData(pos->getLeft(),e));
    }
    else if(e> pos->getData()){
        pos->setRight(deleteData(pos->getRight(),e));
    }
    else{
        if(pos->getLeft() == nullptr && pos->getRight() == nullptr){
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
Node<T>*& BTree<T>::findData(Node<T>*& r, const T &e)
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
Node<T>*& BTree<T>::getLowest()
{
    return getLowest(root);
}

template<class T>
Node<T>*& BTree<T>::getHighest()
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
BTree<T>& BTree<T>::operator =(const BTree<T> &e)
{
    deleteAll(this->getRoot());
    copyAll(e.root);
    return *this;
}

#endif // BTREE_H
