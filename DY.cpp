#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <stack>

using namespace std;

// Funkcja obliczająca maksymalne pole prostokąta metodą dynamicznego programowania
int maksymalnePoleProstokataDP(int** macierz, int m, int n) {
    if (m == 0 || n == 0) {
        return 0;
    }

    int maksymalnePole = 0;
    int dp[m][n];

    // Inicjalizacja pierwszego wiersza
    for (int j = 0; j < n; ++j) {
        dp[0][j] = macierz[0][j];
    }

    // Inicjalizacja pozostałych wierszy
    for (int i = 1; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (macierz[i][j] == 1) {
                dp[i][j] = dp[i-1][j] + 1;
            } else {
                dp[i][j] = 0;
            }
        }
    }

    // Obliczanie maksymalnego pola prostokąta dla każdego wiersza
    for (int i = 0; i < m; ++i) {
        stack<int> s;
        int j = 0;
        while (j < n) {
            if (s.empty() || dp[i][s.top()] <= dp[i][j]) {
                s.push(j++);
            } else {
                int tp = s.top();
                s.pop();
                int pole = dp[i][tp] * (s.empty() ? j : j - s.top() - 1);
                maksymalnePole = max(maksymalnePole, pole);
            }
        }
        while (!s.empty()) {
            int tp = s.top();
            s.pop();
            int pole = dp[i][tp] * (s.empty() ? j : j - s.top() - 1);
            maksymalnePole = max(maksymalnePole, pole);
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

    int wynik = maksymalnePoleProstokataDP(macierz, m, n);
    cout << "Najwieksze pole prostokata z jedynek: " << wynik << endl;

    // Zapis wyniku do pliku
    outputFile << "Najwieksze pole prostokata z jedynek: " << wynik << endl;
    outputFile.close();

    for (int i = 0; i < m; ++i) {
        delete[] macierz[i];
    }
    delete[] macierz;

    return 0;
}