#include "BST.hpp"
#include <algorithm> // max fonksiyonu için
using namespace std;

BST::BST() {
    root = nullptr;
}

BST::~BST() {
    postOrderDelete(root);
}

void BST::postOrderDelete(Node* subNode) {
    if (subNode == nullptr) return;
    postOrderDelete(subNode->left);
    postOrderDelete(subNode->right);
    delete subNode;
}

// --- PRIVATE YARDIMCI FONKSİYONLAR ---

void BST::insert(Node*& subNode, int newItem) {
    if (subNode == nullptr) {
        subNode = new Node(newItem);
        return;
    }

    // KRİTİK KURAL: Eşitse veya küçükse SOLA, büyükse SAĞA
    if (newItem <= subNode->data) {
        insert(subNode->left, newItem);
    } else {
        insert(subNode->right, newItem);
    }
}

int BST::getHeight(Node* subNode) {
    if (subNode == nullptr) return 0;
    
    // Sol ve sağın yüksekliğini ölç, büyük olana 1 ekle
    return 1 + max(getHeight(subNode->left), getHeight(subNode->right));
}

// --- PUBLIC FONKSİYONLAR ---

void BST::insert(int newItem) {
    insert(root, newItem);
}

int BST::getHeight() {
    return getHeight(root);
}

int BST::getRootData() {
    if (root != nullptr) return root->data;
    return -1; // Boşsa hata değeri
}


// 1. Ağaçtaki eleman sayısını bulur (Recursive)
int BST::getSize(Node* subNode) {
    if (subNode == nullptr) return 0;
    return 1 + getSize(subNode->left) + getSize(subNode->right);
}

// 2. Public size fonksiyonu
int BST::size() {
    return getSize(root);
}

// 3. Postorder (Sol-Sağ-Kök) dolaşarak diziyi doldurur
void BST::postOrderToArray(Node* subNode, int* arr, int& index) {
    if (subNode == nullptr) return;

    // Önce Sol
    postOrderToArray(subNode->left, arr, index);
    // Sonra Sağ
    postOrderToArray(subNode->right, arr, index);
    // En Son Kök (Veriyi yaz)
    arr[index] = subNode->data;
    index++;
}

// 4. Verileri dizi halinde dışarı verir
int* BST::getPostOrderArray() {
    int count = size();
    if (count == 0) return nullptr;

    // Dinamik dizi oluştur (Bunu kullanan kişi delete[] yapmalı!)
    int* arr = new int[count];
    int index = 0;
    
    postOrderToArray(root, arr, index);
    return arr;
}