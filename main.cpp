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

void show(const Item& item)
{
    cout << item << "\n";
}
/*
Payment cardScheme(const Log& log)
{
    int max_pos{-1};

    for (auto i{0}; i < log.get_count(); i++)
    {
        auto ptr { dynamic_cast<const PaymentSpec*>(&*log[i].get_spec()) }; // or dynamic_cast<const Bicycle*>(&log[i]) if the property is in the abstration class
        if (nullptr == ptr) //if the instance does not refer to a required type
            continue;
        :::
        max_pos = i; 
    }
    :::

    if (max_pos >= 0)
	{
		auto item_p { & log[max_pos] };
		auto payment_p { static_cast<const Payment*>(item_p) };
		return * payment_p;
	}
	else
	{
		return Payment{}; // if there is no bicycle in the log
	}
}*/

/*double get_largest_payment(const Log& log) {
    return log.find_largest_payment();
}

double get_average_amount(const Log& log) {
    return log.find_average_amount();
}*/
// solution entry function
int main()
{
    Log log;
    auto test_time{ std::chrono::system_clock::now() };
 // Create shared pointers for PaymentSpec objects
    
    auto spec_bmx{std::make_shared<PaymentSpec>(PaymentSpec::CardType::CREDIT,PaymentSpec::CardScheme::VISA, PaymentSpec::PaymentType::AUTH)};
    auto p1{std::make_shared<Payment>(8, "1234567890123456", "USD", 1520, test_time - std::chrono::hours(100), spec_bmx)};
    log.add_item(p1);

    auto p2{std::make_shared<Payment>(2 ,"7234567890123456", "EUR", 1520, test_time - std::chrono::hours(180), std::make_shared<PaymentSpec>(PaymentSpec::CardType::CREDIT, PaymentSpec::CardScheme::MASTERCARD, PaymentSpec::PaymentType::CHARGEBACK))};
    log.add_item(p2);

    auto spec_cards{std::make_shared<PaymentSpec>(PaymentSpec
    ::CardType::EBT, PaymentSpec::CardScheme::MASTERCARD, PaymentSpec::PaymentType::CHARGEBACK)};
    log.add_item(std::make_shared<Payment>(5, "1034277890123456", "EUR", 1000, test_time - std::chrono::hours(60), spec_cards));
    log.add_item(std::make_shared<Payment>(3, "1034277890123456", "USD", 2434, test_time - std::chrono::hours(80), spec_cards));

    show(log.find_item(PaymentSpec(PaymentSpec::CardType::ANY, PaymentSpec::CardScheme::ANY, PaymentSpec::PaymentType::ANY)));
    
    show(log.find_item(*spec_cards));
    show(log.find_item(PaymentSpec{}));

    show(log.find_item(PaymentSpec{PaymentSpec::CardType::DEBIT, PaymentSpec::CardScheme::ANY, PaymentSpec::PaymentType::ANY}));
    
    auto g1{std::make_shared<Location>(8, 8902, std::make_shared<LocationSpec>("EUR", LocationSpec::CardType::VIRTUAL))};
    log.add_item(g1);

    show(log.find_item(LocationSpec{"", LocationSpec::CardType::VIRTUAL }));
    

    
    //cerr << "The largest payment:\n" << get_largest_payment(log) << "\n";

    //cerr << "Payment average: " << get_average_amount(log) << "\n";
    
    return 0;
}