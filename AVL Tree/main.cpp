#include <iostream>
#include <chrono>
#include <random>
#include <functional>
#include <ctime>
#include "avltree.h"

using namespace std;

int main()
{/*
       default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
       uniform_int_distribution<unsigned> intDistribution(0,100000);
       auto intDice = bind(intDistribution, generator);*/

       unsigned aleatorio;

       AvlTree<unsigned> tree;

       cout<<"\n\t\t------ Insertando datos en el arbol ----"<<endl;
       for (unsigned i = 0; i < 20; ++i) {
           try{

//               aleatorio = intDice();
               cout<<"Insertando: "<<i<<endl;
               tree.insertData(i);

           }catch(exception& e){
               string txt = "Hubo un error!!\El sistema informa: ";
               txt += e.what();
               cout<<txt<<endl;
           }
       }

       cout<<endl<<"\n\t\t\t\t.: Altura del arbol :.   "<<tree.getHeight()<<endl<<endl;

       cout<<"\n\tRecorrido preOrden:"<<endl<<endl;
       tree.parsePreOrder();
       cout<<endl<<endl;
       cout<<endl<<"--------------------------------------------------------"<<endl;
       cout<<"\n\tRecorrido InOrden:"<<endl<<endl;
       tree.parseInOrder();
       cout<<endl<<endl;
       cout<<endl<<"--------------------------------------------------------"<<endl;
       cout<<"\n\tRecorrido postOrden:"<<endl<<endl;
       tree.parsePostOrder();
       cout<<endl<<endl<<endl<<endl;

       cout<<"Altura del subarbol izquierdo: "<<tree.getLeftHeight()<<endl<<endl;
       cout<<"Altura del subarbol derecho: "<<tree.getRightHeight()<<endl<<endl;


       AvlTree<unsigned> tree3(tree); //constructor copia

cout<<endl<<endl<<"Arbol 3: "<<endl;
tree3.parsePreOrder();
cout<<endl<<endl<<"..................................."<<endl<<endl;
tree3.parseInOrder();
cout<<endl<<endl<<"..................................."<<endl<<endl;
tree3.parsePostOrder();
cout<<endl;


    return 0;
}
