#include "i2Vector.hpp"

i2Vector::i2Vector()
{
	this->_x = 0;
	this->_y = 0;
}

i2Vector::i2Vector(int x, int y)
{
	this->_x = x;
	this->_y = y;
}

i2Vector::i2Vector(const i2Vector &copy)
{
	this->_x = copy.getX();
	this->_y = copy.getY();
}

i2Vector::i2Vector(const i2Vector *copy)
{
	this->_x = copy->getX();
	this->_y = copy->getY();
}

i2Vector::i2Vector(Direction::Value direction, int pace)
{
	*this = i2Vector::convertFromDirection(direction) * pace; 
}

i2Vector::i2Vector(int x, int y, Direction::Value direction, int pace)
{
	this->_x = x;
	this->_y = y;
	*this += i2Vector::convertFromDirection(direction) * pace;
}

i2Vector::i2Vector(const i2Vector &position, Direction::Value direction, int pace)
{
	this->_x = position.getX();
	this->_y = position.getY();
	*this += i2Vector::convertFromDirection(direction) * pace;
}

void
i2Vector::assignFromInt(int x, int y)
{
	this->_x = x;
	this->_y = y;
}

void
i2Vector::assignFromIntDirection(int x, int y, Direction::Value direction, int pace)
{
	this->_x = x;
	this->_y = y;
	*this += i2Vector::convertFromDirection(direction) * pace;
}

void
i2Vector::assignFromVector(const i2Vector &position)
{
	this->_x = position.getX();
	this->_y = position.getY();
}

void
i2Vector::assignFromVectorDirection(const i2Vector &position, Direction::Value direction, int pace)
{
	this->_x = position.getX();
	this->_y = position.getY();
	*this += i2Vector::convertFromDirection(direction) * pace;
}

void
i2Vector::addDirection(Direction::Value direction, int pace)
{
	*this += i2Vector::convertFromDirection(direction) * pace;
}

void
i2Vector::setX(int x)
{
	this->_x = x;
}

void
i2Vector::setY(int y)
{
	this->_y = y;
}

int
i2Vector::getX() const
{
	return (this->_x);
}

int
i2Vector::getY() const
{
	return (this->_y);
}

int &
i2Vector::x()
{
	return (this->_x);
}

int &
i2Vector::y()
{
	return (this->_y);
}

float
i2Vector::distanceTo(const i2Vector &to) const
{
	return std::sqrt(std::pow((this->getX() - to.getX()), 2) + std::pow((this->getY() - to.getY()), 2));
}

int
i2Vector::inlineThis(int width, int height) const
{
	int 	res;

	if ((res = this->_y * width + this->_x) >= width * height || res < 0)
		return (-1);
	return (res);
}

std::string
i2Vector::toString() const
{
	std::ostringstream convert;

	convert << "X : " << this->_x << " Y: " << this->_y;
	return (convert.str());
}

i2Vector
i2Vector::convertFromImpulse(const Impulse &impulse)
{
	//
}

i2Vector &
i2Vector::operator=(const i2Vector &that)
{
	this->_x = that.getX();
	this->_y = that.getY();
	return (*this);
}

i2Vector &
i2Vector::operator-=(const i2Vector &that)
{
	this->_x -= that.getX();
	this->_y -= that.getY();
	return (*this);
}

i2Vector &
i2Vector::operator+=(const i2Vector &that)
{
	this->_x += that.getX();
	this->_y += that.getY();
	return (*this);
}

i2Vector &
i2Vector::operator*=(int scale)
{
	this->_x *= scale;
	this->_y *= scale;
	return (*this);
}

i2Vector &
i2Vector::operator/=(int scale)
{
	this->_x /= scale;
	this->_y /= scale;
	return (*this);
}

i2Vector &
i2Vector::operator*=(float scale)
{
	this->_x *= scale;
	this->_y *= scale;
	return (*this);
}

i2Vector &
i2Vector::operator/=(float scale)
{
	this->_x /= scale;
	this->_y /= scale;
	return (*this);
}

i2Vector
i2Vector::operator+(const i2Vector &that) const
{
	return (i2Vector(this->_x + that.getX(), this->_y + that.getY()));
}

i2Vector
i2Vector::operator-(const i2Vector &that) const
{
	return (i2Vector(this->_x - that.getX(), this->_y - that.getY()));
}

i2Vector
i2Vector::operator*(int scale) const
{
	return (i2Vector(this->_x * scale, this->_y * scale));
}

i2Vector
i2Vector::operator/(int scale) const
{
	return (i2Vector(this->_x / scale, this->_y / scale));
}

i2Vector
i2Vector::operator*(float scale) const
{
	return (i2Vector(this->_x * scale, this->_y * scale));
}

i2Vector
i2Vector::operator/(float scale) const
{
	return (i2Vector(this->_x / scale, this->_y / scale));
}

bool
i2Vector::operator!() const
{
	return (this->_x < 0 || this->_y < 0);
}

bool
i2Vector::operator==(const i2Vector &that) const
{
	return (this->_x == that.getX() && this->_y == that.getY());
}

bool
i2Vector::operator!=(const i2Vector &that) const
{
	return (!(*this == that));
}

bool
i2Vector::operator>(const i2Vector &that) const
{
	return (this->_x > that.getX() && this->_y > that.getY());
}

bool
i2Vector::operator<(const i2Vector &that) const
{
	return (this->_x < that.getX() && this->_y < that.getY());
}

bool
i2Vector::operator>=(const i2Vector &that) const
{
	return (this->_x >= that.getX() && this->_y >= that.getY());
}

bool
i2Vector::operator<=(const i2Vector &that) const
{
	return (this->_x <= that.getX() && this->_y <= that.getY());
}

std::ostream& operator<<(std::ostream& os, const i2Vector& that)
{
	os << that.toString();
	return (os);
}