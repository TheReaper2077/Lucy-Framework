#pragma once

	template <typename T>
	struct Vec2T {
		union {
			struct { T x, y; };
		};

		Vec2T(T X = 0, T Y = 0): x(X), y(Y) {}
		
		bool operator!=(const Vec2T &) const;
		bool operator==(const Vec2T &) const;
		bool operator>(const Vec2T &) const;
		bool operator<(const Vec2T &) const;
		bool operator>=(const Vec2T &) const;
		bool operator<=(const Vec2T &) const;
		
		Vec2T<T> operator+(const Vec2T &) const;
		Vec2T<T> operator-(const Vec2T &) const;
		Vec2T<T> operator*(const Vec2T &) const;
		Vec2T<T> operator/(const Vec2T &) const;
		Vec2T<T> operator&(const Vec2T &) const;
		Vec2T<T> operator|(const Vec2T &) const;
		Vec2T<T> operator^(const Vec2T &) const;

		void operator=(const Vec2T &);

		void operator+=(const Vec2T &);
		void operator-=(const Vec2T &);
		void operator*=(const Vec2T &);
		void operator/=(const Vec2T &);
		void operator&=(const Vec2T &);
		void operator|=(const Vec2T &);
		void operator^=(const Vec2T &);
		
		template <typename R> Vec2T<T> operator*(const R &) const;
		template <typename R> Vec2T<T> operator/(const R &) const;
		template <typename R> void operator*=(const R &);
		template <typename R> void operator/=(const R &);
	};

	template <typename T> inline void Vec2T<T>::operator=(const Vec2T &tmp) {
		x = tmp.x;
		y = tmp.y;
	}

	template <typename T> void Vec2T<T>::operator+=(const Vec2T &tmp) {
		x += tmp.x;
		y += tmp.y;
	}
	template <typename T> void Vec2T<T>::operator-=(const Vec2T &tmp) {
		x -= tmp.x;
		y -= tmp.y;
	}
	template <typename T> void Vec2T<T>::operator*=(const Vec2T &tmp) {
		x *= tmp.x;
		y *= tmp.y;
	}
	template <typename T> void Vec2T<T>::operator/=(const Vec2T &tmp) {
		x /= tmp.x;
		y /= tmp.y;
	}
	template <typename T> void Vec2T<T>::operator&=(const Vec2T &tmp) {
		x &= tmp.x;
		y &= tmp.y;
	}
	template <typename T> void Vec2T<T>::operator|=(const Vec2T &tmp) {
		x |= tmp.x;
		y |= tmp.y;
	}
	template <typename T> void Vec2T<T>::operator^=(const Vec2T &tmp) {
		x ^= tmp.x;
		y ^= tmp.y;
	}
	
	template <typename T> bool Vec2T<T>::operator!=(const Vec2T &tmp) const {
		return (x != tmp.x && y != tmp.y);
	}
	template <typename T> bool Vec2T<T>::operator==(const Vec2T &tmp) const {
		return (x == tmp.x && y == tmp.y);
	}
	template <typename T> bool Vec2T<T>::operator>(const Vec2T &tmp) const {
		return (x > tmp.x && y > tmp.y);
	}
	template <typename T> bool Vec2T<T>::operator<(const Vec2T &tmp) const {
		return (x < tmp.x && y < tmp.y);
	}
	template <typename T> bool Vec2T<T>::operator>=(const Vec2T &tmp) const {
		return (x >= tmp.x && y >= tmp.y);
	}
	template <typename T> bool Vec2T<T>::operator<=(const Vec2T &tmp) const {
		return (x <= tmp.x && y <= tmp.y);
	}

	template <typename T> Vec2T<T> Vec2T<T>::operator+(const Vec2T &tmp) const {
		return Vec2T(x + tmp.x, y + tmp.y);
	}
	template <typename T> Vec2T<T> Vec2T<T>::operator-(const Vec2T &tmp) const {
		return Vec2T(x - tmp.x, y - tmp.y);
	}
	template <typename T> Vec2T<T> Vec2T<T>::operator*(const Vec2T &tmp) const {
		return Vec2T(x * tmp.x, y * tmp.y);
	}
	template <typename T> Vec2T<T> Vec2T<T>::operator/(const Vec2T &tmp) const {
		return Vec2T(x / tmp.x, y / tmp.y);
	}
	template <typename T> Vec2T<T> Vec2T<T>::operator&(const Vec2T &tmp) const {
		return Vec2T(x & tmp.x, y & tmp.y);
	}
	template <typename T> Vec2T<T> Vec2T<T>::operator|(const Vec2T &tmp) const {
		return Vec2T(x | tmp.x, y | tmp.y);
	}
	template <typename T> Vec2T<T> Vec2T<T>::operator^(const Vec2T &tmp) const {
		return Vec2T(x ^ tmp.x, y ^ tmp.y);
	}

	using Vec2 = Vec2T<float>;
	using Vec2d = Vec2T<double>;
	using Vec2i = Vec2T<int>;
	using Vec2ui = Vec2T<unsigned int>;