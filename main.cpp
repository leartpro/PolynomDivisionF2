#include <iostream>
#include <string>
#include <bitset>

using namespace std;

// Funktion zur Umwandlung eines Binärstrings in eine Zahl
unsigned int binaryStringToNumber(const string& binary) {
    return bitset<32>(binary).to_ulong();
}

// Funktion zur Polynomdivision in F2
unsigned int polynomialDivision(unsigned int dividend, unsigned int divisor, unsigned int& remainder) {
    // Bestimmen der Gradzahl (höchstwertiges Bit)
    int dividendDegree = 31 - __builtin_clz(dividend);
    int divisorDegree = 31 - __builtin_clz(divisor);

    // Kopie des Dividenden, die bearbeitet wird
    unsigned int workingDividend = dividend;

    // Division durchführen
    while (dividendDegree >= divisorDegree) {
        // Verschieben des Divisors, um auf die gleiche Stufe zu kommen
        unsigned int shiftedDivisor = divisor << (dividendDegree - divisorDegree);

        // XOR für Subtraktion (Modulo-2)
        workingDividend ^= shiftedDivisor;

        // Aktualisieren des höchsten Grads des Dividenden
        dividendDegree = 31 - __builtin_clz(workingDividend);
    }

    // Der verbleibende Rest
    remainder = workingDividend;

    // Wenn der Rest 0 ist, ist der Dividend durch den Divisor teilbar
    return (remainder == 0);
}

int main() {
    string dividendInput, divisorInput;

    // Eingabe von Divisor und Dividend in Binärform
    cout << "Geben Sie den Dividend (Binärform) ein: ";
    cin >> dividendInput;
    cout << "Geben Sie den Divisor (Binärform) ein: ";
    cin >> divisorInput;

    // Umwandlung in Ganzzahlen
    unsigned int dividend = binaryStringToNumber(dividendInput);
    unsigned int divisor = binaryStringToNumber(divisorInput);

    // Rest der Division
    unsigned int remainder = 0;

    // Polynomdivision ausführen
    bool isDivisible = polynomialDivision(dividend, divisor, remainder);

    // Ausgabe
    cout << "Teilbarkeit: " << (isDivisible ? "Ja" : "Nein") << endl;
    cout << "Rest (Binär): " << bitset<32>(remainder).to_string() << endl;

    return 0;
}