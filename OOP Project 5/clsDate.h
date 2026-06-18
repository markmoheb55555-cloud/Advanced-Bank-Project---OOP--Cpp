#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include "clsString.h"
using namespace std;
class clsDate
{
public:
	short _year = 1900;
	short _month = 1;
	short _day = 1;
public:
	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_day = now->tm_mday;
		_month = now->tm_mon + 1;
		_year = now->tm_year + 1900;
	}

	clsDate(string sDate)
	{

		vector <string> vDate;
		vDate = clsString::Split(sDate, "/");

		_day = stoi(vDate[0]);
		_month = stoi(vDate[1]);
		_year = stoi(vDate[2]);

	}

	clsDate(short Day, short Month, short Year)
	{

		_day = Day;
		_month = Month;
		_year = Year;

	}

	clsDate(short DateOrderInYear, short Year)
	{
		//This will construct a date by date order in year
		clsDate Date1 = ConvertDaysToDate(DateOrderInYear, Year);
		_day = Date1._day;
		_month = Date1._month;
		_year = Date1._year;
	}


	void SetDay(int Day)
	{
		_day = Day;

	}
	short GetDay()
	{
		return _day;
	}

	void SetMonth(int month)
	{
		_month = month;

	}

	short GetMonth()
	{
		return _month;

	}

	void SetYear(int year)
	{

		_year = year;

	}
	short GetYear()
	{
		return _year;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;
	__declspec(property(get = GetYear, put = SetYear)) short Year;


	static bool leapyear(int year)
	{

		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	bool leapyear()
	{

		return leapyear(_year);
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m)
			/ 12)) % 7;
	}
	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_day, _month, _year);
	}
	string DayName(short dayofweekorder)
	{
		string arr7Days[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arr7Days[dayofweekorder];
	}

	static int DaysOfMonth(int year, int month)
	{

		int Days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (month == 2) ? (leapyear(year) ? 29 : 28) : Days[month - 1];
	}
	int DaysOfMonth()
	{
		return DaysOfMonth(Year, Month);
	}

	static string MonthName(int month)
	{
		string arrMonth[13] = { "","January","February","March","April","May","June","July","August","September","October","November","December" };
		return arrMonth[month];
	}

	string MonthName()
	{
		return MonthName(_month);
	}
	static void PrintCalender(int month, int year)
	{
		int current = DayOfWeekOrder(1, month, year);
		int NumberOfDaysInMonth = DaysOfMonth(year, month);
		cout << "__________________________________" << MonthName(month) << "__________________________________" << endl;
		cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;
		int i = 0;
		for (i = 0; i < current; i++)
		{
			printf("     ");
		}
		for (int j = 1; j <= NumberOfDaysInMonth; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}

		}

		printf("\n___________________________________\n");
		cout << endl;
	}

	void PrintCalender()
	{
		PrintCalender(_month, _year);
	}

	static void PrintYearClender(int year)
	{
		cout << "________________________________" << endl << endl;
		cout << "     Calender - " << year << "     " << endl << endl;
		cout << "________________________________" << endl << endl;
		for (int i = 1; i <= 12; i++)
		{
			PrintCalender(i, year);
		}
	}
	void PrintYearClender()
	{
		PrintYearClender(_year);
	}
	static string GetSystemDateTimeString()
	{
	
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));

	}
	static short TotalDaysFromBeginningYear(int Days, short Month, int Year)
	{
		int Sum = 0;
		for (int i = 1; i < Month; i++)
		{

			Sum = DaysOfMonth(Year, i) + Sum;
		}
		Sum = Days + Sum;
		return Sum;

	}
	short TotalDaysFromBeginningYear()
	{
		return TotalDaysFromBeginningYear(_day, _month, _year);
	}

	static clsDate ConvertDaysToDate(short DataOrderInYear, short year)
	{
		clsDate Date;
		short RemainingDays = DataOrderInYear;
		short MonthDays;
		Date.Year = year;
		Date._month = 1;
		while (true)
		{
			MonthDays = DaysOfMonth(year, Date.Month);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._month++;
			}

			else
			{
				Date._day = RemainingDays;
				break;
			}
		}
		return Date;
	}

	static clsDate DateAddDays(short Days, clsDate& Date)
	{
		short RemainingDays = TotalDaysFromBeginningYear(Date._day, Date._month, Date.Year) + Days;
		short MonthDays;
		Date._month = 1;
		while (true)
		{
			MonthDays = DaysOfMonth(Date.Year, Date._month);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._month++;
				if (Date._month > 12)
				{
					Date._month = 1;
					Date.Year += 1;
				}
			}

			else
			{
				Date._day = RemainingDays;
				break;
			}
		}
		return Date;


	}
	clsDate DateAddDays(short Days)
	{
		return DateAddDays(Days, *this);
	}
	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._year < Date2._year) ? true : ((Date1._year == Date2._year) ? (Date1._month < Date2._month ? true : (Date1._month == Date2._month ? Date1._day < Date2._day : false)) : false);
	}
	bool IsDate1BeforeDate2(clsDate Date2)
	{
		return  IsDate1BeforeDate2(*this, Date2);
	}

	static bool CheckIfItLastDay(clsDate Date)
	{
		int DaysInMonth = DaysOfMonth(Date.Year, Date._month);

		if (DaysInMonth == Date._day)
		{
			return true;
		}
		return false;

	}
	bool CheckIfItLastDay()
	{
		return CheckIfItLastDay(*this);
	}
	static bool CheckIfItLastMonthInYear(clsDate Date)
	{
		if (Date._month == 12)
		{
			return true;
		}
		return false;
	}
	bool CheckIfItLastMonthInYear()
	{
		return CheckIfItLastMonthInYear(*this);
	}
	static clsDate ReadDateToIncreaseByOneDay(clsDate Date)
	{
		if (CheckIfItLastDay(Date))
		{
			if (CheckIfItLastMonthInYear(Date))
			{

				Date.Year++;
				Date._month = 1;
				Date._day = 1;
			}
			else
			{
				Date._day = 1;
				Date._month++;
			}

		}
		else
		{
			Date._day++;
		}

		return Date;

	}
	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate Temp;
		Temp._day = Date1._day;
		Temp._month = Date1._month;
		Temp._year = Date1._year;

		Date1._day = Date2._day;
		Date1._month = Date2._month;
		Date1._year = Date2._year;

		Date2._day = Temp._day;
		Date2._month = Temp._month;
		Date2._year = Temp._year;
	}

	void SwapDates(clsDate& Date2)
	{
		SwapDates(*this, Date2);
	}
	static clsDate AddOneDay(clsDate Date)
	{
		if (CheckIfItLastDay(Date))
		{
			if (CheckIfItLastMonthInYear(Date))
			{
				Date._month = 1;
				Date._day = 1;
				Date.Year++;
			}
			else
			{
				Date._day = 1;
				Date._month++;
			}
		}
		else
		{
			Date._day++;
		}

		return Date;
	}

	void AddOneDay()

	{
		*this = AddOneDay(*this);
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		//this will take care of negative diff
		int Days = 0;
		short SawpFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			//Swap Dates 
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;

		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);
		}

		return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
	}

	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}
	static clsDate GetSystemDate()
	{
		clsDate Date2;
		time_t t = time(nullptr);
		tm nowStruct;
		localtime_s(&nowStruct, &t);
		Date2._year = nowStruct.tm_year + 1900;
		Date2._month = nowStruct.tm_mon + 1;
		Date2._day = nowStruct.tm_mday;
		return Date2;
	}
	static clsDate DecreaseOneDay(clsDate& Date)
	{
		if (Date._day == 1)
		{
			if (Date._month == 1)
			{
				Date._month = 12;
				Date.Year--;
				Date._day = DaysOfMonth(Date.Year, Date._month);
			}
			else
			{
				Date._month--;
				Date._day = DaysOfMonth(Date.Year, Date._month);
			}

		}
		else
		{
			Date._day--;
		}
		return Date;
	}
	clsDate DecreaseOneDay()
	{
		return DecreaseOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate& Date1, int XDays)
	{
		clsDate f;
		for (int i = 0; i < XDays; i++)
		{
			Date1 = AddOneDay(Date1);
		}

		return Date1;
	}
	static clsDate Add1Week(clsDate& Date)
	{
		Date = IncreaseDateByXDays(Date, 7);
		return Date;
	}
	clsDate Add1Week()
	{
		return Add1Week(*this);
	}
	static clsDate AddXWeak(clsDate& Date, int XWeek)
	{
		for (int i = 0; i < XWeek; i++)
		{
			Date = Add1Week(Date);
		}
		return Date;
	}
	clsDate AddXWeak(int Week)
	{
		return AddXWeak(*this, Week);
	}
	static clsDate Add1Month(clsDate& Date)
	{


		if (Date._month == 12)
		{
			Date._month = 1;
			Date.Year++;
		}
		else
		{
			Date._month++;
		}



		short NumberOfDaysInCurrentMonth = DaysOfMonth(Date.Year, Date.Month);
		if (Date._day > NumberOfDaysInCurrentMonth)
		{
			Date._day = NumberOfDaysInCurrentMonth;
		}
		return Date;


	}
	clsDate Add1Month()
	{
		return Add1Month(*this);
	}

	static clsDate AddXMonth(clsDate& Date, int Xmonths)
	{
		for (int i = 0; i < Xmonths; i++)
		{
			Date = Add1Month(Date);

		}
		return Date;
	}

	clsDate AddXMonth(int Xmonths)
	{
		return AddXMonth(*this, Xmonths);
	}

	static clsDate Add1Year(clsDate& Date)
	{
		Date.Year++;
		return Date;
	}
	clsDate Add1Year()
	{
		return Add1Year(*this);
	}

	static clsDate AddXYear(clsDate& Date, int Xyears)
	{
		for (int i = 1; i <= Xyears; i++)
		{
			Date = Add1Year(Date);
		}
		return Date;
	}
	clsDate AddXYear(int yea)
	{
		return AddXYear(*this, yea);
	}

	static clsDate Add1Decade(clsDate& Date)
	{
		Date = AddXYear(Date, 10);
		return Date;
	}
	clsDate Add1Decade()
	{
		return Add1Decade(*this);
	}
	static clsDate AddXDecade(clsDate& Date, int XDecade)
	{
		for (int i = 1; i <= XDecade; i++)
		{
			Date = Add1Decade(Date);

		}
		return Date;
	}
	clsDate AddXDecade(int XDecade)
	{
		return AddXDecade(*this, XDecade);
	}
	static clsDate Add1Century(clsDate& Date)
	{
		Date = AddXDecade(Date, 10);
		return Date;
	}
	clsDate Add1Century()
	{
		return Add1Century(*this);
	}
	static clsDate Add1Millennium(clsDate& Date)
	{
		for (int i = 1; i <= 10; i++)
		{
			Date = Add1Century(Date);
		}
		return Date;
	}
	clsDate Add1Millennium()
	{
		return Add1Millennium(*this);
	}


	static bool IsEndOfWeek(clsDate Date)
	{
		if (DayOfWeekOrder(Date._day, Date._month, Date.Year) == 6)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}
	static bool IsWeekEnd(clsDate Date)
	{
		if (DayOfWeekOrder(Date._day, Date._month, Date.Year) == 5 || DayOfWeekOrder(Date._day, Date._month, Date.Year) == 6)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		if (DayOfWeekOrder(Date._day, Date._month, Date.Year) != 5 && DayOfWeekOrder(Date._day, Date._month, Date.Year) != 6)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}
	static int DaysUntilEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date._day, Date._month, Date.Year);
	}
	int DaysUntilEndOfWeek()
	{
		return DaysUntilEndOfWeek(*this);
	}
	static int DaysUntilEndOfMonth(clsDate Date)
	{
		return DaysOfMonth(Date.Year, Date._month) - Date._day;
	}
	int DaysUntilEndOfMonth()
	{
		return DaysUntilEndOfMonth(*this);
	}
	static int DaysUntilEndOfYear(clsDate Date)
	{
		if (leapyear(Date.Year))
		{
			int h = TotalDaysFromBeginningYear(Date._day, Date._month, Date.Year) - 366;
			return h * -1;
		}
		return (TotalDaysFromBeginningYear(Date._day, Date._month, Date.Year) - 365) * -1;
	}

	int DaysUntilEndOfYear()
	{
		return DaysUntilEndOfYear(*this);
	}
	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{

		short WeekEndCounter = 0;

		//in case the data  is weekend keep adding one day util you reach business day
		//we get rid of all weekends before the first business day
		while (IsWeekEnd(DateFrom))
		{
			DateFrom = ReadDateToIncreaseByOneDay(DateFrom);
		}

		//here we increase the vacation dates to add all weekends to it.

		for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
		{

			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = ReadDateToIncreaseByOneDay(DateFrom);
		}

		//in case the return date is week end keep adding one day util you reach business day
		while (IsWeekEnd(DateFrom))
		{
			DateFrom = ReadDateToIncreaseByOneDay(DateFrom);
		}

		return DateFrom;
	}

	clsDate CalculateVacationReturnDate(short VacationDays)
	{
		return CalculateVacationReturnDate(*this, VacationDays);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._year == Date2._year) ? ((Date1._month == Date2._month) ? ((Date1._day == Date2._day) ? true : false) : false) : false;
	}
	bool IsDate1EqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}
	static bool CheckDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	bool CheckDate1AfterDate2(clsDate Date2)
	{
		return CheckDate1AfterDate2(*this, Date2);
	}
	clsDate StringToDate(string DateString)
	{
		clsDate Date;
		vector <string> vDate;
		vDate = clsString::Split(DateString, "/");
		Date._day = stoi(vDate[0]);
		Date._month = stoi(vDate[1]);
		Date.Year = stoi(vDate[2]);
		return Date;
	}
	static bool ValidationDate(clsDate Date)
	{
		return(DaysOfMonth(Date.Year, Date._month) >= Date._day && Date._month <= 12 && Date._month >= 1 && Date._day >= 1);
	}
	bool ValidationDate()
	{
		return ValidationDate(*this);
	}
	static string DateToString(clsDate Date)
	{
		return to_string(Date._day) + "/" + to_string(Date._month) + "/" + to_string(Date.Year);
	}
	string DateToString()
	{
		return DateToString(*this);
	}
	static string ReplaceWordInString(string S1, string StringToReplace, string sRepalceTo)
	{
		short pos = S1.find(StringToReplace);
		while (pos != std::string::npos)
		{
			S1 = S1.replace(pos, StringToReplace.length(),
				sRepalceTo);
			pos = S1.find(StringToReplace);//find next
		}
		return S1;
	}
	static string FormatDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormattedDate = "";
		FormattedDate = (ReplaceWordInString(DateFormat, "dd", to_string(Date._day)));
		FormattedDate = ReplaceWordInString(FormattedDate, "mm", to_string(Date._month));
		FormattedDate = ReplaceWordInString(FormattedDate, "yyyy", to_string(Date.Year));
		return FormattedDate;
	}
	string FormatDate(string DateFormat = "dd/mm/yyyy")
	{
		return FormatDate(*this, DateFormat);
	}
	void Print()
	{
		cout << DateToString(*this) << endl;
	}

};



