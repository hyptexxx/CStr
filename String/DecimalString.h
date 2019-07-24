#pragma once
#include "String.h"
class DecimalString : public String
{
private:
	bool isPositive();
	void hasFirstBitVAR();
	int START_POSITION;
	int number;
public:
	DecimalString() {
		pStr = NULL;
		_size = 0;
		START_POSITION = 0;
	}
	DecimalString(const char *str) {
		_size = strlen(str) + 1;
		pStr = new char[_size];
		strcpy_s(pStr, this->_size, str);
		hasFirstBitVAR();
		getNumber();
	}
	~DecimalString() {

	}
	const String &operator = (const DecimalString & obj);
	bool isdecimal();
	const int& operator - (const DecimalString &obj);
	const bool operator > (const DecimalString &str);
	const bool operator < (const DecimalString &str);
	virtual int getNumber();
};
 
inline bool DecimalString::isdecimal() {
	bool isDecimal = true; 
	for (int  i = START_POSITION; i < this->_size-1; i++) {
		if (isDecimal) {
			for (int j = 0; j < 10; j++) {
				if (this->pStr[i]-'0' == j) { isDecimal = true; break; } 
				isDecimal = false;
			}
		}
	} return isDecimal;
}
inline bool DecimalString::isPositive() {
	if (this->isdecimal()) {
		if (this->pStr[0] == '-') { return false; }
		if (this->pStr[0] == '+') { return true; }
	} return true;
}
inline void DecimalString::hasFirstBitVAR() {
	if (this->pStr[0] == '-') { this->START_POSITION = 1; } 
	else {
		if (this->pStr[0] == '+') { this->START_POSITION = 1; }
		else { this->START_POSITION = 0; }
	} 
}
inline const String & DecimalString::operator = (const DecimalString & obj) {
	if (&obj == this) { return *this; }
	_size = obj._size;
	pStr = new char[_size + 1];
	strcpy_s(pStr, this->_size, obj.pStr);
	hasFirstBitVAR(); 
	getNumber();
	return *this;
}
inline const int & DecimalString::operator - (const DecimalString & obj) {
	int result = this->getNumber()-obj.number;
	_size = obj._size;
	pStr = new char[_size + 1];
	strcpy_s(pStr, this->_size, obj.pStr);
	return result;
}
inline const bool DecimalString::operator > (const DecimalString & str) {
	return this->getNumber() > str.number ? true : false;
}
inline const bool DecimalString::operator < (const DecimalString & str) {
	return this->getNumber() < str.number ? true : false;
}
inline int DecimalString::getNumber()  {
	if (this->isdecimal()) {
		if (this->isPositive()) {
			number = atoi(this->pStr); 
			return atoi(this->pStr); }
		else { 
			int result = atoi(this->pStr) * -1;
			number = result*-1;
			return result * -1;
		}
	}
}

 