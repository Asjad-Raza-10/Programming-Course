#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class InsufficientFundsException : public exception
{
  public:
	const char *what() const noexcept override
	{
		return "Error: Insufficient funds.";
	}
};

class InvalidTransactionAmountException : public exception
{
  public:
	const char *what() const noexcept override
	{
		return "Error: Invalid transaction amount. Must be greater than 0.";
	}
};

class bankAccount
{
  private:
	double Balance;
	double Deposit;
	double Withdraw;
	string transactions[5][2];
	int count;

  public:
	bankAccount(int b = 0)
	{
		Deposit = 0;
		Withdraw = 0;
		Balance = b;
		count = 0;
		for (int i = 0; i < 5; i++)
		{
			transactions[i][0] = "";
			transactions[i][1] = "";
		}
	}

	void deposit(double d)
	{
		if (d < 0)
		{
			throw InvalidTransactionAmountException();
		}
		Balance += d;
		int index = count++ % 5;
		transactions[index][0] = "Deposit: ";
		transactions[index][1] = to_string(d);
		cout << "Transaction Successful!" << endl;
	}

	void withdraw(double w)
	{
		if (w > Balance)
		{
			throw InsufficientFundsException();
		}
		Balance -= w;
		int index = count++ % 5;
		transactions[index][0] = "Withdraw: ";
		transactions[index][1] = to_string(w);
		cout << "Transaction Successful!" << endl;
	}

	void getTransactions()
	{
		cout << "--- Transaction History (Last 5 Transactions) ---" << endl;
		for (int i = 0; i < 5; i++)
		{
			if (!transactions[i][0].empty())
				cout << transactions[i][0] << transactions[i][1] << endl;
		}
	}
};

int main()
{
	bankAccount account1;
	double n = 0.0;
	char choice = '\0';

	cout << "Enter D for deposit and W for withdrawl, then enter the amount. Enter X to stop." << endl;

	while (true)
	{
		try
		{
			cout << "Enter Choice: ";
			cin >> choice;
			if (choice == 'X' || choice == 'x')
			{
				break;
			}
			else if (choice == 'D' || choice == 'd')
			{
				cout << "Enter Amount: ";
				cin >> n;
				account1.deposit(n);
			}
			else if (choice == 'W' || choice == 'w')
			{
				cout << "Enter Amount: ";
				cin >> n;
				account1.withdraw(n);
			}
			else
			{
				cout << "Invalid Input!" << endl;
			}
		}
		catch (const exception &e)
		{
			cout << e.what() << endl;
		}
	}

	account1.getTransactions();

	return 0;
}
