#include <iostream>
//#include "tester\tester.h"
#include "matrix.h"

int main() {
    /*Tester::execute();
    return EXIT_SUCCESS;*/
    Matrix<int> m1(10, 10);
    m1.set(0, 0, 1);
    m1.set(1, 1, 1);
    m1.set(2, 2, 1);
    m1.set(3, 3, 1);
    m1.set(4, 4, 1);
    m1.set(5, 5, 1);
    m1.set(6, 6, 1);
    m1.set(7, 7, 1);
    m1.set(8, 8, 1);
    m1.set(9, 9, 1);
    Matrix<int> m2(10, 10);
    m2.set(0, 0, 5);
    m2.set(1, 1, 5);
    m2.set(2, 2, 5);
    m2.set(3, 3, 5);
    m2.set(4, 4, 5);
    m2.set(5, 5, 5);
    m2.set(6, 6, 5);
    m2.set(7, 7, 5);
    m2.set(8, 8, 5);
    m2.set(9, 9, 5);
    Matrix<int> m3 = m1.operator*(m2);
    m3.print();

    return 0;
}