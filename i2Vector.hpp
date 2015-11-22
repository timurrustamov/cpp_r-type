#ifndef I2VECTOR_HPP_
#define I2VECTOR_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>

#define D_PACE (1)

class i2Vector
{
public:
	//constructors
	i2Vector(); //initialize to 0
	i2Vector(const i2Vector &copy);
	i2Vector(const i2Vector *copy);
	i2Vector(int x, int y); //initialize to value
	i2Vector(int x, int y, const Impulse &impulse); //initialize from coords to direction
	i2Vector(const i2Vector &position, const Impulse &impulse); //initialize from coords to direction

	virtual ~i2Vector() {};

	void assignFromInt(int x, int y);
	void assignFromIntDirection(int x, int y, const Impulse &impulse);
	void assignFromVector(const i2Vector &position); //alias operator=
	void assignFromVectorDirection(const i2Vector &position, const Impulse &impulse);

	void addDirection(const Impulse &impulse);

	void setX(int x = 0);
	void setY(int y = 0);

	int getX() const;
	int getY() const;

	int &x();
	int &y();

	float distanceTo(const i2Vector &to) const;

	int inlineThis(int width, int height) const;
	std::string toString() const;

	static i2Vector convertFromImpulse(const Impulse &impulse);

	//operators
	i2Vector &operator=(const i2Vector &that);
	i2Vector &operator-=(const i2Vector &that);
	i2Vector &operator+=(const i2Vector &that);
	i2Vector &operator+=(const Impulse &impulse);
	i2Vector &operator*=(int);
	i2Vector &operator/=(int);
	i2Vector &operator*=(float);
	i2Vector &operator/=(float);
	
	i2Vector operator+(const i2Vector &that) const;
	i2Vector operator-(const i2Vector &that) const;
	i2Vector operator+(const Impulse &impulse) const;
	i2Vector operator*(int) const;
	i2Vector operator/(int) const;
	i2Vector operator*(float) const;
	i2Vector operator/(float) const;

	bool operator!() const;
	bool operator==(const i2Vector &that) const;
	bool operator!=(const i2Vector &that) const;
	bool operator<(const i2Vector &that) const;
	bool operator>(const i2Vector &that) const;
	bool operator<=(const i2Vector &that) const;
	bool operator>=(const i2Vector &that) const;

private:
	int _x;
	int _y;
};

std::ostream& operator<<(std::ostream& os, const i2Vector& that);

#endif