#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include"node.h"
using namespace std;

template <typename T>
class Matrix {
public:
    Node<T> *root;
    unsigned rows, columns;

    Matrix(unsigned rows, unsigned columns): root(nullptr), rows(rows), columns(columns){
        root = new Node<T>(-1, -1, -1);
        Node<T>* current1 = root;
        Node<T>* current2 = root;
        for(int i = 0; i < rows + 1; i++){
            Node<T>* newNode1 = new Node<T>(i, -1, i);
            current1->next = newNode1;
            current1 = current1->next;
        }
        for(int i = 0; i < columns + 1; i++){
            Node<T>* newNode1 = new Node<T>(-1, i, i);
            current2->down = newNode1;
            current2 = current2->down;
        }
        cout << rows << " " << columns << endl;
    };

    Node<T>* find(int x, int y) const{
        if(x > columns || y > rows){
            throw out_of_range("Index out of range");
        }
        Node<T> *current = root;
        while(current->x < x && current->next != nullptr){
            current = current->next;
        }
        while(current->y < y && current->down != nullptr){
            current = current->down;
        }
        if(current->x == x && current->y == y){
            return current;
        }
        else{
            return nullptr;
        }
    }

    void set(int x, int y, T data) const{
        if(find(x, y) != nullptr) {
            cout << "found" << " " << endl;
            (find(x, y))->data = data;
        }
        else {
            cout << "not found" << endl;
            Node<T> *newNode = new Node<T>(x, y, data);
            Node<T> *currentX = root->next;
            Node<T> *currentY = root->down;
            cout << "current x: " << currentX->x << endl;
            cout << "x: " << x << endl;
            while (currentX->x != x) {
                cout << "current x: " << currentX->x << endl;
                currentX = currentX->next;
            }
            cout << "current y: " << currentY->y << endl;
            cout << "y: " << y << endl;
            while (currentY->y != y) {
                currentY = currentY->down;
            }
            cout << "coordinates set" << endl;
            if (currentX->down == nullptr) {
                cout << "no nodes down" << endl;
                currentX->down = newNode;
            }
            else {
                cout << "nodes down: " << currentX->data << endl;
                while (currentX->y != y && currentX->down != nullptr) {
                    cout << currentX->y << " " << y << endl;
                    currentX = currentX->down;
                    cout << currentX->y << " " << y << endl;
                }
                cout << "moved" << endl;
                if (currentX->down == nullptr) {
                    currentX->down = newNode;
                } else {
                    Node<T> *currentDown = currentX->down;
                    currentX->down = newNode;
                    newNode->down = currentDown;
                }
            }
            if (currentY->next == nullptr) {
                currentY->next = newNode;
            }
            else {
                while (currentY->x != x && currentY->next != nullptr) {
                    currentY = currentY->next;
                }
                if (currentY->next == nullptr) {
                    currentY->next = newNode;
                } else {
                    Node<T> *currentNext = currentY->next;
                    currentY->next = newNode;
                    newNode->next = currentNext;
                }
            }
        }
        cout << "set complete" << endl;
};

    T operator()(int x, int y) const{
        Node<T>* tempNode = find(x, y);
        if(tempNode == nullptr){
            throw out_of_range("Node not found");
        }
        else{
            return tempNode->data;
        }
    };

    Matrix<T> operator*(T scalar) const{
        Matrix<T> m1(rows, columns);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if(find(i, j) != nullptr) {
                    cout << "multiplying" << endl;
                    cout << find(i, j)->data*scalar << endl;
                    m1.set(i, j, find(i, j)->data*scalar);
                }
            }
        }
        return m1;
    };
    Matrix<T> operator*(Matrix<T> other) const{
        Matrix<T> m1(rows, other.columns);
        for(int i = 0; i < other.columns; i++){
            for(int j = 0; j < rows; j++){
                float suma = 0;
                for(int k = 0; k < columns; k++)
                if(find(i, j) != nullptr && other.find(i, j) != nullptr) {
                    suma += find(j, k)->data*other.find(k, i)->data;
                }
                m1.set(i, j, suma);
            }
        }
        return m1;
    };
    Matrix<T> operator+(Matrix<T> other) const{
        Matrix<T> m1(rows, other.columns);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if(find(i, j) != nullptr && other.find(i, j) != nullptr) {
                    m1.set(i, j, find(i, j)->data + other.find(i, j)->data);
                }
            }
        }
        return m1;
    };
    Matrix<T> operator-(Matrix<T> other) const{
        Matrix<T> m1(rows, other.columns);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if(find(i, j) != nullptr && other.find(i, j) != nullptr) {
                    m1.set(i, j, find(i, j)->data - other.find(i, j)->data);
                }
            }
        }
        return m1;
    };
    Matrix<T> transpose() const{
        Matrix<T> m1(columns, rows);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if(find(i, j) != nullptr) {
                    m1.set(j, i, find(i, j)->data);
                }
            }
        }
        return m1;
    };

    void print() const{
        for(unsigned i = 0; i < rows; i++){
            for(unsigned j = 0; j < columns; j++) {
                if (find(i, j) != nullptr) {
                    cout << find(i, j)->data << " ";
                } else {
                    cout << "  ";
                }
            }
            cout << endl;
        }
    };

    //~Matrix();
};

#endif //SPARSE_MATRIX_MATRIX_H