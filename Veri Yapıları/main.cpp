#include "Kitap.h"
#include "Ogrenci.h"
#include <fstream>
#include <iostream>

using namespace std;

// Kitapları dosyadan okuyup bağlı listeye ekliyorum
void loadBooks(Kitap& kitaplar) {
    ifstream file("Kitaplar.txt");
    if (!file.is_open()) {
        cout << "Kitaplar.txt dosyasi acilamadi!" << endl;
        return;
    }
    int id, adet;
    string adi, yazar;
    int count = 0;
    while (file >> id) {
        file.ignore();
        getline(file, adi, '\t');
        getline(file, yazar, '\t');
        file >> adet;
        kitaplar.kitapEkle(id, adi, yazar, adet);
        count++;
        cout << "Kitap eklendi: " << adi << endl;
    }
    file.close();
    cout << "Toplam " << count << " kitap yuklendi." << endl;
}

// Öğrencileri okuyup işlemleri yapıyorum, ödünç veya iade
void processStudents(Ogrenci& ogrenciler, Kitap& kitaplar) {
    ifstream file("Ogrenciler.txt");
    if (!file.is_open()) {
        cout << "Ogrenciler.txt dosyasi acilamadi!" << endl;
        return;
    }
    int oid, kid, islem;
    string ad;
    int count = 0;
    while (file >> oid) {
        file.ignore();
        getline(file, ad, '\t');
        file >> kid >> islem;
        cout << "Ogrenci okundu: " << ad << ", Islem: " << islem << endl;
        if (islem == 1) {
            ogrenciler.oduncAl(oid, ad, kid, kitaplar);
        } else if (islem == 0) {
            string kitap_adi = kitaplar.kitapAra(kid);
            if (!kitap_adi.empty()) {
                ogrenciler.iadeEt(oid, ad, kid, kitap_adi, kitaplar);
            } else {
                cout << "Kitap bulunamadi: " << kid << endl;
            }
        }
        count++;
    }
    file.close();
    cout << "Toplam " << count << " ogrenci islendi." << endl;
}


int main() {
    Kitap kitaplar;
    Ogrenci ogrenciler;
    loadBooks(kitaplar);
    processStudents(ogrenciler, kitaplar);

    int secim;
    do {
        cout << "\n1. Tum kitaplari goster\n2. Kitap odunc ver (manuel)\n3. Kitap odunc ver (kuyruktan)\n4. Bekleyen odunc alma taleplerini goster\n5. Odunc alinan kitaplari goster\n6. Iade edilen kitaplari goster\n7. Kitap iade al\n8. Kuyruga manuel talep ekle\n9. Cikis\nSecim: ";
        if (!(cin >> secim)) {
            cout << "Hata: Gecersiz secim girisi! Lutfen 1-9 arasinda bir sayi girin." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        switch (secim) {
            case 1:
                kitaplar.kitaplarilistele();
                break;
            case 2: {
                int oid, kid;
                string ad;
                cout << "Ogrenci ID: ";
                cin >> oid;
                cin.ignore();
                cout << "Ad Soyad: ";
                getline(cin, ad);
                cout << "Kitap ID: ";
                cin >> kid;

                // Kitap ID’sini kontrol et
                if (kitaplar.kitapAra(kid).empty()) {
                    cout << "Hata: Kitap ID " << kid << " sistemde bulunamadi, odunc verilemedi!" << endl;
                    break;
                }

                // Manuel ödünç verme işlemini yap
                ogrenciler.oduncAl(oid, ad, kid, kitaplar);
                break;
            }
            case 3:
                ogrenciler.kuyrukIsle(kitaplar);
                break;
            case 4:
                ogrenciler.kuyrukGoster();
                break;
            case 5:
                ogrenciler.oduncListesiGoster();
                break;
            case 6:
                ogrenciler.yiginGoster();
                break;
            case 7: {
                int oid, kid;
                string ad, kitap_adi;
                cout << "Ogrenci ID: ";
                if (!(cin >> oid)) {
                    cout << "Hata: Gecersiz Ogrenci ID girisi!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                }
                cin.ignore();
                cout << "Ad Soyad: ";
                getline(cin, ad);
                cout << "Kitap ID: ";
                if (!(cin >> kid)) {
                    cout << "Hata: Gecersiz Kitap ID girisi!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                }
                cin.ignore();
                cout << "Kitap Adi: ";
                getline(cin, kitap_adi);

                
                if (kitaplar.kitapAra(kid).empty()) {
                    cout << "Hata: Kitap ID " << kid << " sistemde bulunamadi, iade yapilamadi!" << endl;
                    break;
                }

                // İade işlemini yap
                if (ogrenciler.kuyruktaKontrolEt(oid, ad, kid)) {
                    if (kitaplar.stokAzalt(kid)) {
                        ogrenciler.iadeEt(oid, ad, kid, kitap_adi, kitaplar);
                        ogrenciler.kuyrukIsle(kitaplar); // Kuyruğu güncelle
                        cout << ad << " kuyruktan kitabi aldi: " << kitap_adi << endl;
                    } else {
                        cout << "Hata: Stok hala yetersiz, iade islemi tamamlanamadi!" << endl;
                    }
                } else {
                    ogrenciler.iadeEt(oid, ad, kid, kitap_adi, kitaplar);
                }
                break;
            }
            case 8: {
                int oid, kid;
                string ad;
                cout << "Ogrenci ID: ";
                if (!(cin >> oid)) {
                    cout << "Hata: Gecersiz Ogrenci ID girisi!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                }
                cin.ignore();
                cout << "Ad Soyad: ";
                getline(cin, ad);
                cout << "Kitap ID: ";
                if (!(cin >> kid)) {
                    cout << "Hata: Gecersiz Kitap ID girisi!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                }
                cin.ignore();

                
                if (kitaplar.kitapAra(kid).empty()) {
                    cout << "Hata: Kitap ID " << kid << " sistemde bulunamadi, kuyruga eklenemedi!" << endl;
                    break;
                }

                // Manuel kuyruk ekleme işlemini yap
                ogrenciler.kuyrugaEkle(oid, ad, kid, kitaplar);
                break;
            }
            case 9:
                cout << "Cikis yapildi.\n";
                break;
            default:
                cout << "Gecersiz secim!\n";
        }
    } while (secim != 9);

    cin.get(); 
    return 0;
}