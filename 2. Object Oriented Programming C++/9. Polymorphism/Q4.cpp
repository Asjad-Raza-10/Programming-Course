#include <iostream>

using namespace std;

class TransportUnit
{
public:
	virtual void transmitData() = 0;
	virtual void showType() = 0;
};

class GroundUnit :public TransportUnit
{
public:

	void transmitData() override
	{
		CalibrateWheels();
	}

	virtual void CalibrateWheels() = 0;

	void showType() override
	{
		cout << "This is a generic transport unit." << endl;
		cout << "----------------------------------------------------------" << endl << endl;
	}
};

class DeliveryBot :public GroundUnit
{
public:

	void CalibrateWheels() override
	{
		cout << "Delivery Bot: Package status OK, location: Street 23." << endl;
	}

	void showType() override
	{
		GroundUnit::showType();
	}
};

class SurveillanceRover :public GroundUnit
{
public:

	void CalibrateWheels() override
	{
		cout << "SurveillanceRover: Patrolling perimeter. All clear." << endl;
	}

	void showType() override
	{
		GroundUnit::showType();
	}
};

class AerialUnit :public TransportUnit
{
public:

	void transmitData() override
	{
		adjustAltitude();
	}

	virtual void adjustAltitude() = 0;

	void showType() override
	{
		cout << "This is a generic transport unit." << endl;
		cout << "----------------------------------------------------------" << endl << endl;
	}
};

class Quadcopter :public AerialUnit
{
public:

	void adjustAltitude() override
	{
		cout << "Quadcopter: Scanning area. Wind speed normal." << endl;
	}

	void showType() override
	{
		AerialUnit::showType();
	}
};

class SurveillanceDrone :public AerialUnit
{
public:

	void adjustAltitude() override
	{
		cout << "SurveillanceDrone: Motion detected in Sector A." << endl;
	}

	void showType() override
	{
		AerialUnit::showType();
	}
};

int main()
{
	TransportUnit* pointer[4];
	pointer[0] = new DeliveryBot();
	pointer[1] = new SurveillanceRover();
	pointer[2] = new Quadcopter();
	pointer[3] = new SurveillanceDrone();

	cout << endl << "Calling transmitData() and showType() through base class pointers:" << endl << endl;

	for (int i = 0; i < 4; i++)
	{
		pointer[i]->transmitData();
		pointer[i]->showType();
	}

	for (int i = 0; i < 3; i++)
	{
		delete[]pointer[i];
	}


	return 0;
}