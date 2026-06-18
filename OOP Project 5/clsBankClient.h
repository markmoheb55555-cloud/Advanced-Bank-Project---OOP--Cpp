#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include <fstream>
#include <vector>
#include <iomanip>
#include "Global.h"
#include "clsUtil.h"

using namespace std;

class clsBankClient :public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1,AddNewMode = 2 };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool MarkedForDeleted = false;

    

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "//")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }
    struct stTransferLogRecord;
    static stTransferLogRecord _ConverLinetoTransferObject(string Line , string Seperator = "//")
    {
        stTransferLogRecord TrnsferLogRecord;
        vector<string> vTransferData;
        vTransferData = clsString::Split(Line, Seperator);

        TrnsferLogRecord.Datetime = vTransferData[0];
        TrnsferLogRecord.srcAccountNumber = vTransferData[1];
        TrnsferLogRecord.desAccountNumber = vTransferData[2];
        TrnsferLogRecord.Amount = stod(vTransferData[3]);
        TrnsferLogRecord.srcAccountBalance = stod(vTransferData[4]);
        TrnsferLogRecord.desAccountBalance = stod(vTransferData[5]);
        TrnsferLogRecord.UserName = vTransferData[6];
        return TrnsferLogRecord;


    }
  

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }
    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "//")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }
    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);
        string DataLine;
        if (MyFile.is_open())
        {
            for (clsBankClient C : vClients)
            {
                if (C.MarkedForDeleted == false)
                {


                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }
    void _Update()
    {
        vector <clsBankClient>_vClients;
        _vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {


                C = *this;
                break;
            }
        }
        _SaveClientsDataToFile(_vClients);
    } 
    void _AddDataLineToFile(string DataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;
            MyFile.close();
        }
    }
     string _ConverTransferInformationsToLine(clsBankClient &Client2, float Amount, string Seperator = "//")
    {
        clsDate Date;

        string stClientRecord = "";

        stClientRecord += Date.GetSystemDateTimeString() + Seperator;


        stClientRecord += AccountNumber() + Seperator;
        stClientRecord += Client2.AccountNumber() + Seperator;
        stClientRecord += to_string(Amount) + Seperator;

        stClientRecord += to_string(AccountBalance) + Seperator;
        stClientRecord += to_string(Client2.AccountBalance) + Seperator;
        stClientRecord += CurrentUser.GetUserName();

        return stClientRecord;

    }
     void _SaveTransferDataToFile(clsBankClient &Client2, float Amount)
     {
         fstream MyFile;

         MyFile.open("TransferLog.txt", ios::out | ios::app);
         
         if (MyFile.is_open())
         {
             string DataLine = _ConverTransferInformationsToLine(Client2, Amount);
             MyFile << DataLine << endl;


             MyFile.close();
         }
     }
public:
    struct stTransferLogRecord
    {
        string Datetime;
        string srcAccountNumber;
        string desAccountNumber;
        int Amount;
        float srcAccountBalance;
        float desAccountBalance;
        string UserName;
    };
    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

 
    static clsBankClient Find(string AccountNumber)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {



        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                 
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        return (!Client1.IsEmpty());
    }
    enum enSaveResults { svFailedemptyObject = 0, svSucceeded = 1 , svFaildAccountNumberExists = 2
    };
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            return enSaveResults::svFailedemptyObject;
        }
        case enMode::UpdateMode:
        {


            _Update();
            return enSaveResults::svSucceeded;
        }
        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }
    }
    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C.MarkedForDeleted = true;
                break;
            }
        }
        _SaveClientsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;
    }
    static vector <clsBankClient> GetClientsList()
    {
        return clsBankClient::_LoadClientsDataFromFile();
    }
   static double GetTotalBalances()
   {
       vector <clsBankClient> vClients = clsBankClient::GetClientsList();

       double TotalBalances = 0;

       for (clsBankClient Client : vClients)
       {

           TotalBalances += Client.AccountBalance;
       }

       return TotalBalances;

   }
  static  void PrintClientRecordBalanceLine(clsBankClient Client)
   {

       cout << "| " << setw(15) << left << Client.AccountNumber();
       cout << "| " << setw(40) << left << Client.FullName();
       cout << "| " << setw(12) << left << Client.AccountBalance;

   }
   static void ShowTotalBalances()
   {

       vector <clsBankClient> vClients = clsBankClient::GetClientsList();

       cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
       cout << "\n_______________________________________________________";
       cout << "_________________________________________\n" << endl;

       cout << "| " << left << setw(15) << "Accout Number";
       cout << "| " << left << setw(40) << "Client Name";
       cout << "| " << left << setw(12) << "Balance";
       cout << "\n_______________________________________________________";
       cout << "_________________________________________\n" << endl;

       double TotalBalances = clsBankClient::GetTotalBalances();

       if (vClients.size() == 0)
           cout << "\t\t\t\tNo Clients Available In the System!";
       else

           for (clsBankClient Client : vClients)
           {
               PrintClientRecordBalanceLine(Client);
               cout << endl;
           }

       cout << "\n_______________________________________________________";
       cout << "_________________________________________\n" << endl;
       cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
       cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";
   }

   void Deposit(double Number)
   {
       AccountBalance += Number;
       Save();
   }
   bool Withdraw(double Amount)
   {
       if (Amount > AccountBalance)
       {
           return false;
       }
       else
       {
           AccountBalance -= Amount;
           Save();
           return true;
       }
   }
   bool Transfer(float Amount, clsBankClient& DestinationClient)
   {
       if (Amount > AccountBalance)
       {
           return false;
       }

       Withdraw(Amount);
       DestinationClient.Deposit(Amount);
       _SaveTransferDataToFile(DestinationClient, Amount);
       return true;
       
   }
    static vector <stTransferLogRecord> _LoadTransfersDataFromFile()
    {

       vector <stTransferLogRecord> vTransfer;
       fstream MyFile;
       MyFile.open("TransferLog.txt", ios::in);//read Mode

       if (MyFile.is_open())
       {

           string Line;


           while (getline(MyFile, Line))
           {

               stTransferLogRecord TransferObject = _ConverLinetoTransferObject(Line);

               vTransfer.push_back(TransferObject);
           }

           MyFile.close();

       }

       return vTransfer;

    }

  
   
};
