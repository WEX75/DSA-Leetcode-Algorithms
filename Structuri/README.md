# Structuri de date — schelete cu teste

Fiecare fișier are o clasă cu toate metodele declarate și explicate, dar cu corpurile goale (`throw NeImplementat();`). Tu scrii codul, iar testele de la finalul fișierului îți spun dacă e corect.

## Cum lucrezi

1. Deschizi fișierul și citești comentariul de sus (ce exersezi și în ce ordine).
2. Alegi o metodă, ștergi `throw NeImplementat();` și scrii codul.
3. Compilezi și rulezi:
   ```bash
   g++ -std=c++17 -Wall 05_lista_simplu_inlantuita.cpp -o lista && ./lista
   ./lista 3        # doar testul 3
   ```
4. Te uiți la rezultat:
   - `OK`: merge.
   - `NEIMPLEMENTAT`: testul folosește o metodă pe care n-ai scris-o încă.
   - `PICAT: ... ai X, trebuia Y [linia N]`: îți arată ce ai returnat, ce trebuia și linia testului.
5. Treci la următoarea metodă. La final trebuie să ai scorul maxim.

**Nu modifica testele** (tot ce e sub linia `TESTE (nu modifica)`) și nici `teste.hpp`.

## Fișierele

| # | Fișier | Ce exersezi |
|---|---|---|
| 01 | `01_vector_dinamic.cpp` | dublarea capacității, O(1) amortizat, regula celor trei (copiere în adâncime) |
| 02 | `02_stiva.cpp` | stivă pe listă înlănțuită + paranteze echilibrate + expresii postfixate |
| 03 | `03_coada_circulara.cpp` | ring buffer: indici „în cerc”, mărirea când coada e ruptă în două |
| 04 | `04_deque.cpp` | coadă cu două capete, `push_front` și restul negativ în C++ |
| 05 | `05_lista_simplu_inlantuita.cpp` | ștergerea cu nodul dinainte, `ultim` ținut la zi, inversare, mijlocul listei |
| 06 | `06_lista_dublu_inlantuita.cpp` | două săgeți de reparat la fiecare operație |
| 07 | `07_heap.cpp` | min-heap în vector, construire în O(n), heapsort, al k-lea cel mai mare |
| 08 | `08_bst.cpp` | recursivitate pe arbori, cele 3 cazuri de ștergere, succesor |
| 09 | `09_avl.cpp` | rotiri, cazurile LL / RR / LR / RL, ștergere (bonus) |
| 10 | `10_hash_inlantuire.cpp` | funcție de dispersie pe string-uri, coliziuni, rehash |
| 11 | `11_hash_adresare_deschisa.cpp` | linear probing, ștergerea cu „piatră funerară” |
| 12 | `12_graf.cpp` | BFS, DFS, componente conexe, drum minim, sortare topologică |
| 13 | `13_union_find.cpp` | compresia drumului, unirea după mărime, Kruskal |

Ordinea din tabel e și ordinea recomandată. 08 trebuie făcut înainte de 09, iar 05 înainte de 06.

## Când ceva nu merge

- **Programul nu se mai termină**: ai o buclă infinită. Testul la care s-a blocat e ultimul afișat. Oprești programul cu `Ctrl+C`.
- **`Segmentation fault`** (sau cod de ieșire 139): ai folosit un pointer invalid, de obicei `nullptr->ceva` sau un nod deja șters.
- **Memory leak și accese greșite la memorie**: compilezi cu verificări de memorie. Îți arată exact linia problemei, inclusiv dacă destructorul nu eliberează tot:
  ```bash
  g++ -std=c++17 -Wall -g -fsanitize=address,undefined 05_lista_simplu_inlantuita.cpp -o lista && ./lista
  ```
- **Warning-uri la compilare**: ia-le în serios. `suggest parentheses around assignment` înseamnă aproape mereu `=` în loc de `==`.

## Soluțiile de referință

În `solutii/` e câte o soluție completă pentru fiecare fișier (trec toate testele). Deschide-le doar după ce termini, ca să compari, sau dacă te-ai blocat de tot. Folderul e în `.gitignore`, deci nu ajunge pe GitHub.
