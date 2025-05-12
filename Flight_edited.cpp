#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <memory>
#include <random>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;

void mainMenu();

class Flight
{
private:
    string destination;
    int flightNumber;
    string departureDate;
    int duration;
    float price;
    int availableSeats;

public:
    Flight(const string &dest, int num, const string &date, int dur, float pr, int seats)
        : destination(dest), flightNumber(num), departureDate(date), duration(dur), price(pr), availableSeats(seats) {}

    // Getters
    string getDestination() const { return destination; }
    int getFlightNumber() const { return flightNumber; }
    string getDepartureDate() const { return departureDate; }
    int getDuration() const { return duration; }
    float getPrice() const { return price; }
    int getAvailableSeats() const { return availableSeats; }

    // Setters
    void setAvailableSeats(int seats) { availableSeats = seats; }

    virtual void displayFlightDetails() const
    {
        cout << "Destination: " << destination << endl;
        cout << "Flight Number: " << flightNumber << endl;
        cout << "Departure Date: " << departureDate << endl;
        cout << "Duration: " << duration << " hours" << endl;
        cout << "Price: Rs. " << price << endl;
        cout << "Available Seats: " << availableSeats << endl;
    }

    virtual ~Flight() {}
};

class DubaiFlight : public Flight
{
public:
    DubaiFlight() : Flight("Dubai", 498, "08-01-2022 8:00 AM", 10, 14000, 100) {}

    void displayFlightDetails() const override
    {
        cout << "__________Welcome to Dubai Emirates__________" << endl;
        Flight::displayFlightDetails();
    }
};

class CanadaFlight : public Flight
{
public:
    CanadaFlight() : Flight("Canada", 198, "09-01-2022 2:00 PM", 20, 34000, 100) {}

    void displayFlightDetails() const override
    {
        cout << "__________Welcome to Canadian Airlines__________" << endl;
        Flight::displayFlightDetails();
    }
};

class Management
{
public:
    Management()
    {
        mainMenu();
    }
};

class Customer
{
private:
    int customerId;
    string name;
    string gender;
    int age;
    string address;
    string contactNumber;

public:
    Customer(int id, const string &custName, const string &custGender, int custAge, const string &custAddress, const string &contact)
        : customerId(id), name(custName), gender(custGender), age(custAge), address(custAddress), contactNumber(contact) {}

    // Getters
    int getCustomerId() const { return customerId; }
    string getName() const { return name; }
    string getGender() const { return gender; }
    int getAge() const { return age; }
    string getAddress() const { return address; }
    string getContactNumber() const { return contactNumber; }

    // Save customer details to file
    void saveToFile(ofstream &out) const
    {
        out << customerId << "," << name << "," << gender << "," << age << "," << address << "," << contactNumber << endl;
    }

    // Load customer details from file
    static Customer loadFromFile(ifstream &in)
    {
        int id, age;
        string name, gender, address, contact;
        char delimiter;

        in >> id >> delimiter;
        getline(in, name, ',');
        getline(in, gender, ',');
        in >> age >> delimiter;
        getline(in, address, ',');
        getline(in, contact);

        return Customer(id, name, gender, age, address, contact);
    }

    // Display customer details
    void displayCustomerDetails() const
    {
        cout << "Customer ID: " << customerId << endl;
        cout << "Name: " << name << endl;
        cout << "Gender: " << gender << endl;
        cout << "Age: " << age << endl;
        cout << "Address: " << address << endl;
        cout << "Contact Number: " << contactNumber << endl;
    }
};

class Details
{
public:
    static string name, gender;
    int phoneNo;
    int age;
    string add;
    static int cId;
    char arr[100];

    void information()
    {
        cout << "\nEnter the customer ID:";
        cin >> cId;
        cout << "\nEnter the name :";
        cin >> name;
        cout << "\nEnter the age :";
        cin >> age;
        cout << "\n Address :";
        cin >> add;
        cout << "\n Gender :";
        cin >> gender;
        cout << "Your details are saved with us\n"
             << endl;
    }
};

int Details::cId;
string Details::name;
string Details::gender;

class Booking;

class Booking
{
private:
    int bookingId;
    int seatNumber;
    string mealPreference;
    float baggageWeight;
    float extraBaggageCharges;

public:
    Booking(int seat, const string &meal, float baggage)
        : seatNumber(seat), mealPreference(meal), baggageWeight(baggage), extraBaggageCharges(0.0f)
    {
        bookingId = generateBookingId();
        calculateExtraBaggageCharges();
    }

