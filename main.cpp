#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

// Funktion zur Umwandlung eines Binärstrings in eine Zahl
unsigned int binaryStringToNumber(const string& binary) {
    return bitset<32>(binary).to_ulong();
}

// Funktion zur Ausgabe eines Polynoms in Binärform
string polynomialToString(unsigned int poly) {
    string result;
    bool firstTerm = true;

    for (int i = 31; i >= 0; --i) {
        if ((poly >> i) & 1) {
            if (!firstTerm) {
                result += "+";
            }
            if (i == 0) {
                result += "1";
            } else {
                result += "x^" + to_string(i);
            }
            firstTerm = false;
        }
    }

    return result.empty() ? "0" : result;
}

// Funktion zur Polynomdivision in F2 mit Zwischenschritten
void polynomialDivisionWithSteps(unsigned int dividend, unsigned int divisor) {
    // Bestimmen der Gradzahl (höchstwertiges Bit)
    int dividendDegree = 31 - __builtin_clz(dividend);
    int divisorDegree = 31 - __builtin_clz(divisor);

    unsigned int workingDividend = dividend;
    unsigned int shiftedDivisor;
    vector<string> steps;

    cout << "Division: (" << polynomialToString(dividend) << ") / (" << polynomialToString(divisor) << ")" << endl;

    // Division durchführen
    while (dividendDegree >= divisorDegree) {
        // Verschieben des Divisors, um es an den aktuellen Grad des Dividenden anzupassen
        shiftedDivisor = divisor << (dividendDegree - divisorDegree);

        // Schritt-Ausgabe
        steps.push_back("Divisor: " + polynomialToString(shiftedDivisor));
        steps.push_back("Dividend: " + polynomialToString(workingDividend));
        steps.push_back("XORing: " + polynomialToString(workingDividend) + " xor " + polynomialToString(shiftedDivisor));

        // XOR durchführen
        workingDividend ^= shiftedDivisor;

        // Aktualisieren des höchsten Grads des Dividenden
        dividendDegree = 31 - __builtin_clz(workingDividend);

        steps.push_back("Result after XOR: " + polynomialToString(workingDividend));
        steps.emplace_back("--------------------------------------------------");
    }

    // Ausgabe der Zwischenschritte
    for (const string& step : steps) {
        cout << step << endl;
    }

    cout << "Remainder (Rest): " << polynomialToString(workingDividend) << endl;
    if (workingDividend == 0) {
        cout << "The polynomial is divisible without remainder." << endl;
    } else {
        cout << "The polynomial is not divisible without remainder." << endl;
    }
}

int main() {
    string dividendInput, divisorInput;

    // Eingabe von Divisor und Dividend in Binärform
    cout << "Polynomial Division in F2" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Geben Sie den Dividend (Binaerform) ein:";
    cin >> dividendInput;
    cout << "Geben Sie den Divisor (Binaerform) ein:";
    cin >> divisorInput;

    // Umwandlung in Ganzzahlen
    unsigned int dividend = binaryStringToNumber(dividendInput);
    unsigned int divisor = binaryStringToNumber(divisorInput);

    // Polynomdivision mit Schritten ausführen
    polynomialDivisionWithSteps(dividend, divisor);

    return 0;
}
