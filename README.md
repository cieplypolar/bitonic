# Sortowanie bitoniczne
Projekt na kurs **Programowanie Współbieżne 2024/25** na **Uniwersytecie Jagiellońskim**
### Warianty sortowania bitonicznego
1. klasyczne
2. z sortowaniem przez wstawianie
3. OpenMP
4. z użyciem wątków systemowych
### Struktura projektu
- `docs/` : zawiera raport i skrypt do generowania wykresów 
- `include/` i `src/` : zawierają kod źródłowy 
- `test/`: znajdują się tam pliki testowe
### Kompilacja
Odbywa się za pomocą narzędzia `Makefile` 
- `make all` : kompiluje cały projekt
  - `obj/` : w nowo-powstałym katalogu znajdują się pliki `.o`
  - `bin/` : tu znajdują się binarki
- `make clean` : czyści projekt
> [!IMPORTANT]
> należy mieć sklonowaną bibliotekę [`moderngpu`](https://github.com/moderngpu/moderngpu) w repozytorium

### Generowanie danych
1. `make all`
2. `./bin/gen > output`
3. wpisz wielkość danych do wygenerowania

### Testowanie
W `test/` znajdują się testy, jeśli plik nie jest w `test/skip` to zostanie on użyty podczas testowania poprawności sortowań
1. `make all`
2. `./test.sh`

### Pomiary czasu
1. `make all`
2. `./bin/main < input`
> [!IMPORTANT]
> bitonic sort na CUDA inaczej mierzy swój czas działania, jest to już zawarte w `./test.sh`
