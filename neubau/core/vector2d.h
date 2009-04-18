// Defines a 2-D vector type.
// adapted from the AI for Games programming book from Millington.

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include "floating.h"
#include <ostream>

using namespace std;

/**
 * Parametized equivalence function with specializations with floating-point equivalence
 * with some arbitrary tolerance.
 * @param a
 * @param b
 * @return
 */
template<typename T>
static inline bool equalsT(T a, T b) {
	return a == b;
}

// Specialized equivalence for floating point and double precision numbers.
template <>
inline bool equalsT<float>(float a, float b) {
	return fequals(a,b);
}

template <>
inline bool equalsT<double>(double a, double b) {
	return equals(a,b);
}


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
    /** The default constructor creates a zero vector, no matter wehat type it is. */
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
    // const static Vector2d<T> UP;
    // const static Vector2d<T> RIGHT;
    // const static Vector2d<T> OUT_OF_SCREEN;
    // const static Vector2d<T> DOWN;
    // const static Vector2d<T> LEFT;
    // const static Vector2d<T> INTO_SCREEN;
    /* @} */

    /**
     * @name Basis Directions
     *
     * These are convenience unit-vectors in the basis directions.
     */
    /* @{ */
    // const static Vector2d<T> X;
    // const static Vector2d<T> Y;
    /* @} */

    /** A zero length vector. */
    // const static Vector2d<T> ZERO;


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
        return equalsT<T>(x,other.x) && equalsT<T>(y,other.y);
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
    T dot(const Vector2d<T> &vector) const
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
            (*this) *= ((T)1)/l; // clever use of the this pointer!
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
	friend ostream& operator<<(ostream&, const Vector2d<U> &);
};


template <typename U>
ostream& operator<< (ostream& os, const Vector2d<U>& vect)
{
	return os << "(" << vect.x << "," << vect.y << ")";
}

typedef Vector2d<int> Vector2di;
typedef Vector2d<float> Vector2df;
typedef Vector2d<double> Vector2dd;


#endif


