#include <iostream>
#include <cassert>
#include <algorithm>
#include "Payment.h"
#include "Log.h"
#include "PaymentSpec.h"

using namespace std;

// outputs abstraction object properties to the console window
void show(const Payment& item)
{
    auto is_p{ item.get_spec() }; // returns smart pointer

    if (!is_p) // if there is no specification object
        is_p.reset(new PaymentSpec()); // construct the default
    
    cerr << item.get_cardNumber() << " "
        << "'" << item.get_currency() << "' "
        << item.get_amountCents() << " "
        << is_p->get_cardType_str() << " "
        << is_p->get_cardScheme_str() << " "
        << is_p->get_paymentType_str() << " "
        << endl;
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

    return 0;

}