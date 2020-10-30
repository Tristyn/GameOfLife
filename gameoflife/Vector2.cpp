#include "Vector2.h"

namespace Conway
{
	template<typename T>
	Vector2<T>::Vector2(T x, T y) : mX(x), mY(y) { };

	template<typename T>
	T Vector2<T>::GetX() const
	{
		return mX;
	}

	template<typename T>
	T Vector2<T>::GetY() const
	{
		return mY;
	}

	template<typename T>
	T Vector2<T>::SetX()
	{
		return mX;
	}

	template<typename T>
	T Vector2<T>::SetY()
	{
		return mY;
	}
	
	// Explicit instantiations
	template class Vector2<int>;
}