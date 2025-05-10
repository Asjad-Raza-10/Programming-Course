#include <cstring>
#include <iostream>
using namespace std;

class EmailValidator
{
  public:
	static bool isValidEmail(char *email)
	{
		int atCount = 0;
		int atIndex = -1;
		int len = strlen(email);

		for (int i = 0; email[i] != '\0'; i++)
		{
			if (email[i] == '@')
			{
				atCount++;
				atIndex = i;
			}
		}

		if (atCount != 1)
		{
			throw "Invalid email: Email must contain exactly one '@' character.";
		}

		if (atIndex == 0 || atIndex == len - 1)
		{
			throw "Invalid email: Email must have characters before and after '@'.";
		}

		const char *validSuffixes[] = {".com", ".org", ".net"};
		int suffixCount = sizeof(validSuffixes) / sizeof(validSuffixes[0]);

		bool validSuffix = false;
		for (int i = 0; i < suffixCount; i++)
		{
			int suffixLen = strlen(validSuffixes[i]);
			if (len >= suffixLen && strcmp(email + len - suffixLen, validSuffixes[i]) == 0)
			{
				validSuffix = true;
				break;
			}
		}

		if (!validSuffix)
		{
			throw "Invalid email: Email must end with a valid domain (.com, .org, .net).";
		}

		return true;
	}
};

class User
{
  private:
	char email[100];

  public:
	void setEmail(char *em)
	{
		while (true)
		{
			try
			{
				if (EmailValidator::isValidEmail(em))
				{
					strcpy(email, em);
					cout << "Email set successfully: " << email << endl;
					break;
				}
			}
			catch (const char *msg)
			{
				cout << msg << endl;
				cout << "Enter your email address: ";
				cin >> em;
			}
		}
	}
};

int main()
{
	User user1;
	char input[100];

	cout << "Enter your email address: ";
	cin >> input;

	user1.setEmail(input);

	return 0;
}
