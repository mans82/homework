#pragma once

namespace containers {
    template <typename T>
    class Vector {
    private:
        const static int INIT_CAPACITY = 2;

        T* elems;
        int _size = 0;
        int alloc;

        void doubleCapacity();
    public:
        Vector();
        Vector(Vector<T>&); // Copy constructor
        Vector<T>& operator=(const Vector<T>&); // Copy assignment
        Vector(Vector<T>&&); // Move constructor
        Vector<T>& operator=(Vector<T>&&); // Move assignment
        void pushBack(T elem);
        T& operator[](const int i);
        int size();
        ~Vector();
    };
}

// Implementation for template classes
namespace containers {
    template <typename T>
    Vector<T>::Vector():
        elems {new T[INIT_CAPACITY]},
        alloc {INIT_CAPACITY} {}

    template <typename T>
    Vector<T>::Vector(Vector<T>& v):
        elems {new T[v.alloc]},
        alloc {v.alloc},
        _size {v._size}
    {
        for (int i = 0; i < v.size(); i++) {
            this->elems[i] = v->elems[i];
        }
    }

    template <typename T>
    Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
        delete[] elems;
        elems = new T[v.alloc];
        this->alloc = v.alloc;
        this->_size = v._size;

        for (int i = 0; i < v.size(); i++) {
            this->elems[i] = v.elems[i];
        }

        return *this;
    }

    template <typename T>
    Vector<T>::Vector(Vector<T>&& v):
        elems {v.elems},
        alloc {v.alloc},
        _size {v._size}
    {
        v.elems = nullptr;
        v.alloc = 0;
        v._size = 0;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator=(Vector<T>&& v) {
        this->elems = v.elems;
        this->_size = v._size;
        this->alloc = v.alloc;

        v.elems = nullptr;
        v.alloc = 0;
        v._size = 0;

        return *this;
    }

    template <typename T>
    void Vector<T>::pushBack(T elem) {
        if (_size == alloc) doubleCapacity();
        elems[_size++] = elem;
    }

    template <typename T>
    T& Vector<T>::operator[](const int i) {
        return elems[i];
    }

    template <typename T>
    void Vector<T>::doubleCapacity() {
        int new_alloc = alloc * 2;
        T* new_elems = new T[new_alloc];

        for (int i = 0; i < _size; i++) {
            new_elems[i] = elems[i];
        }

        this->alloc = new_alloc;
        this->elems = new_elems;
    }

    template <typename T>
    int Vector<T>::size() {
        return _size;
    }

    template <typename T>
    Vector<T>::~Vector() {
        delete[] this->elems;
    }
}