#include "vector.h"
#include <ostream>

// Vector

template <typename T>
Vector<T>::Vector(int x): size(x) {
    if (x > 0) {
        p_mas = new T[x];
    } else p_mas = nullptr;
}

template <typename T>
Vector<T>::Vector(const Vector& v): size(v.size), p_mas(new T[v.size]) {
    for (int i = 0; i < size; i++) this->p_mas[i] = v.p_mas[i];
}

template <typename T>
Vector<T>::~Vector() {
    delete[] p_mas;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& v) {
    if (this == &v) return *this;

    delete[] p_mas;

    size = v.size;
    p_mas = new T[size];
    for (int i = 0; i < size; i++) this->p_mas[i] = v.p_mas[i];

    return *this;
}

template <typename T>
bool Vector<T>::operator==(const Vector& v) const {
    if (size != v.size) return false;
    
    for (int i = 0; i < size; i++) {
        if (this->p_mas[i] != v.p_mas[i]) return false;
    }

    return true;
}

template <typename T>
T& Vector<T>::operator[](int i) {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Index out of range");
    } else {
        return p_mas[i];
    } 
}

template <typename T>
T Vector<T>::operator[](int i) const {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Index out of range");
    } else {
        return p_mas[i];
    }
}

template <typename U>
std::ostream& operator<<(std::ostream& out, const Vector<U>& v) {
    for (int i = 0; i < v.size; i++) {
        out << v.p_mas[i] << ' ';
    }
    return out;
}

template <typename U>
std::istream& operator>>(std::istream& in, Vector<U>& v) {
    for (int i = 0; i < v.size; i++) {
        in >> v.p_mas[i];
    }
    return in;
}

template <typename T>
int Vector<T>::Get_size() const {
    return size;
}

// Set_Vectors
template <typename T>
Set_Vectors<T>::Set_Vectors(int d, int kol): kol(kol), set(new Vector<T>[kol]) {
    for (int i = 0; i < kol; i++) {
        set[i] = Vector<T>(d);
    }
}

template <typename T>
Set_Vectors<T>::Set_Vectors(const Set_Vectors& sv): kol(sv.kol), set(new Vector<T>[sv.kol]) {
    for (int i = 0; i < kol; i++) {
        set[i] = sv.set[i];
    }
}

template <typename T>
Set_Vectors<T>::~Set_Vectors() {
    if (set != nullptr) {
        delete[] set;
    }
}

template <typename T>
int Set_Vectors<T>::Get_d() const {
    if (kol == 0) {
        return 0;
    } else {
        return set[0].Get_size();
    }
}

template <typename T>
bool Set_Vectors<T>::Is_member(const Vector<T>& v) const {
    for (int i = 0; i < kol; i++) {
        if (set[i] == v) return true;
    }
    return false;
}

template <typename U>
std::istream& operator>>(std::istream& in, Set_Vectors<U>& sv) {
    for (int i = 0; i < sv.kol; i++) {
        in >> sv.set[i];
    }
    return in;
}

template <typename U>
std::ostream& operator<<(std::ostream& out, const Set_Vectors<U>& sv) {
    for (int i = 0; i < sv.kol; i++) {
        out << sv.set[i] << std::endl;
    }
    return out;
}

template <typename T>
Set_Vectors<T>& Set_Vectors<T>::operator+=(const Set_Vectors<T>& sv) {
    if (!Is_Equal_Dim(*this, sv)) {
        return *this;
    }

    for (int i = 0; i < sv.kol; i++) {
        if (!Is_member(sv.set[i])) {
            Add_Vector(sv.set[i]);
        }
    }

    return *this;
}

template <typename T>
int Set_Vectors<T>::Get_kol() const {
    return kol;
}

template <typename T>
bool Set_Vectors<T>::Is_Equal_Dim(const Set_Vectors<T>& sv1, const Set_Vectors<T>& sv2) {
    if (sv1.Get_d() != sv2.Get_d()) {
        return false;
    } else {
        return true;
    }
}

template <typename T>
void Set_Vectors<T>::Add_Vector(const Vector<T>& vect) {
    Vector<T>* new_set = new Vector<T>[kol + 1];

    for (int i = 0; i < kol; i++) {
        new_set[i] = set[i];
    }

    new_set[kol] = vect;

    delete[] set;
    set = new_set;
    kol++;
}

template <typename T>
Set_Vectors<T>& Set_Vectors<T>::operator=(const Set_Vectors<T>& sv) {
    if (this == &sv) return *this;

    Vector<T>* new_set = new Vector<T>[sv.kol];
    for (int i = 0; i < sv.kol; i++) {
        new_set[i] = sv.set[i];
    }

    delete[] set;
    set = new_set;
    kol = sv.kol;

    return *this;
}