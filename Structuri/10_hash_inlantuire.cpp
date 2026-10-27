// 10. Tabela de dispersie cu inlantuire (separate chaining): string -> int
//
// Compilare:  g++ -std=c++17 -Wall 10_hash_inlantuire.cpp -o hash
// Rulare:     ./hash         (toate testele)
//             ./hash 3       (doar testul 3)
//
// Ce exersezi:
//   - functia de dispersie: transformi o cheie (string) intr-un indice de galeata
//   - coliziuni: cheile cu acelasi indice stau in aceeasi galeata, intr-o
//     lista simplu inlantuita
//   - rehash: cand factorul de incarcare (elemente / galeti) trece de 1,
//     dublezi numarul de galeti ca operatiile sa ramana O(1) in medie
//   - aplicatie: frecventa cuvintelor dintr-un text
//
// Ordinea recomandata: constructor, marime/goala/factor_incarcare, indice,
// pune, contine, valoare, sterge, rehash, destructor, cel_mai_frecvent.

#include "teste.hpp"
#include <unordered_map>
using namespace std;

// ============================== CLASA ==============================

class TabelaHash {
    struct Nod {
        string cheie;
        int valoare;
        Nod* next;  // urmatorul nod din ACEEASI galeata
    };
    Nod** galeti;   // vector de nr_galeti pointeri; galeti[i] = capul listei galetii i
    int nr_galeti;
    int dim;        // cate perechi (cheie, valoare) sunt in tabela

    // Indicele galetii pentru cheie, in [0, nr_galeti).
    // Idee: parcurgi caracterele si combini un "hash" acumulat cu fiecare
    // caracter (inmultesti cu un numar prim mic, apoi aduni caracterul).
    // Lucreaza pe unsigned long long, ca depasirea sa nu dea numere negative.
    // La final, restul impartirii la nr_galeti.
    int indice(const string& cheie) const {
        throw NeImplementat();
    }

    // Dubleaza nr_galeti si muta TOATE nodurile in galetile noi. Indicele
    // unei chei depinde de nr_galeti, deci se schimba! Poti refolosi nodurile
    // existente (doar le relegi), nu e nevoie sa creezi altele.
    void rehash() {
        throw NeImplementat();
    }

public:
    // Tabela goala cu `galetiInitiale` galeti, toate goale (nullptr).
    explicit TabelaHash(int galetiInitiale = 8) {
        throw NeImplementat();
    }

    // Elibereaza toate nodurile din toate galetile, apoi vectorul de galeti.
    ~TabelaHash() {
    }

    TabelaHash(const TabelaHash&) = delete;
    TabelaHash& operator=(const TabelaHash&) = delete;

    int marime() const {
        throw NeImplementat();
    }

    bool goala() const {
        throw NeImplementat();
    }

    // dim / nr_galeti (ca double).
    double factor_incarcare() const {
        throw NeImplementat();
    }

    // Adauga perechea; daca cheia exista deja, doar ii actualizezi valoarea.
    // Dupa adaugare, daca dim > nr_galeti, faci rehash().
    void pune(const string& cheie, int valoare) {
        throw NeImplementat();
    }

    bool contine(const string& cheie) const {
        throw NeImplementat();
    }

    // Valoarea cheii. Cheia nu exista -> out_of_range.
    int valoare(const string& cheie) const {
        throw NeImplementat();
    }

    // Sterge cheia; false daca nu exista. E stergere din lista simplu
    // inlantuita a galetii, cu aceleasi cazuri ca la 05.
    bool sterge(const string& cheie) {
        throw NeImplementat();
    }
};

// Aplicatie. Cuvantul care apare de cele mai multe ori in text (cuvintele
// sunt separate prin spatii). La egalitate, cel care apare primul in text.
// Text fara cuvinte -> "". Foloseste TabelaHash pentru numarare.
//   "a b a c b a" -> "a"        "x y y x" -> "x"
string cel_mai_frecvent(const string& text) {
    throw NeImplementat();
}

// ======================= TESTE (nu modifica) =======================

void test_goala() {
    TabelaHash t;
    VERIFICA(t.goala(), "tabela noua trebuie sa fie goala");
    VERIFICA_EGAL(t.marime(), 0, "marimea tabelei noi");
    VERIFICA_EGAL(t.factor_incarcare(), 0.0, "factorul de incarcare al tabelei noi");
    VERIFICA(!t.contine("ceva"), "tabela goala nu contine nimic");
}

