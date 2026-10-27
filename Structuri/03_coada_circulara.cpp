// 03. Coada circulara (FIFO: primul intrat, primul iesit), pe vector
//
// Compilare:  g++ -std=c++17 -Wall 03_coada_circulara.cpp -o coada
// Rulare:     ./coada        (toate testele)
//             ./coada 3      (doar testul 3)
//
// Ce exersezi:
//   - "ring buffer": pop nu muta elementele, doar avanseaza fata; cand ajungi
//     la capatul vectorului, continui de la 0 (ca acele unui ceas)
//   - marirea cand coada e "rupta" in doua bucati
//
// Ordinea recomandata: constructor, goala/marime, push, fata, spate, pop,
// mareste, erorile pe coada goala.

#include "teste.hpp"
#include <queue>
using namespace std;

// ============================== CLASA ==============================

class Coada {
    int* v;    // vectorul cu elementele
    int cap;   // cate locuri are v
    int prim;  // indexul primului element (fata cozii)
    int dim;   // cate elemente sunt in coada acum

    // Dubleaza capacitatea. ATENTIE: elementele trebuie copiate in ordinea
    // cozii, incepand de la `prim`, nu de la 0.
    void mareste() {
        throw NeImplementat();
    }

public:
    explicit Coada(int capInitiala = 4) {
        throw NeImplementat();
    }

    ~Coada() {
    }

    Coada(const Coada&) = delete;
    Coada& operator=(const Coada&) = delete;

    bool goala() const {
        throw NeImplementat();
    }

    int marime() const {
        throw NeImplementat();
    }

    int capacitate() const {
        throw NeImplementat();
    }

    // Adauga x la SFARSITUL cozii. Daca e plina, intai mareste().
    void push(int x) {
        throw NeImplementat();
    }

    // Scoate elementul din FATA cozii. Coada goala -> out_of_range.
    void pop() {
        throw NeImplementat();
    }

    // Primul element (cel care iese urmatorul). Coada goala -> out_of_range.
    int fata() const {
        throw NeImplementat();
    }

    // Ultimul element adaugat. Coada goala -> out_of_range.
    int spate() const {
        throw NeImplementat();
    }
};

// ======================= TESTE (nu modifica) =======================

void test_noua() {
    Coada c;
    VERIFICA(c.goala(), "coada noua trebuie sa fie goala");
    VERIFICA_EGAL(c.marime(), 0, "marimea cozii noi");
    VERIFICA_EGAL(c.capacitate(), 4, "capacitatea implicita");
}

void test_push_fata_spate() {
    Coada c;
    c.push(10); c.push(20); c.push(30);
    VERIFICA(!c.goala(), "dupa 3 push-uri coada nu e goala");
    VERIFICA_EGAL(c.marime(), 3, "marime dupa 3 push");
    VERIFICA_EGAL(c.fata(), 10, "fata dupa push 10,20,30");
    VERIFICA_EGAL(c.spate(), 30, "spate dupa push 10,20,30");
}

void test_fifo() {
    Coada c;
    c.push(1); c.push(2); c.push(3);
    c.pop();
    VERIFICA_EGAL(c.fata(), 2, "fata dupa un pop");
    c.pop();
    VERIFICA_EGAL(c.fata(), 3, "fata dupa doua pop-uri");
    c.pop();
    VERIFICA(c.goala(), "dupa 3 push si 3 pop coada e goala");
}

void test_wrap_around() {
    Coada c(4);
    c.push(1); c.push(2); c.push(3); c.push(4);  // plina: [1 2 3 4]
    c.pop(); c.pop();                            // [_ _ 3 4], prim = 2
    c.push(5); c.push(6);                        // [5 6 3 4], spatele s-a intors la 0
    VERIFICA_EGAL(c.capacitate(), 4, "capacitatea nu trebuia sa creasca (era loc la inceput)");
    VERIFICA_EGAL(c.marime(), 4, "marime dupa wrap-around");
    VERIFICA_EGAL(c.spate(), 6, "spate dupa wrap-around");
    for (int x : {3, 4, 5, 6}) {
        VERIFICA_EGAL(c.fata(), x, "ordinea dupa wrap-around");
        c.pop();
    }
}

void test_marire_rupta() {
    Coada c(4);
    c.push(1); c.push(2); c.push(3); c.push(4);
    c.pop(); c.pop();
    c.push(5); c.push(6);  // [5 6 3 4], prim = 2
    c.push(7);             // plina -> mareste()
    VERIFICA_EGAL(c.capacitate(), 8, "capacitatea trebuia sa se dubleze");
    VERIFICA_EGAL(c.marime(), 5, "marime dupa marire");
    for (int x : {3, 4, 5, 6, 7}) {
        VERIFICA_EGAL(c.fata(), x, "ordinea dupa marire (ai copiat de la prim?)");
        c.pop();
    }
    VERIFICA(c.goala(), "goala la final");
}

void test_multe() {
    Coada c(1);
    for (int i = 0; i < 100000; i++) c.push(i);
    VERIFICA_EGAL(c.marime(), 100000, "marime dupa 100000 push");
    for (int i = 0; i < 100000; i++) {
        VERIFICA_EGAL(c.fata(), i, "ordine la 100000 elemente");
        c.pop();
    }
}

void test_erori() {
    Coada c;
    VERIFICA(arunca<out_of_range>([&] { c.pop(); }), "pop pe coada goala trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { c.fata(); }), "fata pe coada goala trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { c.spate(); }), "spate pe coada goala trebuie sa arunce out_of_range");
    c.push(1); c.pop();
    VERIFICA(arunca<out_of_range>([&] { c.pop(); }), "pop dupa ce s-a golit trebuie sa arunce out_of_range");
}

void test_aleator() {
    mt19937 rng(42);
    Coada c(2);
    queue<int> ref;
    for (int pas = 0; pas < 200000; pas++) {
        if (ref.empty() || rng() % 3 != 0) {
            int x = rng() % 1000;
            c.push(x); ref.push(x);
        } else {
            VERIFICA_EGAL(c.fata(), ref.front(), "fata vs std::queue");
            c.pop(); ref.pop();
        }
        VERIFICA_EGAL(c.marime(), (int)ref.size(), "marime vs std::queue");
        if (!ref.empty()) VERIFICA_EGAL(c.spate(), ref.back(), "spate vs std::queue");
    }
}

int main(int argc, char** argv) {
    return ruleaza_teste(argc, argv, {
        {"coada noua", test_noua},
        {"push, fata, spate", test_push_fata_spate},
        {"FIFO", test_fifo},
        {"wrap-around fara marire", test_wrap_around},
        {"marire cand coada e rupta in doua", test_marire_rupta},
        {"100000 de elemente", test_multe},
        {"erori pe coada goala", test_erori},
        {"operatii aleatoare vs std::queue", test_aleator},
    });
}
