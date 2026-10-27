// 06. Lista dublu inlantuita
//
// Compilare:  g++ -std=c++17 -Wall 06_lista_dublu_inlantuita.cpp -o lista2
// Rulare:     ./lista2       (toate testele)
//             ./lista2 3     (doar testul 3)
//
// Ce exersezi:
//   - fiecare nod are DOUA sageti (prev si next): la fiecare inserare sau
//     stergere ai de reparat ambele directii, la vecinul din stanga SI la
//     cel din dreapta
//   - spre deosebire de lista simpla, poti sterge un nod daca il ai doar pe el
//   - testele parcurg lista in ambele sensuri, deci prind orice `prev` uitat
//
// Ordinea recomandata: constructor, goala/marime, push_back, la_vector,
// la_vector_invers, push_front, fata/spate, pop_front, pop_back, nodul,
// insereaza, sterge, inverseaza, destructor.

#include "teste.hpp"
#include <list>
using namespace std;

// ============================== CLASA ==============================

class ListaDubla {
    struct Nod {
        int info;
        Nod* prev;  // nodul din stanga; nullptr pentru primul nod
        Nod* next;  // nodul din dreapta; nullptr pentru ultimul nod
    };
    Nod* prim;
    Nod* ultim;
    int dim;

    // Nodul de pe pozitia poz (0 <= poz < dim). Bonus: porneste de la capatul
    // mai apropiat (de la prim daca poz < dim/2, altfel de la ultim pe prev).
    Nod* nodul(int poz) const {
        throw NeImplementat();
    }

public:
    ListaDubla() {
        throw NeImplementat();
    }

    // Elibereaza toate nodurile (fara throw).
    ~ListaDubla() {
    }

    ListaDubla(const ListaDubla&) = delete;
    ListaDubla& operator=(const ListaDubla&) = delete;

    bool goala() const {
        throw NeImplementat();
    }

    int marime() const {
        throw NeImplementat();
    }

    // Elementele de la prim la ultim, mergand pe `next`.
    vector<int> la_vector() const {
        throw NeImplementat();
    }

    // Elementele de la ultim la prim, mergand pe `prev`.
    vector<int> la_vector_invers() const {
        throw NeImplementat();
    }

    void push_front(int x) {
        throw NeImplementat();
    }

    void push_back(int x) {
        throw NeImplementat();
    }

    // Lista goala -> out_of_range.
    void pop_front() {
        throw NeImplementat();
    }

    // Lista goala -> out_of_range. (Aici se vede avantajul fata de lista
    // simpla: ajungi la penultimul nod direct, prin ultim->prev.)
    void pop_back() {
        throw NeImplementat();
    }

    // Lista goala -> out_of_range.
    int fata() const {
        throw NeImplementat();
    }

    // Lista goala -> out_of_range.
    int spate() const {
        throw NeImplementat();
    }

    // Insereaza x astfel incat sa ajunga pe pozitia poz (0 <= poz <= dim).
    // poz == 0 si poz == dim sunt push_front / push_back.
    // poz invalid -> out_of_range.
    void insereaza(int poz, int x) {
        throw NeImplementat();
    }

    // Sterge nodul de pe pozitia poz (0 <= poz < dim). poz invalid -> out_of_range.
    void sterge(int poz) {
        throw NeImplementat();
    }

    // Inverseaza lista pe loc, O(n): la fiecare nod interschimbi prev cu
    // next, apoi interschimbi prim cu ultim.
    void inverseaza() {
        throw NeImplementat();
    }
};

// ======================= TESTE (nu modifica) =======================

// Verifica ca lista e aceeasi citita in ambele sensuri si are marimea buna.
static void verifica_legaturi(const ListaDubla& l, const vector<int>& asteptat, const string& context) {
    VERIFICA_EGAL(l.la_vector(), asteptat, context + " (parcurgere pe next)");
    vector<int> invers(asteptat.rbegin(), asteptat.rend());
    VERIFICA_EGAL(l.la_vector_invers(), invers, context + " (parcurgere inapoi pe prev)");
    VERIFICA_EGAL(l.marime(), (int)asteptat.size(), context + " (marime)");
}

void test_noua() {
    ListaDubla l;
    VERIFICA(l.goala(), "lista noua trebuie sa fie goala");
    verifica_legaturi(l, {}, "lista noua");
}

void test_push() {
    ListaDubla l;
    l.push_back(2); l.push_back(3); l.push_front(1); l.push_front(0); l.push_back(4);
    verifica_legaturi(l, {0, 1, 2, 3, 4}, "dupa push_front/push_back");
    VERIFICA_EGAL(l.fata(), 0, "fata");
    VERIFICA_EGAL(l.spate(), 4, "spate");
}

