// Copyright (C) 2009 Hok Shun Poon

// Defines a 2-D vector type.

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <math.h>
#include <ostream>

/**
 * Holds a vector in 2 dimensions. This class has a whole series
 * of methods used to manipulate the vector.
 *
 * Four T data members are allocated for the vector. When you
 * are working with single precision floating point values on a
 * PC, for example, having four members allocated allows the
 * Vector to site on a 16-byte alignment boundary, for improved
 * memory performance. If you are using other types of T value
 * (IEEE extended precision floats, for example), then it makes no
 * sense to have this pad value here, so it can be safely removed.
 *
 * @note This class contains a lot of inline methods for basic
 * mathematics. The implementations are included in the header
 * file so that an intelligent compiler will inline them into the
 * compiled code.
 */
template <typename T>
class Vector2d {
public:
     /** Holds the value along the x axis. */
    T x;

    /** Holds the value along the y axis. */
    T y;

private:
    /** Padding to ensure 4 word alignment. */
    T _pad;

public:
    /** The default constructor creates a zero vector. */
    Vector2d<T>() : x(0), y(0) {}

    /**
     * @name Default Directions
     *
     * This is a series of convenience unit-vectors for each of
     * the six cardinal directions in a standard right-handed
     * coordinate system. This assumes, as in the vast majority of
     * games that the plane of the screen is in the X,Y plane,
     * with the Y axis pointing up and the X axis pointing right.
     */
    /* @{ */
    const static Vector2d<T> UP;
    const static Vector2d<T> RIGHT;
    const static Vector2d<T> OUT_OF_SCREEN;
    const static Vector2d<T> DOWN;
    const static Vector2d<T> LEFT;
    const static Vector2d<T> INTO_SCREEN;
    /* @} */

    /**
     * @name Basis Directions
     *
     * These are convenience unit-vectors in the basis directions.
     */
    /* @{ */
    const static Vector2d<T> X;
    const static Vector2d<T> Y;
    /* @} */

    /** A zero length vector. */
    const static Vector2d<T> ZERO;


    /**
     * The explicit constructor creates a vector with the given
     * components.
     */
    Vector2d<T>(const T x, const T y)
        : x(x), y(y) {}

    /** Creates a vector between the given two points. */
    Vector2d<T>(const Vector2d<T>& from, const Vector2d<T>& to)
    {
        x = to.x - from.x;
        y = to.y - from.y;
    }

    /** Adds the given vector to this. */
    void operator+=(const Vector2d<T>& v)
    {
        x += v.x;
        y += v.y;
    }

    /**
     * Returns the value of the given vector added to this.
     */
    Vector2d<T> operator+(const Vector2d<T>& v) const
    {
        return Vector2d<T>(x+v.x, y+v.y);
    }

    /** Subtracts the given vector from this. */
    void operator-=(const Vector2d<T>& v)
    {
        x -= v.x;
        y -= v.y;
    }

    /**
     * Returns the value of the given vector subtracted from this.
     */
    Vector2d<T> operator-(const Vector2d<T>& v) const
    {
        return Vector2d<T>(x-v.x, y-v.y);
    }

    /** Multiplies this vector by the given scalar. */
    void operator*=(const T value)
    {
        x *= value;
        y *= value;
    }

    /** Returns a copy of this vector scaled the given value. */
    Vector2d<T> operator*(const T value) const
    {
        return Vector2d<T>(x*value, y*value);
    }

    /** Checks if the two vectors have identical components. */
    bool operator==(const Vector2d<T>& other) const
    {
        return x == other.x &&
            y == other.y;
    }

    /** Checks if the two vectors have non-identical components. */
    bool operator!=(const Vector2d<T>& other) const
    {
        return !(*this == other);
    }

    /**
     * Checks if this vector is component-by-component less than
     * the other.
     *
     * @note This does not behave like a single-value comparison:
     * !(a < b) does not imply (b >= a).
     */
    bool operator<(const Vector2d<T>& other) const
    {
        return x < other.x && y < other.y;
    }

    /**
     * Checks if this vector is component-by-component less than
     * the other.
     *
     * @note This does not behave like a single-value comparison:
     * !(a < b) does not imply (b >= a).
     */
    bool operator>(const Vector2d<T>& other) const
    {
        return x > other.x && y > other.y;
    }

