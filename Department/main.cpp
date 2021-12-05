#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

#define tab "\t"

class Human
{
protected:
	string last_name;
	string first_name;
	unsigned int age;
public:
	const string& get_last_name()const
	{
		return last_name;
	}
	const string& get_first_name()const
	{
		return first_name;
	}
	unsigned int get_age()const
	{
		return age;
	}
	void set_last_name(const string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}
	Human(const string& last_name, const string& first_name, unsigned int age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	virtual ostream& print(ostream& os)const
	{
		os.width(10);
		os << std::left;
		os << last_name;
		os.width(10);
		os << std::left;
		os << first_name;
		os.width(5);
		os << age;
		return os;
	}
	virtual ofstream& print(ofstream& os)const
	{
		os.width(15);
		os << left;
		os << typeid(*this).name() << " | ";
		os.width(10);
		os << std::left;
		os << last_name << " | ";
		os.width(10);
		os << std::left;
		os << first_name << " | ";
		os.width(5);
		os << age << " | ";
		return os;
	}
	virtual istream& input(istream& is) 
	{
		return is >> last_name >> first_name >> age;
	}

};
ostream& operator<<(ostream& os, const Human& obj)
{
	return obj.print(os);
}
ofstream& operator<<(ofstream& os, const Human& obj)
{
	return obj.print(os);
}
istream& operator<<(istream& is, Human& obj)
{
	return obj.input(is);
}

class Employee :public Human
{
	std::string position;
public:
	const std::string& get_position()const
	{
		return position;
	}
	void set_position(const std::string& position)
	{
		this->position = position;
	}
	Employee(
		const string& last_name, const string& first_name, unsigned int age,
		const std::string& position) 
		:Human(last_name, first_name, age)
	{
		this->position = position;
		cout << "EConstructor:\t" << this << endl;
	}
	~Employee()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	virtual double count_salary()const
	{
		return 0;
	}
};
class ResidentEmployee :public Employee
{
	double salary;
public:
	/*double get_salary()const
	{
		return salary;
	}
	void set_salary(double salary)
	{
		this->salary = salary;
	}*/
	ResidentEmployee
	(const string& last_name, const string& first_name, unsigned int age,
		const std::string& position, double salary)
		:Employee(last_name, first_name, age, position)
	{
		this->salary = salary;
		cout << "RConstructor:\t" << this << endl;
	}
	~ResidentEmployee()
	{
		cout << "RDestructor:\t" << this << endl;
	}
	double count_salary()const
	{
		return salary;
	}
};
class HourEmployee :public Employee
{
	double rate;
	int complete_hours;
public:
	HourEmployee
	(
		const string& last_name, const string& first_name, unsigned int age,
		const std::string& position,
		double rate,
		int complete_hours
	) :Employee(last_name, first_name, age, position), rate(rate), complete_hours(complete_hours)
	{
		cout << "HEConstructor:\t" << this << endl;
	}
	~HourEmployee()
	{
		cout << "HEDestructor:\t" << this << endl;
	}
	double count_salary()const
	{
		return rate * complete_hours;
	}
};


void main()
{
	setlocale(LC_ALL, "");
	Employee* department[] =
	{
		new HourEmployee("Noris", "Chak", 23, "Helper", 20000, 20),
		new HourEmployee("Skaletty", "Antonio", 26, "Weapons distribution", 25000, 10),
		new ResidentEmployee("Ladan", "Ben", 43, "Politic", 320000),
		new ResidentEmployee("Karadiz", "Ricardo", 54, "Director", 90000),
		new ResidentEmployee("Shultz", "Osman", 58, "Detective", 62000),
		new HourEmployee("Tesla", "Nikola", 37, "Physics", 2600, 40)
	};
	double total_money = 0;
	for (int i = 0; i < sizeof(department) / sizeof(department[0]); i++)
	{
		cout << *department[i] << "salary: " << department[i]->count_salary() << endl;
		total_money += department[i]->count_salary();
	}
	cout << "Total money: " << setprecision(20) << total_money << "USD" << endl;
	for (int i = 0; i < sizeof(department) / sizeof(department[0]); i++)
	{
		delete department[i];
	}

}