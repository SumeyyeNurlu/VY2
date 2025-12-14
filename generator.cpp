
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() 
{
    // rastgele
    srand(time(0));

    // bin klasörüne kaydedilecek dosya oluşturma 
    ofstream file("bin/Data.txt");

    if (!file.is_open())
    {
        cout << "HATA: Dosya olusturulamadi! 'bin' klasorunun var oldugundan emin olun." << endl;
        return 1;
    }

    cout << "50.000 satirlik veri uretiliyor... Lutfen bekleyin." << endl;

    int satirSayisi = 50000;

    for (int i = 0; i < satirSayisi; i++)
    {
        
        int elemanSayisi = (rand() % 7) + 1;

        for (int j = 0; j < elemanSayisi; j++) {
            // sayılar üret (1 ile 100 arası)
            int sayi = (rand() % 100) + 1;
            file << sayi << " ";
        }
        
        
        file << endl;
    }

    file.close();
    cout << "BASARILI! 'bin/Data.txt' dosyasi olusturuldu." << endl;

    return 0;
}