    int generateBookingId()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(10000, 99999);
        return dis(gen);
    }

    void calculateExtraBaggageCharges()
    {
        if (baggageWeight > 20.0f) // Assuming 20kg is the free baggage limit
        {
            extraBaggageCharges = (baggageWeight - 20.0f) * 500; // Rs. 500 per extra kg
        }
    }

    // Save booking details to file
    void saveToFile(ofstream &out) const
    {
        out << bookingId << "," << seatNumber << "," << mealPreference << "," 
            << baggageWeight << "," << extraBaggageCharges << endl;
    }

    // Load booking details from file
    static Booking loadFromFile(ifstream &in)
    {
        int id, seat;
        string meal;
        float baggage, extraCharges;
        char delimiter;

        in >> id >> delimiter >> seat >> delimiter;
        getline(in, meal, ',');
        in >> baggage >> delimiter >> extraCharges;

        Booking booking(seat, meal, baggage);
        booking.bookingId = id;
        booking.extraBaggageCharges = extraCharges;
        return booking;
    }

    void displayBookingDetails() const
    {
        cout << "Booking ID: " << bookingId << endl;
        cout << "Seat Number: " << seatNumber << endl;
        cout << "Meal Preference: " << mealPreference << endl;
        cout << "Baggage Weight: " << baggageWeight << " kg" << endl;
        cout << "Extra Baggage Charges: Rs. " << extraBaggageCharges << endl;
    }
};

class BookingManager
{
public:
    static void createBooking(Flight &flight)
    {
        if (flight.getAvailableSeats() <= 0)
        {
            cout << "Sorry, no seats are available on this flight." << endl;
            return;
        }

        int seatNumber;
        string mealPreference;
        float baggageWeight;

        cout << "Enter seat number (1 to " << flight.getAvailableSeats() << "): ";
        cin >> seatNumber;

        if (seatNumber < 1 || seatNumber > flight.getAvailableSeats())
        {
            cout << "Invalid seat number. Please try again." << endl;
            return;
        }

        cout << "Enter meal preference (Veg/Non-Veg): ";
        cin >> mealPreference;

        cout << "Enter baggage weight (in kg): ";
        cin >> baggageWeight;

        Booking booking(seatNumber, mealPreference, baggageWeight);
        flight.setAvailableSeats(flight.getAvailableSeats() - 1);

        cout << "Booking successful!" << endl;
        booking.displayBookingDetails();
    }
};

class registration
{
public:
    static int choice;
    int back;
    static float charges;

    void flights()
    {
        std::vector<std::unique_ptr<Flight>> flightOptions;
        flightOptions.push_back(std::make_unique<DubaiFlight>());
        flightOptions.push_back(std::make_unique<CanadaFlight>());

        for (size_t i = 0; i < flightOptions.size(); ++i)
        {
            cout << (i + 1) << ". Flight to " << flightOptions[i]->getDestination() << endl;
        }

        cout << "\nSelect the flight you want to book: ";
        cin >> choice;

        if (choice < 1 || choice > static_cast<int>(flightOptions.size()))
        {
            cout << "Invalid choice. Returning to main menu." << endl;
            return;
        }

        // Get the selected flight
        Flight* selectedFlight = flightOptions[choice - 1].get();
        
        // Display flight details
        cout << "\nSelected Flight Details:" << endl;
        selectedFlight->displayFlightDetails();
        
        // Calculate charges
        charges = selectedFlight->getPrice();
        
        // Create booking
        BookingManager::createBooking(*selectedFlight);
    }
};

float registration::charges;
int registration::choice;

class ticket : public registration, Details
{
public:
    char arr[100];
    void Bill()
    {
        string destination = "";
        ofstream outf("records.txt");
        {
            outf << "_____________Indigo Airways____________" << endl;
            outf << "______________Ticket_________________" << endl;
            outf << "_____________________________________" << endl;

            outf << "Customer ID:" << Details::cId << endl;
            outf << "Customer Name:" << Details::name << endl;
            outf << "Customer Gender:" << Details::gender << endl;
            outf << "\tDescription" << endl
                 << endl;

            if (registration::choice == 1)
            {
                destination = "Dubai";
            }

            else if (registration::choice == 2)
            {
                destination = "Canada";
            }
            else if (registration::choice == 3)
            {
                destination = "UK";
            }
            else if (registration::choice == 4)
            {
                destination = "USA";
            }
            else if (registration::choice == 5)
            {
                destination = "Australia";
            }
            else if (registration::choice == 6)
            {
                destination = "Europe";
            }

            outf << "Destination\t\t" << destination << endl;
            outf << "Flight cost :\t\t" << registration::charges << endl;
        }
        outf.close();
    }
    void dispBill()
    {
        ifstream ifs("records.txt");
        {
            if (!ifs)
            {
                cout << "File error!" << endl;
            }
            while (!ifs.eof())
            {
                ifs.getline(arr, 100);
                cout << arr << endl;
            }
        }
        ifs.close();
    }
};


inline void PrintTicketDetails(ticket &t)
{
    t.dispBill();
    cout << "Press any key to go back to the main menu:" << endl;
    int back;
    cin >> back;

    if (back == 1)
    {
        mainMenu();
    }
    else
    {
        mainMenu();
    }
}

