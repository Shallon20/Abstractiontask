#include <iostream>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Payment.h"
#include "Log.h"
#include "PaymentSpec.h"

using namespace std;

// outputs abstraction object properties to the console window
void show(const Payment& item)
{
    cout << item << "\n";
}

const Payment get_largest_payment(const Log& log) {
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
    auto spec1 = std::make_shared<PaymentSpec>(PaymentSpec::CardType::CREDIT, PaymentSpec::CardScheme::VISA, PaymentSpec::PaymentType::AUTH);
    auto spec2 = std::make_shared<PaymentSpec>(PaymentSpec::CardType::DEBIT, PaymentSpec::CardScheme::MASTERCARD, PaymentSpec::PaymentType::CHARGEBACK);
    auto spec3 = std::make_shared<PaymentSpec>(PaymentSpec::CardType::GIFT, PaymentSpec::CardScheme::DISCOVER, PaymentSpec::PaymentType::AUTH);

    // Adds several different Payment objects to the log
    log.add_item("1234567890123456", "USD", 1520, test_time - std::chrono::hours(100), spec1);
    log.add_item("1034277890123456", "EUR", 1000, test_time - std::chrono::hours(60), spec2);
    log.add_item("1034277890123456", "EUR", 2434, test_time - std::chrono::hours(80), spec3);

    // Provides querying values (some can be default to denote unset criteria)

    auto qry = Payment{ "1234567890123456", "", 0, {}, spec1};
    auto result = log.find_item(qry);
    show(result);
    assert(result.get_amountCents() == 1520);
    assert(result.get_dateTime() == test_time - std::chrono::hours(100));

    qry = Payment{ "", "EUR", 1000, {}, spec2};
    result = log.find_item(qry);
    show(result);
    assert(result.get_cardNumber() == "1034277890123456");

    qry = Payment{ "", "EUR", 2434, {}, spec3};
    result = log.find_item(qry);
    show(result);
    assert(result.get_dateTime() == test_time - std::chrono::hours(80));

    auto shared_spec = std::make_shared<PaymentSpec>(PaymentSpec::CardType::CREDIT, PaymentSpec::CardScheme::ANY, PaymentSpec::PaymentType::CHARGEBACK);
    log.add_item("1034277890123456", "EUR", 3000, test_time - std::chrono::hours(80), shared_spec);
    show(log.find_item(*shared_spec));
    
    // Tests for nonmatching object

    qry = Payment{ "", "", 1111, {}, {} };
    result = log.find_item(qry);
    show(result);
    assert(result.get_amountCents() == 0);

    cerr << "The largest payment:\n";
    show(log.find_largest_payment());

    cerr << "Payment average: " << log.find_average_amount() << "\n";
    auto spec_bmx = std::make_shared<PaymentSpec>(new PaymentSpec(PaymentSpec::CardType::CREDIT, PaymentSpec::CardScheme::AMEX, PaymentSpec::PaymentType::AUTH) );
    Payment p1("", "EUR", 1234, {}, spec_bmx);
    cout << p1 << "\n";
    // Save all items to file:
    auto filename{ "payments.csv" };
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
         << p2 << "\n----\n";

    auto file_name{ "pay.csv"};
    log.save(file_name);

    // Load items into different object:
    Log another_log(file_name);
    // TODO: Test, that loading into another_log succeededs:
    return 0;

}