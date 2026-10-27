// 12. Graf cu liste de adiacenta: BFS, DFS, componente, drum minim, sortare topologica
//
// Compilare:  g++ -std=c++17 -Wall 12_graf.cpp -o graf
// Rulare:     ./graf         (toate testele)
//             ./graf 3       (doar testul 3)
//
// Ce exersezi:
//   - reprezentarea: pentru fiecare nod, lista vecinilor (memorie O(n + m))
//   - BFS (latime): cu o coada, viziteaza nodurile in ordinea distantei
//   - DFS (adancime): recursiv, merge cat de departe poate, apoi se intoarce
//   - aplicatii: componente conexe, drumul cu cele mai putine muchii,
//     sortarea topologica a unui graf orientat fara cicluri
//   - aici ai voie la std::vector si std::queue: accentul e pe algoritmi
//
// Ordinea recomandata: constructor, noduri, adauga_muchie, bfs, distante,
// dfs, numar_componente, drum_minim, sortare_topologica.

#include "teste.hpp"
#include <queue>
#include <set>
using namespace std;

// ============================== CLASA ==============================

class Graf {
    int n;           // nodurile sunt 0, 1, ..., n-1
    bool orientat;   // orientat: muchia u -> v merge doar intr-un sens
    vector<vector<int>> vecini;  // vecini[u] = nodurile in care ajungi direct din u,
                                 // in ordinea in care au fost adaugate muchiile

    // Aici adaugi functia ta recursiva pentru DFS, de exemplu
    //   void dfs(int u, vector<bool>& vizitat, vector<int>& ordine) const;

public:
    // Graf cu n noduri si fara muchii.
    Graf(int n, bool orientat) {
        throw NeImplementat();
    }

    int noduri() const {
        throw NeImplementat();
    }

    // Neorientat: v intra la vecinii lui u SI u la vecinii lui v.
    // Orientat: doar v la vecinii lui u.
    // u sau v in afara [0, n) -> out_of_range.
    void adauga_muchie(int u, int v) {
        throw NeImplementat();
    }

    // Ordinea in care BFS viziteaza nodurile pornind din start (doar cele la
    // care se poate ajunge). Vecinii se iau in ordinea din lista.
    // start invalid -> out_of_range.
    vector<int> bfs(int start) const {
        throw NeImplementat();
    }

    // d[v] = numarul minim de muchii de la start la v, sau -1 daca nu se
    // poate ajunge. Tot BFS, dar tii minte distanta in loc de ordine.
    vector<int> distante(int start) const {
        throw NeImplementat();
    }

    // Ordinea in care DFS recursiv viziteaza nodurile pornind din start:
    // vizitezi nodul, apoi, pentru fiecare vecin nevizitat IN ORDINE, apelezi
    // recursiv. start invalid -> out_of_range.
    vector<int> dfs(int start) const {
        throw NeImplementat();
    }

    // Numarul de componente conexe (pentru graf neorientat): cate DFS-uri
    // (sau BFS-uri) trebuie sa pornesti ca sa vizitezi toate nodurile.
    int numar_componente() const {
        throw NeImplementat();
    }

    // Un drum cu numar minim de muchii de la s la t, ca lista de noduri
    // (incepe cu s, se termina cu t). Gol daca nu exista drum.
    // Idee: BFS din s care tine minte, pentru fiecare nod, din ce nod ai
    // ajuns in el (parintele); apoi refaci drumul de la t inapoi spre s.
    vector<int> drum_minim(int s, int t) const {
        throw NeImplementat();
    }

    // Pentru graf orientat: o ordine a tuturor nodurilor in care, pentru
    // fiecare muchie u -> v, u apare inaintea lui v. Gol daca graful are ciclu.
    // Idee (Kahn): numeri cate muchii intra in fiecare nod; pui intr-o coada
    // nodurile in care nu intra nimic; scoti pe rand cate unul si "stergi"
    // muchiile care pleaca din el.
    vector<int> sortare_topologica() const {
        throw NeImplementat();
    }
};

// ======================= TESTE (nu modifica) =======================