void test_pune_valoare() {
    TabelaHash t;
    t.pune("mere", 3);
    t.pune("pere", 5);
    t.pune("", 7);  // si sirul gol e o cheie valida
    VERIFICA_EGAL(t.marime(), 3, "marime dupa 3 chei");
    VERIFICA_EGAL(t.valoare("mere"), 3, "valoare(mere)");
    VERIFICA_EGAL(t.valoare("pere"), 5, "valoare(pere)");
    VERIFICA_EGAL(t.valoare(""), 7, "valoare(\"\")");
    VERIFICA(t.contine("mere"), "contine(mere)");
    VERIFICA(!t.contine("prune"), "!contine(prune)");
    VERIFICA(arunca<out_of_range>([&] { t.valoare("prune"); }), "valoare pentru o cheie lipsa trebuie sa arunce out_of_range");
}

void test_actualizare() {
    TabelaHash t;
    t.pune("a", 1);
    t.pune("a", 2);
    VERIFICA_EGAL(t.marime(), 1, "a doua oara aceeasi cheie nu se adauga, se actualizeaza");
    VERIFICA_EGAL(t.valoare("a"), 2, "valoarea actualizata");
}

void test_sterge() {
    TabelaHash t;
    t.pune("unu", 1); t.pune("doi", 2); t.pune("trei", 3);
    VERIFICA(t.sterge("doi"), "sterge(doi) trebuie sa returneze true");
    VERIFICA(!t.contine("doi"), "doi nu mai trebuie sa existe");
    VERIFICA(!t.sterge("doi"), "sterge(doi) a doua oara trebuie sa returneze false");
    VERIFICA_EGAL(t.marime(), 2, "marime dupa stergere");
    VERIFICA_EGAL(t.valoare("unu"), 1, "celelalte chei raman");
    VERIFICA_EGAL(t.valoare("trei"), 3, "celelalte chei raman");
}

void test_coliziuni() {
    TabelaHash t(1);  // o singura galeata: la inceput totul se ciocneste
    for (int i = 0; i < 50; i++) t.pune("k" + to_string(i), i);
    for (int i = 0; i < 50; i += 2) VERIFICA(t.sterge("k" + to_string(i)), "sterge cheie para");
    for (int i = 0; i < 50; i++) {
        string k = "k" + to_string(i);
        VERIFICA_EGAL(t.contine(k), i % 2 == 1, "contine dupa stergeri");
        if (i % 2) VERIFICA_EGAL(t.valoare(k), i, "valoare dupa stergeri");
    }
}

void test_rehash() {
    TabelaHash t(2);
    for (int i = 0; i < 10000; i++) {
        t.pune("cheia_" + to_string(i), i * 3);
        VERIFICA(t.factor_incarcare() <= 1.0, "factorul de incarcare a trecut de 1: rehash nu s-a facut");
    }
    VERIFICA_EGAL(t.marime(), 10000, "marime dupa 10000 de chei");
    for (int i = 0; i < 10000; i++)
        VERIFICA_EGAL(t.valoare("cheia_" + to_string(i)), i * 3, "valoare dupa rehash (ai recalculat indicii?)");
}

void test_aleator() {
    mt19937 rng(23);
    TabelaHash t(4);
    unordered_map<string, int> ref;
    for (int pas = 0; pas < 100000; pas++) {
        string k = "c" + to_string(rng() % 3000);
        int op = rng() % 4, v = rng() % 1000;
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

void test_frecvent() {
    VERIFICA_EGAL(cel_mai_frecvent("a b a c b a"), string("a"), "\"a b a c b a\"");
    VERIFICA_EGAL(cel_mai_frecvent("x y y x"), string("x"), "la egalitate, primul aparut in text");
    VERIFICA_EGAL(cel_mai_frecvent("unu"), string("unu"), "un singur cuvant");
    VERIFICA_EGAL(cel_mai_frecvent(""), string(""), "text gol");
    VERIFICA_EGAL(cel_mai_frecvent("   "), string(""), "doar spatii");
    VERIFICA_EGAL(cel_mai_frecvent("  ana  are mere ana are pere are "), string("are"), "spatii multiple");
}

int main(int argc, char** argv) {
    return ruleaza_teste(argc, argv, {
        {"tabela goala", test_goala},
        {"pune si valoare", test_pune_valoare},
        {"actualizarea unei chei", test_actualizare},
        {"sterge", test_sterge},
        {"coliziuni intr-o singura galeata", test_coliziuni},
        {"rehash", test_rehash},
        {"operatii aleatoare vs std::unordered_map", test_aleator},
        {"aplicatie: cel mai frecvent cuvant", test_frecvent},
    });
}
