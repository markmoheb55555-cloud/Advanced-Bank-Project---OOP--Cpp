#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include "clsString.h"
#include "clsDate.h"
#include <limits>
using namespace std;
class clsInputValidate
{
public:

	static string ReadString()
	{
		string  S1 = "";
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, S1);
		return S1;
	}

	template <typename T> static  T ReadNumber(string ErrorMessage = "InValidNumber Enter Again \n")
	{


		T Number;
		cin >> Number;

		while (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << ErrorMessage;
			cin >> Number;
		}

		return Number;

	}

	static bool IsNumberBetween(int num, int from, int to)
	{
		if (num <= from && num >= to)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	static bool IsDateBetween(clsDate DateBt, clsDate DateFrom, clsDate DateTo)
	{
		if (clsDate::CheckDate1AfterDate2(DateBt, DateFrom) && clsDate::IsDate1BeforeDate2(DateBt, DateTo))
		{
			return true;
		}
		if (clsDate::CheckDate1AfterDate2(DateBt, DateTo) && clsDate::IsDate1BeforeDate2(DateBt, DateFrom))
		{
			return true;
		}
		return false;

	}

	template <typename T>	static T ReadNumberBetween(T numFrom, T numTo, string FailedMessage = "")
	{

		T num = ReadNumber<T>();
		while (num < numFrom || num > numTo)
		{
			cout << FailedMessage << endl;
			cout << "Enter the number between " << numFrom << " and " << numTo << endl;
			num = ReadNumber<T>();
		}
		return num;
	}
};

