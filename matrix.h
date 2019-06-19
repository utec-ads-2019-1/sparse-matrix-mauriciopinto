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

    void addNode(int x, int y, T data) const{
        if(find(x, y) != nullptr) {
            find(x, y)->data = data;
        }
        else {
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
            }
            else {
                while (currentX->y != y && currentX->down != nullptr) {
                    currentX = currentX->down;
                }
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
    }

    void remove(Node<T>* node)const{
        if(node != nullptr) {
            Node<T> *currentX = root->next;
            Node<T> *currentY = root->down;
            while (currentX->x != node->x) {
                currentX = currentX->next;
            }
            while (currentY->y != node->y) {
                currentY = currentY->down;
            }
            while (currentX->down != node) {
                currentX = currentX->down;
            }
            while (currentY->next != node) {
                currentY = currentY->next;
            }
            currentX->down = node->down;
            currentY->next = node->next;
            node = nullptr;
        }
        else{
            return;
        }
    }

    void set(int x, int y, T data) const{
        if(data != 0) {
            addNode(x, y, data);
        }
        else{
            remove(find(x, y));
        }
    };

    T operator()(int x, int y) const{
        Node<T>* tempNode = find(x, y);
        if(tempNode == nullptr){
            return 0;
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
                    m1.set(i, j, operator()(i, j)*scalar);
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
                    suma += operator()(j, k)*operator()(k, i);
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
                m1.set(i, j, operator()(i, j) + other.operator()(i, j));
            }
        }
        return m1;
    };
    Matrix<T> operator-(Matrix<T> other) const{
        Matrix<T> m1(rows, other.columns);
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                m1.set(i, j, operator()(i, j)- other.operator()(i, j));
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

    /*~Matrix(){
        for(int i = rows; i >= 0; i--){
            find(0, i)->killSelf();
        }
    };*/
};

#endif //SPARSE_MATRIX_MATRIX_H