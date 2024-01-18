#include <iostream>
using namespace std;

class MyString
{
	char* str;
	int size;
	static int count;//статическое поле 

public:


	MyString() : MyString(80) {}

	MyString(int length) : size(length)
	{
		str = new char[size + 1];
		strcpy_s(str, size + 1, "");
		count++;
	}

	MyString(const char* Str) : MyString(strlen(Str))
	{
		strcpy_s(str, size + 1, Str);
		cout << "The copy constructor worked" << endl;
	}

	MyString(const MyString& string) : MyString(string.size)
	{
		strcpy_s(str, size + 1, string.str);
	}


	void StrInput() {

		cout << "Enter a string: ";
		cin.getline(str, size + 1);
	}

	void Output()
	{
		cout << "String: " << str << endl;
	}

	static int GetCount()
	{
		return count;
	}


	int GetSize() const
	{
		return size;
	}

	char* GetStr() const
	{
		return str;
	}

	void SetSize(int newSize) {
		size = newSize;
	}

	void SetStr(char* newStr) {
		str = newStr;
	}


	MyString& operator++ () {

		int newSize = size + 1;
		char* newString = new char[newSize + 1];

		strcpy_s(newString, newSize + 1, str);
		newString[size] = 'x';
		newString[newSize] = '\0';

		delete[] str;
		str = newString;
		size = newSize;

		return *this;
	}

	MyString& operator-- () {

		if (size > 0) {

			int newSize = size - 1;
			char* newString = new char[newSize + 1];

			strncpy_s(newString, newSize + 1, str, newSize);
			newString[newSize] = '\0';

			delete[] str;
			str = newString;
			size = newSize;
		}

		return *this;
	}

	MyString operator+(int number) const {

		if (number < 0) {
			return *this;
		}

		int newSize = size + number;
		char* newStr = new char[newSize + 1];

		strcpy_s(newStr, newSize + 1, str);

		for (int i = size; i < newSize; ++i) {

			newStr[i] = 'x';
		}
		newStr[newSize] = '\0';

		MyString newString(newStr);

		delete[] newStr;

		return newString;

	}

	MyString operator-(int number) const {

		if (number <= 0 || number > size) {
			return *this;
		}

		int newSize = size - number;
		char* newStr = new char[newSize + 1];

		strncpy_s(newStr, newSize + 1, str, newSize);

		newStr[newSize] = '\0';

		MyString newString(newStr);

		delete[] newStr;
		return newString;
	}

	MyString& operator=(const MyString& object)
	{
		cout << "Copy assignment\n";
		if (!(this == &object))
		{
			if (str != nullptr)
			{
				delete[] str;
			}
			if (object.str == nullptr)
			{
				str = nullptr;
				size = object.size;
				return *this;
			}
			str = new char[strlen(object.str) + 1];
			strcpy_s(str, strlen(object.str) + 1, object.str);
			size = object.size;
			return *this;
		}
		return *this;
	}


	MyString operator++ (int) {

		MyString temp(*this);
		operator++();
		return temp;
	}

	MyString operator-- (int) {

		MyString temp(*this);
		operator--();
		return temp;
	}

	~MyString() {

		delete[] str;
		count--;
	}

	friend istream& operator>>(istream& is, MyString& myString);
	friend ostream& operator<<(ostream& os, const MyString& myString);
};

int MyString::count = 0;

MyString operator+(int number, const MyString& myString) {

	if (number < 0) {
		return myString;
	}

	MyString temp;

	temp.SetSize(myString.GetSize() + number);
	temp.SetStr(new char[temp.GetSize() + 1]);

	for (int i = 0; i < number; ++i) {

		temp.GetStr()[i] = 'x';
	}

	if (myString.GetStr() != nullptr) {
		strcpy_s(temp.GetStr() + number, myString.GetSize() + 1, myString.GetStr());
	}

	return temp;
}

istream& operator>>(istream& is, MyString& myString) {
	cout << "Enter a string: ";
	is.getline(myString.str, myString.size + 1);
	return is;
}

ostream& operator<<(ostream& os, const MyString& myString)
{
	os << "String: " << myString.str << '\t';
	os << "Size of string = " << myString.size << '\n';
	return os;
}

int main()
{
	MyString str1;
	cin >> str1;

	MyString str2(20);
	cin >> str2;

	MyString str3("Hello");

	cout << "\nObjects str: \n\n";


	cout << str1;
	cout << str2;
	cout << str3;
	cout << endl;

	MyString str4 = str3;
	cout << str4;
	cout << endl;

	MyString increment = ++str3;
	cout << "Increment: " << increment << endl;

	MyString decrement = --str3;
	cout <<"Decrement: " << decrement<< endl;

	MyString plus = str3 + 4;
	cout <<"Plus: "<< plus<< endl;


	MyString minus = str3 - 2;
	cout <<"Minus: "<< minus<< endl ;

	str1 = str2;
	cout << str1<< endl;

	cout << "Operation of the postfix form of increment" << endl;
	increment++;
	cout << increment << endl;
	cout << "Operation of the postfix form of dikrimenta" << endl;
	decrement--;
	cout << decrement << endl;

	MyString HelloWorld = "Hello Word";
	MyString newString;
	newString = 4 + HelloWorld;
	cout << newString << endl;


	cout << "\nNumber of objects created " << MyString::GetCount() << endl;
	return 0;
}

