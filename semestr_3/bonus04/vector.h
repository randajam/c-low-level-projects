#pragma once
#include <iostream>

template <typename T>
class Vector {
private:
    int size;
    T *data;
public:
    Vector();
    Vector(int size);
    Vector(int size, const T* data);
    Vector(const Vector& other);
    
    ~Vector();

    Vector& operator=(const Vector& other);
    Vector operator+(const Vector& other) const;
    Vector operator*(const Vector& other) const;
    T& operator[](int i);
    T operator[](int i) const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, const Vector<U>& v);

    template<typename U>
    friend std::istream& operator>>(std::istream& in, Vector<U>& v);
};

template<typename T>
Vector<T>::Vector(): size(0), data(nullptr) {}

template<typename T>
Vector<T>::Vector(int size): size(size), data(new T[size]()) {}

template<typename T>
Vector<T>::Vector(int size, const T* data): size(size), data(new T[size]()) {
    for(int i = 0; i < size; i++) this->data[i] = data[i];
}

template<typename T>
Vector<T>::Vector(const Vector& other): size(other.size), data(new T[other.size]()) {
    for(int i = 0; i < size; i++) this->data[i] = other.data[i];
}

template<typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this == &other) return *this;

    delete[] data;
    
    size = other.size;
    data = new T[size];

    for(int i = 0; i < size; i++) 
        data[i] = other.data[i];

    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector& other) const {
    int max_size = std::max(size, other.size);
    Vector<T> result(max_size);

    for(int i = 0; i < max_size; i++) {
        if (i < size && i < other.size) 
            result.data[i] = data[i] + other.data[i];
        else if (i < size) 
            result.data[i] = data[i];
        else 
            result.data[i] = other.data[i];
    }

    return result;
}

template<typename T>
Vector<T> Vector<T>::operator*(const Vector& other) const {
    int max_size = std::max(size, other.size);
    Vector<T> result(max_size);

    for(int i = 0; i < max_size; i++) {
        if (i < size && i < other.size) 
            result.data[i] = data[i] * other.data[i];
        else 
            result.data[i] = T();
    }

    return result;
}

template<typename T>
T& Vector<T>::operator[](int i) {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Index out of range");
    } else {
        return data[i];
    }
}

template<typename T>
T Vector<T>::operator[](int i) const {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Index out of range");
    } else {
        return data[i];
    }
}

template<typename U>
std::ostream& operator<<(std::ostream& out, const Vector<U>& v) {
    for (int i = 0; i < v.size; i++) {
        out << v.data[i] << std::endl;
    }
    return out;
}

template<typename U>
std::istream& operator>>(std::istream& in, Vector<U>& v) {
    for (int i = 0; i < v.size; i++) {
        in >> v.data[i];
    }
    return in;
}