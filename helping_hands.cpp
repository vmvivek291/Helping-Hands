#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
 
namespace report
{
    inline void printData()
    {
        cout<<endl<<endl;
        cout<< "Welcome to SHOPBAZAAR!!!"<<endl<<endl;
        cout<<"Please choose the place you want to apply for:"<<endl;
        cout<<"1. Rajajinagar"<<endl;
        cout<<"2. Jayanagar"<<endl;
        cout<<"3. Exit"<<endl;
    }
    
}

class Employee
{
    public:
        string typeOfShop;
        string section;
        string name;
};

class Base 
{
    protected:
    static vector<string> confirmedNames;
};

std::vector<std::string> Base::confirmedNames = {};

class Small : public Base 
{

    protected:
        int grocery_vacancies;

    public:
        Small() : grocery_vacancies(2) {}

        int getGroceryVacancies() const
        {
            return grocery_vacancies;
        }

        bool accessNames(const string &name) const
        {
            return (find(confirmedNames.begin(), confirmedNames.end(), name) != confirmedNames.end());
        }

        void appendNames(const string &name)
        {
            confirmedNames.push_back(name);
        }

        void reduceGroceryVacancies()
        {
            grocery_vacancies--;
        }
};

class Medium : public Small
{

    protected:
        int stationary_vacancies;

    public:
        Medium() : stationary_vacancies(2) {}

        int getStationaryVacancies() const
        {
            return stationary_vacancies;
        }

        bool accessNames(const string &name) const
        {
            return (find(confirmedNames.begin(), confirmedNames.end(), name) != confirmedNames.end());
        }

        void appendNames(const string &name)
        {
            confirmedNames.push_back(name);
        }

        void reduceStationaryVacancies()
        {
            stationary_vacancies--;
        }
};

class Large : public Medium
{

    protected:
        int meat_vacancies;
        int bakery_vacancies;

    public:
        Large() : meat_vacancies(2), bakery_vacancies(2) {}

        int getMeatVacancies() const
        {
            return meat_vacancies;
        }

        int getBakeryVacancies() const
        {
            return bakery_vacancies;
        }

        bool accessNames(const string &name) const
        {
            return (find(confirmedNames.begin(), confirmedNames.end(), name) != confirmedNames.end());
        }

        void appendNames(const string &name)
        {
            confirmedNames.push_back(name);
        }

        void reduceMeatVacancies()
        {
            meat_vacancies--;
        }

        void reduceBakeryVacancies()
        {
            bakery_vacancies--;
        }
};

class Rajajinagar
{
    private:
        vector<Employee> employees;
        Small *smallObj;
        Large *largeObj;

    public:
    int ch;
    std::string filename;

    Rajajinagar() : smallObj(nullptr), largeObj(nullptr) {}

    string readtxtfile(const string &file) 
    {
        ifstream infile(file);
        string content;

        if (infile.is_open()) 
        {
            if (std::getline(infile, content)) 
            {
                infile.close();
                filename = content; 
                return content;
            } 
            else 
            {
                infile.close();
                return "";
            }
        } 
        else 
        {
            std::cout << "Unable to open file: " << file << std::endl;
            return "";
        }
    }


        int createObject()
        {
            cout << "Choose the type of shop : " << endl;
            cout << "1. Large" << endl
                << "2. Small" << endl;
            cin >> ch;

            switch (ch)
            {
            case 1:
                if (!largeObj)
                    largeObj = new Large();
                break;

            case 2:
                if (!smallObj)
                    smallObj = new Small();
                break;
            }

            return ch;
        }

        int chooseVacancy(int choice)
        {
            ch = choice;
            if (ch == 1)
            {
                cout << "1. Grocery" << endl
                    << "2. Stationary" << endl
                    << "3. Bakery" << endl
                    << "4. Meat";
                cout << endl;
                cin >> ch;
                return ch;
            }
            else
            {
                cout << "1. Grocery";
                cout << endl;
                cin >> ch;
                return ch;
            }
        }

