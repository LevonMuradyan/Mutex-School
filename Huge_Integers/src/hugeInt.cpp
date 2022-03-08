#include "hugeInt.hpp"
#include <iostream>

HugeInt::HugeInt()
{

}

HugeInt::HugeInt(std::string value)
{
	// check the validation of input
	if (!isInputValid(value)) {
		throw std::invalid_argument("Invalid input, please write a correct number");
	}

	// reserve memory for the vector exactly by digits count
	m_digits.reserve(value.size());
	for (auto it = value.rbegin(); it != value.rend(); ++it) {
		if (*it != '-') {
			m_digits.push_back(static_cast<int>(*it - '0'));
		} else {
			m_sign = false;
		}
	}
}

HugeInt::HugeInt(int value)
{
	if (value < 0) {
		m_sign = false;
		value = -value;
	}

	if (value == 0) {
		m_digits.push_back(0);
	}

	while (value) {
		m_digits.push_back(value % 10);
		value /= 10;
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
		if ((*it < '0' || *it > '9') &&
			(*it != '-' || it != value.begin() || value.size() <= 1)) {
			return false;
		}
	}

	return true;
}

HugeInt HugeInt::operator +(const HugeInt &rhs) const
{
	HugeInt result;

	if (m_sign == rhs.m_sign) {
		int carry = 0;
		for (size_t i = 0; i < std::max(size(), rhs.size()); ++i) {
			int sum = 0;

			if (i < size() && i < rhs.size()) {
				sum = m_digits[i] + rhs.m_digits[i] + carry;
			} else if (i < size() && i >= rhs.size()) {
				sum = m_digits[i] + carry;
			} else if (i >= size() && i < rhs.size()) {
				sum = rhs.m_digits[i] + carry;
			}

			carry = sum / 10;
			result.m_digits.push_back(sum % 10);
		}

		if (carry != 0) {
			result.m_digits.push_back(carry);
		}

		result.m_sign = m_sign;
	} else {

		const HugeInt * bigger;
		const HugeInt * smaller;

		if (isLessByModul(rhs)) {
			bigger = &rhs;
			smaller = this;
		} else if (rhs.isLessByModul(*this)) {
			bigger = this;
			smaller = &rhs;
		} else {
			return HugeInt(0);
		}

		int debt = 0;

		for (size_t i = 0; i < bigger->size(); ++i) {
			int sub = 0;

			if (i < smaller->size() && i < bigger->size()) {
				if (bigger->m_digits[i] - debt < smaller->m_digits[i]) {
					sub = bigger->m_digits[i] - debt - smaller->m_digits[i] + 10;
					debt = 1;
				} else {
					sub = bigger->m_digits[i] - debt - smaller->m_digits[i];
					debt = 0;
				}
			} else if (i >= smaller->size() && i < bigger->size()) {
				if (bigger->m_digits[i] - debt < 0) {
					sub = bigger->m_digits[i] - debt + 10;
					debt = 1;
				} else {
					sub = bigger->m_digits[i] - debt;
					debt = 0;
				}
			}

			if (i == bigger->size() - 1 && sub == 0) {
				break;
			}

			result.m_digits.push_back(sub);
		}

		result.m_sign = bigger->m_sign;
	}

	return result;
}

HugeInt HugeInt::operator *(const HugeInt &rhs) const
{
	if ((size() == 1 && m_digits[0] == 0) ||
		(rhs.size() == 1 && rhs.m_digits[0] == 0)) {
		return HugeInt(0);
	}

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

	if (m_sign != rhs.m_sign) {
		result.m_sign = false;
	}

	return result;
}

bool HugeInt::isLessByModul(const HugeInt &rhs) const
{
	if (size() < rhs.size()) {
		return true;
	} else if (size() > rhs.size()) {
		return false;
	} else {
		for (int i = size() - 1; i >= 0; --i) {
			if (m_digits[i] > rhs.m_digits[i]) {
				return false;
			} else if (m_digits[i] < rhs.m_digits[i]) {
				return true;
			}
		}
	}

	return false;
}

bool HugeInt::operator ==(const HugeInt &rhs) const
{
	if (size() != rhs.size() || m_sign != rhs.m_sign) {
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
	out << (number.m_sign ? "" : "-");
	for (auto it = number.m_digits.rbegin(); it != number.m_digits.rend(); ++it) {
		out << std::to_string(*it);
	}

	return out;
}
