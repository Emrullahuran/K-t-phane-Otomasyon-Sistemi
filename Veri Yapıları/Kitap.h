#ifndef KITAP_H
#define KITAP_H

#include <string>

using namespace std;


class Kitap {
private:
    
    struct Node {
        int kitap_id; 
        string kitap_adi; 
        string yazar; 
        int kitap_adet;
        Node* next; 
        Node(int id, string adi, string y, int adet) : kitap_id(id), kitap_adi(adi), yazar(y), kitap_adet(adet), next(nullptr) {}
    };
    Node* head; 

public:
    Kitap(); 
    ~Kitap(); 
    void kitapEkle(int id, string adi, string yazar, int adet); 
    void kitaplarilistele(); 
    string kitapAra(int kitap_id); 
    bool stokAzalt(int kitap_id); 
    void stokArttir(int kitap_id); 
    int stokGetir(int kitap_id);
};

#endif