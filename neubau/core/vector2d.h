// Copyright (C) 2009 Hok Shun Poon

// Defines a 2-D vector type.

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <math.h>
#include <ostream>

template <typename T>
struct Vector2
{
	T x, y;

	//! trivial ctor
	Vector2<T>() {}

	//! setting ctor
	Vector2<T>(const T x0, const T y0): x(x0), y(y0) {}

	//! array indexing
	T &operator [](unsigned int i)
	{   return *(&x+i);   }

	//! array indexing
	const T &operator [](unsigned int i) const
	{	return *(&x+i);   }

	//! function call operator
	void operator ()(const T x0, const T y0)
	{	x= x0; y= y0;	}

	//! test for equality
	bool operator==(const Vector2<T> &v)
	{	return (x==v.x && y==v.y);	}

	//! test for inequality
	bool operator!=(const Vector2<T> &v)
	{	return (x!=v.x || y!=v.y);	}

	//! set to value
	const Vector2<T> &operator =(const Vector2<T> &v)
	{
		x= v.x; y= v.y;
		return *this;
	}

	//! negation
	const Vector2<T> operator -(void) const
	{	return Vector2<T>(-x, -y);	}

	//! addition
	const Vector2<T> operator +(const Vector2<T> &v) const
	{	return Vector2<T>(x+v.x, y+v.y);	}

	//! subtraction
	const Vector2<T> operator -(const Vector2<T> &v) const
	{   return Vector2<T>(x-v.x, y-v.y);	}

	//! uniform scaling
	const Vector2<T> operator *(const T num) const
	{
		Vector2<T> temp(*this);
		return temp*=num;
	}

	//! uniform scaling
	const Vector2<T> operator /(const T num) const
	{
		Vector2<T> temp(*this);
		return temp/=num;
	}

	//! addition
	const Vector2<T> &operator +=(const Vector2<T> &v)
	{
		x+=v.x;	y+=v.y;
		return *this;
	}

	//! subtraction
	const Vector2<T> &operator -=(const Vector2<T> &v)
	{
		x-=v.x;	y-=v.y;
		return *this;
	}

	//! uniform scaling
	const Vector2<T> &operator *=(const T num)
	{
		x*=num;	y*=num;
		return *this;
	}

	//! uniform scaling
	const Vector2<T> &operator /=(const T num)
	{
		x/=num;	y/=num;
		return *this;
	}

	//! dot product
	T operator *(const Vector2<T> &v) const
	{	return x*v.x + y*v.y;	}

	//! stream redirection operator.
	template <typename U>
	friend std::ostream& operator<<(std::ostream&, const Vector2<U> &);
};

/*
template <typename T>
std::ostream& operator <<(std::ostream& os, const Vector2<T> &v){
	return os << "(" << v.x <<"," << v.y << ")";
}*/

// global function. should work!
template <typename U>
std::ostream& operator<< (std::ostream& ostr, const Vector2<U>& vect)
{
  ostr << "(" << vect.x << "," << vect.y << ")";
  return ostr;
}

// macro to make creating the ctors for derived vectors easier
#define Vector2_CTORS(name, type)   \
	/* trivial ctor */				\
	name() {}						\
	/* down casting ctor */			\
	name(const Vector2<type> &v): Vector2<type>(v.x, v.y) {}	\
	/* make x,y combination into a vector */					\
	name(type x0, type y0): Vector2<type>(x0, y0) {}



	struct Vector2di: public Vector2<int>
	{
		Vector2_CTORS(Vector2di, int)
	};


	struct Vector2ui: public Vector2<unsigned int>
	{
		Vector2_CTORS(Vector2ui, unsigned int)
	};


	struct Vector2df: public Vector2<float>
	{
		Vector2_CTORS(Vector2df, float)

		//! gets the length of this vector squared
		float length_squared() const
		{	return (float)(*this * *this);   }

		//! gets the length of this vector
		float length() const
		{	return (float)sqrt(*this * *this);   }

		//! normalizes this vector
		void normalize()
		{	*this/=length();	}

		//! returns the normalized vector
		Vector2df normalized() const
		{   return  *this/length();  }

		//! reflects this vector about n
		void reflect(const Vector2df &n)
		{
			Vector2df orig(*this);
			project(n);
			*this= *this*2 - orig;
		}

		//! projects this vector onto v
		void project(const Vector2df &v)
		{	*this= v * (*this * v)/(v*v);	}

		//! returns this vector projected onto v
		Vector2df projected(const Vector2df &v)
		{   return v * (*this * v)/(v*v);	}

		//! computes the angle between 2 arbitrary vectors
		static inline float angle(const Vector2df &v1, const Vector2df &v2)
		{   return acosf((v1*v2) / (v1.length()*v2.length()));  }

		//! computes the angle between 2 normalized arbitrary vectors
		static inline float angle_normalized(const Vector2df &v1, const Vector2df &v2)
		{   return acosf(v1*v2);  }
	};


#endif


