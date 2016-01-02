//
// Created by rustam_t on 12/2/15.
//

#ifndef CPP_R_TYPE_RECTANGLE_HPP
#define CPP_R_TYPE_RECTANGLE_HPP

#include <cstddef>
#include "t2Vector.hpp"

template <typename T>
class Rectangle {

public:

    Rectangle() {};
    Rectangle(t2Vector<T> size, t2Vector<T> position) : _size(size), _position(position) {};

    Rectangle(T sizeX, T sizeY, T posX, T posY)
    {
        this->_size.assign(sizeX, sizeY);
        this->_position.assign(posX, posY);
    };

    template <typename U>
    Rectangle(const Rectangle<U> &copy)
    {
        this->_size = copy.getSize();
        this->_position = copy.getPosition();
    }

    ~Rectangle() {};

    template <typename U>
    Rectangle &operator=(const Rectangle<U> &copy)
    {
        this->_size = copy.getSize();
        this->_position = copy.getPosition();
        return (*this);
    }

    t2Vector<T> &size()
    {
        return (this->_size);
    };

    t2Vector<T> &position()
    {
        return (this->_position);
    };

    const t2Vector<T> &getSize() const
    {
        return (this->_size);
    };
    const t2Vector<T> &getPosition() const
    {
        return (this->_position);
    };

    Rectangle &setSize(const t2Vector<T> size)
    {
        this->_size = size;
        return (*this);
    };
    Rectangle &setPosition(const t2Vector<T> position)
    {
        this->_position = position;
        return (*this);
    };

    T getLeftBoundry() const
    {
        return (this->_position.getX() - (this->getSize().getX() / 2));
    }

    T getRightBoundry() const
    {
        return (this->_position.getX() + (this->getSize().getX() / 2));
    }

    T getUpperBoundry() const
    {
        return (this->_position.getY() + (this->getSize().getY() / 2));
    }

    T getLowerBoundry() const
    {
        return (this->_position.getY() - (this->getSize().getY() / 2));
    }

    template <typename U>
    bool    fitsIn(const Rectangle<U> &that) const
    {
        return (this->getSize() <= that.getSize() &&
                static_cast<T>(that.getUpperBoundry()) >= this->getUpperBoundry() &&
                static_cast<T>(that.getLowerBoundry()) <= this->getLowerBoundry() &&
                static_cast<T>(that.getLeftBoundry()) <= this->getLeftBoundry() &&
                static_cast<T>(that.getRightBoundry()) >= this->getRightBoundry());
    }

    template <typename U>
    bool    touches(const Rectangle<U> &that) const
    {
        return ((static_cast<T>(that.getUpperBoundry()) > this->getLowerBoundry() &&
                  static_cast<T>(that.getLowerBoundry()) < this->getUpperBoundry() &&
                  static_cast<T>(that.getLeftBoundry()) < this->getRightBoundry() &&
                  static_cast<T>(that.getRightBoundry()) > this->getLeftBoundry()));
    }

    template <typename U>
    bool    touchUpper(const Rectangle<U> &that) const
    {
        return (this->getLowerBoundry() < that.getUpperBoundry() && this->getLowerBoundry() > that.getLowerBoundry() &&
                !(this->getUpperBoundry() > that.getLowerBoundry() && this->getUpperBoundry() < that.getUpperBoundry()));
    }

    template <typename U>
    bool    touchLower(const Rectangle<U> &that) const
    {
        return (this->getUpperBoundry() > that.getLowerBoundry() && this->getUpperBoundry() < that.getUpperBoundry() &&
                 !(this->getLowerBoundry() < that.getUpperBoundry() && this->getLowerBoundry() > that.getLowerBoundry()));
    }

    template <typename U>
    bool    touchRight(const Rectangle<U> &that) const
    {
        return (this->getLeftBoundry() < that.getRightBoundry() && this->getLeftBoundry() > that.getLeftBoundry() &&
                !(this->getRightBoundry() > that.getLeftBoundry() && this->getRightBoundry() < that.getRightBoundry()));
    }

    template <typename U>
    bool    touchLeft(const Rectangle<U> &that) const
    {
        return (this->getRightBoundry() > that.getLeftBoundry() && this->getRightBoundry() < that.getRightBoundry() &&
                !(this->getLeftBoundry() > that.getLeftBoundry() && this->getLeftBoundry() < that.getRightBoundry()));
    }

private:
    t2Vector<T> _size;
    t2Vector<T> _position;
};


#endif //CPP_R_TYPE_RECTANGLE_HPP
