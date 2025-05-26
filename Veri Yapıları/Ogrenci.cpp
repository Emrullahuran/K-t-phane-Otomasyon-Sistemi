#include "Ogrenci.h"
#include <iostream>

using namespace std;


Ogrenci::Ogrenci() : borrowHead(nullptr), qFront(nullptr), qRear(nullptr), sTop(nullptr) {}


Ogrenci::~Ogrenci() {
    while (borrowHead) {
        BorrowNode* temp = borrowHead;
        borrowHead = borrowHead->next;
        delete temp;
    }
    while (qFront) {
        QueueNode* temp = qFront;
        qFront = qFront->next;
        delete temp;
    }
    while (sTop) {
        StackNode* temp = sTop;
        sTop = sTop->next;
        delete temp;
    }
    if (qRear) delete qRear; 
}

// Ödünç alma işlemi, stok varsa direkt veriyorum, yoksa kuyruğa ekliyorum
void Ogrenci::oduncAl(int ogrenci_id, string ad_soyad, int kitap_id, Kitap& kitaplar) {
    if (kitaplar.stokAzalt(kitap_id)) {
        string kitap_adi = kitaplar.kitapAra(kitap_id);
        int kalan_stok = kitaplar.stokGetir(kitap_id);
        cout << ad_soyad << " '" << kitap_adi << "' kitabi odunc aldi, kalan stok: " << kalan_stok << endl;

        // Ödünç alma listesine ekliyorum
        BorrowNode* newNode = new BorrowNode(ogrenci_id, ad_soyad, kitap_id, kitap_adi);
        if (!borrowHead) {
            borrowHead = newNode;
        } else {
            BorrowNode* temp = borrowHead;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    } else {
        QueueNode* newNode = new QueueNode(ogrenci_id, ad_soyad, kitap_id);
        if (!qFront) {
            qFront = qRear = newNode;
        } else {
            qRear->next = newNode;
            qRear = newNode;
        }
        string kitap_adi = kitaplar.kitapAra(kitap_id);
        cout << ad_soyad << " kuyruga eklendi, kitap stokta yok: " << kitap_adi << " (ID: " << kitap_id << ")" << endl;
    }
}

// İade işlemi, kitabı yığına ekliyorum ve stoğu artırıyorum
void Ogrenci::iadeEt(int ogrenci_id, string ad_soyad, int kitap_id, string kitap_adi, Kitap& kitaplar) {
    kitaplar.stokArttir(kitap_id);
    StackNode* newNode = new StackNode(ogrenci_id, ad_soyad, kitap_id, kitap_adi);
    newNode->next = sTop;
    sTop = newNode;
    int kalan_stok = kitaplar.stokGetir(kitap_id);
    cout << ad_soyad << " '" << kitap_adi << "' kitabi iade etti, kalan stok: " << kalan_stok << endl;
}

// Kuyruğa manuel ekleme fonksiyonu, stok kontrolü ile ekleme yapıyorum
void Ogrenci::kuyrugaEkle(int ogrenci_id, string ad_soyad, int kitap_id, Kitap& kitaplar) {
    string kitap_adi = kitaplar.kitapAra(kitap_id);
    if (kitap_adi.empty()) {
        cout << "Hata: Kitap ID " << kitap_id << " sistemde yok, kuyruga eklenemedi!" << endl;
        return;
    }
    int stok = kitaplar.stokGetir(kitap_id);
    if (stok <= 0) {
        cout << "Hata: " << kitap_adi << " (ID: " << kitap_id << ") stokta yok, kuyruga eklenemedi!" << endl;
        return;
    }
    QueueNode* newNode = new QueueNode(ogrenci_id, ad_soyad, kitap_id);
    if (!qFront) {
        qFront = qRear = newNode;
    } else {
        qRear->next = newNode;
        qRear = newNode;
    }
    cout << ad_soyad << " kuyruga eklendi, talep edilen kitap: " << kitap_adi << " (ID: " << kitap_id << "), stok: " << stok << endl;
}

// Ödünç alınan kitapları gösteriyorum, liste boşsa uyarı yazıyorum
void Ogrenci::oduncListesiGoster() {
    if (!borrowHead) {
        cout << "Odunc alinan kitap yok!" << endl;
        return;
    }
    BorrowNode* temp = borrowHead;
    while (temp) {
        cout << "Ogrenci ID: " << temp->ogrenci_id << ", Ad: " << temp->ad_soyad << ", Kitap: " << temp->kitap_adi << " (ID: " << temp->kitap_id << ")" << endl;
        temp = temp->next;
    }
}

// Kuyruktakileri gösteriyorum, boşsa uyarı yazıyorum
void Ogrenci::kuyrukGoster() {
    if (!qFront) {
        cout << "Kuyruk bos!" << endl;
        return;
    }
    QueueNode* temp = qFront;
    while (temp) {
        cout << "Ogrenci ID: " << temp->ogrenci_id << ", Ad: " << temp->ad_soyad << ", Kitap ID: " << temp->kitap_id << endl;
        temp = temp->next;
    }
}

//  sırayla kitabı varsa ödünç veriyorum, yoksa kuyrukta bırakıyorum
void Ogrenci::kuyrukIsle(Kitap& kitaplar) {
    cout << "Kuyruk isleme basladi..." << endl;
    if (!qFront) {
        cout << "Kuyruk bos, islenecek talep yok!" << endl;
        cout << "Kuyruk islemesi bitti." << endl;
        return;
    }
    QueueNode* current = qFront;
    QueueNode* prev = nullptr;
    while (current) {
        int kitap_id = current->kitap_id;
        string kitap_adi = kitaplar.kitapAra(kitap_id);
        if (kitap_adi.empty()) {
            cout << "Hata: Kitap ID " << kitap_id << " sistemde yok, " << current->ad_soyad << " kuyruktan cikarildi!" << endl;
            if (current == qFront) {
                qFront = current->next;
                if (!qFront) qRear = nullptr;
            } else {
                prev->next = current->next;
                if (current == qRear) qRear = prev;
            }
            QueueNode* temp = current;
            current = current->next;
            delete temp;
            continue;
        }
        if (kitaplar.stokAzalt(kitap_id)) {
            int kalan_stok = kitaplar.stokGetir(kitap_id);
            cout << current->ad_soyad << " '" << kitap_adi << "' kitabi odunc aldi (kuyruktan), kalan stok: " << kalan_stok << endl;

            // Ödünç alma listesine ekliyorum
            BorrowNode* newNode = new BorrowNode(current->ogrenci_id, current->ad_soyad, current->kitap_id, kitap_adi);
            if (!borrowHead) {
                borrowHead = newNode;
            } else {
                BorrowNode* temp = borrowHead;
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }

            // Kuyruktan çıkar
            if (current == qFront) {
                qFront = current->next;
                if (!qFront) qRear = nullptr;
            } else {
                prev->next = current->next;
                if (current == qRear) qRear = prev;
            }
            QueueNode* temp = current;
            current = current->next;
            delete temp;
        } else {
            cout << "Stok yetersiz: " << kitap_adi << " (ID: " << kitap_id << "), " << current->ad_soyad << " beklemeye devam ediyor." << endl;
            prev = current;
            current = current->next;
        }
    }
    if (!qFront) qRear = nullptr;
    cout << "Kuyruk islemesi bitti." << endl;
}


bool Ogrenci::kuyruktaKontrolEt(int ogrenci_id, string ad_soyad, int kitap_id) {
    QueueNode* current = qFront;
    while (current) {
        if (current->ogrenci_id == ogrenci_id && current->ad_soyad == ad_soyad && current->kitap_id == kitap_id) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Yığındakileri gösteriyorum, boşsa uyarı 
void Ogrenci::yiginGoster() {
    if (!sTop) {
        cout << "Yigin bos!" << endl;
        return;
    }
    StackNode* temp = sTop;
    while (temp) {
        cout << "Ogrenci ID: " << temp->ogrenci_id << ", Ad: " << temp->ad_soyad << ", Kitap: " << temp->kitap_adi << endl;
        temp = temp->next;
    }
}