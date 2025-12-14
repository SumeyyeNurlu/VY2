#ifndef BST_HPP
#define BST_HPP
#include "Node.hpp"
#include <iostream>

using namespace std;

class BST 
{
private:
    Node* root;

    void insert(Node*& subNode, int newItem); //ekleme
    int getHeight(Node* subNode);              //yükseklik
    void postOrderDelete(Node* subNode);    //postorder silme
    
    
    int getSize(Node* subNode); 
    void postOrderToArray(Node* subNode, int* arr, int& index);

public:
    BST();
    ~BST();
    void insert(int newItem);
    int getHeight();
    int getRootData();
    
   
    int size(); // Ağaçtaki toplam eleman sayısı
    int* getPostOrderArray(); // Verileri Postorder dizisi olarak döndürür
};

#endif