// 09. Arbore AVL (BST care se echilibreaza singur)
//
// Compilare:  g++ -std=c++17 -Wall 09_avl.cpp -o avl
// Rulare:     ./avl          (toate testele)
//             ./avl 3        (doar testul 3)
//
// Fa intai 08_bst.cpp: AVL-ul e un BST la care, dupa fiecare inserare sau
// stergere, repari echilibrul pe drumul de intoarcere spre radacina.
//
// Ce exersezi:
//   - factorul de echilibru: h(stanga) - h(dreapta), trebuie sa fie -1, 0 sau 1
//   - rotirile la stanga si la dreapta, si cele 4 cazuri: LL, RR, LR, RL
//   - de ce inaltimea ramane O(log n) chiar daca inserezi chei sortate
//
// Ordinea recomandata: constructor, goala/marime, inalt, actualizeaza,
// rotire_dreapta, rotire_stanga, echilibreaza, insereaza, contine, inordine,
// preordine, inaltime, apoi bonusul: sterge.

#include "teste.hpp"
#include <climits>
#include <cmath>
#include <set>
using namespace std;

// ============================== CLASA ==============================

class AVL {
    struct Nod {
        int cheie;
        int h;    // inaltimea subarborelui cu radacina in nodul asta (frunza: 1)
        Nod* st;
        Nod* dr;
    };
    Nod* rad;
    int dim;

    // Inaltimea memorata a lui n; 0 pentru nullptr.
    static int inalt(Nod* n) {
        throw NeImplementat();
    }

    // Recalculeaza n->h din inaltimile copiilor.
    static void actualizeaza(Nod* n) {
        throw NeImplementat();
    }

    //        y                x
    //       / \              / \     .
    //      x   C    ==>     A   y
    //     / \                  / \   .
    //    A   B                B   C
    // Returneaza noua radacina a subarborelui (x). Nu uita sa actualizezi
    // inaltimile, in ordinea buna (intai cel care a ajuns mai jos).
    static Nod* rotire_dreapta(Nod* y) {
        throw NeImplementat();
    }

    // Oglinda lui rotire_dreapta.
    static Nod* rotire_stanga(Nod* x) {
        throw NeImplementat();
    }

    // Apelata pe fiecare nod de pe drumul de intoarcere dupa o inserare sau
    // stergere: actualizeaza inaltimea, calculeaza factorul de echilibru si,
    // daca e 2 sau -2, aplica rotirea (sau rotirile) potrivite.
    // Atentie la cazul in care copilul are factorul 0 (apare doar la stergere):
    // acolo ajunge o singura rotire.
    // Returneaza noua radacina a subarborelui.
    static Nod* echilibreaza(Nod* n) {
        throw NeImplementat();
    }

    // Aici adaugi functiile tale recursive, de exemplu
    //   Nod* insereaza(Nod* n, int x, bool& inserat);  // returneaza noua radacina
    //   Nod* sterge(Nod* n, int x, bool& sters);

    // Pentru teste (nu modifica): returneaza inaltimea reala a subarborelui,
    // sau -1 daca nu e AVL corect (ordine BST, inaltimi memorate, echilibru).
    static int verifica(Nod* n, long long lo, long long hi) {
        if (!n) return 0;
        if (n->cheie <= lo || n->cheie >= hi) return -1;
        int a = verifica(n->st, lo, n->cheie), b = verifica(n->dr, n->cheie, hi);
        if (a < 0 || b < 0 || abs(a - b) > 1) return -1;
        if (n->h != 1 + max(a, b)) return -1;
        return 1 + max(a, b);
    }

public:
    AVL() {
        throw NeImplementat();
    }

    // Elibereaza toate nodurile (fara throw).
    ~AVL() {
    }

    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = delete;

    bool goala() const {
        throw NeImplementat();
    }

    int marime() const {
        throw NeImplementat();
    }

    // Fara duplicate: daca x exista deja, returneaza false.
    bool insereaza(int x) {
        throw NeImplementat();
    }

    bool contine(int x) const {
        throw NeImplementat();
    }

    vector<int> inordine() const {
        throw NeImplementat();
    }

    vector<int> preordine() const {
        throw NeImplementat();
    }

    // Inaltimea arborelui (gol: 0).
    int inaltime() const {
        throw NeImplementat();
    }

    // BONUS. Stergere ca la BST (cazul cu doi copii: succesorul), apoi
    // echilibreaza pe drumul de intoarcere. false daca x nu exista.
    bool sterge(int x) {
        throw NeImplementat();
    }

    // Pentru teste (nu modifica).
    bool e_avl() const { return verifica(rad, LLONG_MIN, LLONG_MAX) >= 0; }
};

// ======================= TESTE (nu modifica) =======================

void test_gol() {
    AVL t;
    VERIFICA(t.goala(), "arborele nou trebuie sa fie gol");
    VERIFICA_EGAL(t.marime(), 0, "marimea arborelui nou");
    VERIFICA_EGAL(t.inaltime(), 0, "inaltimea arborelui gol");
    VERIFICA(!t.contine(5), "arborele gol nu contine nimic");
    VERIFICA(t.e_avl(), "arborele gol e AVL");
}

