#include <iostream>
#include <cmath>
using namespace std;

struct Node {
    int coef;  
    int exp;   
    Node* link; 
};

class Polynomial {
private:
    Node* head; 

public:
    Polynomial(); 
    Polynomial(const Polynomial& a); 
    ~Polynomial(); 

    const Polynomial& operator=(const Polynomial& a); 
    Polynomial operator+(const Polynomial& b) const; 
    Polynomial operator-(const Polynomial& b) const; 
    Polynomial operator*(const Polynomial& b) const; 
    float Evaluate(float x) const; 

    friend istream& operator>>(istream& is, Polynomial& x);
    friend ostream& operator<<(ostream& os, const Polynomial& x); 
};

Polynomial::Polynomial() {
    head = new Node;
    head->link = head; 
}

Polynomial::~Polynomial() {
    Node* current = head->link;
    while (current != head) {
        Node* temp = current;
        current = current->link;
        delete temp;
    }
    delete head;
}

Polynomial::Polynomial(const Polynomial& a) {
    head = new Node;
    head->link = head;
    Node* current = a.head->link;
    Node* last = head;
    while (current != a.head) {
        Node* newNode = new Node;
        newNode->coef = current->coef;
        newNode->exp = current->exp;
        last->link = newNode;
        last = newNode;
        current = current->link;
    }
    last->link = head;
}

const Polynomial& Polynomial::operator=(const Polynomial& a) {
    if (this == &a) return *this;

    this->~Polynomial();

    head = new Node;
    head->link = head;
    Node* current = a.head->link;
    Node* last = head;
    while (current != a.head) {
        Node* newNode = new Node;
        newNode->coef = current->coef;
        newNode->exp = current->exp;
        last->link = newNode;
        last = newNode;
        current = current->link;
    }
    last->link = head;
    return *this;
}

istream& operator>>(istream& is, Polynomial& x) {
    x.~Polynomial(); 
    x.head = new Node;
    x.head->link = x.head;

    int n;
    is >> n;
    for (int i = 0; i < n; ++i) {
        int coef, exp;
        is >> coef >> exp;
        Node* newNode = new Node;
        newNode->coef = coef;
        newNode->exp = exp;

        Node* curr = x.head;
        while (curr->link != x.head && curr->link->exp > exp) {
            curr = curr->link;
        }
        newNode->link = curr->link;
        curr->link = newNode;
    }
    return is;
}

ostream& operator<<(ostream& os, const Polynomial& x) {
    Node* current = x.head->link;
    bool first = true;
    while (current != x.head) {
        if (!first && current->coef > 0) os << " + ";
        if (current->coef == 1 && current->exp != 0) {
            os << "1";
        } else if (current->coef == -1 && current->exp != 0) {
            os << "-1";
        } else {
            os << current->coef;
        }
        if (current->exp > 1) {
            os << "x^" << current->exp;
        } else if (current->exp == 1) {
            os << "1";
        }
        current = current->link;
        first = false;
    }
    return os;
}

float Polynomial::Evaluate(float x) const {
    float result = 0.0;
    Node* current = head->link;
    while (current != head) {
        result += current->coef * pow(x, current->exp);
        current = current->link;
    }
    return result;
}

Polynomial Polynomial::operator+(const Polynomial& b) const {
    Polynomial result;
    Node* aCurrent = head->link;
    Node* bCurrent = b.head->link;
    Node* last = result.head;

    while (aCurrent != head && bCurrent != b.head) {
        Node* newNode = new Node;
        if (aCurrent->exp > bCurrent->exp) {
            newNode->coef = aCurrent->coef;
            newNode->exp = aCurrent->exp;
            aCurrent = aCurrent->link;
        } else if (aCurrent->exp < bCurrent->exp) {
            newNode->coef = bCurrent->coef;
            newNode->exp = bCurrent->exp;
            bCurrent = bCurrent->link;
        } else {
            newNode->coef = aCurrent->coef + bCurrent->coef;
            newNode->exp = aCurrent->exp;
            aCurrent = aCurrent->link;
            bCurrent = bCurrent->link;
        }
        last->link = newNode;
        last = newNode;
    }

    while (aCurrent != head) {
        Node* newNode = new Node;
        newNode->coef = aCurrent->coef;
        newNode->exp = aCurrent->exp;
        last->link = newNode;
        last = newNode;
        aCurrent = aCurrent->link;
    }

    while (bCurrent != b.head) {
        Node* newNode = new Node;
        newNode->coef = bCurrent->coef;
        newNode->exp = bCurrent->exp;
        last->link = newNode;
        last = newNode;
        bCurrent = bCurrent->link;
    }

    last->link = result.head;
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& b) const {
    Polynomial result;
    Node* aCurrent = head->link;
    Node* bCurrent = b.head->link;
    Node* last = result.head;

    while (aCurrent != head && bCurrent != b.head) {
        Node* newNode = new Node;
        if (aCurrent->exp > bCurrent->exp) {
            newNode->coef = aCurrent->coef;
            newNode->exp = aCurrent->exp;
            aCurrent = aCurrent->link;
        } else if (aCurrent->exp < bCurrent->exp) {
            newNode->coef = -bCurrent->coef;
            newNode->exp = bCurrent->exp;
            bCurrent = bCurrent->link;
        } else {
            newNode->coef = aCurrent->coef - bCurrent->coef;
            newNode->exp = aCurrent->exp;
            aCurrent = aCurrent->link;
            bCurrent = bCurrent->link;
        }
        last->link = newNode;
        last = newNode;
    }

    while (aCurrent != head) {
        Node* newNode = new Node;
        newNode->coef = aCurrent->coef;
        newNode->exp = aCurrent->exp;
        last->link = newNode;
        last = newNode;
        aCurrent = aCurrent->link;
    }

    while (bCurrent != b.head) {
        Node* newNode = new Node;
        newNode->coef = -bCurrent->coef;
        newNode->exp = bCurrent->exp;
        last->link = newNode;
        last = newNode;
        bCurrent = bCurrent->link;
    }

    last->link = result.head;
    return result;
}

Polynomial Polynomial::operator*(const Polynomial& b) const {
    Polynomial result;
    Node* aCurrent = head->link;

    while (aCurrent != head) {
        Node* bCurrent = b.head->link;
        while (bCurrent != b.head) {
            int newCoef = aCurrent->coef * bCurrent->coef;
            int newExp = aCurrent->exp + bCurrent->exp;
            Node* curr = result.head;
            while (curr->link != result.head && curr->link->exp > newExp) {
                curr = curr->link;
            }
            if (curr->link != result.head && curr->link->exp == newExp) {
                curr->link->coef += newCoef;
                if (curr->link->coef == 0) {
                    Node* temp = curr->link;
                    curr->link = temp->link;
                    delete temp;
                }
            } else {
                Node* newNode = new Node;
                newNode->coef = newCoef;
                newNode->exp = newExp;
                newNode->link = curr->link;
                curr->link = newNode;
            }
            bCurrent = bCurrent->link;
        }
        aCurrent = aCurrent->link;
    }

    return result;
}

int main() {
    Polynomial p1, p2, result;
    cout << " p1 :";
    cin >> p1;
    cout << " p2: ";
    cin >> p2;

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;

    result = p1 * p2;
    cout << "p1 * p2 = " << result << endl;

    float x;
    cout << " p1(x): ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Evaluate(x) << endl;

    return 0;
}