#include <iostream>
#include <cassert>
#include <algorithm>
#include "Payment.h"
#include "Log.h"

using namespace std;

// outputs abstraction object properties to the console window
void show(Payment item)
{
    cout << item.get_cardNumber() << " "
        << "'" << item.get_currency() << "' "
        << item.get_amountCents() << " "
        << item.get_spec().get_cardType_str() << " "
        << item.get_spec().get_cardScheme_str() << " "
        << item.get_spec().get_paymentType_str() << " "
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

    // adds several different abstraction objects to the log
    log.add_item("1234567890123456", "USD", 1520, test_time - std::chrono::hours(100), { PaymentSpec::CardType::CREDIT, PaymentSpec::CardScheme::VISA, PaymentSpec::PaymentType::AUTH });
    log.add_item("1034277890123456", "EUR", 1000, test_time - std::chrono::hours(60), { PaymentSpec::CardType::DEBIT, PaymentSpec::CardScheme::MASTERCARD, PaymentSpec::PaymentType::CHARGEBACK });
    log.add_item("1034277890123456", "EUR", 2434, test_time - std::chrono::hours(80), { PaymentSpec::CardType::GIFT, PaymentSpec::CardScheme::DISCOVER, PaymentSpec::PaymentType::AUTH });

    // provides querying values (some can be default (e.g., "", 0) to denote unset criteria)

    auto qry = Payment{"1234567890123456", "", 0, {}, {}};
    auto result = log.find_item(qry);
    show(result);
    assert(result.get_amountCents() == 1520);
    assert(result.get_dateTime() == test_time - std::chrono::hours(100));

    qry = Payment{"", "EUR", 0, {}, {}};
    result = log.find_item(qry);
    show(result);
    assert(result.get_cardNumber() == "1034277890123456");

    qry = Payment{"", "EUR", 2434, {}, {}};
    result = log.find_item(qry);
    show(result);
    assert(result.get_dateTime() == test_time - std::chrono::hours(80));

    qry = Payment{"", "", 0, {}, { PaymentSpec::CardType::DEBIT, PaymentSpec::CardScheme::ANY, PaymentSpec::PaymentType::ANY}};
    result = log.find_item(qry);
    show(result);
    assert(result.get_cardNumber() == "1034277890123456");
    assert(result.get_amountCents() == 1000);
    assert(result.get_currency() == "EUR");
    assert(result.get_spec().get_cardType() == PaymentSpec::CardType::DEBIT);
    assert(result.get_spec().get_cardType_str() == "Debit");

    result = log.find_item({ PaymentSpec::CardType::GIFT, PaymentSpec::CardScheme::ANY, PaymentSpec::PaymentType::ANY});
    show(result);
    assert(result.get_dateTime() == test_time - std::chrono::hours(80));
    assert(result.get_spec().get_paymentType() == PaymentSpec::PaymentType::AUTH);
    assert(result.get_spec().get_cardScheme() == PaymentSpec::CardScheme::DISCOVER);

    // tests for nonmatching object

    qry = Payment{"", "", 1111, {}, {}};
    result = log.find_item(qry);
    show(result);
    assert(result.get_amountCents() == 0);

    std::cout << "The largest payment:\n";
    show(get_largest_payment(log));

    std::cout << "Payment average: " << get_average_amount(log) << "\n";

    return 0;

}