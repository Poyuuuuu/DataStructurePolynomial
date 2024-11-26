#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

class Polynomial;	//forward declaration

class Term {
	friend Polynomial;
	private:
		float coef;	//coefficient
		int exp;	//exponent
};

class Polynomial {
	private:
		Term *termArray;	//array of nonzero terms
		int capacity;	//size of termArray
		int terms;	//number of nonzero terms
	public:
		Polynomial(int C = 0, int T = 0) : capacity(C), terms(T) {	//constructor.
			termArray = new Term[capacity];
		}
		//construct the polynomial p(x) = 0;
		void showTerm();
		//To show the polynomial.
		void NewTerm(const float theCoeff, const int theExp);
		//Add a new term to the end of termArray.
		Polynomial Add(Polynomial poly);
		//Return the sum of the polynomials *this and poly.
		Polynomial Mult(Polynomial poly);
		//Return the product of the polynomials *this and poly.
		float Eval(float f);
		//Evaluate the polynomial *this at f and return the result.
};

void Polynomial::showTerm() {	//To show the polynomial.
	for(int j=0;j<terms;j++) {
		if((int)termArray[j].coef != 0 && (int)termArray[j].exp > 0) cout<<termArray[j].coef<<"x^"<<termArray[j].exp;
		else if(termArray[j].exp == 0) cout<<termArray[j].coef;
		else continue;
		if(j==terms-1) break;
		cout<<" + ";
	}
}

Polynomial Polynomial::Add(Polynomial b) {	//Return the sum of the polynomials *this and b.
	Polynomial c;
	int aPos = 0, bPos = 0;
	while((aPos<terms) && (bPos<b.terms)) {
		if((termArray[aPos].exp==b.termArray[bPos].exp)) {
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if(t) c.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if((termArray[aPos].exp<b.termArray[bPos].exp)) {
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else {
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	} 
	for(;aPos<terms;aPos++) c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for(;bPos<b.terms;bPos++) c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c;
}

Polynomial Polynomial::Mult(Polynomial b) {	//Return the product of the polynomials *this and b.
	Polynomial d;
	int aPos = 0, bPos = 0, dPos = 0, temp, count = 0;
	float temp1;
	for(aPos=0;aPos<terms;aPos++) {
		for(bPos=0;bPos<b.terms;bPos++)	{
		    float t=termArray[aPos].coef*b.termArray[bPos].coef;
			int r=termArray[aPos].exp+b.termArray[bPos].exp;
		    if(r>=0) d.NewTerm(t,r);
		}
	}
	for(int i=0;i<d.terms;i++) {
	    for(int j=i+1;j<=d.terms;j++) {
		   	if(d.termArray[i].exp<d.termArray[j].exp) {
		   	    temp=d.termArray[i].exp;
		   	    d.termArray[i].exp=d.termArray[j].exp;
		   	    d.termArray[j].exp=temp;
		   	    temp1=d.termArray[i].coef;
		   	    d.termArray[i].coef=d.termArray[j].coef;
		   	    d.termArray[j].coef=temp1;	
			}
			if(d.termArray[i].exp==d.termArray[j].exp && d.termArray[i].exp>0) {    
				temp1=d.termArray[i].coef+d.termArray[j].coef;
				d.termArray[i].coef=temp1;
			    for(int k=j;k<d.terms;k++) {
					d.termArray[k]=d.termArray[++k];
					k--;
			    }
				d.terms--;
			}
	    }
    }
    return d;
}

float Polynomial::Eval(float f) {	//Evaluate the polynomial *this at f and return the result.
	float sum = 0;
	for(int i=0;i<terms;i++) sum+= termArray[i].coef*pow(f,termArray[i].exp);
	return sum;
}

void Polynomial::NewTerm(const float theCoeff, const int theExp) {	//Add a new term to the end of termArray.
	if(terms == capacity) {	//double capacity of termArray
		capacity*=2;
		Term *temp = new Term[capacity];	//new array
		copy(termArray, termArray + terms, temp);
		delete [] termArray;	//deallocate old memory
		termArray = temp;
	}
	termArray[terms].coef = theCoeff;
	termArray[terms++].exp = theExp;
}

int main() {
	int capacity, terms, exponent;
	float coefficient, f;
	cout<<"Enter the capacity and number of terms for this polynomial(p1): ";
	cin>>capacity>>terms;
	Polynomial p(capacity);
	for(int i=0;i<terms;i++) {
		cout<<"Enter the coefficient and its exponent: ";
		cin>>coefficient>>exponent;
		p.NewTerm(coefficient ,exponent);
	}
	cout<<"p1(x) = ";
	p.showTerm();
	cout<<'\n';
	cout<<"Enter the capacity and number of terms for another polynomial(p2): ";
	cin>>capacity>>terms;
	Polynomial p2(capacity);
	for(int i=0;i<terms;i++) {
		cout<<"Enter the coefficient and its exponent: ";
		cin>>coefficient>>exponent;
		p2.NewTerm(coefficient ,exponent);
	}
	cout<<"p2(x) = ";
	p2.showTerm();
	cout<<'\n';
	cout<<"The sum of p1 and p2 = ";
	p.Add(p2).showTerm();
	cout<<'\n';
	cout<<"The product of p1 and p2 = ";
	p.Mult(p2).showTerm();
	cout<<'\n';
	cout<<"Enter a number(the value of x) to evaluate the polynomial : ";
	cin>>f;
	cout<<"p1(x) = "<<p.Eval(f)<<endl;
	cout<<"p2(x) = "<<p2.Eval(f)<<endl;
	cout<<"p1(x) + p2(x) = "<<p.Eval(f)+p2.Eval(f)<<endl;
	cout<<"p1(x) * p2(x) = "<<p.Eval(f)*p2.Eval(f)<<endl;
	return 0;
}
