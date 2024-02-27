#include <iostream>
#include <cassert>
#include "Payment.h"
#include "Log.h"

using namespace std;

// outputs abstraction object properties to the console window
void show(Payment item)
{
    cout << item.get_cardNumber() << " "
        << "'" << item.get_currency() << "' "
        << item.get_amountCents() << " "
        << endl;
}

// solution entry function
int main()
{
    Log log;
    auto test_time{ std::chrono::system_clock::now() };

    // adds several different abstraction objects to the log
    log.add_item("1234567890123456", "USD", 1520, test_time - std::chrono::hours(100));
    log.add_item("1034277890123456", "EUR", 1000, test_time - std::chrono::hours(60));
    log.add_item("1034277890123456", "EUR", 2434, test_time - std::chrono::hours(80));

    // provides querying values (some can be default (e.g., "", 0) to denote unset criteria)

    auto qry = Payment{"1234567890123456", "", 0, {}};
    auto result = log.find_item(qry);
    show(result);
    assert(result.get_amountCents() == 1520);
    assert(result.get_dateTime() == test_time - std::chrono::hours(100));

    qry = Payment{"", "EUR", 0, {}};
    result = log.find_item(qry);
    show(result);
    assert(result.get_cardNumber() == "1034277890123456");

    qry = Payment{"", "EUR", 2434, {}};
    result = log.find_item(qry);
    show(result);
    assert(result.get_dateTime() == test_time - std::chrono::hours(80));

    // tests for nonmatching object

    qry = Payment{"", "", 1111, {}};
    result = log.find_item(qry);
    show(result);
    assert(result.get_amountCents() == 0);

    return 0;
}