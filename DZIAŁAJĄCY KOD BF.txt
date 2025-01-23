#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>

using namespace std;

// Funkcja obliczająca maksymalne pole prostokąta metodą brute force
int maksymalnePoleProstokataBruteForce(int** macierz, int m, int n) {
    if (m == 0 || n == 0) {
        return 0;
    }

    int maksymalnePole = 0;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (macierz[i][j] == 1) {
                int minSzerokosc = n;
                for (int k = i; k < m && macierz[k][j] == 1; ++k) {
                    int szerokosc = 0;
                    while (j + szerokosc < n && macierz[k][j + szerokosc] == 1) {
                        ++szerokosc;
                    }
                    minSzerokosc = min(minSzerokosc, szerokosc);
                    maksymalnePole = max(maksymalnePole, minSzerokosc * (k - i + 1));
                }
            }
        }
    }

    return maksymalnePole;
}

int main() {
    ifstream inputFile("cyferki.txt");
    ofstream outputFile("cyferki_wynik.txt");

    if (!inputFile) {
        cerr << "Nie mozna otworzyc pliku wejsciowego!" << endl;
        return 1;
    }

    int m = 5, n = 5;
    int** macierz = new int*[m];
    for (int i = 0; i < m; ++i) {
        macierz[i] = new int[n];
    }

    // Wczytywanie danych wejściowych z pliku
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> macierz[i][j];
        }
    }

    inputFile.close();

    int wynik = maksymalnePoleProstokataBruteForce(macierz, m, n);
    cout << "Najwieksze pole prostokata z jedynek (Brute Force): " << wynik << endl;

    // Zapis wyniku do pliku
    outputFile << "Najwieksze pole prostokata z jedynek (Brute Force): " << wynik << endl;
    outputFile.close();

    for (int i = 0; i < m; ++i) {
        delete[] macierz[i];
    }
    delete[] macierz;

    return 0;
}