// Adding persistent storage for customers and bookings
#include <vector>

class DataManager
{
public:
    static void saveCustomers(const std::vector<Customer> &customers)
    {
        ofstream out("customers.txt");
        if (!out)
        {
            cout << "Error opening customers.txt for writing." << endl;
            return;
        }

        for (const auto &customer : customers)
        {
            customer.saveToFile(out);
        }

        out.close();
    }

    static std::vector<Customer> loadCustomers()
    {
        std::vector<Customer> customers;
        ifstream in("customers.txt");
        if (!in)
        {
            cout << "No customer data found." << endl;
            return customers;
        }

        while (in.peek() != EOF)
        {
            customers.push_back(Customer::loadFromFile(in));
        }

        in.close();
        return customers;
    }

    static void saveBookings(const std::vector<Booking> &bookings)
    {
        ofstream out("bookings.txt");
        if (!out)
        {
            cout << "Error opening bookings.txt for writing." << endl;
            return;
        }

        for (const auto &booking : bookings)
        {
            booking.saveToFile(out);
        }

        out.close();
    }

    static std::vector<Booking> loadBookings()
    {
        std::vector<Booking> bookings;
        ifstream in("bookings.txt");
        if (!in)
        {
            cout << "No booking data found." << endl;
            return bookings;
        }

        while (in.peek() != EOF)
        {
            bookings.push_back(Booking::loadFromFile(in));
        }

        in.close();
        return bookings;
    }
};

// Fixing the incorrect use of 'static' for customers and bookings vectors
void mainMenu()
{
    int lchoice;
    int back;

    cout << "\t               Indigo Airways \n"
         << endl;
    cout << "\t______________Main Menu______________" << endl;

    cout << "\t____________________________________________________" << endl;
    cout << "\t|\t\t\t\t\t\t|" << endl;

    cout << "\t|\t Press 1 to add the Customer Details    \t|" << endl;
    cout << "\t|\t Press 2 for Flight Registration        \t|" << endl;
    cout << "\t|\t Press 3 for Ticket and Charges         \t|" << endl;
    cout << "\t|\t Press 4 to View Saved Customers        \t|" << endl;
    cout << "\t|\t Press 5 to View Saved Bookings         \t|" << endl;
    cout << "\t|\t Press 6 to Exit                        \t|" << endl;
    cout << "\t|\t\t\t\t\t\t|" << endl;
    cout << "\t_____________________________________________________" << endl;

    cout << "Enter the choice : ";
    cin >> lchoice;

    Details d;
    registration *r;
    ticket t;
    std::vector<Customer> customers;
    std::vector<Booking> bookings;

    switch (lchoice)
    {
    case 1:
    {
        cout << "__________Customers__________\n"
             << endl;
        d.information();
        customers.push_back(Customer(Details::cId, Details::name, Details::gender, d.age, d.add, std::to_string(d.phoneNo)));
        DataManager::saveCustomers(customers);
        cout << "Press any key to go back to Main menu ";
        cin >> back;

        if (back == 1)
        {
            mainMenu();
        }
        else
        {
            mainMenu();
        }
        break;
    }

    case 2:
    {
        cout << "________Book a flight using this system ____________\n"
             << endl;
        r = new registration();
        r->flights();
        delete r;
        break;
    }

    case 3:
    {
        cout << "_____GET YOUR TICKET____\n"
             << endl;
        t.Bill();

        cout << "Your ticket is printed, you can collect it \n"
             << endl;
        cout << "Press 1 to display your ticket ";

        cin >> back;

        if (back == 1)
        {
            t.dispBill();
            cout << "Press any key to go back to main menu:";
            cin >> back;
            if (back == 1)
            {
                mainMenu();
            }
            else
            {
                mainMenu();
            }
        }
        else
        {
            mainMenu();
        }
        break;
    }

    case 4:
    {
        cout << "__________Saved Customers__________\n"
             << endl;
        customers = DataManager::loadCustomers();
        for (const auto &customer : customers)
        {
            customer.displayCustomerDetails();
            cout << "-----------------------------" << endl;
        }
        cout << "Press any key to go back to Main menu ";
        cin >> back;
        mainMenu();
        break;
    }

    case 5:
    {
        cout << "__________Saved Bookings__________\n"
             << endl;
        bookings = DataManager::loadBookings();
        for (const auto &booking : bookings)
        {
            booking.displayBookingDetails();
            cout << "-----------------------------" << endl;
        }
        cout << "Press any key to go back to Main menu ";
        cin >> back;
        mainMenu();
        break;
    }

    case 6:
    {
        cout << "\n\n\t_________Thank-you_______" << endl;
        break;
    }

    default:
    {
        cout << "Invalid input, Please try again!\n"
             << endl;
        mainMenu();
        break;
    }
    }
}

int main()
{
    try
    {
        Management m;
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}