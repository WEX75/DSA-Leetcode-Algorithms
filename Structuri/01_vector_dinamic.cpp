// 01. Vector dinamic (ce face std::vector<int> pe dinauntru)
//
// Compilare:  g++ -std=c++17 -Wall 01_vector_dinamic.cpp -o vector
// Rulare:     ./vector       (toate testele)
//             ./vector 3     (doar testul 3)
//
// Ce exersezi:
//   - dublarea capacitatii => push_back in O(1) amortizat (lectia 1, §10.1)
//   - regula celor trei: destructor + constructor de copiere + operator=
//     (copiere "in adancime": fiecare vector are memoria lui)
//
// Ordinea recomandata: constructor, marime/gol/capacitate, push_back + at,
// realoca, pop_back, operator[], insereaza, sterge, copiere, atribuire.

#include "teste.hpp"
using namespace std;

// ============================== CLASA ==============================

class VectorDinamic {
    int* date;  // elementele, pe pozitiile 0 .. dim-1
    int dim;    // cate elemente sunt folosite
    int cap;    // cate locuri are `date` (mereu cap >= 1 si dim <= cap)

    // Aloca un `date` nou cu `nouaCap` locuri, copiaza cele `dim` elemente
    // si elibereaza vechiul `date`.
    void realoca(int nouaCap) {
        throw NeImplementat();
    }

public:
    // Vector gol, cu capacitate 1.
    VectorDinamic() {
        throw NeImplementat();
    }

    // Elibereaza memoria. Destructorul nu are voie sa arunce exceptii, de aceea
    // aici nu e `throw NeImplementat();`. Compileaza cu -fsanitize=address ca sa
    // vezi daca ai memory leak.
    ~VectorDinamic() {
    }

    // Constructor de copiere:  VectorDinamic b = a;
    // b trebuie sa aiba memoria LUI, cu aceleasi elemente ca a.
    VectorDinamic(const VectorDinamic& altul) {
        throw NeImplementat();
    }

    // Atribuire:  b = a;
    // b avea deja memoria lui, care trebuie eliberata. Atentie la `a = a;`.
    // Returneaza *this (ca sa mearga si `c = b = a;`).
    VectorDinamic& operator=(const VectorDinamic& altul) {
        throw NeImplementat();
    }

    int marime() const {
        throw NeImplementat();
    }

    int capacitate() const {
        throw NeImplementat();
    }

    bool gol() const {
        throw NeImplementat();
    }

    // Adauga x la final. Daca nu mai e loc, intai dubleaza capacitatea.
    void push_back(int x) {
        throw NeImplementat();
    }

    // Scoate ultimul element. Vector gol -> throw out_of_range("...").
    void pop_back() {
        throw NeImplementat();
    }

    // Elementul de pe pozitia i, CU verificare: i in afara [0, dim) -> out_of_range.
    int at(int i) const {
        throw NeImplementat();
    }

    // Elementul de pe pozitia i, FARA verificare (ca la std::vector).
    // Returneaza o referinta, ca sa mearga si  v[i] = 5;
    int& operator[](int i) {
        throw NeImplementat();
    }

    // Insereaza x pe pozitia poz (0 <= poz <= dim). Elementele de la poz
    // incolo se muta cu o pozitie la dreapta. poz invalid -> out_of_range.
    void insereaza(int poz, int x) {
        throw NeImplementat();
    }

    // Sterge elementul de pe pozitia poz (0 <= poz < dim). Elementele de dupa
    // se muta cu o pozitie la stanga. poz invalid -> out_of_range.
    void sterge(int poz) {
        throw NeImplementat();
    }
};

// ======================= TESTE (nu modifica) =======================

static vector<int> continut(const VectorDinamic& v) {
    vector<int> r;
    for (int i = 0; i < v.marime(); i++) r.push_back(v.at(i));
    return r;
}

