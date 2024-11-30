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

    friend istream& operator>>(istream& is, Polynomial& poly);
    friend ostream& operator<<(ostream& os, const Polynomial& poly);
};

istream& operator>>(istream& is, Polynomial& poly) {
    int numTerms;
    float coef;
    int exp;
    cout << "Enter number of terms: ";
    is >> numTerms;
    for (int i = 0; i < numTerms; ++i) {
        cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        is >> coef >> exp;
        poly.AddTerm(coef, exp);
    }
    return is;
}

ostream& operator<<(ostream& os, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; ++i) {
        if (i > 0 && poly.termArray[i].coef > 0) {
            os << " + ";
        }
        os << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
    }
    return os;
}

int main() {
    Polynomial p1, p2;

    cout << "Enter polynomial p1:" << endl;
    cin >> p1;
    cout << "Enter polynomial p2:" << endl;
    cin >> p2;

    cout << "Polynomial p1: " << p1 << endl;
    cout << "Polynomial p2: " << p2 << endl;

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