    /**
     * Checks if this vector is component-by-component less than
     * the other.
     *
     * @note This does not behave like a single-value comparison:
     * !(a <= b) does not imply (b > a).
     */
    bool operator<=(const Vector2d<T>& other) const
    {
        return x <= other.x && y <= other.y;
    }

    /**
     * Checks if this vector is component-by-component less than
     * the other.
     *
     * @note This does not behave like a single-value comparison:
     * !(a <= b) does not imply (b > a).
     */
    bool operator>=(const Vector2d<T>& other) const
    {
        return x >= other.x && y >= other.y;
    }

    /**
     * Calculates and returns a component-wise product of this
     * vector with the given vector.
     */
    Vector2d<T> componentProduct(const Vector2d<T> &vector) const
    {
        return Vector2d<T>(x * vector.x, y * vector.y);
    }

    /**
     * Performs a component-wise product with the given vector and
     * sets this vector to its result.
     */
    void componentProductUpdate(const Vector2d<T> &vector)
    {
        x *= vector.x;
        y *= vector.y;
    }

    /**
     * Calculates and returns the vector product of this vector
     * with the given vector.
     */
//    Vector2d<T> vectorProduct(const Vector2d<T> &vector) const
//    {
//        return Vector2d<T>(y*vector.z-z*vector.y,
//                       z*vector.x-x*vector.z,
//                       x*vector.y-y*vector.x);
//    }

    /**
     * Updates this vector to be the vector product of its current
     * value and the given vector.
     */
    void operator %=(const Vector2d<T> &vector)
    {
        *this = vectorProduct(vector);
    }

    /**
     * Calculates and returns the vector product of this vector
     * with the given vector.
     */
//    Vector2d<T> operator%(const Vector2d<T> &vector) const
//    {
//        return Vector2d<T>(y*vector.z-z*vector.y,
//                       z*vector.x-x*vector.z,
//                       x*vector.y-y*vector.x);
//    }

    /**
     * Calculates and returns the scalar product of this vector
     * with the given vector.
     */
    T scalarProduct(const Vector2d<T> &vector) const
    {
        return x*vector.x + y*vector.y;
    }

    /**
     * Calculates and returns the scalar product of this vector
     * with the given vector.
     */
    T operator*(const Vector2d<T> &vector) const
    {
        return x*vector.x + y*vector.y;
    }

    /**
     * Adds the given vector to this, scaled by the given amount.
     */
    void addScaledVector(const Vector2d<T>& vector, T scale)
    {
        x += vector.x * scale;
        y += vector.y * scale;
    }

    /** Gets the magnitude of this vector. */
    T magnitude() const
    {
        return sqrt(x*x+y*y);
    }

    /** Gets the squared magnitude of this vector. */
    T squareMagnitude() const
    {
        return x*x+y*y;
    }

    /** Turns a non-zero vector into a vector of unit length. */
    void normalize()
    {
        T l = magnitude();
        if (l > 0)
        {
            (*this) *= ((T)1)/l;
        }
    }

	/** Returns a unit vector in the direction of this vector. */
	Vector2d<T> unit() const
	{
		Vector2d<T> result = *this;
		result.normalize();
		return result;
	}

    void setMagnitude(T magnitude)
    {
        normalize();
        (*this) *= magnitude;
    }

    /** Zero all the components of the vector. */
    void clear()
    {
        x = y = 0;
    }

    /** Flips all the components of the vector. */
    void invert()
    {
        x = -x;
        y = -y;
    }


    /** Checks if the vector is zero */
    bool isZero() const
    {
        return x == 0 && y == 0 == 0;
    }

    /** Finds this distance from this point to that given. */
    T distance(const Vector2d<T> &other) const
    {
        return Vector2d<T>(*this, other).magnitude();
    }

	//! stream redirection operator.
	template <typename U>
	friend std::ostream& operator<<(std::ostream&, const Vector2d<U> &);
};

/*
template <typename T>
std::ostream& operator <<(std::ostream& os, const Vector2<T> &v){
	return os << "(" << v.x <<"," << v.y << ")";
}*/

// global function. should work!
template <typename U>
std::ostream& operator<< (std::ostream& ostr, const Vector2d<U>& vect)
{
	ostr << "(" << vect.x << "," << vect.y << ")";
	return ostr;
}


typedef Vector2d<int> Vector2di;
typedef Vector2d<float> Vector2df;
typedef Vector2d<double> Vector2dd;

