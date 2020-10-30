#ifndef __VECTOR2__
#define __VECTOR2__

namespace Conway
{
	template<typename T>
	class Vector2
	{
	private:
		T mX;
		T mY;

	public:
		Vector2() = default;
		Vector2(T x, T y);

		T GetX() const;
		T GetY() const;
		T SetX();
		T SetY();
	};

	template<typename T>
	Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left.GetX() + right.GetX(), left.GetY() + right.GetY());
	}

	template<typename T>
	Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left.GetX() - right.GetX(), left.GetY() - right.GetY());
	}

	template<typename T>
	bool operator ==(const Vector2<T>& left, const Vector2<T>& right)
	{
		return left.GetX() == right.GetX() && left.GetY() == right.GetY();
	}

	template<typename T>
	bool operator !=(const Vector2<T>& left, const Vector2<T>& right)
	{
		return left.GetX() != right.GetX() || left.GetY() != right.GetY();
	}

	// Define common types we'll use
	typedef Vector2<int> Vector2Int;
}

#endif // __VECTOR2__