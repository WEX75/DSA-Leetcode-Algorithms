// 07. Min-heap (coada de prioritati), pe vector
//
// Compilare:  g++ -std=c++17 -Wall 07_heap.cpp -o heap
// Rulare:     ./heap         (toate testele)
//             ./heap 3       (doar testul 3)
//
// Ce exersezi:
//   - un arbore binar complet tinut intr-un vector, fara pointeri
//   - proprietatea de heap: fiecare parinte <= copiii lui, deci minimul e in a[0]
//   - urca (sift-up) dupa inserare, coboara (sift-down) dupa extragere: O(log n)
//   - construirea unui heap din n elemente in O(n), nu O(n log n)
//   - aplicatii: heapsort si al k-lea cel mai mare element (LeetCode 215)
//
// Ordinea recomandata: goala/marime, minim, urca, insereaza, coboara,
// extrage_min, constructorul din vector, heapsort, al_k_lea_cel_mai_mare.

#include "teste.hpp"
#include <queue>
using namespace std;

// ============================== CLASA ==============================

class MinHeap {
    // Arborele, nivel cu nivel. Pentru nodul de pe pozitia i:
    //   copiii sunt pe 2*i + 1 si 2*i + 2, parintele e pe (i - 1) / 2.
    vector<int> a;

    // Elementul de pe pozitia i urca (schimbandu-se cu parintele) cat timp
    // e mai mic decat parintele.
    void urca(int i) {
        throw NeImplementat();
    }

    // Elementul de pe pozitia i coboara (schimbandu-se cu copilul MAI MIC)
    // cat timp e mai mare decat vreunul dintre copii.
    void coboara(int i) {
        throw NeImplementat();
    }

public:
    // Heap gol: vectorul e deja gol, nu e nimic de facut.
    MinHeap() {}

    // Construieste heap-ul din v in O(n): copiezi v in a, apoi apelezi
    // coboara() pentru fiecare nod care are copii, de la ultimul spre radacina.
    explicit MinHeap(const vector<int>& v) {
        throw NeImplementat();
    }

    bool goala() const {
        throw NeImplementat();
    }

    int marime() const {
        throw NeImplementat();
    }

    // Cel mai mic element. Heap gol -> out_of_range.
    int minim() const {
        throw NeImplementat();
    }

    // Pui x la sfarsitul vectorului, apoi il lasi sa urce.
    void insereaza(int x) {
        throw NeImplementat();
    }

    // Scoate si returneaza minimul. Ultimul element ia locul radacinii, apoi
    // coboara. Heap gol -> out_of_range.
    int extrage_min() {
        throw NeImplementat();
    }

    // Pentru teste (nu modifica): verifica proprietatea de heap.
    bool e_heap() const {
        for (size_t i = 1; i < a.size(); i++)
            if (a[(i - 1) / 2] > a[i]) return false;
        return true;
    }
};

// Sorteaza crescator folosind un MinHeap. O(n log n).
vector<int> heapsort(const vector<int>& v) {
    throw NeImplementat();
}

// Al k-lea cel mai mare element din v (k = 1: maximul), 1 <= k <= v.size().
// Ideea: tii un MinHeap cu cele mai mari k elemente vazute pana acum;
// la final, minimul lui e raspunsul. O(n log k).
// k invalid -> out_of_range.
int al_k_lea_cel_mai_mare(const vector<int>& v, int k) {
    throw NeImplementat();
}

// ======================= TESTE (nu modifica) =======================