// The old implementation ... lol


//// macro to make creating the ctors for derived vectors easier
//#define Vector2_CONSTRUCTORS(name, type)   \
//	/* trivial ctor */				\
//	name() {}						\
//	/* down casting ctor */			\
//	name(const Vector2d<type> &v): Vector2d<type>(v.x, v.y) {}	\
//	/* make x,y combination into a vector */					\
//	name(type x0, type y0): Vector2d<type>(x0, y0) {}
//
//
//
//struct Vector2di: public Vector2d<int>
//{
//	Vector2_CONSTRUCTORS(Vector2di, int)
//};
//
//struct Vector2dd: public Vector2d<double>
//{
//	Vector2_CONSTRUCTORS(Vector2dd, double);
//
//
//	//! gets the length of this vector squared
//	double squareMagnitude() const
//	{	return (double)(*this * *this);   }
//
//	//! gets the length of this vector
//	double magnitude() const
//	{	return (double)sqrt(*this * *this);   }
//
//	//! normalizes this vector
//	void normalize()
//	{	*this/=magnitude();	}
//
//	//! returns the normalized vector
//	Vector2dd normalized() const
//	{   return  *this/magnitude();  }
//
//	//! reflects this vector about n
//	void reflect(const Vector2dd &n)
//	{
//		Vector2dd orig(*this);
//		project(n);
//		*this= *this*2 - orig;
//	}
//
//	//! clears this vector
//	void clear() {
//		x = 0;
//		y = 0;
//	}
//
//	/** Returns a unit vector in the direction of this vector. */
//	Vector2dd unit() const
//	{
//		Vector2dd result = *this;
//		result.normalize();
//		return result;
//	}
//
//	//! projects this vector onto v
//	void project(const Vector2dd &v)
//	{	*this= v * (*this * v)/(v*v);	}
//
//
//	//! returns this vector projected onto v
//	Vector2dd projected(const Vector2dd &v)
//	{   return v * (*this * v)/(v*v);	}
//
//	//! computes the angle between 2 arbitrary vectors
//	static inline double angle(const Vector2dd &v1, const Vector2dd &v2)
//	{   return acosf((v1*v2) / (v1.magnitude()*v2.magnitude()));  }
//
//	//! computes the angle between 2 normalized arbitrary vectors
//	static inline double angle_normalized(const Vector2dd &v1, const Vector2dd &v2)
//	{   return acosf(v1*v2);  }
//};
//
//
//struct Vector2ui: public Vector2d<unsigned int>
//{
//	Vector2_CONSTRUCTORS(Vector2ui, unsigned int)
//};
//
//
//struct Vector2df: public Vector2d<float>
//{
//	Vector2_CONSTRUCTORS(Vector2df, float)
//
//	//! gets the length of this vector squared
//	float squareMagnitude() const
//	{	return (float)(*this * *this);   }
//
//	//! gets the length of this vector
//	float magnitude() const
//	{	return (float)sqrt(*this * *this);   }
//
//	//! normalizes this vector
//	void normalize()
//	{	*this/=magnitude();	}
//
//	//! returns the normalized vector
//	Vector2df normalized() const
//	{   return  *this/magnitude();  }
//
//	//! reflects this vector about n
//	void reflect(const Vector2df &n)
//	{
//		Vector2df orig(*this);
//		project(n);
//		*this= *this*2 - orig;
//	}
//
//	//! clears this vector
//	void clear() {
//		x = 0;
//		y = 0;
//	}
//
//	/** Returns a unit vector in the direction of this vector. */
//	Vector2df unit() const
//	{
//		Vector2df result = *this;
//		result.normalize();
//		return result;
//	}
//
//	//! projects this vector onto v
//	void project(const Vector2df &v)
//	{	*this= v * (*this * v)/(v*v);	}
//
//	//! returns this vector projected onto v
//	Vector2df projected(const Vector2df &v)
//	{   return v * (*this * v)/(v*v);	}
//
//	//! computes the angle between 2 arbitrary vectors
//	static inline float angle(const Vector2df &v1, const Vector2df &v2)
//	{   return acosf((v1*v2) / (v1.magnitude()*v2.magnitude()));  }
//
//	//! computes the angle between 2 normalized arbitrary vectors
//	static inline float angle_normalized(const Vector2df &v1, const Vector2df &v2)
//	{   return acosf(v1*v2);  }
//};


#endif