        void confirmVacancy(const string &name, int ch,int type)
        {
            if ((largeObj && largeObj->accessNames(name)) || (smallObj && smallObj->accessNames(name)))
            {
                cout << "\nVacancy already exists for this object." << endl;
                return;
            }

            if(ch==1)
            {
            
                switch(type)
                {
                    case 1:
                        if (largeObj && largeObj->getGroceryVacancies() > 0)
                        {
                            largeObj->appendNames(name);
                            largeObj->reduceGroceryVacancies();

                            Employee employee;
                            employee.name = name;
                            employee.typeOfShop = "Large";
                            employee.section = "Grocery";
                            employees.push_back(employee);

                            writeToFile(filename);

                            cout << "Vacancy confirmed for grocery by " << name << "." << endl;
                        }
                        else
                        {
                            cout << "Vacancy not available for grocery." << endl;
                        }
                        break;

                    case 2: 
                        if (largeObj && largeObj->getStationaryVacancies() > 0)
                        {
                            largeObj->appendNames(name);
                            largeObj->reduceStationaryVacancies();

                            Employee employee;
                            employee.name = name;
                            employee.typeOfShop = "Large";
                            employee.section = "Stationary";
                            employees.push_back(employee);

                            writeToFile("Rajajinagar.bin");

                            cout << "Vacancy confirmed for Stationary by " << name << "." << endl;
                        }
                        else
                        {
                            cout << "Vacancy not available for Stationary." << endl;
                        }
                        break;
        

                    case 3:
                        if (largeObj && largeObj->getBakeryVacancies() > 0)
                        {
                            largeObj->appendNames(name);
                            largeObj->reduceBakeryVacancies();

                            Employee employee;
                            employee.name = name;
                            employee.typeOfShop = "Large";
                            employee.section = "Bakery";
                            employees.push_back(employee);

                            writeToFile("Rajajinagar.bin");

                            cout << "Vacancy confirmed for bakery by " << name << "." << endl;
                        }
                        else
                        {
                            cout << "Vacancy not available for bakery." << endl;
                        }
                        break;
                    

                    case 4:
                        if (largeObj && largeObj->getMeatVacancies() > 0)
                        {
                            largeObj->appendNames(name);
                            largeObj->reduceMeatVacancies();

                            Employee employee;
                            employee.name = name;
                            employee.typeOfShop = "Large";
                            employee.section = "Stationary";
                            employees.push_back(employee);

                            writeToFile("Rajajinagar.bin");

                            cout << "Vacancy confirmed for meat by " << name << "." << endl;
                        }
                        else
                        {
                            cout << "Vacancy not available for meat." << endl;
                        }
                        break;
                }

            }

            else
            {
                switch(type)
                {
                    case 1:
                        if (smallObj && smallObj->getGroceryVacancies() > 0)
                        {
                            smallObj->appendNames(name);
                            smallObj->reduceGroceryVacancies();

                            Employee employee;
                            employee.name = name;
                            employee.typeOfShop = "Small";
                            employee.section = "Grocery";
                            employees.push_back(employee);

                            writeToFile("Rajajinagar.bin");

                            cout << "Vacancy confirmed for grocery by " << name << "." << endl;
                        }
                        else
                        {
                            cout << "Vacancy not available for grocery." << endl;
                        }
                        break;
                }
            }

    }
        

        void readFromFile(const string &filename) {
            try {
                ifstream inputFile(filename, ios::binary);

                employees.clear();

                Employee employee;
                while (inputFile.read(reinterpret_cast<char *>(&employee), sizeof(Employee))) {
                    employees.push_back(employee);
                }

                inputFile.close();
            } 
            catch (const exception &e) {
                cerr << e.what() << endl;
            }
        }

        void writeToFile(const string &filename)
        {
            ofstream outputFile(filename, ios::binary | ios::trunc); // Open in trunc mode to clear existing content
            if (!outputFile)
            {
                cerr << "Error opening file: " << filename << endl;
                return;
            }

            for (const auto &employee : employees)
            {
                outputFile.write(reinterpret_cast<const char *>(&employee), sizeof(Employee));
            }

            outputFile.close();
        }

        void printData(string shop, string section) 
        {  
            for (const auto &employee : employees) 
            {
                if (employee.typeOfShop == shop && employee.section == section) 
                {
                    cout <<"Name: "<< employee.name << endl;
                }
            }
        }

        ~Rajajinagar()
        {
            delete smallObj;
            delete largeObj;
        }
};

int main()
{
    int ch;
    int type;
    int city;
    string name;
    Rajajinagar rajajinagar;

    report::printData();

    while (true) 
    {
        std::cout <<endl<<"Enter a city code (1 for Rajajinagar, 2 for Jayanagar, 3 to exit): ";
        if (!(std::cin >> city)) 
        {
            std::cout << "Invalid input. Please enter an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (city == 3) 
        {
            std::cout << "Exiting..." << std::endl;
            break; // Exit the loop
        }

        switch (city) 
        {
            case 1:
                std::cout << "Enter your name: ";
                std::cin >> name;
                ch = rajajinagar.createObject();
                rajajinagar.readtxtfile("file.txt");
                type = rajajinagar.chooseVacancy(ch);
                rajajinagar.confirmVacancy(name, ch, type);
                std::cout << "Performing actions related to Rajajinagar..." << std::endl;
                break;

            default:
                std::cout << "Invalid input" << std::endl;
                break;
        }
    }

    std::cout << "Recruitment-Vacancy Report" << std::endl << std::endl;

    // Display a section for Rajajinagar
    std::cout << "Place: Rajajinagar" << std::endl << std::endl;

    // Large Shops Section
    std::cout << "Type of Shop: LARGE" << std::endl << std::endl;
    
    // Grocery Section
    std::cout << "Section: GROCERY" << std::endl;
    rajajinagar.readFromFile(rajajinagar.filename);
    rajajinagar.printData("Large", "Grocery");
    std::cout << std::endl;

    // Stationary Section
    std::cout << "Section: STATIONARY" << std::endl;
    rajajinagar.readFromFile(rajajinagar.filename);
    rajajinagar.printData("Large", "Stationary");
    std::cout << std::endl;

    // Meat Section
    std::cout << "Section: MEAT" << std::endl;
    rajajinagar.readFromFile(rajajinagar.filename);
    rajajinagar.printData("Large", "Meat");
    std::cout << std::endl;

    // Bakery Section
    std::cout << "Section: BAKERY" << std::endl;
    rajajinagar.readFromFile(rajajinagar.filename);
    rajajinagar.printData("Large", "Bakery");
    std::cout << std::endl;

    // Small Shops Section
    std::cout << "Type of Shop: SMALL" << std::endl;

    // Grocery Section for Small Shops
    std::cout << "Section: GROCERY" << std::endl;
    rajajinagar.readFromFile(rajajinagar.filename);
    rajajinagar.printData("Small", "Grocery");
    std::cout << std::endl;


    std::cout << "End of Report" << std::endl;

    return 0;
}