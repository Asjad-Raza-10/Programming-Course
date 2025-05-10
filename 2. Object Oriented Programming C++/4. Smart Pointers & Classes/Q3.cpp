#include <iostream>
#include <memory>
using namespace std;

class BankAccount
{
private:
	int account_number;
	string holder_name;
	float balance;

public:
	BankAccount()
	{
		account_number = 0;
		holder_name = "";
		balance = 0.0;
		cout << "Account Created with default values." << endl;
	}

	BankAccount(int an, string hn, float b)
	{
		account_number = an;
		holder_name = hn;
		balance = b;
		cout << "Account " << account_number << " created for " << holder_name << " with balance: " << balance << endl;
	}

	int deposit(int d)
	{
		cout << "Account " << account_number << " Balance: " << balance << endl;
		balance += d;
		cout << "Deposited: " << d << " New Balance: " << balance << endl;
		cout << "Account Balance after deposit: " << balance << endl;
		return balance;
	}

	int withdraw(int d)
	{
		cout << "Account " << account_number << " Balance: " << balance << endl;

		if (d > balance)
		{
			cout << "Insufficient Funds to Withdraw " << d << endl;
			cout << "Current balance " << balance << " is less than the requested amount";
		}
		else
		{
			balance -= d;
			cout << "Withdrawn: " << d << " New Balance: " << balance << endl;
			cout << "Account Balance after withdraw: " << balance << endl;
			return balance;
		}
		
		return balance;
	}

	int getBalance()
	{
		cout << "Account " << account_number << " Balance: " << balance << endl;
		return balance;
	}

};


int main()
{
	BankAccount Asjad(1, "Asjad", 1000);
	int balance = 0;

	balance = Asjad.deposit(500);
	balance = Asjad.withdraw(700);
	balance = Asjad.getBalance();
	balance = Asjad.withdraw(1000);

	return 0;
}