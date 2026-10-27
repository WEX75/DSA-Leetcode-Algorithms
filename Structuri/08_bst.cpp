// 08. Arbore binar de cautare (BST)
//
// Compilare:  g++ -std=c++17 -Wall 08_bst.cpp -o bst
// Rulare:     ./bst          (toate testele)
//             ./bst 3        (doar testul 3)
//
// Ce exersezi:
//   - regula BST: tot ce e in stanga unui nod < nod < tot ce e in dreapta
//   - recursivitate pe arbori: aproape fiecare operatie are o functie
//     ajutatoare privata care primeste un Nod* (subarborele) si se apeleaza
//     pe st si pe dr
//   - stergerea, cu cele 3 cazuri: frunza, un copil, doi copii
//   - parcurgerile: inordine (iese sortat!) si preordine
//
// Ordinea recomandata: constructor, goala/marime, insereaza, contine,
// inordine, preordine, minim/maxim, inaltime, succesor, sterge, destructor.

#include "teste.hpp"
#include <set>
using namespace std;

// ============================== CLASA ==============================

class BST {
    struct Nod {
        int cheie;
        Nod* st;  // subarborele cu chei mai mici
        Nod* dr;  // subarborele cu chei mai mari
    };
    Nod* rad;  // radacina; nullptr pentru arbore gol
    int dim;

    // Aici adaugi functiile tale recursive ajutatoare, de exemplu
    //   void inordine(Nod* n, vector<int>& rez) const;
    //   int inaltime(Nod* n) const;
    //   Nod* sterge(Nod* n, int x, bool& sters);   // returneaza noua radacina a subarborelui
    //   void elibereaza(Nod* n);

public:
    BST() {
        throw NeImplementat();
    }

    // Elibereaza toate nodurile (fara throw). Hint: intai copiii, apoi nodul.
    ~BST() {
    }

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    bool goala() const {
        throw NeImplementat();
    }

    int marime() const {
        throw NeImplementat();
    }

    // Insereaza x. Fara duplicate: daca x exista deja, nu face nimic si
    // returneaza false.
    bool insereaza(int x) {
        throw NeImplementat();
    }

    bool contine(int x) const {
        throw NeImplementat();
    }

    // Cea mai mica / cea mai mare cheie. Arbore gol -> out_of_range.
    int minim() const {
        throw NeImplementat();
    }

    int maxim() const {
        throw NeImplementat();
    }

    // Stanga, nod, dreapta: cheile ies sortate crescator.
    vector<int> inordine() const {
        throw NeImplementat();
    }

    // Nod, stanga, dreapta. Testele o folosesc ca sa verifice FORMA arborelui.
    vector<int> preordine() const {
        throw NeImplementat();
    }

    // Numarul de noduri de pe cel mai lung drum radacina -> frunza.
    // Arbore gol: 0. Un singur nod: 1.
    int inaltime() const {
        throw NeImplementat();
    }

    // Cea mai mica cheie STRICT mai mare decat x (x nu trebuie sa fie in
    // arbore). Nu exista -> out_of_range. O(inaltime), fara inordine().
    int succesor(int x) const {
        throw NeImplementat();
    }

    // Sterge x; false daca nu exista. Cazul cu doi copii: inlocuiesti cheia
    // nodului cu SUCCESORUL ei (minimul din subarborele drept), apoi stergi
    // succesorul din subarborele drept. (Testele verifica forma, deci
    // foloseste succesorul, nu predecesorul.)
    bool sterge(int x) {
        throw NeImplementat();
    }
};

// ======================= TESTE (nu modifica) =======================

// Arborele din teste (inserat in ordinea 5, 3, 8, 1, 4, 7, 9):
//
//          5
//        /   \     .
//       3     8
//      / \   / \   .
//     1   4 7   9
static void construieste(BST& t) {
    for (int x : {5, 3, 8, 1, 4, 7, 9}) t.insereaza(x);
}