void test_pop() {
    ListaDubla l;
    for (int x : {1, 2, 3, 4}) l.push_back(x);
    l.pop_front();
    verifica_legaturi(l, {2, 3, 4}, "dupa pop_front");
    l.pop_back();
    verifica_legaturi(l, {2, 3}, "dupa pop_back");
    l.pop_back(); l.pop_front();
    verifica_legaturi(l, {}, "dupa ce am scos tot");
    l.push_back(7);
    verifica_legaturi(l, {7}, "push_back dupa golire");
}

void test_erori() {
    ListaDubla l;
    VERIFICA(arunca<out_of_range>([&] { l.pop_front(); }), "pop_front pe lista goala");
    VERIFICA(arunca<out_of_range>([&] { l.pop_back(); }), "pop_back pe lista goala");
    VERIFICA(arunca<out_of_range>([&] { l.fata(); }), "fata pe lista goala");
    VERIFICA(arunca<out_of_range>([&] { l.spate(); }), "spate pe lista goala");
    VERIFICA(arunca<out_of_range>([&] { l.sterge(0); }), "sterge(0) pe lista goala");
    VERIFICA(arunca<out_of_range>([&] { l.insereaza(1, 5); }), "insereaza(1) pe lista goala");
}

void test_insereaza() {
    ListaDubla l;
    l.insereaza(0, 2);
    verifica_legaturi(l, {2}, "insereaza in lista goala");
    l.insereaza(0, 0);
    verifica_legaturi(l, {0, 2}, "insereaza la inceput");
    l.insereaza(2, 4);
    verifica_legaturi(l, {0, 2, 4}, "insereaza la final");
    l.insereaza(1, 1);
    verifica_legaturi(l, {0, 1, 2, 4}, "insereaza la mijloc");
    l.insereaza(3, 3);
    verifica_legaturi(l, {0, 1, 2, 3, 4}, "insereaza la mijloc, langa final");
    VERIFICA(arunca<out_of_range>([&] { l.insereaza(6, 9); }), "insereaza(marime+1) trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { l.insereaza(-1, 9); }), "insereaza(-1) trebuie sa arunce out_of_range");
}

void test_sterge() {
    ListaDubla l;
    for (int x : {0, 1, 2, 3, 4, 5}) l.push_back(x);
    l.sterge(2);
    verifica_legaturi(l, {0, 1, 3, 4, 5}, "sterge din mijloc");
    l.sterge(0);
    verifica_legaturi(l, {1, 3, 4, 5}, "sterge primul");
    l.sterge(3);
    verifica_legaturi(l, {1, 3, 4}, "sterge ultimul");
    l.sterge(1);
    verifica_legaturi(l, {1, 4}, "sterge din mijloc");
    VERIFICA(arunca<out_of_range>([&] { l.sterge(2); }), "sterge(marime) trebuie sa arunce out_of_range");
}

void test_inverseaza() {
    ListaDubla l;
    l.inverseaza();
    verifica_legaturi(l, {}, "inversarea listei goale");
    for (int x : {1, 2, 3, 4}) l.push_back(x);
    l.inverseaza();
    verifica_legaturi(l, {4, 3, 2, 1}, "inversare");
    l.push_back(0); l.push_front(5);
    verifica_legaturi(l, {5, 4, 3, 2, 1, 0}, "push-uri dupa inversare");
}

void test_aleator() {
    mt19937 rng(9);
    ListaDubla l;
    list<int> ref;
    for (int pas = 0; pas < 20000; pas++) {
        int op = rng() % 8, x = rng() % 100;
        if (op == 0) { l.push_front(x); ref.push_front(x); }
        else if (op == 1) { l.push_back(x); ref.push_back(x); }
        else if (op == 2 && !ref.empty()) { l.pop_front(); ref.pop_front(); }
        else if (op == 3 && !ref.empty()) { l.pop_back(); ref.pop_back(); }
        else if (op == 4 || op == 5) {
            int poz = rng() % (ref.size() + 1);
            l.insereaza(poz, x); ref.insert(next(ref.begin(), poz), x);
        } else if (op == 6 && !ref.empty()) {
            int poz = rng() % ref.size();
            l.sterge(poz); ref.erase(next(ref.begin(), poz));
        } else if (rng() % 50 == 0) { l.inverseaza(); ref.reverse(); }
        VERIFICA_EGAL(l.marime(), (int)ref.size(), "marime vs std::list");
        if (pas % 500 == 0) verifica_legaturi(l, vector<int>(ref.begin(), ref.end()), "vs std::list");
    }
    verifica_legaturi(l, vector<int>(ref.begin(), ref.end()), "continutul final vs std::list");
}

int main(int argc, char** argv) {
    return ruleaza_teste(argc, argv, {
        {"lista noua", test_noua},
        {"push_front si push_back", test_push},
        {"pop_front si pop_back", test_pop},
        {"erori pe lista goala", test_erori},
        {"insereaza", test_insereaza},
        {"sterge", test_sterge},
        {"inverseaza", test_inverseaza},
        {"operatii aleatoare vs std::list", test_aleator},
    });
}
