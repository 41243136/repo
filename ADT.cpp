#include <iostream>
#include <cmath>
using namespace std;
class Polynomial {
private:
    struct Term {
        float coef;
        int exp;
    };
    Term* termArray;
    int capacity;
    int terms;

    void Resize(int newCapacity) {
        Term* newArray = new Term[newCapacity];
        for (int i = 0; i < terms; ++i) {
            newArray[i] = termArray[i];
        }
        delete[] termArray;
        termArray = newArray;
        capacity = newCapacity;
    }

public:
    Polynomial() : capacity(10), terms(0) {
        termArray = new Term[capacity];
    }

    ~Polynomial() {
        delete[] termArray;
    }

    void AddTerm(float coef, int exp) {
        for (int i = 0; i < terms; ++i) {
            if (termArray[i].exp == exp) {
                termArray[i].coef += coef;
                return;
            }
        }
        if (terms == capacity) {
            Resize(2 * capacity);
        }
        termArray[terms].coef = coef;
        termArray[terms].exp = exp;
        ++terms;
    }

    Polynomial Add(const Polynomial& poly) const {
        Polynomial result;
        for (int i = 0; i < terms; ++i) {
            result.AddTerm(termArray[i].coef, termArray[i].exp);
        }
        for (int j = 0; j < poly.terms; ++j) {
            result.AddTerm(poly.termArray[j].coef, poly.termArray[j].exp);
        }
        return result;
    }

    Polynomial Mult(const Polynomial& poly) const {
        Polynomial result;
        for (int i = 0; i < terms; ++i) {
            for (int j = 0; j < poly.terms; ++j) {
                float newCoef = termArray[i].coef * poly.termArray[j].coef;
                int newExp = termArray[i].exp + poly.termArray[j].exp;
                result.AddTerm(newCoef, newExp);
            }
        }
        return result;
    }

    float Eval(float f) const {
        float result = 0;
        for (int i = 0; i < terms; ++i) {
            result += termArray[i].coef * pow(f, termArray[i].exp);
        }
        return result;
    }

    void Print() const {
        for (int i = 0; i < terms; ++i) {
            if (i > 0 && termArray[i].coef > 0) {
                cout << " + ";
            }
            cout << termArray[i].coef << "x^" << termArray[i].exp;
        }
        cout << endl;
    }
};

int main() {
    Polynomial p1, p2;
    int numTerms;
    float coef;
    int exp;

    cout << "Enter number of terms for polynomial p1: ";
    cin >> numTerms;
    for (int i = 0; i < numTerms; ++i) {
        cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        cin >> coef >> exp;
        p1.AddTerm(coef, exp);
    }

    cout << "Enter number of terms for polynomial p2: ";
    cin >> numTerms;
    for (int i = 0; i < numTerms; ++i) {
        cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        cin >> coef >> exp;
        p2.AddTerm(coef, exp);
    }

    cout << "Polynomial p1: ";
    p1.Print();
    cout << "Polynomial p2: ";
    p2.Print();

    float x;
    cout << "Enter a value to evaluate the polynomials: ";
    cin >> x;

    float p1Value = p1.Eval(x);
    float p2Value = p2.Eval(x);
    float sumValue = p1Value + p2Value;
    float productValue = p1Value * p2Value;

    cout << "p1(" << x << ") = " << p1Value << endl;
    cout << "p2(" << x << ") = " << p2Value << endl;
    cout << "sum(" << x << ") = " << sumValue << endl;
    cout << "product(" << x << ") = " << productValue << endl;

    return 0;
}