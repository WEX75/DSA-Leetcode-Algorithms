// Mini-framework de teste, folosit de toate fisierele din folderul asta.
// Nu trebuie modificat si nici inteles ca sa lucrezi la structuri.

#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Corpurile functiilor neimplementate arunca asta; testul apare ca NEIMPLEMENTAT.
struct NeImplementat : std::runtime_error {
    NeImplementat() : std::runtime_error("NeImplementat") {}
};

struct Picat : std::runtime_error {
    using std::runtime_error::runtime_error;
};

namespace teste_detail {

inline std::string text(const std::string& s) { return "\"" + s + "\""; }
inline std::string text(const char* s) { return text(std::string(s)); }
inline std::string text(bool b) { return b ? "true" : "false"; }

template <class T>
std::string text(const T& x) {
    std::ostringstream os;
    os << x;
    return os.str();
}

template <class T>
std::string text(const std::vector<T>& v) {
    std::string s = "[";
    for (size_t i = 0; i < v.size(); i++) {
        if (i == 20 && v.size() > 25) {
            s += "... (" + std::to_string(v.size()) + " elemente)";
            break;
        }
        if (i) s += ", ";
        s += text(v[i]);
    }
    return s + "]";
}

inline std::string linia(int l) { return "   [linia " + std::to_string(l) + "]"; }

}  // namespace teste_detail

#define VERIFICA(cond, mesaj)                                                  \
    do {                                                                       \
        if (!(cond))                                                           \
            throw Picat(std::string(mesaj) + teste_detail::linia(__LINE__));   \
    } while (0)

// Atentie: un argument cu acolade, ca vector<int>{1, 2}, trebuie pus intre
// paranteze, altfel virgulele lui sunt luate drept separatori de macro.
#define VERIFICA_EGAL(a, b, mesaj)                                             \
    do {                                                                       \
        auto _a = (a);                                                         \
        auto _b = (b);                                                         \
        if (!(_a == _b))                                                       \
            throw Picat(std::string(mesaj) + ": ai " +                         \
                        teste_detail::text(_a) + ", trebuia " +                \
                        teste_detail::text(_b) + teste_detail::linia(__LINE__)); \
    } while (0)

// true daca f() arunca o exceptie de tipul E (de ex. std::out_of_range).
template <class E, class F>
bool arunca(F f) {
    try {
        f();
    } catch (const E&) {
        return true;
    } catch (const NeImplementat&) {
        throw;
    } catch (...) {
    }
    return false;
}

struct Test {
    const char* nume;
    std::function<void()> f;
};

// ./program      -> ruleaza toate testele
// ./program 3    -> ruleaza doar testul 3
inline int ruleaza_teste(int argc, char** argv, const std::vector<Test>& teste) {
    int doar = argc > 1 ? std::atoi(argv[1]) : 0;
    int ok = 0, rulate = 0;
    for (size_t i = 0; i < teste.size(); i++) {
        int nr = (int)i + 1;
        if (doar && nr != doar) continue;
        rulate++;
        // flush: daca testul intra in bucla infinita, vezi la care s-a blocat
        std::cout << "Test " << nr << " (" << teste[i].nume << ") => " << std::flush;
        try {
            teste[i].f();
            std::cout << "OK\n";
            ok++;
        } catch (const NeImplementat&) {
            std::cout << "NEIMPLEMENTAT\n";
        } catch (const Picat& e) {
            std::cout << "PICAT: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "PICAT: exceptie neasteptata: " << e.what() << "\n";
        }
    }
    std::cout << "\nScor: " << ok << "/" << rulate << "\n";
    return ok == rulate ? 0 : 1;
}
