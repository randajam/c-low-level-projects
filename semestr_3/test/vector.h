#pragma once
#include <ostream>

template <typename T>
class Vector {
private: 
    int size;
    T* p_mas;
public:
    Vector(int x = 0);
    Vector(const Vector& v);
    ~Vector();

    Vector& operator=(const Vector& vect);
    bool operator==(const Vector& vect) const;
    T& operator[](int i);
    T operator[](int i) const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, const Vector<U>& v);

    template<typename U>
    friend std::istream& operator>>(std::istream& in, Vector<U>& v);

    int Get_size() const;
};

template<typename T>
class Set_Vectors{
private:
    int kol;
    Vector<T>* set;
public:
    Set_Vectors(int d = 0, int kol = 0);
    Set_Vectors(const Set_Vectors& sv);
    ~Set_Vectors();

    int Get_d() const;
    bool Is_member(const Vector<T>& vect) const;

    template <typename U>
    friend std::istream& operator>>(std::istream& in, Set_Vectors<U>& sv);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Set_Vectors<U>& sv);

    Set_Vectors& operator+=(const Set_Vectors& sv);
    Set_Vectors& operator=(const Set_Vectors& sv);

    int Get_kol() const;
    bool Is_Equal_Dim(const Set_Vectors& sv1, const Set_Vectors& sv2);
    void Add_Vector(const Vector<T>& vect);
};