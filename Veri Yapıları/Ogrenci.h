#ifndef OGRENCI_H
#define OGRENCI_H

#include <string>
#include "Kitap.h"

using namespace std;


class Ogrenci {
private:
    
    struct BorrowNode {
        int ogrenci_id;
        string ad_soyad; 
        int kitap_id;
        string kitap_adi; 
        BorrowNode* next; 
        BorrowNode(int oid, string ad, int kid, string kadi) : ogrenci_id(oid), ad_soyad(ad), kitap_id(kid), kitap_adi(kadi), next(nullptr) {}
    };
   
    struct QueueNode {
        int ogrenci_id; 
        string ad_soyad; 
        int kitap_id; 
        QueueNode* next; 
        QueueNode(int oid, string ad, int kid) : ogrenci_id(oid), ad_soyad(ad), kitap_id(kid), next(nullptr) {}
    };
    
    struct StackNode {
        int ogrenci_id; 
        string ad_soyad; 
        int kitap_id; 
        string kitap_adi; 
        StackNode* next; 
        StackNode(int oid, string ad, int kid, string kadi) : ogrenci_id(oid), ad_soyad(ad), kitap_id(kid), kitap_adi(kadi), next(nullptr) {}
    };
    BorrowNode* borrowHead; 
    QueueNode* qFront; 
    QueueNode* qRear; 
    StackNode* sTop; 

public:
    Ogrenci(); 
    ~Ogrenci(); 
    void oduncAl(int ogrenci_id, string ad_soyad, int kitap_id, Kitap& kitaplar); // Ödünç alma fonksiyonu
    void iadeEt(int ogrenci_id, string ad_soyad, int kitap_id, string kitap_adi, Kitap& kitaplar); // İade etme
    void kuyrugaEkle(int ogrenci_id, string ad_soyad, int kitap_id, Kitap& kitaplar); // Kuyruğa manuel ekleme fonksiyonu
    void oduncListesiGoster(); // Ödünç alınan kitapları gösteriyorum
    void kuyrukGoster(); // Kuyruktakileri gösteriyorum
    void kuyrukIsle(Kitap& kitaplar); // Kuyruktaki talepleri işliyorum
    bool kuyruktaKontrolEt(int ogrenci_id, string ad_soyad, int kitap_id); 
    void yiginGoster(); 
};

#endif