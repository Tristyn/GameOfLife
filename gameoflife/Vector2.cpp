#include "Vector2.h"
namespace Conway
{
	template<typename T>
	Vector2<T>::Vector2() = default;

	template<typename T>
	Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left->m_x + right->m_x, left->m_y + right->m_y);
	}

	template<typename T>
	Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left->m_x - right->m_x, left->m_y - right->m_y);
	}

	template<typename T>
	bool operator ==(const Vector2<T>& left, const Vector2<T>& right)
	{
		return left->m_x == right->m_x && left->m_y == right->m_y;
	}

	template<typename T>
	bool operator !=(const Vector2<T>& left, const Vector2<T>& right)
	{
		return left->m_x != right->m_x || left->m_y != right->m_y;
	}
}
