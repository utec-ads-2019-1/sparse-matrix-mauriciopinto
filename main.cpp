#include <iostream>
//#include "tester\tester.h"
#include "matrix.h"
#include <stdlib.h>

int main() {
    /*Tester::execute();
    return EXIT_SUCCESS;*/
    Matrix<int> m1(9, 10);
    for(int i = 0; i < m1.rows; i++){
        for(int j = 0; j < m1.columns; j++){
            m1.set(i, j, rand()%10);
        }
    }
    Matrix<int> m2(10, 9);
    for(int i = 0; i < m2.rows; i++){
        for(int j = 0; j < m2.columns; j++){
            m2.set(i, j, rand()%10);
        }
    }
    Matrix<int> m3 = m1.operator+(m2);
    m1.print();
    cout << endl;
    m2.print();
    cout << endl;
    m3.print();
    /*m3.remove(m3.find(8, 7));
    m3.print();*/
    return 0;
}