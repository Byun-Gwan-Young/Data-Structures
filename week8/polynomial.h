#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "arrayList.h"

typedef arrayList polynomial;

extern polynomial* createPolynomial(int capacity);
extern polynomial* addItemPolynomial(polynomial* po, elementType item);
extern void printPolynomial(polynomial* po);
extern polynomial* addPolynomial(polynomial* p1, polynomial* p2);
extern polynomial* multiplyPolynomial(polynomial* p1, polynomial* p2);
extern polynomial* inputPolynomial(void);

#endif /* POLYNOMIAL_H */
