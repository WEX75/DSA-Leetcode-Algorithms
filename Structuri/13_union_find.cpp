// 13. Union-Find (DSU, paduri de multimi disjuncte) + Kruskal
//
// Compilare:  g++ -std=c++17 -Wall 13_union_find.cpp -o dsu
// Rulare:     ./dsu          (toate testele)
//             ./dsu 3        (doar testul 3)
//
// Ce exersezi:
//   - fiecare multime e un arbore; radacina lui e "reprezentantul" multimii
//   - doua optimizari care fac operatiile aproape O(1):
//       * compresia drumului: la gaseste(x), tot drumul spre radacina se
//         leaga direct de radacina
//       * unirea dupa marime: arborele mai mic se agata sub cel mai mare
//   - aplicatie: algoritmul lui Kruskal (arborele partial de cost minim)
//
// Ordinea recomandata: constructor, gaseste, uneste, impreuna,
// numar_multimi, marime_multime, cost_apm.

#include "teste.hpp"
using namespace std;

// ============================== CLASA ==============================

class DSU {
    vector<int> parinte;  // parinte[x] == x  <=>  x e radacina (reprezentantul) multimii lui
    vector<int> marime;   // marime[r] = cate elemente are multimea cu radacina r
                          // (are sens doar pentru radacini)
    int multimi;          // cate multimi sunt acum

    // Aici poti pune functii ajutatoare, daca ai nevoie.

public:
    // n multimi cu cate un element: {0}, {1}, ..., {n-1}.
    explicit DSU(int n) {
        throw NeImplementat();
    }

    // Reprezentantul multimii lui x, cu compresia drumului.
    // x in afara [0, n) -> out_of_range.
    int gaseste(int x) {
        throw NeImplementat();
    }

    // Uneste multimile lui a si b (radacina celei mai mici se agata sub
    // radacina celei mai mari). false daca erau deja in aceeasi multime.
    bool uneste(int a, int b) {
        throw NeImplementat();
    }

    // Sunt a si b in aceeasi multime?
    bool impreuna(int a, int b) {
        throw NeImplementat();
    }

    int numar_multimi() const {
        throw NeImplementat();
    }

    // Cate elemente are multimea lui x.
    int marime_multime(int x) {
        throw NeImplementat();
    }
};

struct Muchie {
    int u, v;
    int cost;
};

// Kruskal: costul total al arborelui partial de cost minim (APM) al grafului
// neorientat cu nodurile 0..n-1. Sortezi muchiile crescator dupa cost si iei
// fiecare muchie care leaga doua componente diferite (DSU-ul iti spune asta).
// Graf neconex (nu exista APM) -> -1.
long long cost_apm(int n, vector<Muchie> muchii) {
    throw NeImplementat();
}

// ======================= TESTE (nu modifica) =======================

