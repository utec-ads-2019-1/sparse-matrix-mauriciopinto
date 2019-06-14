#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    Node<T> *next, *down;
    int x, y;
    T data;
public:
    explicit Node(int x, int y, T data) : next(nullptr), down(nullptr), x(x), y(y), data(data){};

    friend class Matrix<T>;
};

#endif //SPARSE_MATRIX_NODE_H
