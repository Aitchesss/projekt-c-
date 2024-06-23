# Wypożyczalnia Pojazdów

Prosty system wypożyczalni pojazdów napisany w języku C++.

## Opis projektu

Projekt stanowi aplikację konsolową symulującą system wypożyczalni pojazdów, obsługujący zarówno samochody, jak i motocykle. Umożliwia użytkownikowi zarządzanie wypożyczonymi pojazdami poprzez funkcje wypożyczania, zwrotu, jazdy oraz tankowania.

## Struktura projektu

Projekt składa się z jednego pliku źródłowego:

- `main.cpp`: Główny plik programu zawierający całą logikę interakcji z użytkownikiem oraz definicje klas.

## Instrukcja instalacji i uruchomienia

### Wymagania

Aby uruchomić program, wymagane jest środowisko zgodne z systemem operacyjnym Windows oraz kompilator obsługujący standard C++11.

### Kompilacja

1. **Pobranie kodu źródłowego:**
   Sklonuj repozytorium lub pobierz plik `main.cpp` do lokalnego katalogu.

2. **Kompilacja:**
   Skompiluj plik `main.cpp` za pomocą kompilatora obsługującego C++11. Na przykład:
   ```bash
   g++ -std=c++11 main.cpp -o wypozyczalnia.exe