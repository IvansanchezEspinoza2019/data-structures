#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include<exception>
#include<string>

#include "node.h"

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
// classs definition
template <class T>
class AvlTree
{
private:

    Node <T>* root;
    void copyAll(Node<T> *);
    void deleteAll(Node<T>*&);
    Node<T>*& deleteData(Node<T>*&, const T &);
    void insertData(Node<T>*&, const T&);
    void copyData(Node<T>*&,const T&);
    Node<T>*& findData(Node<T>*&,const T&);
    Node<T>*& getLowest(Node<T>*&);
    Node<T>*& getHighest(Node<T>*&);
    unsigned getHeight(Node<T>*&);
    void parsePreOrder(Node<T>*&);
    void parseInOrder(Node<T>*&);
    void parsePostOrder(Node<T>*&);

    void simpleLeftRot(Node<T>*&);
    void simpleRightRot(Node<T>*&);
    void doubleLeftRot(Node<T>*&);
    void doubleRightRot(Node<T>*&);

    int getBalanceFator(Node<T>*&);

    void doBalancing(Node<T>*&);

public:
    // constructors
    AvlTree();
    AvlTree(const AvlTree<T> &);
    ~AvlTree();

    // methods
    void deleteAll();
    bool isEmpty();
    bool isLeaf(Node<T>*&);
    void insertData(const T&);
    void copyData(const T&);
    void deleteData(const T &);
    Node<T>*& getLowest();
    Node<T>*& getHighest();
    unsigned getHeight();
    unsigned getLeftHeight();
    unsigned getRightHeight();
    Node<T>*& findData(const T&);
    Node<T>*& getRoot();


    void parsePreOrder();
    void parseInOrder();
    void parsePostOrder();

    AvlTree<T>& operator = (const AvlTree<T> &);
};

//privados
template<class T>
void AvlTree<T>::copyAll(Node<T> *a) // copy the data from other avl tree
{
  if(a!= nullptr){
      copyData(a->getData());
      copyAll(a->getLeft());
      copyAll(a->getRight());
  }
}
template<class T>
void AvlTree<T>::deleteAll(){  // delete all data
    deleteAll(root);
}

template<class T>
void AvlTree<T>::deleteAll(Node<T>*& x)
{
    if(x!=nullptr){
        deleteAll(x->getLeft());
        deleteAll(x->getRight());
        delete x;
        x = nullptr;
    }
}

template<class T>
void AvlTree<T>::insertData(Node<T> *& r, const T & e)  // inserts data at position 'p'
{
    if (r == nullptr) {//inserts as a leaf
        if((r = new Node<T>(e)) == nullptr){
            throw Exception("Error");
        }
    }
    else{// decides to wich part belongs the new data based on its value(to the left or to the right part of the tree)
        if(e < r->getData())
            insertData(r->getLeft(),e);
        else{
            insertData(r->getRight(),e);
        }
       // now we have to check the tree balance
        doBalancing(r); // balance the tree
    }
}

template<class T>
void AvlTree<T>::copyData(Node<T> *& r, const T & e)
{
    if (r == nullptr) {//inserts as a leaf 
        if((r = new Node<T>(e)) == nullptr){
            throw Exception("Error");
        }
    }
    else{
        if(e < r->getData())
            copyData(r->getLeft(),e);
        else{
            copyData(r->getRight(),e);
        }
    }
}

template<class T>
Node<T> *&AvlTree<T>::getLowest(Node<T> *& r)  // get the lowest value of the tree
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
Node<T>*& AvlTree<T>::getHighest(Node<T> *& r)  // get the highest value
{
    if(r == nullptr or r->getRight() == nullptr){
        return r;
    }

    return getHighest(r->getRight());
}

template<class T>
unsigned AvlTree<T>::getHeight(Node<T> *& r) // height
{
    if (r == nullptr) {
        return 0;
    }

    unsigned lH(getHeight(r->getLeft()));
    unsigned rH(getHeight(r->getRight()));

    return 1 + (lH > rH ? lH : rH);

}

template<class T>
void AvlTree<T>::parsePreOrder(Node<T> *& r)  
{
    if (r == nullptr) {
        return;
    }
    cout << r->getData() << " ";

    parsePreOrder(r->getLeft());

    parsePreOrder(r->getRight());

}

template<class T>
void AvlTree<T>::parseInOrder(Node<T> *& r)
{
    if (r == nullptr) {
        return;
    }

    parseInOrder(r->getLeft());

    cout << r->getData() << " ";

    parseInOrder(r->getRight());
}

