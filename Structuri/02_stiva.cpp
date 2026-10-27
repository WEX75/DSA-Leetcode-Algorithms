// 02. Stiva (LIFO: ultimul intrat, primul iesit), pe lista inlantuita
//
// Compilare:  g++ -std=c++17 -Wall 02_stiva.cpp -o stiva
// Rulare:     ./stiva        (toate testele)
//             ./stiva 3      (doar testul 3)
//
// Ce exersezi:
//   - stiva ca lista simplu inlantuita in care lucrezi DOAR la capul listei
//     (de ce la cap si nu la coada? gandeste-te ce costa pop la coada)
//   - doua aplicatii clasice de examen: paranteze echilibrate si
//     evaluarea unei expresii postfixate
//
// Ordinea recomandata: constructor, goala/marime, push, top, pop,
// destructor, paranteze_echilibrate, evalueaza_postfix.

#include "teste.hpp"
#include <stack>
using namespace std;

// ============================== CLASA ==============================

class Stiva {
    struct Nod {
        int info;
        Nod* next;  // nodul de sub el in stiva
    };
    Nod* varf;  // nodul din varf (ultimul pus); nullptr daca stiva e goala
    int dim;

public:
    // Stiva goala.
    Stiva() {
        throw NeImplementat();
    }

    // Elibereaza toate nodurile. (Fara throw: destructorul nu are voie sa arunce.)
    ~Stiva() {
    }

    // Interzicem copierea (altfel doua stive ar sterge aceleasi noduri).
    Stiva(const Stiva&) = delete;
    Stiva& operator=(const Stiva&) = delete;

    bool goala() const {
        throw NeImplementat();
    }

    int marime() const {
        throw NeImplementat();
    }

    // Pune x in varf. O(1).
    void push(int x) {
        throw NeImplementat();
    }

    // Scoate varful (si elibereaza nodul). Stiva goala -> out_of_range.
    void pop() {
        throw NeImplementat();
    }

    // Valoarea din varf, fara s-o scoata. Stiva goala -> out_of_range.
    int top() const {
        throw NeImplementat();
    }
};

// Aplicatia 1. Verifica daca parantezele ( ) [ ] { } din s sunt echilibrate.
// Celelalte caractere se ignora.
//   "{[()]}" -> true     "([)]" -> false     "((" -> false     "" -> true
// Foloseste clasa Stiva de mai sus (caracterele se pot pune in stiva ca int).
bool paranteze_echilibrate(const string& s) {
    throw NeImplementat();
}

// Aplicatia 2. Evalueaza o expresie postfixata (forma poloneza inversa).
// Numerele sunt intregi nenegative (pot avea mai multe cifre); numerele si
// operatorii + - * / sunt separati prin cate un spatiu. Impartirea e intreaga.
//   "3 4 + 2 *"  ->  (3 + 4) * 2 = 14
// Expresie invalida (lipsesc operanzi sau raman numere in plus)
// -> throw invalid_argument("...").
int evalueaza_postfix(const string& expr) {
    throw NeImplementat();
}

// ======================= TESTE (nu modifica) =======================

void test_noua() {
    Stiva s;
    VERIFICA(s.goala(), "stiva noua trebuie sa fie goala");
    VERIFICA_EGAL(s.marime(), 0, "marimea stivei noi");
}

void test_push_top() {
    Stiva s;
    s.push(10);
    VERIFICA_EGAL(s.top(), 10, "top dupa push(10)");
    s.push(20);
    VERIFICA_EGAL(s.top(), 20, "top dupa push(20)");
    VERIFICA_EGAL(s.marime(), 2, "marime dupa 2 push");
    VERIFICA(!s.goala(), "stiva cu elemente nu e goala");
}

void test_lifo() {
    Stiva s;
    s.push(1); s.push(2); s.push(3);
    VERIFICA_EGAL(s.top(), 3, "primul care iese e ultimul intrat");
    s.pop();
    VERIFICA_EGAL(s.top(), 2, "top dupa un pop");
    s.pop();
    VERIFICA_EGAL(s.top(), 1, "top dupa doua pop-uri");
    s.pop();
    VERIFICA(s.goala(), "goala dupa ce am scos tot");
    s.push(7);
    VERIFICA_EGAL(s.top(), 7, "push dupa ce s-a golit");
}

