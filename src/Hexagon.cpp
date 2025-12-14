#include "Hexagon.hpp"
#include <iostream>

using namespace std;

Hexagon::Hexagon() {
    front = 0;
    rear = -1;
    count = 0;
    
    // Diziyi null ile başlat
    for (int i = 0; i < 6; i++) {
        agaclar[i] = nullptr;
    }
}

Hexagon::~Hexagon() {
    // Kuyruk silinirken içindeki ağaçları da temizlemeliyiz
    for (int i = 0; i < 6; i++) {
        if (agaclar[i] != nullptr) {
            delete agaclar[i];
        }
    }
}

bool Hexagon::isFull() {
    return count == 6;
}

bool Hexagon::isEmpty() {
    return count == 0;
}

void Hexagon::agacEkle(BST* yeniAgac) {
    if (isFull()) {
        cout << "HATA: Altigen dolu! Ekleme yapilamadi.\n";
        return;
    }

    // Dairesel ilerleme: (rear + 1) % 6
    rear = (rear + 1) % 6;
    agaclar[rear] = yeniAgac;
    count++;
}

BST* Hexagon::agacCikar() {
    if (isEmpty()) return nullptr;

    BST* cikanAgac = agaclar[front];
    agaclar[front] = nullptr; // Orayı boşalt
    
    // Dairesel ilerleme
    front = (front + 1) % 6;
    count--;

    return cikanAgac;
}

void Hexagon::printQueue() {
    cout << "Kuyruk Durumu (Front -> Rear): ";
    if (isEmpty()) {
        cout << "Bos";
    } else {
        // Dairesel olarak gez
        for (int i = 0; i < count; i++) {
            int index = (front + i) % 6;
            if (agaclar[index] != nullptr) {
                cout << "[" << agaclar[index]->getRootData() << "] ";
            }
        }
    }
    cout << endl;
}

// Kuyruktaki en yüksek ağacı bulur (Öncelikli Olan)
BST* Hexagon::getMaxHeightTree() {
    if (isEmpty()) return nullptr;

    BST* maxTree = agaclar[front];
    int maxHeight = maxTree->getHeight();

    // Kuyruktaki tüm elemanları gez
    for (int i = 1; i < count; i++) {
        // Dairesel index hesabı
        int index = (front + i) % 6;
        
        if (agaclar[index]->getHeight() > maxHeight) {
            maxHeight = agaclar[index]->getHeight();
            maxTree = agaclar[index];
        }
    }
    return maxTree;
}

// Ödevdeki özel bölme işlemini yapar
// Formül: (Çıkmak üzere olanın kökü) / (En yükseğin kökü)
int Hexagon::calculateSpecialNumber() {
    if (isEmpty()) return 0;

    // 1. Çıkmak üzere olan (Kuyruğun başındaki)
    BST* normalCikan = agaclar[front];
    
    // 2. Öncelikli olan (En yüksek boylu)
    BST* oncelikliCikan = getMaxHeightTree();

    if (normalCikan == nullptr || oncelikliCikan == nullptr) return 0;

    int pay = normalCikan->getRootData();
    int payda = oncelikliCikan->getRootData();

    // Sıfıra bölünme hatası olmasın
    if (payda == 0) return 0;

    return pay / payda; // Tamsayı bölmesi [cite: 16]
}


// ...

int Hexagon::getCount() {
    return count;
}

// Belirli bir sıradaki ağaca sayı ekle (Round Robin için)
void Hexagon::insertValueToTreeAtOffset(int offset, int value) {
    if (isEmpty()) return;

    // Dairesel index hesabı: (front + offset) % 6
    // Ancak offset, mevcut eleman sayısından büyükse başa sarmalı (Mod count)
    // Ödevde: "Kuyruğun sonuna gelinirse tekrar başlanıp devam edilir"
    
    int targetIndex = (front + (offset % count)) % 6;
    
    if (agaclar[targetIndex] != nullptr) {
        agaclar[targetIndex]->insert(value);
    }
}

BST* Hexagon::deleteMaxHeightTree() {
    if (isEmpty()) return nullptr;

    // 1. En yüksek ağacı bul
    int maxIndex = front;
    int maxHeight = agaclar[front]->getHeight();
    int searchIndex;

    // Kuyruktaki tüm elemanları gez
    for (int i = 1; i < count; i++) {
        searchIndex = (front + i) % 6;
        if (agaclar[searchIndex]->getHeight() > maxHeight) {
            maxHeight = agaclar[searchIndex]->getHeight();
            maxIndex = searchIndex;
        }
    }

    // 2. O ağacı al
    BST* deletedTree = agaclar[maxIndex];

    // 3. Kuyruğu Kaydır (Boşluğu kapat)
    // Silinen elemandan (maxIndex) sonraki tüm elemanları bir geri çekeceğiz
    // Taa ki rear'a kadar.
    
    // Basit bir yöntem: Elemanı silip, rear'a kadar olanları kaydıralım.
    // Ancak dairesel dizide kaydırma karmaşıktır.
    // Alternatif: Diziyi düzgün tutmak için, silinen noktadan itibaren
    // bir sonrakini bir öncekine kopyala.
    
    int current = maxIndex;
    // (Döngü sayısı: silinenden sonuncuya kadar kaç eleman varsa)
    // Bu hesap biraz karışık olabilir, o yüzden count üzerinden gidelim.
    
    // Kuyruk mantığını bozmamak için: 
    // Silinecek eleman arada ise, arkasındakileri öne çekiyoruz.
    while (current != rear) {
        int next = (current + 1) % 6;
        agaclar[current] = agaclar[next];
        current = next;
    }
    
    // Sonuncuyu boşalt ve rear'ı bir geri al
    agaclar[rear] = nullptr;
    rear = (rear - 1 + 6) % 6; // Negatif olmasın diye +6
    count--;

    return deletedTree;
}