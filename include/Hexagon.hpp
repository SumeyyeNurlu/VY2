#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "BST.hpp"
using namespace std;
class Hexagon 
{
private:
    BST* agaclar[6];
    int front;
    int rear;
    int count;
    //  (öncelikli) ağacı bulur
    BST* getMaxHeightTree();

public:
    Hexagon();
    ~Hexagon();

    void agacEkle(BST* yeniAgac);
    BST* agacCikar();
    bool isFull();
    bool isEmpty();
    void printQueue();

    // yazılacak sayıyı hesapla
    int calculateSpecialNumber();


    BST* deleteMaxHeightTree();

    //kuyruğun başından (front) itibaren 'offset' kadar
    // ilerideki ağaca 'value' ekler.
    void insertValueToTreeAtOffset(int offset, int value);
    
    // YENİ: O an kuyrukta kaç ağaç var? (Dağıtım döngüsü için lazım)
    int getCount();
};

#endif