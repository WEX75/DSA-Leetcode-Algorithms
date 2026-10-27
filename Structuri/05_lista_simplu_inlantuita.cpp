// 05. Lista simplu inlantuita (cu pointer la primul SI la ultimul nod)
//
// Compilare:  g++ -std=c++17 -Wall 05_lista_simplu_inlantuita.cpp -o lista
// Rulare:     ./lista        (toate testele)
//             ./lista 3      (doar testul 3)
//
// Ce exersezi (ai inceput deja la Laborator 2, ex1):
//   - parcurgerea cu un cursor, cazurile "lista goala" si "un singur nod"
//   - stergerea unui nod: iti trebuie nodul DINAINTEA lui
//   - sa tii `ultim` la zi dupa FIECARE operatie (testele verifica asta
//     facand adauga_final dupa stergeri si dupa inversare)
//   - doua probleme clasice de interviu: inversarea listei si mijlocul ei
//
// Ordinea recomandata: constructor, goala/marime, adauga_final, la_vector,
// adauga_inceput, sterge_inceput, contine, al_k_lea, sterge_valoare,
// inverseaza, mijloc, destructor.

#include "teste.hpp"
#include <list>
using namespace std;

// ============================== CLASA ==============================

class ListaSimpla {
    struct Nod {
        int info;
        Nod* next;
    };
    Nod* prim;   // primul nod; nullptr daca lista e goala
    Nod* ultim;  // ultimul nod; nullptr daca lista e goala
    int dim;

public:
    ListaSimpla() {
        throw NeImplementat();
    }

    // Elibereaza toate nodurile (fara throw).
    ~ListaSimpla() {
    }

    ListaSimpla(const ListaSimpla&) = delete;
    ListaSimpla& operator=(const ListaSimpla&) = delete;

    bool goala() const {
        throw NeImplementat();
    }

    int marime() const {
        throw NeImplementat();
    }

    // Elementele, de la primul la ultimul. Testele il folosesc peste tot,
    // deci fa-l printre primele.
    vector<int> la_vector() const {
        throw NeImplementat();
    }

    // Adauga x la inceput. O(1).
    void adauga_inceput(int x) {
        throw NeImplementat();
    }

    // Adauga x la final. O(1), datorita lui `ultim`.
    void adauga_final(int x) {
        throw NeImplementat();
    }

    // Sterge primul nod. Lista goala -> out_of_range.
    void sterge_inceput() {
        throw NeImplementat();
    }

    bool contine(int x) const {
        throw NeImplementat();
    }

    // Elementul de pe pozitia k (de la 0). k invalid -> out_of_range.
    int al_k_lea(int k) const {
        throw NeImplementat();
    }

    // Sterge PRIMA aparitie a lui x. Returneaza false daca x nu exista.
    // Cazuri: x e primul nod, x e la mijloc, x e ultimul nod (atentie la `ultim`).
    bool sterge_valoare(int x) {
        throw NeImplementat();
    }

    // Inverseaza lista pe loc: fara noduri noi, fara vector auxiliar, O(n).
    // Idee: parcurgi lista si intorci fiecare sageata `next` spre nodul de
    // dinainte. De cati pointeri ai nevoie ca sa nu pierzi restul listei?
    void inverseaza() {
        throw NeImplementat();
    }

    // Elementul din mijloc, intr-o SINGURA parcurgere, fara sa folosesti dim:
    // doi cursori, unul avanseaza cate un nod, celalalt cate doua. Cand cel
    // rapid ajunge la capat, cel lent e la mijloc.
    // Pentru numar par de elemente, al doilea dintre cele doua din mijloc
    // ([1, 2, 3, 4] -> 3). Lista goala -> out_of_range.
    int mijloc() const {
        throw NeImplementat();
    }
};

// ======================= TESTE (nu modifica) =======================

void test_noua() {
    ListaSimpla l;
    VERIFICA(l.goala(), "lista noua trebuie sa fie goala");
    VERIFICA_EGAL(l.marime(), 0, "marimea listei noi");
    VERIFICA_EGAL(l.la_vector(), vector<int>(), "la_vector pe lista goala");
}

void test_adaugari() {
    ListaSimpla l;
    l.adauga_final(2); l.adauga_final(3); l.adauga_inceput(1); l.adauga_final(4); l.adauga_inceput(0);
    VERIFICA_EGAL(l.la_vector(), (vector<int>{0, 1, 2, 3, 4}), "dupa adaugari la ambele capete");
    VERIFICA_EGAL(l.marime(), 5, "marime");
    ListaSimpla m;
    m.adauga_inceput(7);  // primul nod adaugat la inceput e si ultimul
    m.adauga_final(8);
    VERIFICA_EGAL(m.la_vector(), (vector<int>{7, 8}),
                  "adauga_inceput pe lista goala trebuie sa seteze si `ultim`");
}

void test_sterge_inceput() {
    ListaSimpla l;
    l.adauga_final(1); l.adauga_final(2);
    l.sterge_inceput();
    VERIFICA_EGAL(l.la_vector(), (vector<int>{2}), "dupa un sterge_inceput");
    l.sterge_inceput();
    VERIFICA(l.goala(), "goala dupa ce am sters tot");
    l.adauga_final(5);  // daca `ultim` a ramas pe nodul sters, aici crapa
    VERIFICA_EGAL(l.la_vector(), (vector<int>{5}),
                  "adauga_final dupa golire (`ultim` trebuie pus pe nullptr cand lista se goleste)");
    l.sterge_inceput();
    VERIFICA(arunca<out_of_range>([&] { l.sterge_inceput(); }), "sterge_inceput pe lista goala trebuie sa arunce out_of_range");
}

