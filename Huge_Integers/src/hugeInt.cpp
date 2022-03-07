#include "hugeInt.hpp"
#include <iostream>

HugeInt::HugeInt()
{

}

HugeInt::HugeInt(std::string value)
{
	if (!isInputValid(value)) {
		throw std::logic_error("Invalid input");
	}

	m_digits.reserve(value.size());
	for (auto it = value.rbegin(); it != value.rend(); ++it) {
		m_digits.push_back(static_cast<int>(*it - '0'));
	}
}

HugeInt::HugeInt(int value)
{
	while (value) {
		m_digits.push_back(value % 10);
		value /= 10;
	}
}

HugeInt::HugeInt(const HugeInt &rhs)
{
	m_digits.resize(rhs.size());
	for (size_t i = 0; i < rhs.size(); ++i) {
		m_digits[i] = rhs.m_digits[i];
	}
}

size_t HugeInt::size() const
{
	return m_digits.size();
}

bool HugeInt::isInputValid(const std::string& value) const
{
	if (value.empty() || (value.size() > 1 && value[0] == '0')) {
		return false;
	}

	for (auto it = value.begin(); it != value.end(); ++it) {
		if (*it < '0' || *it > '9') {
			return false;
		}
	}

	return true;
}

int& HugeInt::operator [](int idx)
{
	return m_digits[idx];
}

HugeInt HugeInt::operator +(const HugeInt &rhs) const
{
	HugeInt result;
	int carry = 0;

	for (size_t i = 0; i < std::max(size(), rhs.size()); ++i) {
		int sum = 0;

		// shorter solution
		// sum = (i < m_digits.size()) * m_digits[i] + (i < rhs.m_digits.size()) * rhs.m_digits[i] + carry;

		if (i < m_digits.size() && i < rhs.m_digits.size()) {
			sum = m_digits[i] + rhs.m_digits[i] + carry;
		} else if (i < m_digits.size() && i >= rhs.m_digits.size()) {
			sum = m_digits[i] + carry;
		} else if (i >= m_digits.size() && i < rhs.m_digits.size()) {
			sum = rhs.m_digits[i] + carry;
		}

		carry = sum / 10;
		result.m_digits.push_back(sum % 10);
	}

	if (carry != 0) {
		result.m_digits.push_back(carry);
	}

	return result;
}

HugeInt HugeInt::operator *(const HugeInt &rhs) const
{
	bool isFirstNumberLonger = size() >= rhs.size();
	HugeInt result;

	for (size_t j = 0; j < std::min(size(), rhs.size()); ++j) {

		HugeInt adder;
		adder.m_digits.resize(j);
		int carry = 0;

		for (size_t i = 0; i < std::max(size(), rhs.size()); ++i) {
			int multiplication = 0;

			if (isFirstNumberLonger) {
				multiplication = m_digits[i] * rhs.m_digits[j] + carry;
			} else {
				multiplication = m_digits[j] * rhs.m_digits[i] + carry;
			}

			carry = multiplication / 10;
			adder.m_digits.push_back(multiplication % 10);
		}

		if (carry != 0) {
			adder.m_digits.push_back(carry);
		}

		result = result + adder;
	}

	return result;
}

bool HugeInt::operator ==(const HugeInt &rhs) const
{
	if (size() != rhs.size()) {
		return false;
	}

	for (size_t i = 0; i < size(); ++i) {
		if (m_digits[i] != rhs.m_digits[i]) {
			return false;
		}
	}

	return true;
}

std::ostream& operator << (std::ostream & out, const HugeInt & number) {
	for (auto it = number.m_digits.rbegin(); it != number.m_digits.rend(); ++it) {
		out << std::to_string(*it);
	}

	return out;
}
