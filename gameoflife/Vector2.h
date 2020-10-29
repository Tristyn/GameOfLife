#pragma once
namespace Conway
{
	template<typename T>
	class Vector2
	{
	public:
		Vector2() = default;
		Vector2(T x, T y) : x(x), y(y) { };

		T x;
		T y;
	};

	// Define common types we'll use
	typedef Vector2<int> Vector2Int;

	// operators
	template<typename T>
	Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left.x + right.x, left.y + right.y);
	}

	template<typename T>
	Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left.x - right.x, left.y - right.y);
	}

	template<typename T>
	bool operator ==(const Vector2<T>& left, const Vector2<T>& right)
	{
		return left.x == right.x && left.y == right.y;
	}

	template<typename T>
	bool operator !=(const Vector2<T>& left, const Vector2<T>& right)
	{
		return left.x != right.x || left.y != right.y;
	}
}