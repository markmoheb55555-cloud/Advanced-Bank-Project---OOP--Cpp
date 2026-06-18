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
class clsUpdateCurrencyScreen :clsScreen
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
    static float _ReadRate()
    {

        cout << "\nEnter the new Currency Rate :" << endl;
        float NewRate = clsInputValidate::ReadNumber<float>();
        return NewRate;
    }
public:
    static void _ShowUpdateCurrencyScreen()
    {
        _DrawScreenHeader("Update Currency Screen");
        string CurrencyCode = "";
        cout << "Enter the Currency Code\n";
        CurrencyCode = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "CurrenyCode Not Exist" << endl;
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        _PrintCurrency(Currency);
        cout << "\nAre you sure you want to update this Rate y/n? ";

        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\n\nUpdate Currency Rate : ";
            cout << "\n__________________________\n";
            
            Currency.UpdateRate(_ReadRate());
            cout << "\n Currency Rate Updates Successfully : \n";
            _PrintCurrency(Currency);
        }

    }
};

