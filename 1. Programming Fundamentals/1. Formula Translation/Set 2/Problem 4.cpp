#include<iostream>
using namespace std;

int main()
{
	float zgr = 386.57, wrp = 524.43, frs = 186.72, piz = 2497.95, drk = 78.32;
	float zgr_amt, wrp_amt, frs_amt, piz_amt, drk_amt;
	float t1, t2, t3, t4, t5, subt, stax, bill;

	cout << "-Zinger: Rs 386.57 \n-Special Wrap: Rs 524.43 \n-Fries : Rs 186.72 \n-Large Kebab stuffed Pizza : Rs 2497.95 \n-Regular drink : Rs 78.32\n\n Enter the quantity of the item you want to purchase, enter 0 for an item you don't want.\n";

	cout << endl << "Zinger Burger:";
	cin >> zgr_amt;
	t1 = zgr * zgr_amt;
	cout << zgr_amt << " Zinger Burgers : " << zgr_amt << " * " << zgr << "= " << t1;

	cout << endl << "Special Wrap: ";
	cin >> wrp_amt;
	t2 = wrp * wrp_amt;
	cout << wrp_amt << " Special Wraps : " << wrp_amt << " * " << wrp << "= " << t2;

	cout << endl << "Fries: ";
	cin >> frs_amt;
	t3 = frs * frs_amt;
	cout << frs_amt << " Fries : " << frs_amt << " * " << frs << "= " << t3;

	cout << endl << "Large Kabab Stuffed Pizza: ";
	cin >> piz_amt;
	t4 = piz * piz_amt;
	cout << piz_amt << " Large Kabab Stuffed Pizza : " << piz_amt << " * " << piz << "= " << t4;

	cout << endl << "Regular Drink: ";
	cin >> drk_amt;
	t5 = drk * drk_amt;
	cout << drk_amt << " Regular Drink: " << drk_amt << " * " << drk << "= " << t5;

	subt = t1 + t2 + t3 + t4 + t5;

	cout << "\n\n Subtotal: " << subt;

	stax = 1.16 * subt;
	cout << "\n 16% sale tax: " << stax;

	bill = subt + stax;
	cout << "\n\n Total Bill to Pay: " << bill;

	cout << endl;
	return 0;
	system("pause");
}