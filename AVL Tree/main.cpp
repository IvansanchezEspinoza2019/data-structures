#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include <ctime>
#include "avltree.h"  // include the avl tree

using namespace std;

int main()
{
      // for generatin random numbers
       default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
       uniform_int_distribution<unsigned> intDistribution(0,100000);
       auto intDice = bind(intDistribution, generator);

       unsigned aleatorio;

       // instance of the avñ tree 
       AvlTree<unsigned> tree;

       cout<<"\n\t\t------ Inserting data  ----"<<endl;
       for (unsigned i = 0; i < 20; ++i) {
           try{

               aleatorio = intDice();
               cout<<"Insertando: "<<aleatorio<<endl;
               tree.insertData(aleatorio);
           }catch(exception& e){
               string txt = "An error ocurred!!\nThe sistem says: ";
               txt += e.what();
               cout<<txt<<endl;
           }
       }
    // tree height
       cout<<endl<<"\n\t\t\t\tAVL Tree height: "<<tree.getHeight()<<endl<<endl;
       cout<<"\n\tPreOrden:"<<endl<<endl;
       tree.parsePreOrder(); 
       cout<<endl;
       cout<<endl<<"--------------------------------------------------------"<<endl;
       cout<<"\n\tInOrden:"<<endl<<endl;
       tree.parseInOrder();
       cout<<endl;
       cout<<endl<<"--------------------------------------------------------"<<endl;
       cout<<"\n\tPostOrden:"<<endl<<endl;
       tree.parsePostOrder();
       cout<<endl<<endl;

    // sub-tree
       cout<<"Sub-tree left height: "<<tree.getLeftHeight()<<endl<<endl;
       cout<<"Sub-tree right height: "<<tree.getRightHeight()<<endl<<endl;

    //  creating other avl tree
    AvlTree<unsigned> tree2(tree); //constructor copia

    cout<<endl<<endl<<"AVL Tree copy: "<<endl<<endl;
    tree2.parsePreOrder();
    cout<<endl<<endl<<"..................................."<<endl<<endl;
    tree2.parseInOrder();
    cout<<endl<<endl<<"..................................."<<endl<<endl;
    tree2.parsePostOrder();
    cout<<endl;


    return 0;
}