template<class T>
void AvlTree<T>::parsePostOrder(Node<T> *& r)
{
    if (r == nullptr) {
        return;
    }

    parsePostOrder(r->getLeft());

    parsePostOrder(r->getRight());

    cout << r->getData() << " ";
}
template<class T>
void AvlTree<T>::simpleLeftRot(Node<T> *& r) // make simple left rotation
{
    Node<T>* aux1(r->getRight());
    Node<T>* aux2(aux1->getLeft());

    r->setRight(aux2);
    aux1->setLeft(r);
    r = aux1;
}

template<class T>
void AvlTree<T>::simpleRightRot(Node<T> *&r) // make simple right rotation
{
    Node<T>* aux1(r->getLeft());
    Node<T>* aux2(aux1->getRight());

    r->setLeft(aux2);
    aux1->setRight(r);
    r = aux1;
}

template<class T>
void AvlTree<T>::doubleLeftRot(Node<T> *&r) // make double left rotation
{
    simpleRightRot(r->getRight());
    simpleLeftRot(r);
}

template<class T>
void AvlTree<T>::doubleRightRot(Node<T> *&r)  // make double right rotation
{
    simpleLeftRot(r->getLeft());
    simpleRightRot(r);
}

template<class T>
int AvlTree<T>::getBalanceFator(Node<T> *& r)
{
    if(r == nullptr){
        return 0;
    }
    return getHeight(r->getRight()) -  getHeight(r->getLeft());
}

template<class T>
void AvlTree<T>::doBalancing(Node<T> *&r)  
{
    /*
        Function that make the balance to de AVL Tree
    */
    switch(getBalanceFator(r)){
    case -2: //right rotation

        if (getBalanceFator(r->getLeft())== -1) { // simple right rotation
            simpleRightRot(r);
            std::cout<<"RSD: "<<r->getData()<<endl;
        }
        else{
            // doble right rotation
            doubleRightRot(r);
            //std::cout<<"RDD: "<<r->getData()<<endl;
        }
        break;

    case 2:    // left rotation
        if (getBalanceFator(r->getRight()) == 1) {
            // simple left rotation
            simpleLeftRot(r);
            //std::cout<<"RSI: "<<r->getData()<<endl;
        }
        else{
            //doble left rotation
            doubleLeftRot(r);
            //std::cout<<"RDI: "<<r->getData()<<endl;
        }
        break;
    }
}


//Publicos
template<class T>
AvlTree<T>::AvlTree(): root(nullptr){}

template<class T>
AvlTree<T>::AvlTree(const AvlTree<T> &r) : root(nullptr)
{
    copyAll(r.root);
}

template<class T>
AvlTree<T>::~AvlTree()
{
    deleteAll(root);
}

template<class T>
bool AvlTree<T>::isEmpty() // empty tree
{
    return root == nullptr;
}

template<class T>
bool AvlTree<T>::isLeaf(Node<T> *& r)
{
    return r->getLeft() == r->getRight();
}

template<class T>
void AvlTree<T>::insertData(const T & e)
{
    insertData(root, e);
}

template<class T>
void AvlTree<T>::copyData(const T &e)
{
    copyData(root,e);
}

template<class T>
void AvlTree<T>::deleteData(const T&e){
    deleteData(root,e);
}

template<class T>
Node<T>*& AvlTree<T>::deleteData(Node<T>*& pos, const T& e)
{
    if(pos == nullptr){
        throw Exception("Invalid position, deleteData()");
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
Node<T>*& AvlTree<T>::findData(Node<T>*& r, const T &e)
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
Node<T>*& AvlTree<T>::getLowest()
{
    return getLowest(root);
}

template<class T>
Node<T>*& AvlTree<T>::getHighest()
{
    return getHighest(root);
}

template<class T>
unsigned AvlTree<T>::getHeight()
{
    return getHeight(root);
}

template<class T>
unsigned AvlTree<T>::getLeftHeight()
{
  return   getHeight(root->getLeft());
}
template<class T>
unsigned AvlTree<T>::getRightHeight()
{
  return   getHeight(root->getRight());
}

template<class T>
Node<T>*& AvlTree<T>::findData(const T &e)
{
    return findData(root,e);
}

template<class T>
Node<T>*& AvlTree<T>::getRoot()
{
    return root;
}

template<class T>
void AvlTree<T>::parsePreOrder()
{
    parsePreOrder(root);
}

template<class T>
void AvlTree<T>::parseInOrder()
{
    parseInOrder(root);
}

template<class T>
void AvlTree<T>::parsePostOrder()
{
    parsePostOrder(root);
}

template<class T>
AvlTree<T>& AvlTree<T>::operator =(const AvlTree<T> & e)
{
    deleteAll(root);
    copyAll(e.root);
    return *this;
}
#endif // AVLTREE_H
