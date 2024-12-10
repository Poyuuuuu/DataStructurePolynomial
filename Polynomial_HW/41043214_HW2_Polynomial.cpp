#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

class Polynomial; // �e�m�ŧi

class Term {
    friend Polynomial;
    friend ostream& operator<<(ostream& out, const Polynomial& p);
    friend istream& operator>>(istream& in, Polynomial& p);

private:
    float coef; // �t��
    int exp;    // ����
};

class Polynomial {
private:
    Term* termArray; // �D�s�����}�C
    int capacity;    // �}�C���j�p
    int terms;       // �D�s�����ƶq

public:
    Polynomial(int C = 10, int T = 0) : capacity(C), terms(T) {
        termArray = new Term[capacity];
    }

    ~Polynomial() { delete[] termArray; }

    void NewTerm(const float theCoeff, const int theExp); // �s�W�@�ӷs����
    Polynomial Add(Polynomial poly);                     // �h�����[�k
    Polynomial Mult(Polynomial poly);                    // �h�������k
    float Eval(float f);                                 // �p��h������

    friend ostream& operator<<(ostream& out, const Polynomial& p);
    friend istream& operator>>(istream& in, Polynomial& p);
};

void Polynomial::NewTerm(const float theCoeff, const int theExp) {
    if (terms == capacity) {
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }
    termArray[terms].coef = theCoeff;
    termArray[terms++].exp = theExp;
}

Polynomial Polynomial::Add(Polynomial b) {
    Polynomial c;
    int aPos = 0, bPos = 0;
    while (aPos < terms && bPos < b.terms) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t) c.NewTerm(t, termArray[aPos].exp);
            aPos++;
            bPos++;
        } else if (termArray[aPos].exp < b.termArray[bPos].exp) {
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        } else {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }
    for (; aPos < terms; aPos++) c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < b.terms; bPos++) c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    return c;
}

Polynomial Polynomial::Mult(Polynomial b) {
    Polynomial d;
    for (int aPos = 0; aPos < terms; aPos++) {
        for (int bPos = 0; bPos < b.terms; bPos++) {
            float t = termArray[aPos].coef * b.termArray[bPos].coef;
            int r = termArray[aPos].exp + b.termArray[bPos].exp;
            d.NewTerm(t, r);
        }
    }
    return d;
}

float Polynomial::Eval(float f) {
    float sum = 0;
    for (int i = 0; i < terms; i++) sum += termArray[i].coef * pow(f, termArray[i].exp);
    return sum;
}

ostream& operator<<(ostream& out, const Polynomial& p) {
    if (p.terms == 0) {
        out << "0";
        return out;
    }
    for (int i = 0; i < p.terms; i++) {
        if (i > 0 && p.termArray[i].coef > 0) out << " + ";
        if (p.termArray[i].exp == 0)
            out << p.termArray[i].coef;
        else if (p.termArray[i].exp == 1)
            out << p.termArray[i].coef << "x";
        else
            out << p.termArray[i].coef << "x^" << p.termArray[i].exp;
    }
    return out;
}

istream& operator>>(istream& in, Polynomial& p) {
    cout << "�п�J�h���������ơG";
    in >> p.terms;
    if (p.terms > p.capacity) {
        delete[] p.termArray;
        p.capacity = p.terms;
        p.termArray = new Term[p.capacity];
    }
    cout << "�̦���J�C�@�����t�ƩM���ơ]�Ҧp�G3 2 �N�� 3x^2�^�G\n";
    for (int i = 0; i < p.terms; i++) {
        cout << "�� " << i + 1 << " ���G";
        in >> p.termArray[i].coef >> p.termArray[i].exp;
    }
    return in;
}

int main() {
    Polynomial p1, p2;
    cout << "��J�Ĥ@�Ӧh���� (p1)�G\n";
    cin >> p1;

    cout << "p1(x) = " << p1 << endl;

    cout << "��J�ĤG�Ӧh���� (p2)�G\n";
    cin >> p2;

    cout << "p2(x) = " << p2 << endl;

    Polynomial sum = p1.Add(p2);
    cout << "p1(x) + p2(x) = " << sum << endl;

    Polynomial product = p1.Mult(p2);
    cout << "p1(x) * p2(x) = " << product << endl;

    float x;
    cout << "��J x ���ȥH�p��h���������G�G";
    cin >> x;

    cout << "p1(" << x << ") = " << p1.Eval(x) << endl;
    cout << "p2(" << x << ") = " << p2.Eval(x) << endl;
    cout << "p1(" << x << ") + p2(" << x << ") = " << p1.Eval(x) + p2.Eval(x) << endl;
    cout << "p1(" << x << ") * p2(" << x << ") = " << p1.Eval(x) * p2.Eval(x) << endl;

    return 0;
}

