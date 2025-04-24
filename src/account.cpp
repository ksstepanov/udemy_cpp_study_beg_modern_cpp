#include "account.h"
#include <iostream>
#include <typeinfo>

int Account::account_number_tracker = 1000;

void Account::_print(std::ostream &o) const
{
    o << "[Account] "<<m_name <<" #" <<m_number << " balance=" <<m_balance;
}

Account::Account(const std::string name, float initial_balance) : m_name(name), m_balance(initial_balance)
{
    m_number = account_number_tracker++;
}

Account::~Account()
{
}

int Account::get_number(void) const
{
    return m_number;
}

float Account::get_balance(void) const
{
    return m_balance;
}

const std::string Account::get_name(void) const
{
    return m_name;
}

void Account::accumulate_interest(void)
{
}

void Account::withdraw(float val)
{
    if (m_balance >= val)
        m_balance -= val;
    else
        std::cout << *this <<": error: Not enough balance (" << m_balance <<" < " << val <<")" <<std::endl;
}

void Account::deposit(float val)
{
    m_balance += val;
}

float Account::get_interest_rate(void) const
{
    return 0.0f;
}

std::ostream &operator<<(std::ostream &out, Account &a)
{
   a._print(out);
   return out;
}

Savings::Savings(const std::string name, float initial_balance, float rate):Account(name, initial_balance), m_rate(rate)
{
}

Savings::~Savings()
{
}

float Savings::get_interest_rate(void) const
{
    return m_rate;
}

void Savings::accumulate_interest(void)
{
    m_balance *= (m_rate + 1.0f);
}

void Savings::_print(std::ostream &o) const
{
    o << "[Savings] ";
    Account::_print(o);
}

std::ostream &operator<<(std::ostream &out, Savings &a)
{
    a._print(out);
    return out;
}

Checking::Checking(const std::string name, float initial_balance, float min_balance):
 Account(name, initial_balance), m_min_balance(min_balance)
{
}

void Checking::withdraw(float val)
{
    if (m_balance >= (val + m_min_balance))
        Account::withdraw(val);
    else
        std::cout << *this <<": error: Not enough balance (" << m_balance <<" < " << val <<"). Min balance should be: "<<m_min_balance <<std::endl;
}

void Checking::_print(std::ostream &o) const
{
    o << "[Checking] ";
    Account::_print(o);
}

float Checking::get_min_balance(void) const
{
    return m_min_balance;
}

std::ostream &operator<<(std::ostream &out, Checking &a)
{
    a._print(out);
    return out;
}

void transact(Account *pAccount)
{
    std::cout << "--> Transaction started: " <<*pAccount << std::endl;
    pAccount->deposit(500);
    pAccount->accumulate_interest();
    if (typeid(*pAccount) == typeid(Checking)) {
        Checking *pChecking = static_cast<Checking *>(pAccount);
        
        std::cout << "Min balance: " <<pChecking->get_min_balance() << std::endl;
    } else {
        std::cout << "Cant get min balance: " << std::endl;
    }

    // Same with dynamic cast to pointer:
    Checking *pChecking = dynamic_cast<Checking *>(pAccount);
    if (pChecking != nullptr) {
        std::cout << "Dynamic cast works " << std::endl;
    }

    // Same with dynamic cast to deference:
    try {
        Checking &pChecking = dynamic_cast<Checking &>(*pAccount);
    } catch(std::exception &ex) {
        std::cout <<"Exception: " <<ex.what() <<std::endl; // WIll throw std::bad_cast
    } 
    std::cout << "Accumulate interest: " <<*pAccount << std::endl;
    pAccount->withdraw(150);
    std::cout << "--> Transaction finished: " <<*pAccount << std::endl;
}

void test_account(void)
{
    Checking bob("Bob", 1000, 0.5f);
    transact(&bob);

    // Upcasting: nothing specific required:
    Account &a = bob;
    transact(&a);

    // This is object slicing: reduce child object so it fits into base class object.
    // Same will happen if a child object is passed to a function that accepts base class by value.
    Account b = bob;

    // Down cast: Base to Child
    Savings *pBob = static_cast<Savings *>(&a);

    // TYpeid can work on compile time (for non polymorphic types) and in runtime (for polymorphic types)
    const std::type_info &ti = typeid(bob);
    std::cout << "--> Typeinfo *pBob: " <<ti.name() << std::endl;
}