// Graful neorientat din teste:
//
//     0 --- 1          5 --- 6
//     |     |
//     2 --- 3 --- 4
//
// muchii adaugate in ordinea: 0-1, 0-2, 1-3, 2-3, 3-4, 5-6
static Graf exemplu() {
    Graf g(7, false);
    g.adauga_muchie(0, 1); g.adauga_muchie(0, 2); g.adauga_muchie(1, 3);
    g.adauga_muchie(2, 3); g.adauga_muchie(3, 4); g.adauga_muchie(5, 6);
    return g;
}

void test_constructie() {
    Graf g(5, false);
    VERIFICA_EGAL(g.noduri(), 5, "numarul de noduri");
    g.adauga_muchie(0, 4);
    VERIFICA(arunca<out_of_range>([&] { g.adauga_muchie(0, 5); }), "muchie spre nodul 5 (nu exista) trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { g.adauga_muchie(-1, 2); }), "muchie din nodul -1 trebuie sa arunce out_of_range");
}

void test_bfs() {
    Graf g = exemplu();
    VERIFICA_EGAL(g.bfs(0), (vector<int>{0, 1, 2, 3, 4}), "bfs(0)");
    VERIFICA_EGAL(g.bfs(4), (vector<int>{4, 3, 1, 2, 0}), "bfs(4)");
    VERIFICA_EGAL(g.bfs(6), (vector<int>{6, 5}), "bfs(6): alta componenta");
    VERIFICA(arunca<out_of_range>([&] { g.bfs(7); }), "bfs(7) trebuie sa arunce out_of_range");
}

void test_distante() {
    Graf g = exemplu();
    VERIFICA_EGAL(g.distante(0), (vector<int>{0, 1, 1, 2, 3, -1, -1}), "distante(0)");
    VERIFICA_EGAL(g.distante(5), (vector<int>{-1, -1, -1, -1, -1, 0, 1}), "distante(5)");
}

void test_dfs() {
    Graf g = exemplu();
    VERIFICA_EGAL(g.dfs(0), (vector<int>{0, 1, 3, 2, 4}), "dfs(0)");
    VERIFICA_EGAL(g.dfs(2), (vector<int>{2, 0, 1, 3, 4}), "dfs(2)");
    VERIFICA(arunca<out_of_range>([&] { g.dfs(-1); }), "dfs(-1) trebuie sa arunce out_of_range");
}

void test_orientat() {
    Graf g(4, true);
    g.adauga_muchie(0, 1); g.adauga_muchie(1, 2); g.adauga_muchie(3, 0);
    VERIFICA_EGAL(g.bfs(0), (vector<int>{0, 1, 2}), "bfs(0) in graf orientat: 3 nu se poate atinge");
    VERIFICA_EGAL(g.bfs(2), (vector<int>{2}), "bfs(2) in graf orientat: din 2 nu pleaca nimic");
    VERIFICA_EGAL(g.distante(3), (vector<int>{1, 2, 3, 0}), "distante(3) in graf orientat");
}

void test_componente() {
    VERIFICA_EGAL(exemplu().numar_componente(), 2, "exemplul are 2 componente");
    VERIFICA_EGAL(Graf(4, false).numar_componente(), 4, "4 noduri fara muchii: 4 componente");
    Graf g(6, false);
    g.adauga_muchie(0, 1); g.adauga_muchie(2, 3); g.adauga_muchie(4, 5); g.adauga_muchie(1, 2);
    VERIFICA_EGAL(g.numar_componente(), 2, "{0, 1, 2, 3} si {4, 5}");
}

// Verifica ca d e un drum valid (fiecare pas e o muchie) de la s la t.
static void verifica_drum(const vector<pair<int, int>>& muchii, bool orientat, const vector<int>& d,
                          int s, int t, int lungime, const string& context) {
    set<pair<int, int>> ex(muchii.begin(), muchii.end());
    if (!orientat) for (auto [u, v] : muchii) ex.insert({v, u});
    VERIFICA_EGAL((int)d.size(), lungime + 1, context + ": numar de noduri pe drum");
    VERIFICA_EGAL(d.front(), s, context + ": drumul trebuie sa inceapa cu s");
    VERIFICA_EGAL(d.back(), t, context + ": drumul trebuie sa se termine cu t");
    for (size_t i = 0; i + 1 < d.size(); i++)
        VERIFICA(ex.count({d[i], d[i + 1]}), context + ": doua noduri consecutive din drum nu sunt legate printr-o muchie");
}

void test_drum_minim() {
    Graf g = exemplu();
    vector<pair<int, int>> m = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {5, 6}};
    verifica_drum(m, false, g.drum_minim(0, 4), 0, 4, 3, "drum_minim(0, 4)");
    verifica_drum(m, false, g.drum_minim(4, 0), 4, 0, 3, "drum_minim(4, 0)");
    verifica_drum(m, false, g.drum_minim(2, 2), 2, 2, 0, "drum_minim(2, 2)");
    VERIFICA_EGAL(g.drum_minim(0, 6), vector<int>(), "drum_minim(0, 6): nu exista drum");
}