void test_gol() {
    BST t;
    VERIFICA(t.goala(), "arborele nou trebuie sa fie gol");
    VERIFICA_EGAL(t.marime(), 0, "marimea arborelui nou");
    VERIFICA_EGAL(t.inaltime(), 0, "inaltimea arborelui gol");
    VERIFICA_EGAL(t.inordine(), vector<int>(), "inordine pe arbore gol");
    VERIFICA(!t.contine(1), "arborele gol nu contine nimic");
    VERIFICA(arunca<out_of_range>([&] { t.minim(); }), "minim pe arbore gol trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { t.maxim(); }), "maxim pe arbore gol trebuie sa arunce out_of_range");
}

void test_insereaza_contine() {
    BST t;
    construieste(t);
    VERIFICA_EGAL(t.marime(), 7, "marime dupa 7 inserari");
    for (int x : {1, 3, 4, 5, 7, 8, 9}) VERIFICA(t.contine(x), "contine o cheie inserata");
    for (int x : {0, 2, 6, 10}) VERIFICA(!t.contine(x), "nu contine o cheie neinserata");
    VERIFICA(!t.insereaza(4), "insereaza(4) a doua oara trebuie sa returneze false");
    VERIFICA_EGAL(t.marime(), 7, "un duplicat nu schimba marimea");
}

void test_parcurgeri() {
    BST t;
    construieste(t);
    VERIFICA_EGAL(t.inordine(), (vector<int>{1, 3, 4, 5, 7, 8, 9}), "inordine (sortat)");
    VERIFICA_EGAL(t.preordine(), (vector<int>{5, 3, 1, 4, 8, 7, 9}), "preordine (forma arborelui)");
}

void test_min_max_inaltime() {
    BST t;
    construieste(t);
    VERIFICA_EGAL(t.minim(), 1, "minim");
    VERIFICA_EGAL(t.maxim(), 9, "maxim");
    VERIFICA_EGAL(t.inaltime(), 3, "inaltimea arborelui echilibrat cu 7 noduri");
    BST lant;
    for (int i = 1; i <= 10; i++) lant.insereaza(i);  // degenereaza intr-o lista
    VERIFICA_EGAL(lant.inaltime(), 10, "inaltimea arborelui degenerat 1..10");
    BST unu;
    unu.insereaza(42);
    VERIFICA_EGAL(unu.inaltime(), 1, "inaltimea arborelui cu un nod");
}

void test_succesor() {
    BST t;
    construieste(t);
    VERIFICA_EGAL(t.succesor(1), 3, "succesor(1)");
    VERIFICA_EGAL(t.succesor(4), 5, "succesor(4): urci spre un stramos");
    VERIFICA_EGAL(t.succesor(5), 7, "succesor(5): minimul din dreapta");
    VERIFICA_EGAL(t.succesor(6), 7, "succesor(6): 6 nu e in arbore");
    VERIFICA_EGAL(t.succesor(-100), 1, "succesor(-100)");
    VERIFICA(arunca<out_of_range>([&] { t.succesor(9); }), "succesor(maxim) trebuie sa arunce out_of_range");
}

void test_sterge_frunza_un_copil() {
    BST t;
    construieste(t);
    VERIFICA(!t.sterge(6), "sterge(6) trebuie sa returneze false");
    VERIFICA(t.sterge(1), "sterge frunza 1");
    VERIFICA_EGAL(t.preordine(), (vector<int>{5, 3, 4, 8, 7, 9}), "dupa stergerea frunzei 1");
    VERIFICA(t.sterge(3), "sterge 3 (are un singur copil)");
    VERIFICA_EGAL(t.preordine(), (vector<int>{5, 4, 8, 7, 9}), "dupa stergerea lui 3 (4 ii ia locul)");
    VERIFICA_EGAL(t.marime(), 5, "marime dupa doua stergeri");
}

void test_sterge_doi_copii() {
    BST t;
    construieste(t);
    VERIFICA(t.sterge(8), "sterge 8 (doi copii)");
    VERIFICA_EGAL(t.preordine(), (vector<int>{5, 3, 1, 4, 9, 7}), "dupa stergerea lui 8 (succesorul 9 ii ia locul)");
    VERIFICA(t.sterge(5), "sterge radacina 5");
    VERIFICA_EGAL(t.preordine(), (vector<int>{7, 3, 1, 4, 9}), "dupa stergerea radacinii (succesorul 7 urca)");
    for (int x : {7, 3, 1, 4, 9}) t.sterge(x);
    VERIFICA(t.goala(), "gol dupa ce am sters tot");
    t.insereaza(2);
    VERIFICA_EGAL(t.preordine(), (vector<int>{2}), "insereaza dupa golire");
}

void test_aleator() {
    mt19937 rng(13);
    BST t;
    set<int> ref;
    for (int pas = 0; pas < 30000; pas++) {
        int op = rng() % 4, x = rng() % 2000;
        if (op <= 1) {
            VERIFICA_EGAL(t.insereaza(x), ref.insert(x).second, "insereaza vs std::set");
        } else if (op == 2) {
            VERIFICA_EGAL(t.sterge(x), ref.erase(x) == 1, "sterge vs std::set");
        } else {
            VERIFICA_EGAL(t.contine(x), ref.count(x) == 1, "contine vs std::set");
            auto it = ref.upper_bound(x);
            if (it != ref.end()) VERIFICA_EGAL(t.succesor(x), *it, "succesor vs std::set");
        }
        VERIFICA_EGAL(t.marime(), (int)ref.size(), "marime vs std::set");
        if (pas % 1000 == 0)
            VERIFICA_EGAL(t.inordine(), vector<int>(ref.begin(), ref.end()), "inordine vs std::set");
    }
}

int main(int argc, char** argv) {
    return ruleaza_teste(argc, argv, {
        {"arbore gol", test_gol},
        {"insereaza si contine", test_insereaza_contine},
        {"inordine si preordine", test_parcurgeri},
        {"minim, maxim, inaltime", test_min_max_inaltime},
        {"succesor", test_succesor},
        {"sterge frunza / nod cu un copil", test_sterge_frunza_un_copil},
        {"sterge nod cu doi copii", test_sterge_doi_copii},
        {"operatii aleatoare vs std::set", test_aleator},
    });
}