void test_nou() {
    VectorDinamic v;
    VERIFICA(v.gol(), "vectorul nou trebuie sa fie gol");
    VERIFICA_EGAL(v.marime(), 0, "marimea vectorului nou");
    VERIFICA_EGAL(v.capacitate(), 1, "capacitatea vectorului nou");
}

void test_push_at() {
    VectorDinamic v;
    v.push_back(10); v.push_back(20); v.push_back(30);
    VERIFICA(!v.gol(), "dupa 3 push_back vectorul nu e gol");
    VERIFICA_EGAL(v.marime(), 3, "marime dupa 3 push_back");
    VERIFICA_EGAL(v.at(0), 10, "at(0)");
    VERIFICA_EGAL(v.at(1), 20, "at(1)");
    VERIFICA_EGAL(v.at(2), 30, "at(2)");
}

void test_crestere() {
    VectorDinamic v;
    int realocari = 0, capAnterioara = v.capacitate();
    for (int i = 0; i < 1000; i++) {
        v.push_back(i);
        VERIFICA(v.marime() <= v.capacitate(), "marime > capacitate: ai scris in afara memoriei");
        if (v.capacitate() != capAnterioara) {
            VERIFICA_EGAL(v.capacitate(), 2 * capAnterioara, "capacitatea trebuie sa se dubleze");
            realocari++;
            capAnterioara = v.capacitate();
        }
    }
    VERIFICA_EGAL(realocari, 10, "numar de realocari pentru 1000 de elemente (1 -> 1024)");
    for (int i = 0; i < 1000; i++)
        VERIFICA_EGAL(v.at(i), i, "elementele trebuie pastrate la realocare");
}

void test_pop() {
    VectorDinamic v;
    v.push_back(1); v.push_back(2); v.push_back(3);
    v.pop_back();
    VERIFICA_EGAL(v.marime(), 2, "marime dupa pop_back");
    VERIFICA_EGAL(v.at(1), 2, "ultimul element dupa pop_back");
    v.pop_back(); v.pop_back();
    VERIFICA(v.gol(), "gol dupa ce am scos tot");
    VERIFICA(arunca<out_of_range>([&] { v.pop_back(); }), "pop_back pe vector gol trebuie sa arunce out_of_range");
}