static void verifica_topologic(const vector<int>& ordine, int n, const vector<pair<int, int>>& muchii) {
    VERIFICA_EGAL((int)ordine.size(), n, "sortarea topologica trebuie sa contina toate nodurile");
    vector<int> poz(n, -1);
    for (int i = 0; i < n; i++) {
        VERIFICA(ordine[i] >= 0 && ordine[i] < n && poz[ordine[i]] == -1, "un nod lipseste sau apare de doua ori");
        poz[ordine[i]] = i;
    }
    for (auto [u, v] : muchii)
        VERIFICA(poz[u] < poz[v], "pentru muchia " + to_string(u) + " -> " + to_string(v) + ", u trebuie sa fie inaintea lui v");
}

void test_topologic() {
    vector<pair<int, int>> m = {{5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1}};
    Graf g(6, true);
    for (auto [u, v] : m) g.adauga_muchie(u, v);
    verifica_topologic(g.sortare_topologica(), 6, m);
    Graf ciclu(3, true);
    ciclu.adauga_muchie(0, 1); ciclu.adauga_muchie(1, 2); ciclu.adauga_muchie(2, 0);
    VERIFICA_EGAL(ciclu.sortare_topologica(), vector<int>(), "graf cu ciclu: rezultat gol");
    Graf coada_ciclu(5, true);  // 4 -> 3 -> 0 -> 1 -> 2 -> 1: ciclul 1 <-> 2, cu noduri inainte
    coada_ciclu.adauga_muchie(4, 3); coada_ciclu.adauga_muchie(3, 0); coada_ciclu.adauga_muchie(0, 1);
    coada_ciclu.adauga_muchie(1, 2); coada_ciclu.adauga_muchie(2, 1);
    VERIFICA_EGAL(coada_ciclu.sortare_topologica(), vector<int>(),
                  "graf cu ciclu dupa cateva noduri: rezultat gol (verifici ca ai pus TOATE nodurile?)");
}

void test_mare() {
    // Un lant 0 - 1 - 2 - ... - 9999 plus muchii in plus, aleatoare.
    const int n = 10000;
    mt19937 rng(31);
    Graf g(n, false);
    for (int i = 0; i + 1 < n; i++) g.adauga_muchie(i, i + 1);
    for (int i = 0; i < 20000; i++) g.adauga_muchie(rng() % n, rng() % n);
    VERIFICA_EGAL((int)g.bfs(0).size(), n, "bfs viziteaza toate nodurile");
    VERIFICA_EGAL((int)g.dfs(0).size(), n, "dfs viziteaza toate nodurile");
    VERIFICA_EGAL(g.numar_componente(), 1, "graful e conex");
    // DAG mare: muchii doar de la nod mic la nod mare.
    Graf dag(n, true);
    vector<pair<int, int>> m;
    for (int i = 0; i < 50000; i++) {
        int u = rng() % n, v = rng() % n;
        if (u == v) continue;
        if (u > v) swap(u, v);
        dag.adauga_muchie(u, v); m.push_back({u, v});
    }
    verifica_topologic(dag.sortare_topologica(), n, m);
}

int main(int argc, char** argv) {
    return ruleaza_teste(argc, argv, {
        {"constructie si muchii invalide", test_constructie},
        {"BFS", test_bfs},
        {"distante (BFS)", test_distante},
        {"DFS", test_dfs},
        {"graf orientat", test_orientat},
        {"componente conexe", test_componente},
        {"drum minim", test_drum_minim},
        {"sortare topologica", test_topologic},
        {"graf mare (10000 de noduri)", test_mare},
    });
}
