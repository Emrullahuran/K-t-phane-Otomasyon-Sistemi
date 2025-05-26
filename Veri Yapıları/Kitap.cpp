#include "Kitap.h"
#include <iostream>

using namespace std;


Kitap::Kitap() : head(nullptr) {}


Kitap::~Kitap() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Yeni bir kitap ekliyorum, bağlı listenin sonuna gidip ekliyorum
void Kitap::kitapEkle(int id, string adi, string yazar, int adet) {
    Node* newNode = new Node(id, adi, yazar, adet);
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Tüm kitapları ekrana yazdırıyorum, liste boşsa uyarı yazıyorum
void Kitap::kitaplarilistele() {
    if (!head) {
        cout << "Kitap listesi bos!" << endl;
        return;
    }
    Node* temp = head;
    while (temp) {
        cout << "ID: " << temp->kitap_id << ", Ad: " << temp->kitap_adi 
             << ", Yazar: " << temp->yazar << ", Adet: " << temp->kitap_adet << endl;
        temp = temp->next;
    }
}

// Kitap ID’sine göre kitap arıyorum, bulursam adını döndürüyorum, yoksa boş dönüyor
string Kitap::kitapAra(int kitap_id) {
    Node* temp = head;
    while (temp) {
        if (temp->kitap_id == kitap_id) return temp->kitap_adi;
        temp = temp->next;
    }
    return "";
}

// Kitabın stokunu bir azaltıyorum
bool Kitap::stokAzalt(int kitap_id) {
    Node* temp = head;
    while (temp) {
        if (temp->kitap_id == kitap_id && temp->kitap_adet > 0) {
            temp->kitap_adet--;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Kitabın stokunu bir artırıyorum, ID’yi bulup artırıyorum
void Kitap::stokArttir(int kitap_id) {
    Node* temp = head;
    bool bulundu = false;
    while (temp) {
        if (temp->kitap_id == kitap_id) {
            temp->kitap_adet++;
            bulundu = true;
            break;
        }
        temp = temp->next;
    }
    if (!bulundu) cout << "Kitap ID: " << kitap_id << " bulunamadi, stok artirilamadi!" << endl;
}

// Kitabın stok değerini döndürüyorum, bulamazsam -1 dönüyorum
int Kitap::stokGetir(int kitap_id) {
    Node* temp = head;
    while (temp) {
        if (temp->kitap_id == kitap_id) return temp->kitap_adet;
        temp = temp->next;
    }
    return -1; // Kitap bulunamadıysa -1 dönüyorum
}