void test_gol() {
    MinHeap h;
    VERIFICA(h.goala(), "heap-ul nou trebuie sa fie gol");
    VERIFICA_EGAL(h.marime(), 0, "marimea heap-ului nou");
    VERIFICA(arunca<out_of_range>([&] { h.minim(); }), "minim pe heap gol trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { h.extrage_min(); }), "extrage_min pe heap gol trebuie sa arunce out_of_range");
}

void test_insereaza() {
    MinHeap h;
    for (int x : {5, 3, 8, 1, 9, 2}) {
        h.insereaza(x);
        VERIFICA(h.e_heap(), "dupa insereaza proprietatea de heap e stricata (urca nu merge?)");
    }
    VERIFICA_EGAL(h.marime(), 6, "marime dupa 6 inserari");
    VERIFICA_EGAL(h.minim(), 1, "minimul");
}

void test_extrage() {
    MinHeap h;
    for (int x : {5, 3, 8, 1, 9, 2, 7}) h.insereaza(x);
    vector<int> scoase;
    while (!h.goala()) {
        scoase.push_back(h.extrage_min());
        VERIFICA(h.e_heap(), "dupa extrage_min proprietatea de heap e stricata (coboara nu merge?)");
    }
    VERIFICA_EGAL(scoase, (vector<int>{1, 2, 3, 5, 7, 8, 9}), "ordinea extragerilor");
}

void test_duplicate_negative() {
    MinHeap h;
    for (int x : {0, -5, 3, -5, 3, 0, -1}) h.insereaza(x);
    vector<int> scoase;
    while (!h.goala()) scoase.push_back(h.extrage_min());
    VERIFICA_EGAL(scoase, (vector<int>{-5, -5, -1, 0, 0, 3, 3}), "duplicate si negative");
}

void test_construieste() {
    vector<int> v;
    for (int i = 0; i < 1000; i++) v.push_back((i * 7919) % 1000);
    MinHeap h(v);
    VERIFICA_EGAL(h.marime(), 1000, "marime dupa construire");
    VERIFICA(h.e_heap(), "heap-ul construit din vector nu respecta proprietatea de heap");
    for (int i = 0; i < 1000; i++)
        VERIFICA_EGAL(h.extrage_min(), i, "extrageri din heap-ul construit");
    MinHeap gol(vector<int>{});
    VERIFICA(gol.goala(), "heap construit din vector gol");
}

void test_heapsort() {
    VERIFICA_EGAL(heapsort({}), vector<int>(), "heapsort pe vector gol");
    VERIFICA_EGAL(heapsort({4, 1, 3, 1, -2}), (vector<int>{-2, 1, 1, 3, 4}), "heapsort");
    mt19937 rng(1);
    vector<int> v(5000);
    for (int& x : v) x = rng() % 100000 - 50000;
    vector<int> sortat = v;
    sort(sortat.begin(), sortat.end());
    VERIFICA_EGAL(heapsort(v), sortat, "heapsort pe 5000 de numere aleatoare");
}

void test_k_lea() {
    vector<int> v = {3, 2, 1, 5, 6, 4};
    VERIFICA_EGAL(al_k_lea_cel_mai_mare(v, 1), 6, "k = 1 (maximul)");
    VERIFICA_EGAL(al_k_lea_cel_mai_mare(v, 2), 5, "k = 2");
    VERIFICA_EGAL(al_k_lea_cel_mai_mare(v, 6), 1, "k = n (minimul)");
    VERIFICA_EGAL(al_k_lea_cel_mai_mare({3, 2, 3, 1, 2, 4, 5, 5, 6}, 4), 4, "cu duplicate");
    VERIFICA(arunca<out_of_range>([&] { al_k_lea_cel_mai_mare(v, 0); }), "k = 0 trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { al_k_lea_cel_mai_mare(v, 7); }), "k > n trebuie sa arunce out_of_range");
}

void test_aleator() {
    mt19937 rng(21);
    MinHeap h;
    priority_queue<int, vector<int>, greater<int>> ref;
    for (int pas = 0; pas < 200000; pas++) {
        if (ref.empty() || rng() % 3 != 0) {
            int x = rng() % 10000;
            h.insereaza(x); ref.push(x);
        } else {
            VERIFICA_EGAL(h.extrage_min(), ref.top(), "extrage_min vs std::priority_queue");
            ref.pop();
        }
        VERIFICA_EGAL(h.marime(), (int)ref.size(), "marime vs std::priority_queue");
        if (!ref.empty()) VERIFICA_EGAL(h.minim(), ref.top(), "minim vs std::priority_queue");
    }
}

int main(int argc, char** argv) {
    return ruleaza_teste(argc, argv, {
        {"heap gol", test_gol},
        {"insereaza (urca)", test_insereaza},
        {"extrage_min (coboara)", test_extrage},
        {"duplicate si negative", test_duplicate_negative},
        {"construire din vector in O(n)", test_construieste},
        {"heapsort", test_heapsort},
        {"al k-lea cel mai mare", test_k_lea},
        {"operatii aleatoare vs std::priority_queue", test_aleator},
    });
}
