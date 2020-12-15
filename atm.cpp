#include <iostream>
using namespace std;
int AccountNumber = 9;
int AccountData[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int PinData[] = {1111, 2222, 3333, 4444, 5555, 6666, 7777, 8888, 9999};
int BalanceData[] = {0,0,0,0,0,0,0,0,0};

class Account
{
  private:
    int card;
    int PIN;
    int Balance;

  public:
    Account()
    {
      card = 0;
      PIN = 0;
      Balance = 0;
    }
    Account(int cardnum, int PINnum, int moneyamount)
    {
      card = cardnum;
      PIN = PINnum;
      Balance = moneyamount;
    }
    void Setaccount(int cardnum, int PINnum, int moneyamount)
    {
      card = cardnum;
      PIN = PINnum;
      Balance = moneyamount;
    }
    int Accountcheck(int cardnum)
    {
      if (card == cardnum) return 1;
      else return 0;
    }
    int PINcheck(int PINnum)
    {
      if (PIN == PINnum) return 1;
      else return 0;
    }
    void Desposit(int moneyamount)
    {
      Balance = Balance + moneyamount;
      ShowAccount();
    }
    bool Withdraw(int moneyamount)
    {
      if (Balance < moneyamount) 
      {
        cout<<endl;
        cout << "ERROR: INSUFFICIENT BALANCE" <<endl;
        ShowAccount();
        return false;
      }
      else
      {
        Balance = Balance - moneyamount;
        return true;
      }
    }  
    void ShowAccount()
    {
      cout<<endl;
      cout << "------MENU------" <<endl;
      cout << "ACCOUNT: " << card << endl;
      cout << "BALANCE: " << Balance <<endl;
    }
};

Account * p[100];

class Screen 
{
  private:
    int user = -1;
    
  public:
    int exit = 0;
    void InsertPIN();
    void Menu();
};
void Screen::InsertPIN()
{
  int input;
  cout << "------INSERT CARD------" << endl;
  cout << "CARD: ";
  cin>> input;
  for (int i=0; i<AccountNumber; i++)
  {
    if(p[i]->Accountcheck(input)==1)
    { 
      cout<<endl;
      cout << "------INSERT PIN------" <<endl;
      cout << "PIN: ";
      cin >> input;
      if(p[i]->PINcheck(input)==1)
      {
        p[i]->ShowAccount();
        user = i;
      }
    }    
  }  
  if (user == -1)
  {
    cout<<endl;
    cout << "ERROR: WRONG CARD & PIN"<<endl;
    InsertPIN();
  }
}
void Screen::Menu()
{
  int input;
  cout<<endl;
  cout<<"------SELECT MENU------"<<endl;
  cout<<"1. DEPOSIT"<<endl;
  cout<<"2. WITHDRAW"<<endl;
  cout<<"3. EXIT"<<endl;
  cout<<"INSERT NUMBER: ";
  cin>>input;
  switch (input){
    case 1:
      cout<<endl;
      cout<<"DESPOSIT: ";
      cin >>input;
      p[user]->Desposit(input);
      break;
    case 2:
      cout<<endl;
      cout<<"WITHDRAW: ";
      cin>>input;
      if(p[user]->Withdraw(input)) p[user]->ShowAccount();
      break;
    case 3:
      cout<<endl;
      cout<<"BYE";
      for (int i=0; i<AccountNumber; i++)
      {
        delete p[i];
      }
      exit = 1;
      break;
  }
}


int main (void)
{
  Screen bank;
  for (int i=0; i<AccountNumber; i++)
  {
    p[i] = new Account(AccountData[i], PinData[i], BalanceData[i]);
    // p[i]->ShowAccount();
  }
  bank.InsertPIN();
  while(1)
  {
    bank.Menu();
    if (bank.exit == 1) break;
  }
  return 0;
}