void test_nou() {
    DSU d(5);
    VERIFICA_EGAL(d.numar_multimi(), 5, "la inceput fiecare element e singur");
    for (int x = 0; x < 5; x++) {
        VERIFICA_EGAL(d.gaseste(x), x, "la inceput fiecare element e propriul reprezentant");
        VERIFICA_EGAL(d.marime_multime(x), 1, "la inceput fiecare multime are un element");
    }
    VERIFICA(!d.impreuna(0, 1), "0 si 1 nu sunt impreuna la inceput");
    VERIFICA(arunca<out_of_range>([&] { d.gaseste(5); }), "gaseste(5) trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { d.gaseste(-1); }), "gaseste(-1) trebuie sa arunce out_of_range");
}

void test_uneste() {
    DSU d(6);
    VERIFICA(d.uneste(0, 1), "uneste(0, 1)");
    VERIFICA(d.uneste(2, 3), "uneste(2, 3)");
    VERIFICA(d.impreuna(0, 1), "0 si 1 sunt impreuna");
    VERIFICA(!d.impreuna(1, 2), "1 si 2 nu sunt impreuna");
    VERIFICA_EGAL(d.numar_multimi(), 4, "numar_multimi dupa doua uniri");
    VERIFICA(d.uneste(1, 3), "uneste(1, 3) leaga {0, 1} cu {2, 3}");
    VERIFICA(d.impreuna(0, 2), "0 si 2 sunt acum impreuna");
    VERIFICA_EGAL(d.marime_multime(3), 4, "marimea multimii {0, 1, 2, 3}");
    VERIFICA_EGAL(d.marime_multime(5), 1, "5 e tot singur");
    VERIFICA(!d.uneste(0, 3), "uneste(0, 3) cand sunt deja impreuna trebuie sa returneze false");
    VERIFICA_EGAL(d.numar_multimi(), 3, "o unire inutila nu schimba numarul de multimi");
    VERIFICA_EGAL(d.gaseste(0), d.gaseste(2), "acelasi reprezentant pentru 0 si 2");
}

void test_aleator() {
    // Comparatie cu o varianta naiva: eticheta[x] = numarul multimii lui x.
    mt19937 rng(37);
    const int n = 300;
    DSU d(n);
    vector<int> eticheta(n);
    for (int i = 0; i < n; i++) eticheta[i] = i;
    int multimi = n;
    for (int pas = 0; pas < 5000; pas++) {
        int a = rng() % n, b = rng() % n;
        if (rng() % 2) {
            bool diferite = eticheta[a] != eticheta[b];
            if (diferite) {
                int vechi = eticheta[b];
                for (int& e : eticheta) if (e == vechi) e = eticheta[a];
                multimi--;
            }
            VERIFICA_EGAL(d.uneste(a, b), diferite, "uneste vs varianta naiva");
        } else {
            VERIFICA_EGAL(d.impreuna(a, b), eticheta[a] == eticheta[b], "impreuna vs varianta naiva");
            int cate = count(eticheta.begin(), eticheta.end(), eticheta[a]);
            VERIFICA_EGAL(d.marime_multime(a), cate, "marime_multime vs varianta naiva");
        }
        VERIFICA_EGAL(d.numar_multimi(), multimi, "numar_multimi vs varianta naiva");
    }
}

void test_viteza() {
    // Fara optimizari (compresie / unire dupa marime), testul asta dureaza foarte mult.
    const int n = 1000000;
    DSU d(n);
    for (int i = 0; i + 1 < n; i++) d.uneste(i, i + 1);
    VERIFICA_EGAL(d.numar_multimi(), 1, "un singur lant");
    for (int rep = 0; rep < 3; rep++)
        for (int i = 0; i < n; i++)
            if (d.gaseste(i) != d.gaseste(0)) throw Picat("toate elementele trebuie sa aiba acelasi reprezentant");
    VERIFICA_EGAL(d.marime_multime(n / 2), n, "marimea multimii finale");
}

// Prim naiv, O(n^2), ca referinta pentru teste.
static long long prim_naiv(int n, const vector<Muchie>& muchii) {
    const long long INF = 1e18;
    vector<vector<long long>> c(n, vector<long long>(n, INF));
    for (auto& m : muchii) c[m.u][m.v] = c[m.v][m.u] = min(c[m.u][m.v], (long long)m.cost);
    vector<long long> best(n, INF);
    vector<bool> in(n, false);
    best[0] = 0;
    long long total = 0;
    for (int it = 0; it < n; it++) {
        int u = -1;
        for (int v = 0; v < n; v++) if (!in[v] && (u == -1 || best[v] < best[u])) u = v;
        if (best[u] == INF) return -1;
        in[u] = true; total += best[u];
        for (int v = 0; v < n; v++) if (!in[v] && c[u][v] < best[v]) best[v] = c[u][v];
    }
    return total;
}

void test_kruskal() {
    //   0 --1-- 1
    //   |     / |
    //   4   2   5
    //   | /     |
    //   2 --3-- 3
    vector<Muchie> m = {{0, 1, 1}, {0, 2, 4}, {1, 2, 2}, {1, 3, 5}, {2, 3, 3}};
    VERIFICA_EGAL(cost_apm(4, m), 6LL, "APM-ul exemplului: 1 + 2 + 3");
    VERIFICA_EGAL(cost_apm(1, {}), 0LL, "un singur nod: cost 0");
    VERIFICA_EGAL(cost_apm(3, {{0, 1, 5}}), -1LL, "graf neconex: -1");
    mt19937 rng(41);
    for (int t = 0; t < 200; t++) {
        int n = 1 + rng() % 30, nm = rng() % 80;
        vector<Muchie> muchii;
        for (int i = 0; i < nm; i++) muchii.push_back({(int)(rng() % n), (int)(rng() % n), (int)(rng() % 100)});
        VERIFICA_EGAL(cost_apm(n, muchii), prim_naiv(n, muchii), "cost_apm vs algoritmul lui Prim");
    }
}

int main(int argc, char** argv) {
    return ruleaza_teste(argc, argv, {
        {"DSU nou", test_nou},
        {"uneste si impreuna", test_uneste},
        {"operatii aleatoare vs varianta naiva", test_aleator},
        {"viteza (1000000 de elemente)", test_viteza},
        {"Kruskal", test_kruskal},
    });
}
