// 04. Deque (coada cu doua capete), pe vector circular
//
// Compilare:  g++ -std=c++17 -Wall 04_deque.cpp -o deque
// Rulare:     ./deque        (toate testele)
//             ./deque 3      (doar testul 3)
//
// Ce exersezi:
//   - aceeasi idee ca la coada circulara (03), dar poti adauga si scoate la
//     AMBELE capete, toate in O(1)
//   - push_front cand prim == 0: unde ajunge noul prim? Atentie, in C++
//     restul impartirii unui numar negativ e negativ: (-1) % 4 == -1
//
// Ordinea recomandata: constructor, goala/marime/capacitate, push_back, at,
// push_front, fata/spate, pop_front, pop_back, mareste.

#include "teste.hpp"
#include <deque>
using namespace std;

// ============================== CLASA ==============================

class Deque {
    int* v;    // vectorul cu elementele
    int cap;   // cate locuri are v
    int prim;  // indexul din v al primului element
    int dim;   // cate elemente sunt in deque

    // Dubleaza capacitatea; elementele se copiaza in ordine, de la `prim`.
    void mareste() {
        throw NeImplementat();
    }

public:
    explicit Deque(int capInitiala = 4) {
        throw NeImplementat();
    }

    ~Deque() {
    }

    Deque(const Deque&) = delete;
    Deque& operator=(const Deque&) = delete;

    bool goala() const {
        throw NeImplementat();
    }

    int marime() const {
        throw NeImplementat();
    }

    int capacitate() const {
        throw NeImplementat();
    }

    // Adauga x la sfarsit.
    void push_back(int x) {
        throw NeImplementat();
    }

    // Adauga x la inceput (devine noul prim element).
    void push_front(int x) {
        throw NeImplementat();
    }

    // Scoate ultimul element. Deque gol -> out_of_range.
    void pop_back() {
        throw NeImplementat();
    }

    // Scoate primul element. Deque gol -> out_of_range.
    void pop_front() {
        throw NeImplementat();
    }

    // Primul element. Deque gol -> out_of_range.
    int fata() const {
        throw NeImplementat();
    }

    // Ultimul element. Deque gol -> out_of_range.
    int spate() const {
        throw NeImplementat();
    }

    // Al i-lea element numarand de la fata (at(0) == fata()).
    // i in afara [0, marime) -> out_of_range.
    int at(int i) const {
        throw NeImplementat();
    }
};

// ======================= TESTE (nu modifica) =======================

static vector<int> continut(const Deque& d) {
    vector<int> r;
    for (int i = 0; i < d.marime(); i++) r.push_back(d.at(i));
    return r;
}

void test_nou() {
    Deque d;
    VERIFICA(d.goala(), "deque-ul nou trebuie sa fie gol");
    VERIFICA_EGAL(d.marime(), 0, "marimea deque-ului nou");
    VERIFICA_EGAL(d.capacitate(), 4, "capacitatea implicita");
}

void test_push_back_at() {
    Deque d;
    d.push_back(1); d.push_back(2); d.push_back(3);
    VERIFICA_EGAL(continut(d), (vector<int>{1, 2, 3}), "dupa push_back 1, 2, 3");
    VERIFICA(arunca<out_of_range>([&] { d.at(3); }), "at(marime) trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { d.at(-1); }), "at(-1) trebuie sa arunce out_of_range");
}

void test_push_front() {
    Deque d(4);
    d.push_front(1);  // prim era 0: noul prim trebuie sa fie la capatul vectorului
    VERIFICA_EGAL(d.capacitate(), 4, "push_front pe deque gol nu trebuie sa mareasca");
    VERIFICA_EGAL(d.fata(), 1, "fata dupa push_front(1)");
    d.push_back(2);
    d.push_front(0);
    VERIFICA_EGAL(continut(d), (vector<int>{0, 1, 2}), "dupa push_front(1), push_back(2), push_front(0)");
    VERIFICA_EGAL(d.capacitate(), 4, "3 elemente incap in 4 locuri");
    VERIFICA_EGAL(d.fata(), 0, "fata");
    VERIFICA_EGAL(d.spate(), 2, "spate");
}

void test_pop_ambele() {
    Deque d;
    for (int i = 1; i <= 5; i++) d.push_back(i);
    d.pop_front();
    VERIFICA_EGAL(continut(d), (vector<int>{2, 3, 4, 5}), "dupa pop_front");
    d.pop_back();
    VERIFICA_EGAL(continut(d), (vector<int>{2, 3, 4}), "dupa pop_back");
    d.pop_back(); d.pop_front(); d.pop_back();
    VERIFICA(d.goala(), "gol dupa ce am scos tot");
    d.push_front(9);
    VERIFICA_EGAL(continut(d), (vector<int>{9}), "push_front dupa ce s-a golit");
}

void test_marire_rupta() {
    Deque d(4);
    d.push_back(3); d.push_back(4);
    d.push_front(2); d.push_front(1);  // plin si rupt: [3 4 1 2] in vector, prim = 2
    d.push_front(0);                   // mareste()
    VERIFICA_EGAL(d.capacitate(), 8, "capacitatea trebuia sa se dubleze");
    VERIFICA_EGAL(continut(d), (vector<int>{0, 1, 2, 3, 4}), "ordinea dupa marire");
    d.push_back(5);
    VERIFICA_EGAL(continut(d), (vector<int>{0, 1, 2, 3, 4, 5}), "push_back dupa marire");
}

void test_erori() {
    Deque d;
    VERIFICA(arunca<out_of_range>([&] { d.pop_front(); }), "pop_front pe deque gol");
    VERIFICA(arunca<out_of_range>([&] { d.pop_back(); }), "pop_back pe deque gol");
    VERIFICA(arunca<out_of_range>([&] { d.fata(); }), "fata pe deque gol");
    VERIFICA(arunca<out_of_range>([&] { d.spate(); }), "spate pe deque gol");
    VERIFICA(arunca<out_of_range>([&] { d.at(0); }), "at(0) pe deque gol");
}

void test_aleator() {
    mt19937 rng(11);
    Deque d(1);
    deque<int> ref;
    for (int pas = 0; pas < 200000; pas++) {
        int op = rng() % 6, x = rng() % 1000;
        if (op == 0 || ref.empty()) { d.push_back(x); ref.push_back(x); }
        else if (op == 1) { d.push_front(x); ref.push_front(x); }
        else if (op == 2) { d.pop_back(); ref.pop_back(); }
        else if (op == 3) { d.pop_front(); ref.pop_front(); }
        else {
            int i = rng() % ref.size();
            VERIFICA_EGAL(d.at(i), ref[i], "at vs std::deque");
        }
        VERIFICA_EGAL(d.marime(), (int)ref.size(), "marime vs std::deque");
        if (!ref.empty()) {
            VERIFICA_EGAL(d.fata(), ref.front(), "fata vs std::deque");
            VERIFICA_EGAL(d.spate(), ref.back(), "spate vs std::deque");
        }
    }
}

int main(int argc, char** argv) {
    return ruleaza_teste(argc, argv, {
        {"deque nou", test_nou},
        {"push_back si at", test_push_back_at},
        {"push_front (indice negativ!)", test_push_front},
        {"pop la ambele capete", test_pop_ambele},
        {"marire cand e rupt in doua", test_marire_rupta},
        {"erori pe deque gol", test_erori},
        {"operatii aleatoare vs std::deque", test_aleator},
    });
}