void test_contine_al_k_lea() {
    ListaSimpla l;
    for (int x : {10, 20, 30}) l.adauga_final(x);
    VERIFICA(l.contine(20), "contine(20)");
    VERIFICA(!l.contine(25), "!contine(25)");
    VERIFICA_EGAL(l.al_k_lea(0), 10, "al_k_lea(0)");
    VERIFICA_EGAL(l.al_k_lea(2), 30, "al_k_lea(2)");
    VERIFICA(arunca<out_of_range>([&] { l.al_k_lea(3); }), "al_k_lea(marime) trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { l.al_k_lea(-1); }), "al_k_lea(-1) trebuie sa arunce out_of_range");
}

void test_sterge_valoare() {
    ListaSimpla l;
    for (int x : {1, 2, 3, 2, 4}) l.adauga_final(x);
    VERIFICA(!l.sterge_valoare(9), "sterge_valoare(9) trebuie sa returneze false");
    VERIFICA(l.sterge_valoare(2), "sterge_valoare(2) trebuie sa returneze true");
    VERIFICA_EGAL(l.la_vector(), (vector<int>{1, 3, 2, 4}), "se sterge doar PRIMA aparitie");
    l.sterge_valoare(1);
    VERIFICA_EGAL(l.la_vector(), (vector<int>{3, 2, 4}), "sterge primul nod");
    l.sterge_valoare(4);
    VERIFICA_EGAL(l.la_vector(), (vector<int>{3, 2}), "sterge ultimul nod");
    l.adauga_final(5);
    VERIFICA_EGAL(l.la_vector(), (vector<int>{3, 2, 5}),
                  "adauga_final dupa ce ai sters ultimul nod (`ultim` trebuie mutat pe nodul dinainte)");
    VERIFICA_EGAL(l.marime(), 3, "marime dupa stergeri");
    ListaSimpla m;
    m.adauga_final(1);
    m.sterge_valoare(1);
    VERIFICA(m.goala(), "sterge singurul nod");
    m.adauga_final(2);
    VERIFICA_EGAL(m.la_vector(), (vector<int>{2}), "adauga_final dupa ce ai sters singurul nod");
}

void test_inverseaza() {
    ListaSimpla goala;
    goala.inverseaza();
    VERIFICA(goala.goala(), "inversarea listei goale");
    ListaSimpla unu;
    unu.adauga_final(1);
    unu.inverseaza();
    VERIFICA_EGAL(unu.la_vector(), (vector<int>{1}), "inversarea unei liste cu un element");
    ListaSimpla l;
    for (int x : {1, 2, 3, 4, 5}) l.adauga_final(x);
    l.inverseaza();
    VERIFICA_EGAL(l.la_vector(), (vector<int>{5, 4, 3, 2, 1}), "inversare");
    l.adauga_final(0);
    l.adauga_inceput(6);
    VERIFICA_EGAL(l.la_vector(), (vector<int>{6, 5, 4, 3, 2, 1, 0}),
                  "adaugari dupa inversare (ai interschimbat prim si ultim?)");
}

void test_mijloc() {
    ListaSimpla l;
    VERIFICA(arunca<out_of_range>([&] { l.mijloc(); }), "mijloc pe lista goala trebuie sa arunce out_of_range");
    l.adauga_final(1);
    VERIFICA_EGAL(l.mijloc(), 1, "mijlocul lui [1]");
    l.adauga_final(2);
    VERIFICA_EGAL(l.mijloc(), 2, "mijlocul lui [1, 2]");
    l.adauga_final(3);
    VERIFICA_EGAL(l.mijloc(), 2, "mijlocul lui [1, 2, 3]");
    l.adauga_final(4);
    VERIFICA_EGAL(l.mijloc(), 3, "mijlocul lui [1, 2, 3, 4]");
    l.adauga_final(5);
    VERIFICA_EGAL(l.mijloc(), 3, "mijlocul lui [1, 2, 3, 4, 5]");
}

void test_aleator() {
    mt19937 rng(5);
    ListaSimpla l;
    list<int> ref;
    for (int pas = 0; pas < 20000; pas++) {
        int op = rng() % 7, x = rng() % 50;
        if (op == 0) { l.adauga_inceput(x); ref.push_front(x); }
        else if (op <= 2) { l.adauga_final(x); ref.push_back(x); }
        else if (op == 3 && !ref.empty()) { l.sterge_inceput(); ref.pop_front(); }
        else if (op == 4) {
            auto it = find(ref.begin(), ref.end(), x);
            bool exista = it != ref.end();
            if (exista) ref.erase(it);
            VERIFICA_EGAL(l.sterge_valoare(x), exista, "sterge_valoare vs std::list");
        } else if (op == 5 && rng() % 20 == 0) { l.inverseaza(); ref.reverse(); }
        else {
            VERIFICA_EGAL(l.contine(x), find(ref.begin(), ref.end(), x) != ref.end(), "contine vs std::list");
        }
        VERIFICA_EGAL(l.marime(), (int)ref.size(), "marime vs std::list");
    }
    VERIFICA_EGAL(l.la_vector(), vector<int>(ref.begin(), ref.end()), "continutul final vs std::list");
}

int main(int argc, char** argv) {
    return ruleaza_teste(argc, argv, {
        {"lista noua", test_noua},
        {"adaugari la inceput si la final", test_adaugari},
        {"sterge_inceput", test_sterge_inceput},
        {"contine si al_k_lea", test_contine_al_k_lea},
        {"sterge_valoare", test_sterge_valoare},
        {"inverseaza", test_inverseaza},
        {"mijloc", test_mijloc},
        {"operatii aleatoare vs std::list", test_aleator},
    });
}
