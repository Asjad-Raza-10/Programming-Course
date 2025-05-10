#include <iostream>
using namespace std;

class Vehicle
{
private:
	string OwnerName;
	string VehicleNo;
public:
	Vehicle(string on = "", string vn = "") :OwnerName(on), VehicleNo(vn) {}

	string getOwnerName()
	{
		return OwnerName;
	}

	string getVehicleNo()
	{
		return VehicleNo;
	}

	void setOwnerName(string on)
	{
		OwnerName = on;
	}

	void setVehicleNo(string vn)
	{
		VehicleNo = vn;
	}
	
	~Vehicle()
	{
	}
};

class Car : public Vehicle
{
private:
	string FuelType;
	unsigned int EngineCapacity;
	unsigned int DisanceTravelled;
	float FuelConsumed;
public:
	Car(string on = "", string vn = "", string ft = "", unsigned int e = 0, unsigned int d = 0, float fc = 0) :Vehicle(on, vn), FuelType(ft), EngineCapacity(e), DisanceTravelled(d), FuelConsumed(fc) {}

	float CalculateMileage()
	{
		return (DisanceTravelled / FuelConsumed);
	}

	string getFuelType()
	{
		return FuelType;
	}

	unsigned int getEngineCapacity()
	{
		return EngineCapacity;
	}

	unsigned int getDisanceTravelled()
	{
		return DisanceTravelled;
	}

	float getFuelConsumed()
	{
		return FuelConsumed;
	}

	void setFuelType(string ft)
	{
		FuelType = ft;
	}

	void setEngineCapacity(unsigned int e)
	{
		EngineCapacity = e;
	}

	void setDisanceTravelled(unsigned int d)
	{
		DisanceTravelled = d;
	}

	void setFuelConsumed(float f)
	{
		FuelConsumed = f;
	}

	~Car()
	{
	}
};

class ElectricCar : public Car
{
private:
	unsigned int BatteryCapacity;
	unsigned int ChargingTime;

public:
	ElectricCar(string on = "", string vn = "", string ft = "Electric", unsigned int e = 0, unsigned int d = 0, float fc = 0, unsigned int bc = 0, unsigned int ct = 0) :Car(on, vn, ft, e, d, fc), BatteryCapacity(bc), ChargingTime(ct) {}

	bool isEcoFriendly()
	{
		if (getFuelType() == "Electric" || getEngineCapacity() > 50)
			return true;
		return false;
	}

	double RegistrationFee(double Basefee)
	{
		if (isEcoFriendly())
		{
			return (0.8 * Basefee);
		}
		return Basefee;
	}

	bool MaintenanceCheck()
	{
		if (ChargingTime > 5 || getDisanceTravelled() > 10000)
			return true;
		return false;
	}

	unsigned int getBatteryCapacity()
	{
		return BatteryCapacity;
	}

	unsigned int getChargingTime()
	{
		return ChargingTime;
	}

	void setBatteryCapacity(unsigned int s)
	{
		BatteryCapacity = s;
	}

	void setChargingTime(unsigned int s)
	{
		ChargingTime = s;
	}

	~ElectricCar()
	{
	}
};

int main()
{
	ElectricCar EC ("Asjad Raza", "ADN 014", "Electric", 1499, 10000, 800, 60, 6);

	cout << endl << "Owner: " << EC.getOwnerName() << endl << "Vehicle No: " << EC.getVehicleNo() << endl << "Fuel Type: " << EC.getFuelType() << endl << "Mileage: " << EC.CalculateMileage() << " km/kWh" << endl << "Eco-Friendly: " << (EC.isEcoFriendly() ? "Yes" : "No") << endl << "Battery Capacity: " << EC.getEngineCapacity() << endl << "Charging Capacity: " << EC.getBatteryCapacity() << " kWh" << endl << "Charging Time: " << EC.getChargingTime() << " hours" << endl << "Registration Fee (after discount): " << EC.RegistrationFee(10000) << endl << "Maintenance Check: " << (EC.MaintenanceCheck() ? "Battery Maintenance Recommended" : "Not Needed") << endl;
	
	return 0;
}