/* 
 * @file            main.cpp
 * @description     HexagonList sınıfını kullanarak altıgen listesini yönetir. Kullanıcıdan tur sayısını alır ve başlatır.       
 * @course          2A
 * @assignment      ÖDEV 2 
 * @date            01.12.2025-12.12.2025
 * @author          Sümeyye Nurlu   g231210053   sumeyye.nurlu@ogr.sakarya.edu.tr
 * */

#include <iostream>
#include "HexagonList.hpp"

using namespace std;

int main() {
    cout << "--- TUR MANTIGI TESTI ---\n";

    HexagonList* liste = new HexagonList();
    
    // Verileri yükle
    cout << "Dosya okunuyor...\n";
    liste->loadFromFile("bin/Data.txt");
    
    if (liste->sizeCount() == 0) {
        cout << "HATA: Veri yuklenemedi. Data.txt dosyasini kontrol edin.\n";
        return 0;
    }

    // Kullanıcıdan tur sayısı al
    int turSayisi;
    cout << "Kac tur calissin?: ";
    cin >> turSayisi;

    // Operasyonu Başlat
    liste->mainOperation(turSayisi);

    delete liste;
    return 0;
}
