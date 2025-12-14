#include "HexagonList.hpp"
#include <iostream>
#include <fstream> 
#include <sstream>

using namespace std;

HexagonList::HexagonList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

HexagonList::~HexagonList() {
    // Listeyi temizlerken tüm düğümleri (ve içindeki altıgenleri) siler
    HexagonNode* current = head;
    while (current != nullptr) {
        HexagonNode* next = current->next;
        delete current; // Node yıkıcısı altıgeni de siler
        current = next;
    }
}


void HexagonList::addHexagon(Hexagon* newHexagon) {
    HexagonNode* newNode = new HexagonNode(newHexagon);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        tail->next = head; // Kendi kendine dönüyor
    } else {
        tail->next = newNode;
        tail = newNode;
        tail->next = head; // Sona eklenen başa dönüyor (Çember tamamlanıyor)
    }
    size++;
}

Hexagon* HexagonList::getHexagon(int index) {
    if (index < 0 || index >= size) return nullptr;

    HexagonNode* temp = head;
    int counter = 0;
    while (temp != nullptr) {
        if (counter == index) {
            return temp->data;
        }
        temp = temp->next;
        counter++;
    }
    return nullptr;
}

int HexagonList::sizeCount() {
    return size;
}





// src/HexagonList.cpp içindeki loadFromFile fonksiyonunu KOMPLE DEĞİŞTİR:

void HexagonList::loadFromFile(string filename) {
    // 1. ÖNCE TOPLAM SAYIYI BUL VE EKRANI HAZIRLA
    int totalHexagons = calculateTotalHexagons(filename);
    
    // Windows için ekranı temizle (Linux için "clear")
    system("cls"); 
    cout << "Dosya Okunuyor... Toplam Altigen Kapasitesi: " << totalHexagons << endl;
    
    // Boş kutuları çiz
    // [ ] -> [ ] -> [ ] ...
    int counter = 0;
    for (int i = 0; i < totalHexagons; i++) {
        cout << "[   ] -> ";
        counter++;
        if (counter % 6 == 0) cout << endl;
    }
    cout << "SON" << endl;

    // İmleci başa al (gotoxy benzeri bir işlem lazım ama basitlik için cls kullanacağız)
    // Ödevde "Ekranda daha önce yazılanlar temizlenmelidir" diyor.
    // Bu yüzden her güncellemede cls yapabiliriz.

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "HATA: Dosya acilamadi!\n";
        return;
    }

    string line;
    Hexagon* currentHexagon = new Hexagon();
    int linesRead = 0; // Okunan satır sayısı

    while (getline(file, line)) {
        if (line.empty()) continue;

        // ... (BST oluşturma ve ekleme kodları AYNI KALSIN) ...
        BST* newTree = new BST();
        stringstream ss(line);
        int number;
        while (ss >> number) {
            newTree->insert(number);
        }

        if (currentHexagon->isFull()) {
            addHexagon(currentHexagon);
            currentHexagon = new Hexagon();
        }
        currentHexagon->agacEkle(newTree);
        // ----------------------------------------------------

        linesRead++;

        // --- DÜZELTME BURADA ---
        // 1. Güncelleme sıklığını azalttık (Her 100 değil, her 5000 satırda bir)
        // 2. printStatus() fonksiyonunu kaldırdık (Çok zaman alıyordu)
        if (linesRead % 5000 == 0) {
            system("cls");
            cout << "Dosya Okunuyor... (" << linesRead << " satir islendi)\n";
            // printStatus(); <--- BUNU SİLDİK/YORUMA ALDIK
        }
    }

    // Kalanı ekle
    if (!currentHexagon->isEmpty()) {
        addHexagon(currentHexagon);
    } else {
        delete currentHexagon;
    }

    file.close();
    
    // Final durumu göster
    system("cls");
    cout << "YUKLEME TAMAMLANDI (" << size << " Altigen Olusturuldu)\n";
    printStatus();
}







// src/HexagonList.cpp içindeki mainOperation fonksiyonunu GÜNCELLE:

void HexagonList::mainOperation(int totalTurns) {
    for (int currentTurn = 1; currentTurn <= totalTurns; currentTurn++) {
        
        // 1. EKRANI TEMİZLE 
        // Windows için "cls", Linux/Mac için "clear"
        system("cls"); 

        // 2. BİLGİ BAS
        cout << "TUR: " << currentTurn << " / " << totalTurns << endl;
        cout << "--------------------------------\n";
        
        // 3. TABLOYU ÇİZ (Sayıları Göster)
        printStatus();

        // --- OPERASYON (TRANSFER) KISMI (Dünkü kodun aynısı) ---
        HexagonNode* temp = head;
        
       for (int i = 0; i < size; i++) {
            Hexagon* sourceHex = temp->data;
            
            // Dairesel olduğu için next her zaman vardır (veya kendisidir)
            // Ama tek eleman varsa next kendisidir, kontrol edelim:
            Hexagon* targetHex = nullptr;
            if (temp->next != nullptr) {
                targetHex = temp->next->data;
            } else {
                // Eğer addHexagon'da dairesel bağlantı kurulmadıysa burası çalışır
                if (head != nullptr) targetHex = head->data;
            }

            if (!sourceHex->isEmpty() && targetHex != nullptr) {
                BST* treeToMove = nullptr;

                if (currentTurn % 2 != 0) {
                    treeToMove = sourceHex->agacCikar(); 
                } else {
                    treeToMove = sourceHex->deleteMaxHeightTree(); 
                }

                if (treeToMove != nullptr) {
                    int nodeCount = treeToMove->size();
                    int* postOrderData = treeToMove->getPostOrderArray();

                    for (int j = 0; j < nodeCount; j++) {
                        targetHex->insertValueToTreeAtOffset(j, postOrderData[j]);
                    }

                    delete[] postOrderData;
                    delete treeToMove;
                }
            }
            temp = temp->next;
        }
        system("cls");
    cout << "\n--- TURLAR TAMAMLANDI (" << totalTurns << " Tur) ---\n";
    cout << "Son Durum:\n";
    printStatus();
    }
}















// src/HexagonList.cpp en sonuna:

void HexagonList::printStatus() {
    if (head == nullptr) return;

    HexagonNode* temp = head;
    int counter = 0;

    // Sonsuz döngüden kurtulmak için "size" kadar dönüyoruz
    for (int i = 0; i < size; i++) {
        int val = temp->data->calculateSpecialNumber();
        
        cout << "[ " << val << " ] -> ";

        counter++;
        if (counter % 6 == 0) {
            cout << endl;
        }

        temp = temp->next;
    }
    cout << "SON" << endl;
}


// src/HexagonList.cpp en sonuna:

int HexagonList::calculateTotalHexagons(string filename) {
    ifstream file(filename);
    if (!file.is_open()) return 0;

    int lineCount = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            lineCount++;
        }
    }
    file.close();

    // Her 6 satır 1 altıgen eder. 
    // Tamsayı bölmesi yeterli (Örn: 13 satır -> 2 tam + 1 yarım -> 3 altıgen)
    // Formül: (satır + 5) / 6
    return (lineCount + 5) / 6;
}