#pragma once
using namespace std;
#include<iostream>
#include<string>
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsCurrencyListScreen.h"
#include "clsCurrency.h"
#include "clsCurrencyMainScreen.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen :protected clsScreen
{
private:
    static void _PrintCurrency(clsCurrency Currency)
    {
     
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }
    static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\n Currency Found : \n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\n Currency Was not Found \n";
        }
    }
public:
    static void ShowFindCurrencyScreen()
    {


        _DrawScreenHeader("\tFind Currency Screen");
        string Code;
        string Country;
        int Choose;
   
        cout << "Find By: [1] Code or [2] Country?" << endl;
       Choose =  clsInputValidate::ReadNumberBetween(1,2);
        if (Choose == 1)
        {
            cout << "Enter the Code" << endl;
            Code = clsInputValidate::ReadString();
          clsCurrency Currency = clsCurrency::FindByCode(Code);
          _ShowResults(Currency);

        }
        else if (Choose == 2)
        {
            cout << "Enter the Country" << endl;
             Country = clsInputValidate::ReadString();
           clsCurrency Currency =clsCurrency::FindByCountry(Country);
           _ShowResults(Currency);
        }
        
    }
};

