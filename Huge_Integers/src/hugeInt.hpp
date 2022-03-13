#ifndef HUGE_INT_HPP
#define HUGE_INT_HPP

#include <string>
#include <vector>

class HugeInt
{
public:
	explicit HugeInt(std::string value);
	explicit HugeInt(int value);
	HugeInt(const HugeInt& rhs) = default;

	HugeInt operator + (const HugeInt & rhs) const;
	HugeInt operator * (const HugeInt & rhs) const;

	bool operator == (const HugeInt & rhs) const;

	friend std::ostream& operator << (std::ostream & out, const HugeInt & rhs);
	size_t size() const;

private:
	HugeInt();
	bool isInputValid(const std::string& value) const;
	bool isLessByModul(const HugeInt& rhs) const;

private:
	 std::vector<int8_t> m_digits;
	 bool m_sign = true;
};

#endif // HUGE_INT_HPP
