#include <iostream>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Payment.h"
#include "Log.h"
#include "Location.h"

using namespace std;

// outputs abstraction object properties to the console window
void show(const Item& item)
{
    cout << item << "\n";
}

const  Payment & get_largest_payment(const Log& log) {
   return log.find_largest_payment();
}
 
double get_average_amount(const Log& log) {
    return log.find_average_amount();
}

// solution entry function
int main()
{
    Log log;
    auto test_time{ std::chrono::system_clock::now() };
 // Create shared pointers for PaymentSpec objects
    
    auto spec_bmx{std::make_shared<PaymentSpec>(PaymentSpec::CardType::CREDIT,PaymentSpec::CardScheme::VISA, PaymentSpec::PaymentType::AUTH)};
    auto p1{std::make_shared<Payment>("1234567890123456", "USD", 1520, test_time - std::chrono::hours(100), spec_bmx)};
    log.add_item(p1);

    auto p2{std::make_shared<Payment>("1234567890123456", "USD", 1520, test_time - std::chrono::hours(100),
    std::make_shared<PaymentSpec>(PaymentSpec::CardType::CREDIT,PaymentSpec::CardScheme::VISA, PaymentSpec::PaymentType::AUTH))};
    log.add_item(p2);

    /*auto filename{ "p1.csv" };
    ofstream ofs(filename);
    if (ofs)
        ofs << p1 << "\n";
    ofs.close(); 
    cout << "Saved...\n"; 

    Payment p2;
    ifstream ifs(filename);
    if (ifs)
        ifs >> p2;
    ifs.close();
    cout << "Read...\n"
         << p2 << "\n----\n";*/

    auto spec_cards{std::make_shared<PaymentSpec>(PaymentSpec
    ::CardType::EBT, PaymentSpec::CardScheme::MASTERCARD, PaymentSpec::PaymentType::CHARGEBACK)};

    log.add_item(std::make_shared<Payment>("2034277890123456", "EUR", 5200, test_time - std::chrono::hours(60), spec_cards));
    log.add_item(std::make_shared<Payment>("1034277890123456", "EUR", 1000, test_time - std::chrono::hours(60), spec_cards));
    log.add_item(std::make_shared<Payment>("3534277890123456", "USD", 6434, test_time - std::chrono::hours(100), spec_cards));
    log.add_item(std::make_shared<Payment>("1034277890123456", "USD", 2434, test_time - std::chrono::hours(180), spec_cards));

    
    show(log.find_item(*spec_cards));
    show(log.find_item(PaymentSpec{}));
    show(log.find_item(PaymentSpec{PaymentSpec::CardType::DEBIT, PaymentSpec::CardScheme::ANY, PaymentSpec::PaymentType::AUTH}));
  //  show(log.find_item(Payment{"1034277890123456", "EUR", 1000, test_time - std::chrono::hours(60), std::make_shared<PaymentSpec>()}));
    // Provides querying values (some can be default to denote unset criteria)

    auto p3{std::make_shared<Location>(35, 2549.45, "Kipsala Bank", std::make_shared<LocationSpec>("East", LocationSpec::Area::URBAN))};
    log.add_item(p3);

    show(log.find_item(LocationSpec{"", LocationSpec::Area::RURAL}));

    cerr << "The largest payment:\n";
    //show(log.find_largest_payment());

    cerr << "Payment average: " << log.find_average_amount() << "\n";
    // Save all items to file:
   /*
    auto file_name{ "pay.csv"};
    log.save(file_name);

    // Load items into different object:
    Log another_log(file_name);
    // TODO: Test, that loading into another_log succeededs:
   */
    return 0;

}