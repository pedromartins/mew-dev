// Copyright (C) 2009 Hok Shun Poon

#ifndef _MEW_Vector2d_H
#define _MEW_Vector2d_H


namespace mew
{
namespace core
{


template <class T>
class Vector2d
{
public:
	//! Default constructor (null vector)
	Vector2d() : X(0), Y(0) {}
	//! Constructor with two different values
	Vector2d(T nx, T ny) : X(nx), Y(ny) {}
	//! Constructor with the same value for both members
	explicit Vector2d(T n) : X(n), Y(n) {}
	//! Copy constructor
	Vector2d(const Vector2d<T>& other) : X(other.X), Y(other.Y) {}

	// operators

	Vector2d<T> operator-() const { return Vector2d<T>(-X, -Y); }

	Vector2d<T>& operator=(const Vector2d<T>& other) { X = other.X; Y = other.Y; return *this; }

	Vector2d<T> operator+(const Vector2d<T>& other) const { return Vector2d<T>(X + other.X, Y + other.Y); }
	Vector2d<T>& operator+=(const Vector2d<T>& other) { X+=other.X; Y+=other.Y; return *this; }
	Vector2d<T> operator+(const T v) const { return Vector2d<T>(X + v, Y + v); }
	Vector2d<T>& operator+=(const T v) { X+=v; Y+=v; return *this; }

	Vector2d<T> operator-(const Vector2d<T>& other) const { return Vector2d<T>(X - other.X, Y - other.Y); }
	Vector2d<T>& operator-=(const Vector2d<T>& other) { X-=other.X; Y-=other.Y; return *this; }
	Vector2d<T> operator-(const T v) const { return Vector2d<T>(X - v, Y - v); }
	Vector2d<T>& operator-=(const T v) { X-=v; Y-=v; return *this; }

	Vector2d<T> operator*(const Vector2d<T>& other) const { return Vector2d<T>(X * other.X, Y * other.Y); }
	Vector2d<T>& operator*=(const Vector2d<T>& other) { X*=other.X; Y*=other.Y; return *this; }
	Vector2d<T> operator*(const T v) const { return Vector2d<T>(X * v, Y * v); }
	Vector2d<T>& operator*=(const T v) { X*=v; Y*=v; return *this; }

	Vector2d<T> operator/(const Vector2d<T>& other) const { return Vector2d<T>(X / other.X, Y / other.Y); }
	Vector2d<T>& operator/=(const Vector2d<T>& other) { X/=other.X; Y/=other.Y; return *this; }
	Vector2d<T> operator/(const T v) const { return Vector2d<T>(X / v, Y / v); }
	Vector2d<T>& operator/=(const T v) { X/=v; Y/=v; return *this; }

	bool operator<=(const Vector2d<T>&other) const { return X<=other.X && Y<=other.Y; }
	bool operator>=(const Vector2d<T>&other) const { return X>=other.X && Y>=other.Y; }

	bool operator<(const Vector2d<T>&other) const { return X<other.X && Y<other.Y; }
	bool operator>(const Vector2d<T>&other) const { return X>other.X && Y>other.Y; }

	bool operator==(const Vector2d<T>& other) const { return equals(other); }
	bool operator!=(const Vector2d<T>& other) const { return !equals(other); }

	// functions

	//! Checks if this vector equals the other one.
	/** Takes floating point rounding errors into account.
	\param other Vector to compare with.
	\return True if the two vector are (almost) equal, else false. */
	bool equals(const Vector2d<T>& other) const
	{
		return core::equals(X, other.X) && core::equals(Y, other.Y);
	}

	//! X coordinate of vector.
	T X;
	//! Y coordinate of vector.
	T Y;
};

	//! Typedef for f32 2d vector.
	typedef Vector2d<f32> Vector2df;
	//! Typedef for integer 2d vector.
	typedef Vector2d<s32> Vector2di;

	template<class S, class T>
	Vector2d<T> operator*(const S scalar, const Vector2d<T>& vector) { return vector*scalar; }

} // end namespace core
} // end namespace mew

#endif

