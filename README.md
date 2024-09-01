# suffix-tree
# Cerința 1

- Salvez în `k` indexul literei curente.
- Dacă litera cu index `i` din cuvântul `sir` nu a fost folosită la nivelul respectiv:
  - Creez nodul.
  - Salvez litera și un șir de caractere care conține doar litera și `\0` pentru a mă ajuta la Cerința 4.
- Funcția de afișare verifică dacă adâncimea curentă este 0:
  - Dacă da, tipărește caracterul din nodul curent și setează `ok` la 1.
  - Apoi, funcția parcurge toți copiii nodului curent și apelează recursiv `printLevel` pentru fiecare copil care nu este `NULL`, cu adâncimea redusă cu 1.

# Cerința 2

- **count_suffixes_of_length**:
  - Verificăm dacă nodul curent este frunză (dacă are `$`):
    - Dacă da, se returnează 1.
  - Parcurgem toți copiii recursiv și stocăm rezultatul în `count`.
- **count_leaf_nodes**:
  - Fac un auxiliar (`aux`) în care stochez numărul de frunze.
  - Dacă copilul de pe poziția `i` nu este `NULL`:
    - Parcurg toți copiii nodului curent și, dacă este frunză, incrementez `count`.
    - Altfel, apelez funcția aceasta recursiv pentru toți copiii.
- **max_direct_descendants**:
  - Funcția parcurge toți copiii nodului curent și crește un contor (`max`) pentru fiecare copil care nu este `NULL`.
  - După aceea, funcția parcurge din nou toți copiii nodului curent și apelează recursiv `max_direct_descendants` pentru fiecare copil care nu este `NULL`.
  - Dacă numărul maxim de descendenți direcți returnat de un apel recursiv este mai mare decât `max`, atunci `max` este actualizat cu acea valoare.

# Cerința 3

- **search**:
  - În `len` pun lungimea șirului căutat.
  - Căutăm litera curentă.
  - În `k` pun indexul literei respective.
  - Verific dacă există copilul de indice `K`:
    - Dacă nu, se scrie 0.
  - După ce toate caracterele din șirul de căutare au fost procesate, funcția verifică dacă nodul curent are un copil care reprezintă sfârșitul unui cuvânt (caracterul `$`):
    - Dacă da, scrie 1 în fișier.

# Cerința 4

- Funcția începe prin setarea unui nod auxiliar (`aux`) la nodul curent.
- Apoi, intră într-un ciclu infinit în care verifică dacă nodul curent are un singur copil (excluzând copilul care reprezintă sfârșitul unui cuvânt):
  - Dacă da, nodul auxiliar coboară la acel copil, șirul de caractere al copilului este adăugat la șirul de caractere al nodului curent, iar copiii nodului devin copiii nodului curent.
  - Acest proces se repetă până când nodul curent are mai mult de un copil sau are un copil care reprezintă sfârșitul unui cuvânt.
- După ce nodul curent a fost comprimat, funcția apelează recursiv `compress` pentru fiecare copil al nodului curent.

