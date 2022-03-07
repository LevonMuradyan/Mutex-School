#ifndef __HUGE_INT_HPP__
#define __HUGE_INT_HPP__

#include <string>
#include <vector>

class HugeInt
{
public:
	HugeInt();
	explicit HugeInt(std::string value);
	explicit HugeInt(int value);
	HugeInt(const HugeInt& rhs);

	int& operator [] (int idx);
	HugeInt operator + (const HugeInt & rhs) const;
	HugeInt operator * (const HugeInt & rhs) const;

	bool operator == (const HugeInt & rhs) const;

	friend std::ostream& operator << (std::ostream & out, const HugeInt & rhs);
	size_t size() const;

private:
	bool isInputValid(const std::string& value) const;

private:
	 std::vector<int> m_digits;
};

#endif // __HUGE_INT_HPP__
