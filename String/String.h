#pragma once
#include <vector>
#include <algorithm>
class String {
protected:
	char *pStr;
	int _size;

public:
	String() {
		pStr = NULL;
		_size = 0;
	} 
	String(const char *str) {
		_size = strlen(str) + 1;
		pStr = new char[_size];
		strcpy_s(pStr,this->_size, str);
	}
	int size();
	void clear();
	const String &operator = (const String & obj);
	const String& operator - (const String &obj);
	const bool operator > (const String &str);
	const bool operator < (const String &str);
	virtual int getNumber() { return 0; };
	char* deleteChars(std::vector<char> string, std::vector<int> points_to_delete, int target_size);
	friend std::ostream &operator << (std::ostream &os, String &string) {
		for (int i = 0; i < string.size(); i++) {
			os << string.pStr[i];
		} return os;
	}
	friend std::ostream &operator << (std::ostream &os, const String &string) {
		for (int i = 0; i < string._size; i++) {
			os << string.pStr[i];
		} return os;
	}
 
	~String() { 
		//delete[]pStr;
	}
};
const String& String::operator=(const String & obj) {
	if (&obj == this) { return *this; }
	_size = obj._size;
	pStr = new char[_size + 1];
	strcpy_s(pStr, this->_size+1, obj.pStr);
	return *this;
}
const String& String::operator - (const String &obj) {
	int count = 0; int pos_to_del = 0;
	std::vector<int> points_to_delete;
	std::vector<char> string;
	for (int i = 0; i < this->_size; i++) { string.push_back(this->pStr[i]); }
	for (int i = 0; i < this->_size-1; i++) {
		if (this->_size - i >= obj._size - 1) {
			for (int  j = 0; j < obj._size - 1; j++) {
				if (this->pStr[i + j] == obj.pStr[j]) {
					if (++count == obj._size - 1) { points_to_delete.push_back(i); count = 0; } 
				} else { count = 0; break; }
			}
		} else { break; }
	}
	char* buff = new char[strlen(deleteChars(string, points_to_delete, obj._size))];
	buff = deleteChars(string, points_to_delete, obj._size);
	this->_size = strlen(buff);
	this->pStr = new char[_size + 1];
	strcpy_s(this->pStr, this->_size+1, buff);
	return *this;
}
inline char* String::deleteChars(std::vector<char> string, std::vector<int> points_to_delete, int target_size) {
	std::vector<char> res;
	char* result = new char[string.size() - (points_to_delete.size()*target_size)];
	for (int i = 0; i < string.size(); i++) {
		if (std::find(points_to_delete.begin(), points_to_delete.end(), i) != points_to_delete.end()) {
			for (int j = 0; j < target_size-2; j++) { ++i; }
		} else {res.push_back(string.at(i)); }
	} 
	for (int i = 0; i < res.size(); i++) {
		result[i] = res.at(i);
	} return result;
}
const bool String::operator > (const String &str) {
	return this->_size > str._size ? true : false;
}
const bool String::operator < (const String &str) {
	return this->_size < str._size ? true : false;
}
inline int String::size() { return this->_size; }
inline void String::clear() {
	delete[] pStr;
	_size = 0;
	pStr = new char[_size + 1];
	strcpy_s(pStr, this->_size, "");
}