void test_erori() {
    Stiva s;
    VERIFICA(arunca<out_of_range>([&] { s.pop(); }), "pop pe stiva goala trebuie sa arunce out_of_range");
    VERIFICA(arunca<out_of_range>([&] { s.top(); }), "top pe stiva goala trebuie sa arunce out_of_range");
    s.push(1); s.pop();
    VERIFICA(arunca<out_of_range>([&] { s.top(); }), "top dupa ce s-a golit trebuie sa arunce out_of_range");
}

void test_aleator() {
    mt19937 rng(3);
    Stiva s;
    stack<int> ref;
    for (int pas = 0; pas < 200000; pas++) {
        if (ref.empty() || rng() % 3 != 0) {
            int x = rng() % 1000;
            s.push(x); ref.push(x);
        } else {
            VERIFICA_EGAL(s.top(), ref.top(), "top vs std::stack");
            s.pop(); ref.pop();
        }
        VERIFICA_EGAL(s.marime(), (int)ref.size(), "marime vs std::stack");
    }
}

void test_paranteze() {
    VERIFICA_EGAL(paranteze_echilibrate(""), true, "\"\"");
    VERIFICA_EGAL(paranteze_echilibrate("()"), true, "\"()\"");
    VERIFICA_EGAL(paranteze_echilibrate("{[()]}"), true, "\"{[()]}\"");
    VERIFICA_EGAL(paranteze_echilibrate("()[]{}"), true, "\"()[]{}\"");
    VERIFICA_EGAL(paranteze_echilibrate("a*(b+c[i]) - {x}"), true, "alte caractere se ignora");
    VERIFICA_EGAL(paranteze_echilibrate("([)]"), false, "\"([)]\": se inchide in alta ordine");
    VERIFICA_EGAL(paranteze_echilibrate("(("), false, "\"((\": raman deschise");
    VERIFICA_EGAL(paranteze_echilibrate("())"), false, "\"())\": se inchide una care nu e deschisa");
    VERIFICA_EGAL(paranteze_echilibrate(")("), false, "\")(\"");
    VERIFICA_EGAL(paranteze_echilibrate("(]"), false, "\"(]\": tip diferit");
}

void test_postfix() {
    VERIFICA_EGAL(evalueaza_postfix("5"), 5, "un singur numar");
    VERIFICA_EGAL(evalueaza_postfix("3 4 +"), 7, "3 4 +");
    VERIFICA_EGAL(evalueaza_postfix("3 4 + 2 *"), 14, "3 4 + 2 *");
    VERIFICA_EGAL(evalueaza_postfix("10 3 -"), 7, "10 3 - (ordinea operanzilor conteaza!)");
    VERIFICA_EGAL(evalueaza_postfix("12 4 /"), 3, "12 4 / (ordinea operanzilor conteaza!)");
    VERIFICA_EGAL(evalueaza_postfix("7 2 /"), 3, "impartire intreaga");
    VERIFICA_EGAL(evalueaza_postfix("5 1 2 + 4 * + 3 -"), 14, "5 1 2 + 4 * + 3 -");
    VERIFICA_EGAL(evalueaza_postfix("100 250 +"), 350, "numere cu mai multe cifre");
}

void test_postfix_invalid() {
    VERIFICA(arunca<invalid_argument>([] { evalueaza_postfix("3 +"); }), "\"3 +\": lipseste un operand");
    VERIFICA(arunca<invalid_argument>([] { evalueaza_postfix("+"); }), "\"+\": lipsesc operanzii");
    VERIFICA(arunca<invalid_argument>([] { evalueaza_postfix("3 4"); }), "\"3 4\": raman doua numere");
    VERIFICA(arunca<invalid_argument>([] { evalueaza_postfix(""); }), "expresie goala");
}

int main(int argc, char** argv) {
    return ruleaza_teste(argc, argv, {
        {"stiva noua", test_noua},
        {"push si top", test_push_top},
        {"LIFO", test_lifo},
        {"erori pe stiva goala", test_erori},
        {"operatii aleatoare vs std::stack", test_aleator},
        {"paranteze echilibrate", test_paranteze},
        {"expresie postfixata", test_postfix},
        {"expresie postfixata invalida", test_postfix_invalid},
    });
}
