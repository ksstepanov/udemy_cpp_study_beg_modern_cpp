#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
#include <iostream>

class Account
{
    std::string m_name;
    int m_number;

    protected:
    float m_balance;
    virtual void _print(std::ostream& o) const;

    static int account_number_tracker;

    public:
    Account(const std::string name, float initial_balance);
    virtual ~Account();
    int get_number(void) const;
    float get_balance(void) const;
    const std::string get_name(void) const;

    virtual void accumulate_interest(void);
    virtual void withdraw(float val);
    virtual void deposit(float val);
    virtual float get_interest_rate(void) const;


    friend std::ostream & operator <<(std::ostream &out, Account &a);
};

std::ostream & operator <<(std::ostream &out, Account &a);

class Savings: public Account
{
    float m_rate;
    protected:
    virtual void _print(std::ostream& o) const override;
    public:
    Savings(const std::string name, float initial_balance, float rate);
    ~Savings();
    float get_interest_rate(void) const override; //Base class function should be virtual to be overriden

    void accumulate_interest(void) override;
    friend std::ostream & operator <<(std::ostream &out, Savings &a);
};

std::ostream & operator <<(std::ostream &out, Savings &a);

class Checking: public Account
{
    const float m_min_balance;
    protected:
    virtual void _print(std::ostream& o) const;
    public:
    // using Account::Account; // this can be used to automatically generate constructor that calls base class constructor
    // with the same arguments
    Checking(const std::string name, float initial_balance, float min_balance);
    void withdraw(float val);
    float get_min_balance(void) const;
    friend std::ostream & operator <<(std::ostream &out, Checking &a);
};
std::ostream & operator <<(std::ostream &out, Checking &a);

class Checking2: private Account
{
    const float m_min_balance;
    protected:
    virtual void _print(std::ostream& o) const;
    public:
    // using Account::Account; // this can be used to automatically generate constructor that calls base class constructor
    // with the same arguments
    Checking2(const std::string name, float initial_balance, float min_balance);
    void withdraw(float val);
    float get_min_balance(void) const;
    friend std::ostream & operator <<(std::ostream &out, Checking2 &a);
};

std::ostream & operator <<(std::ostream &out, Checking2 &a);

void test_account(void);

#endif /* ACCOUNT_H_ */