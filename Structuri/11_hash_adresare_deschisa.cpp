// 11. Tabela de dispersie cu adresare deschisa (linear probing): int -> int
//
// Compilare:  g++ -std=c++17 -Wall 11_hash_adresare_deschisa.cpp -o hash2
// Rulare:     ./hash2        (toate testele)
//             ./hash2 3      (doar testul 3)
//
// Ce exersezi:
//   - fara liste: toate perechile stau direct intr-un vector; la coliziune
//     incerci locul urmator (i, i+1, i+2, ... si o iei de la 0 la capat)
//   - stergerea cu "piatra funerara" (STERS): de ce nu ai voie sa marchezi
//     locul pur si simplu LIBER? (gandeste-te la o cheie care, la inserare,
//     a trebuit sa sara peste locul pe care tocmai l-ai golit)
//   - rehash cand tabela se umple pe jumatate (altfel cautarile devin lungi,
//     iar daca se umple de tot, intri in bucla infinita)
//
// Ordinea recomandata: constructor, marime/goala, indice, pune, contine,
// valoare, sterge, rehash, destructor.

#include "teste.hpp"
#include <unordered_map>
using namespace std;

// ============================== CLASA ==============================

class TabelaDeschisa {
    enum Stare { LIBER, OCUPAT, STERS };

    int* chei;      // chei[i] si valori[i] au sens doar daca stare[i] == OCUPAT
    int* valori;
    Stare* stare;
    int cap;        // cate locuri are fiecare dintre cei trei vectori
    int dim;        // cate locuri sunt OCUPAT
    int sterse;     // cate locuri sunt STERS

    // Locul de pornire pentru cheie, in [0, cap). Atentie: in C++ restul unui
    // numar negativ e negativ, de exemplu -7 % 8 == -7.
    int indice(int cheie) const {
        throw NeImplementat();
    }

    // Aloca vectori noi de 2 * cap si reinsereaza DOAR cheile OCUPAT (pietrele
    // funerare dispar). Apeleaz-o din pune() cand (dim + sterse) * 2 > cap.
    void rehash() {
        throw NeImplementat();
    }

public:
    // Tabela goala: toate locurile LIBER.
    explicit TabelaDeschisa(int capInitiala = 8) {
        throw NeImplementat();
    }

    // Elibereaza cei trei vectori (fara throw).
    ~TabelaDeschisa() {
    }

    TabelaDeschisa(const TabelaDeschisa&) = delete;
    TabelaDeschisa& operator=(const TabelaDeschisa&) = delete;

    int marime() const {
        throw NeImplementat();
    }

    bool goala() const {
        throw NeImplementat();
    }

    // Adauga perechea, sau actualizeaza valoarea daca cheia exista deja.
    // Atentie: cheia poate exista MAI DEPARTE, dupa o piatra funerara; nu o
    // pune in primul STERS gasit inainte sa verifici asta.
    void pune(int cheie, int valoare) {
        throw NeImplementat();
    }

    // Cauti de la indice(cheie) inainte. Te opresti la un loc LIBER (cheia
    // sigur nu e in tabela), dar NU la unul STERS.
    bool contine(int cheie) const {
        throw NeImplementat();
    }

    // Cheia nu exista -> out_of_range.
    int valoare(int cheie) const {
        throw NeImplementat();
    }

    // Marcheaza locul STERS. false daca cheia nu exista.
    bool sterge(int cheie) {
        throw NeImplementat();
    }
};

// ======================= TESTE (nu modifica) =======================

void test_goala() {
    TabelaDeschisa t;
    VERIFICA(t.goala(), "tabela noua trebuie sa fie goala");
    VERIFICA_EGAL(t.marime(), 0, "marimea tabelei noi");
    VERIFICA(!t.contine(5), "tabela goala nu contine nimic");
    VERIFICA(arunca<out_of_range>([&] { t.valoare(5); }), "valoare pe tabela goala trebuie sa arunce out_of_range");
}

void test_pune_valoare() {
    TabelaDeschisa t;
    t.pune(1, 10); t.pune(2, 20); t.pune(3, 30);
    VERIFICA_EGAL(t.marime(), 3, "marime dupa 3 chei");
    VERIFICA_EGAL(t.valoare(2), 20, "valoare(2)");
    t.pune(2, 22);
    VERIFICA_EGAL(t.valoare(2), 22, "valoarea actualizata");
    VERIFICA_EGAL(t.marime(), 3, "actualizarea nu schimba marimea");
}