void test_fara_rotiri() {
    AVL t;
    for (int x : {5, 3, 8}) t.insereaza(x);
    VERIFICA_EGAL(t.preordine(), (vector<int>{5, 3, 8}), "forma dupa 5, 3, 8");
    VERIFICA_EGAL(t.inaltime(), 2, "inaltime");
    VERIFICA(t.e_avl(), "nu e AVL corect (inaltimile memorate sunt bune?)");
    VERIFICA(!t.insereaza(3), "duplicat");
    VERIFICA_EGAL(t.marime(), 3, "marime");
}

static void verifica_rotire(vector<int> ordine, const string& caz) {
    AVL t;
    for (int x : ordine) t.insereaza(x);
    VERIFICA(t.e_avl(), "cazul " + caz + ": arborele nu e AVL corect");
    VERIFICA_EGAL(t.preordine(), (vector<int>{2, 1, 3}), "cazul " + caz + ": forma dupa rotire");
}

void test_ll()  { verifica_rotire({3, 2, 1}, "LL (3, 2, 1 -> rotire dreapta)"); }
void test_rr()  { verifica_rotire({1, 2, 3}, "RR (1, 2, 3 -> rotire stanga)"); }
void test_lr()  { verifica_rotire({3, 1, 2}, "LR (3, 1, 2 -> stanga pe copil, apoi dreapta)"); }
void test_rl()  { verifica_rotire({1, 3, 2}, "RL (1, 3, 2 -> dreapta pe copil, apoi stanga)"); }

void test_sortat() {
    AVL t;
    for (int i = 1; i <= 1023; i++) t.insereaza(i);
    VERIFICA(t.e_avl(), "dupa inserarea cheilor 1..1023 arborele nu e AVL corect");
    VERIFICA_EGAL(t.inaltime(), 10, "inaltimea dupa 1..1023 in ordine (la BST simplu ar fi 1023)");
    VERIFICA_EGAL(t.marime(), 1023, "marime");
    vector<int> asteptat;
    for (int i = 1; i <= 1023; i++) asteptat.push_back(i);
    VERIFICA_EGAL(t.inordine(), asteptat, "inordine");
}

void test_aleator_inserari() {
    mt19937 rng(17);
    AVL t;
    set<int> ref;
    for (int i = 0; i < 100000; i++) {
        int x = rng() % 1000000;
        VERIFICA_EGAL(t.insereaza(x), ref.insert(x).second, "insereaza vs std::set");
    }
    VERIFICA(t.e_avl(), "dupa 100000 de inserari arborele nu e AVL corect");
    VERIFICA_EGAL(t.marime(), (int)ref.size(), "marime vs std::set");
    double limita = 1.45 * log2(ref.size() + 2);
    VERIFICA(t.inaltime() <= limita, "inaltimea e prea mare pentru un AVL");
    VERIFICA_EGAL(t.inordine(), vector<int>(ref.begin(), ref.end()), "inordine vs std::set");
    for (int i = 0; i < 1000; i++) {
        int x = rng() % 1000000;
        VERIFICA_EGAL(t.contine(x), ref.count(x) == 1, "contine vs std::set");
    }
}

void test_sterge_bonus() {
    AVL t;
    for (int x : {2, 1, 4, 3, 5}) t.insereaza(x);
    VERIFICA(t.sterge(1), "sterge(1)");  // dezechilibreaza radacina: rotire stanga
    VERIFICA(t.e_avl(), "dupa sterge(1) arborele nu e AVL corect");
    VERIFICA_EGAL(t.preordine(), (vector<int>{4, 2, 3, 5}), "forma dupa sterge(1)");
    VERIFICA(!t.sterge(1), "sterge(1) a doua oara");
    mt19937 rng(19);
    AVL a;
    set<int> ref;
    for (int pas = 0; pas < 100000; pas++) {
        int x = rng() % 5000;
        if (rng() % 2) VERIFICA_EGAL(a.insereaza(x), ref.insert(x).second, "insereaza vs std::set");
        else VERIFICA_EGAL(a.sterge(x), ref.erase(x) == 1, "sterge vs std::set");
        if (pas % 5000 == 0) VERIFICA(a.e_avl(), "dupa stergeri arborele nu mai e AVL corect");
    }
    VERIFICA(a.e_avl(), "la final arborele nu e AVL corect");
    VERIFICA_EGAL(a.inordine(), vector<int>(ref.begin(), ref.end()), "inordine vs std::set");
}

int main(int argc, char** argv) {
    return ruleaza_teste(argc, argv, {
        {"arbore gol", test_gol},
        {"inserari fara rotiri", test_fara_rotiri},
        {"rotire LL", test_ll},
        {"rotire RR", test_rr},
        {"rotire LR", test_lr},
        {"rotire RL", test_rl},
        {"chei sortate 1..1023", test_sortat},
        {"100000 de inserari aleatoare", test_aleator_inserari},
        {"BONUS: stergere", test_sterge_bonus},
    });
}