void test_at_invalid() {
    VectorDinamic v;
    VERIFICA(arunca<out_of_range>([&] { v.at(0); }), "at(0) pe vector gol trebuie sa arunce out_of_range");
    v.push_back(5);
    VERIFICA(arunca<out_of_range>([&] { v.at(-1); }), "at(-1) trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { v.at(1); }), "at(marime) trebuie sa arunce out_of_range");
}

void test_paranteze() {
    VectorDinamic v;
    v.push_back(1); v.push_back(2); v.push_back(3);
    v[1] = 42;
    VERIFICA_EGAL(v.at(1), 42, "v[1] = 42 trebuie sa modifice elementul (returnezi referinta?)");
    v[0] += 5;
    VERIFICA_EGAL(v.at(0), 6, "v[0] += 5");
}

void test_insereaza() {
    VectorDinamic v;
    v.push_back(1); v.push_back(2); v.push_back(3);
    v.insereaza(0, 0);
    VERIFICA_EGAL(continut(v), (vector<int>{0, 1, 2, 3}), "insereaza la inceput");
    v.insereaza(4, 9);
    VERIFICA_EGAL(continut(v), (vector<int>{0, 1, 2, 3, 9}), "insereaza la final");
    v.insereaza(2, 7);
    VERIFICA_EGAL(continut(v), (vector<int>{0, 1, 7, 2, 3, 9}), "insereaza la mijloc");
    VERIFICA(arunca<out_of_range>([&] { v.insereaza(-1, 5); }), "insereaza(-1) trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { v.insereaza(7, 5); }), "insereaza(marime+1) trebuie sa arunce out_of_range");
}

void test_sterge() {
    VectorDinamic v;
    for (int i = 0; i < 6; i++) v.push_back(i);
    v.sterge(0);
    VERIFICA_EGAL(continut(v), (vector<int>{1, 2, 3, 4, 5}), "sterge primul");
    v.sterge(4);
    VERIFICA_EGAL(continut(v), (vector<int>{1, 2, 3, 4}), "sterge ultimul");
    v.sterge(1);
    VERIFICA_EGAL(continut(v), (vector<int>{1, 3, 4}), "sterge din mijloc");
    VERIFICA(arunca<out_of_range>([&] { v.sterge(3); }), "sterge(marime) trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { v.sterge(-1); }), "sterge(-1) trebuie sa arunce out_of_range");
}

// La copiere superficiala (doar pointerul), a si b ar sterge aceeasi memorie
// in destructor, iar programul ar crapa inainte sa afiseze de ce. De aceea
// vectorii de aici sunt pe heap si se sterg doar daca testul a trecut.
void test_copiere() {
    VectorDinamic* a = new VectorDinamic;
    a->push_back(1); a->push_back(2); a->push_back(3);
    VectorDinamic* b = new VectorDinamic(*a);
    VERIFICA_EGAL(continut(*b), (vector<int>{1, 2, 3}), "copia are alte elemente");
    (*b)[0] = 100;
    b->push_back(4);
    VERIFICA_EGAL(continut(*a), (vector<int>{1, 2, 3}),
                  "a s-a schimbat cand ai modificat b: copiezi doar pointerul, nu elementele");
    delete a;
    delete b;
}

void test_atribuire() {
    VectorDinamic* a = new VectorDinamic;
    VectorDinamic* b = new VectorDinamic;
    a->push_back(1); a->push_back(2); a->push_back(3);
    b->push_back(9);
    *b = *a;
    VERIFICA_EGAL(continut(*b), (vector<int>{1, 2, 3}), "dupa b = a");
    (*b)[0] = 100;
    VERIFICA_EGAL(a->at(0), 1, "a s-a schimbat cand ai modificat b: atribuirea nu copiaza in adancime");
    *a = *a;
    VERIFICA_EGAL(continut(*a), (vector<int>{1, 2, 3}), "a = a a stricat vectorul");
    delete a;
    delete b;
}

void test_aleator() {
    mt19937 rng(7);
    VectorDinamic v;
    vector<int> ref;
    for (int pas = 0; pas < 20000; pas++) {
        int op = rng() % 10, x = rng() % 1000;
        if (op <= 4) {
            v.push_back(x); ref.push_back(x);
        } else if (op == 5 && !ref.empty()) {
            v.pop_back(); ref.pop_back();
        } else if (op == 6) {
            int poz = rng() % (ref.size() + 1);
            v.insereaza(poz, x); ref.insert(ref.begin() + poz, x);
        } else if (op == 7 && !ref.empty()) {
            int poz = rng() % ref.size();
            v.sterge(poz); ref.erase(ref.begin() + poz);
        } else if (op == 8 && !ref.empty()) {
            int poz = rng() % ref.size();
            v[poz] = x; ref[poz] = x;
        } else if (!ref.empty()) {
            int poz = rng() % ref.size();
            VERIFICA_EGAL(v.at(poz), ref[poz], "at vs std::vector");
        }
        VERIFICA_EGAL(v.marime(), (int)ref.size(), "marime vs std::vector");
    }
    VERIFICA_EGAL(continut(v), ref, "continutul final vs std::vector");
}

int main(int argc, char** argv) {
    return ruleaza_teste(argc, argv, {
        {"vector nou", test_nou},
        {"push_back si at", test_push_at},
        {"dublarea capacitatii", test_crestere},
        {"pop_back", test_pop},
        {"at cu indice invalid", test_at_invalid},
        {"operator[]", test_paranteze},
        {"insereaza", test_insereaza},
        {"sterge", test_sterge},
        {"constructor de copiere", test_copiere},
        {"operator=", test_atribuire},
        {"operatii aleatoare vs std::vector", test_aleator},
    });
}
