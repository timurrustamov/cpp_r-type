//
// Created by rustam_t on 11/24/15.
//

#ifndef CPP_R_TYPE_T2VECTOR_HPP
#define CPP_R_TYPE_T2VECTOR_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>

template <typename T>
class t2Vector {

public:
    t2Vector()
    {
        this->_x = 0;
        this->_y = 0;
    };

    template <typename U>
    t2Vector(const t2Vector<U> &copy)
    {
        this->_x = static_cast<T>(copy.getX());
        this->_y = static_cast<T>(copy.getY());
    }

    template <typename U>
    t2Vector(const t2Vector<U> *copy)
    {
        this->_x = static_cast<T>(copy->getX());
        this->_y = static_cast<T>(copy->getY());
    }

    t2Vector(T x, T y)
    {
        this->_x = x;
        this->_y = y;
    }

	virtual ~t2Vector() {};

	t2Vector &assign(T x, T y)
    {
        this->_x = x;
        this->_y = y;
        return (*this);
    }

    template <typename U>
	t2Vector &assign(const t2Vector &copy)
    {
        this->_x = static_cast<T>(copy.getX());
        this->_y = static_cast<T>(copy.getY());
        return (*this);
    }

    template <typename U>
    t2Vector &assign(const t2Vector *copy)
    {
        this->_x = static_cast<T>(copy->getX());
        this->_y = static_cast<T>(copy->getY());
        return (*this);
    }

	t2Vector &setX(T x = 0)
    {
        this->_x = x;
        return (*this);
    }

	t2Vector &setY(T y = 0)
    {
        this->_y = y;
        return (*this);
    }

	T getX() const
    {
        return (this->_x);
    }

	T getY() const
    {
        return (this->_y);
    }

	T &x()
    {
        return (this->_x);
    }

	T &y()
    {
        return (this->_y);
    }


	float distanceTo(const t2Vector &to) const
    {
        return std::sqrt(std::pow(static_cast<double>(this->getX() - to.getX()), 2) +
                                 std::pow(static_cast<double>(this->getY() - to.getY()), 2));
    }

	int inlineThis(int width, int height) const
    {
        int 	res;

        if ((res = static_cast<int>(this->_y) * width + static_cast<int>(this->_x)) >= width * height || res < 0)
            return (-1);
        return (res);
    }

	std::string toString() const
    {
        std::ostringstream convert;

        convert << "X : " << this->_x << " Y: " << this->_y;
        return (convert.str());
    }

    float length() const
    {
        return (sqrtf(static_cast<float>(this->_x) * static_cast<float>(this->_x) +
                                    static_cast<float>(this->_y) * static_cast<float>(this->_y)));
    };

    t2Vector<T> toAbsolute() const
    {
        t2Vector<T> vec((this->getX() > 0 ? this->getX() : -this->getX()),
                        (this->getY() > 0 ? this->getY() : -this->getY()));
        return (vec);
    }

    t2Vector<T> normalize() const
    {
        float length = this->length();
        t2Vector<T> vec(this->_x / length, this->_y / length);

        return (vec);
    }

    template <typename U>
    t2Vector<U> convert() const
    {
        t2Vector<U> v = t2Vector(static_cast<U>(this->getX()), static_cast<U>(this->getY()));
        return (v);
    };

	//operators
    template <typename U>
	t2Vector &operator=(const t2Vector<U> &that)
    {
        this->_x = static_cast<T>(that.getX());
        this->_y = static_cast<T>(that.getY());
        return (*this);
    }

    template <typename U>
	t2Vector &operator-=(const t2Vector<U> &that)
    {
        this->_x = this->getX() - static_cast<T>(that.getX());
        this->_y = this->getY() - static_cast<T>(that.getY());
        return (*this);
    }

    template <typename U>
	t2Vector &operator+=(const t2Vector<U> &that)
    {
        this->_x = this->getX() + static_cast<T>(that.getX());
        this->_y = this->getY() + static_cast<T>(that.getY());
        return (*this);
    }

    template <typename U>
	t2Vector &operator*=(U var)
    {
        U tmpx = static_cast<U>(this->getX()) * var;
        U tmpy = static_cast<U>(this->getY()) * var;
        this->_x = static_cast<T>(tmpx);
        this->_y = static_cast<T>(tmpy);
        return (*this);
    }

    template <typename U>
	t2Vector &operator/=(U var)
    {
        U tmpx = static_cast<U>(this->getX()) / var;
        U tmpy = static_cast<U>(this->getY()) / var;
        this->_x = static_cast<T>(tmpx);
        this->_y = static_cast<T>(tmpy);
        return (*this);
    }

    template <typename U>
	t2Vector operator+(const t2Vector<U> &that) const
    {
        T x = this->_x + static_cast<T>(that.getX());
        T y = this->_y + static_cast<T>(that.getY());

        t2Vector<T> v(x, y);
        return (v);
    }

    template <typename U>
	t2Vector operator-(const t2Vector<U> &that) const
    {
        T x = this->_x - static_cast<T>(that.getX());
        T y = this->_y - static_cast<T>(that.getY());

        t2Vector<T> v(x, y);
        return (v);
    }

    template <typename U>
	t2Vector operator*(U var) const
    {
        U tmpx = static_cast<U>(this->getX()) * var;
        U tmpy = static_cast<U>(this->getY()) * var;

        t2Vector<T> v(static_cast<T>(tmpx), static_cast<T>(tmpy));
        return (v);
    }

    template <typename U>
	t2Vector operator/(U var) const
    {
        U tmpx = static_cast<U>(this->getX()) / var;
        U tmpy = static_cast<U>(this->getY()) / var;

        t2Vector<T> v(static_cast<T>(tmpx), static_cast<T>(tmpy));
        return (v);
    }

	bool operator!() const
    {
        t2Vector<int> v = t2Vector(0,0);
        return (*this >= v);
    }

    template <typename U>
	bool operator==(const t2Vector<U> &that) const
    {
        return (this->getX() == static_cast<T>(that.getX()) &&
                this->getY() == static_cast<T>(that.getY()));
    }

    template <typename U>
	bool operator!=(const t2Vector<U> &that) const
    {
        return (!(*this == that));
    }

    template <typename U>
    bool operator<(const t2Vector<U> &that) const
    {
        return (this->getX() < static_cast<T>(that.getX()) &&
                this->getY() < static_cast<T>(that.getY()));
    }

    template <typename U>
    bool operator>(const t2Vector<U> &that) const
    {
        return (this->getX() > static_cast<T>(that.getX()) &&
                this->getY() > static_cast<T>(that.getY()));
    }

    template <typename U>
    bool operator<=(const t2Vector<U> &that) const
    {
        return (this->getX() <= static_cast<T>(that.getX()) &&
                this->getY() <= static_cast<T>(that.getY()));
    }

    template <typename U>
    bool operator>=(const t2Vector<U> &that) const
    {
        return (this->getX() >= static_cast<T>(that.getX()) &&
                this->getY() >= static_cast<T>(that.getY()));
    }

private:
    T _x;
    T _y;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const t2Vector<T>& that)
{
    os << that.toString();
    return (os);
}


#endif //CPP_R_TYPE_T2VECTOR_HPP
