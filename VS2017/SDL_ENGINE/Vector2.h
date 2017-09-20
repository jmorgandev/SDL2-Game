#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

//Vector2 template class
template <class TYPE> class Vector2 {
public:
	Vector2() : m_X(0), m_Y(0){}
	Vector2(TYPE x, TYPE y) : m_X(x), m_Y(y){}

	TYPE getX() { return m_X; }
	TYPE getY() { return m_Y; }

	void setX(TYPE x) { m_X = x; }
	void setY(TYPE y) { m_Y = y; }

	void modX(TYPE x) { m_X += x; }
	void modY(TYPE y) { m_Y += y; }

	void setZero() { m_X = 0; m_Y = 0; }

	TYPE length() { return sqrt(m_X * m_X + m_Y * m_Y); }

	TYPE distance(const Vector2& v2) {
		int xd = abs(v2.m_X) - abs(m_X);
		int yd = abs(v2.m_Y) - abs(m_Y);
		return sqrt(xd * xd + yd * yd);
	}

	void normalize() {
		TYPE l = length();
		if (l > 0) {
			m_X /= l;
			m_Y /= l;
		}
	}

	Vector2 operator+(const Vector2& v2) const {
		return Vector2(m_X + v2.m_X, m_Y + v2.m_X);
	}

	Vector2 operator-(const Vector2& v2) const {
		return Vector2(m_X - v2.m_X, m_Y - v2.m_Y);
	}
	Vector2 operator-() {
		Vector2 v;
		v.m_X = -m_X;
		v.m_Y = -m_Y;
		return v;
	}

	Vector2& operator+=(const Vector2& v2) {
		m_X += v2.m_X;
		m_Y += v2.m_Y;

		return *this;
	}

	Vector2& operator-=(const Vector2& v2) {
		m_X -= v2.m_X;
		m_Y -= v2.m_Y;

		return *this;
	}

	Vector2 operator*(TYPE scalar) {
		return Vector2(m_X * scalar, m_Y * scalar);
	}

	Vector2 operator/(TYPE scalar) {
		return Vector2(m_X / scalar, m_Y / scalar);
	}

	Vector2 operator*=(TYPE scalar) {
		m_X *= scalar;
		m_Y *= scalar;

		return *this;
	}

	Vector2& operator/=(TYPE scalar) {
		m_X /= scalar;
		m_Y /= scalar;

		return *this;
	}

private:
	TYPE m_X, m_Y;
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

#endif