void test_negative() {
    TabelaDeschisa t;
    t.pune(-1, 1); t.pune(-9, 9); t.pune(-1000000, 7); t.pune(0, 0);
    VERIFICA_EGAL(t.valoare(-1), 1, "valoare(-1)");
    VERIFICA_EGAL(t.valoare(-9), 9, "valoare(-9)");
    VERIFICA_EGAL(t.valoare(-1000000), 7, "valoare(-1000000)");
    VERIFICA_EGAL(t.valoare(0), 0, "valoare(0)");
}

void test_piatra_funerara() {
    TabelaDeschisa t(8);
    // Cu indice(k) = k % 8, cheile 1, 9 si 17 vor toate locul 1: 9 ajunge pe
    // 2, iar 17 pe 3. Testul trebuie sa treaca oricum ti-ai alege indicele.
    t.pune(1, 100); t.pune(9, 900); t.pune(17, 1700);
    VERIFICA(t.sterge(9), "sterge(9)");
    VERIFICA(!t.contine(9), "9 a fost sters");
    VERIFICA(t.contine(17), "17 nu mai e gasit dupa ce ai sters 9 (te opresti la locul sters?)");
    VERIFICA_EGAL(t.valoare(17), 1700, "valoare(17) dupa stergerea lui 9");
    t.pune(17, 1701);
    VERIFICA_EGAL(t.marime(), 2, "pune(17) a adaugat o copie a lui 17 in loc sa-l actualizeze");
    t.sterge(17);
    VERIFICA(!t.contine(17), "17 inca exista dupa sterge: ai avut doua copii ale lui");
    t.pune(9, 901);
    VERIFICA_EGAL(t.valoare(9), 901, "pune dupa stergere");
    VERIFICA_EGAL(t.marime(), 2, "marime");
}

void test_rehash() {
    TabelaDeschisa t(2);
    for (int i = 0; i < 20000; i++) t.pune(i * 7, i);
    VERIFICA_EGAL(t.marime(), 20000, "marime dupa 20000 de chei");
    for (int i = 0; i < 20000; i++)
        VERIFICA_EGAL(t.valoare(i * 7), i, "valoare dupa rehash");
}

void test_multe_stergeri() {
    // Daca nu numeri si locurile STERS la decizia de rehash, tabela se umple
    // de pietre funerare si cautarea unei chei lipsa nu se mai termina.
    TabelaDeschisa t(16);
    for (int runda = 0; runda < 2000; runda++) {
        t.pune(runda, runda);
        VERIFICA(t.sterge(runda), "sterge cheia tocmai pusa");
        VERIFICA(!t.contine(-1), "cautarea unei chei lipsa");
    }
    VERIFICA(t.goala(), "goala dupa ce am sters tot");
}

void test_aleator() {
    mt19937 rng(29);
    TabelaDeschisa t(4);
    unordered_map<int, int> ref;
    for (int pas = 0; pas < 200000; pas++) {
        int k = (int)(rng() % 1001) - 500, op = rng() % 4, v = rng() % 1000;
        if (op <= 1) { t.pune(k, v); ref[k] = v; }
        else if (op == 2) { VERIFICA_EGAL(t.sterge(k), ref.erase(k) == 1, "sterge vs std::unordered_map"); }
        else {
            bool exista = ref.count(k) == 1;
            VERIFICA_EGAL(t.contine(k), exista, "contine vs std::unordered_map");
            if (exista) VERIFICA_EGAL(t.valoare(k), ref[k], "valoare vs std::unordered_map");
        }
        VERIFICA_EGAL(t.marime(), (int)ref.size(), "marime vs std::unordered_map");
    }
}

int main(int argc, char** argv) {
    return ruleaza_teste(argc, argv, {
        {"tabela goala", test_goala},
        {"pune, valoare, actualizare", test_pune_valoare},
        {"chei negative", test_negative},
        {"stergere cu piatra funerara", test_piatra_funerara},
        {"rehash", test_rehash},
        {"multe stergeri (rehash numara si STERS)", test_multe_stergeri},
        {"operatii aleatoare vs std::unordered_map", test_aleator},
    });
}
