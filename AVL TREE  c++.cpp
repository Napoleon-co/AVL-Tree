#include <iostream>
#include <algorithm> 
using namespace std;

struct Node {
    int data;       
    Node* kiri;     
    Node* kanan;    
    int tinggi;     
    
    Node(int val) : data(val), kiri(nullptr), kanan(nullptr), tinggi(1) {}
};

class AVLTree {
private:
    Node* root;

    int gettinggi(Node* N) {
        if (N == nullptr)
            return 0;
        return N->tinggi;
    }

    int getbalance(Node* N) {
        if (N == nullptr)
            return 0;
        return gettinggi(N->kiri) - gettinggi(N->kanan); //rumus keseimbangan
    }

    Node* rotasikanan(Node* y) {
        Node* x = y->kiri;
        Node* T2 = x->kanan;

        x->kanan = y;
        y->kiri = T2;

        y->tinggi = 1 + max(gettinggi(y->kiri), gettinggi(y->kanan));
        x->tinggi = 1 + max(gettinggi(x->kiri), gettinggi(x->kanan));

        return x; 
    }

    Node* rotasikiri(Node* x) {
        Node* y = x->kanan;
        Node* T2 = y->kiri;

        y->kiri = x;
        x->kanan = T2;

        x->tinggi = 1 + max(gettinggi(x->kiri), gettinggi(x->kanan));
        y->tinggi = 1 + max(gettinggi(y->kiri), gettinggi(y->kanan));

        return y; 
    }

    Node* insertnilai(Node* node, int data) {
        if (node == nullptr)
            return new Node(data);

        if (data < node->data)
            node->kiri = insertnilai(node->kiri, data);
        else if (data > node->data)
            node->kanan = insertnilai(node->kanan, data);
        else 
            return node; 

        node->tinggi = 1 + max(gettinggi(node->kiri), gettinggi(node->kanan));

        int balance = getbalance(node);

        // LL Case
        if (balance > 1 && data < node->kiri->data)
            return rotasikanan(node);

        // RR Case
        if (balance < -1 && data > node->kanan->data)
            return rotasikiri(node);

        // LR Case
        if (balance > 1 && data > node->kiri->data) {
            node->kiri = rotasikiri(node->kiri);
            return rotasikanan(node);
        }

        // RL Case
        if (balance < -1 && data < node->kanan->data) {
            node->kanan = rotasikanan(node->kanan);
            return rotasikiri(node);
        }

        return node;
    }

    void cetakurutan(Node* node) {
        if (node != nullptr) {
            cetakurutan(node->kiri);
            cout << node->data << " ";
            cetakurutan(node->kanan);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int data) {
        cout << "\nMemasukkan " << data;
        root = insertnilai(root, data);
    }

    void tampilurutan() {
        cout << "\n Hasil urutan:\n";
        cetakurutan(root);

    }
};

int main() {
    AVLTree pohonAVL;

    cout << "PROSES\n";
    pohonAVL.insert(10);
    pohonAVL.insert(20); 
    pohonAVL.insert(30);
    pohonAVL.insert(60); 
    pohonAVL.insert(45);
    pohonAVL.insert(9);
    pohonAVL.insert(25); 

    pohonAVL.tampilurutan();

    return 0;
}