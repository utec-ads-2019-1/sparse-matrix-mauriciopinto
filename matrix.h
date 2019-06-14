#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include"node.h"
using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *root;
    unsigned rows, columns;

public:
    Matrix(unsigned rows, unsigned columns): root(nullptr), rows(rows), columns(columns){
        root = new Node<T>(-1, -1, -1);
        Node<T>* current1 = root;
        Node<T>* current2 = root;
        for(int i = 0; i < rows + 1; i++){
            Node<T>* newNode1 = new Node<T>(i, -1, i);
            Node<T>* newNode2 = new Node<T>(-1, i, i);
            current1->next = newNode1;
            current2->down = newNode2;
            current1 = current1->next;
            current2 = current2->down;
        }
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
        cout << "setting" << endl;
        if(find(x, y) != nullptr) {
            (find(x, y))->data = data;
        }
        else {
            cout << "hola" << endl;
            Node<T> *newNode = new Node<T>(x, y, data);
            Node<T> *currentX = root->next;
            Node<T> *currentY = root->down;
            while (currentX->x != x) {
                currentX = currentX->next;
            }
            while (currentY->y != y) {
                currentY = currentY->down;
            }
            if (currentX->down == nullptr) {
                currentX->down = newNode;
            } else {
                while (currentX->down->y < y) {
                    currentX = currentX->down;
                }
                if (currentX->down == nullptr) {
                    currentX->down = newNode;
                } else {
                    Node<T> *currentDown = currentX->down;
                    currentX->down = newNode;
                    newNode->down = currentDown;
                }
                if (currentY->next == nullptr) {
                    currentY->next = newNode;
                } else {
                    while (currentY->next->x < x) {
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
        }
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
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if(find(i, j) != nullptr && other.find(i, j) != nullptr) {
                    m1.set(i, j, find(i, j)->data * other.find(i, j)->data);
                }
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
        return *this;
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