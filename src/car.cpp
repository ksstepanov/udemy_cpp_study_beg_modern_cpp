#include "car.h"
#include <iostream>
int Car::totalCnt = 0;
Car::Car(void):Car(0)   // Delegating constructor! to initialize values inside one place instead of duplicating
{
    std::cout << "Call Car() default: " <<std::endl;
    Car::Dashboard();
}

Car::Car(float fuel_initial):Car(fuel_initial, 0)   // Delegating constructor!
{
    std::cout << "Call Car(float fuel_initial)" <<std::endl;
    Car::Dashboard();
}

Car::Car(float fuel_initial, int pass)
{
    Car::totalCnt ++;
    fuel = fuel_initial;
    speed = 0;
    passengers = pass;
    std::cout << "Call Car(float fuel_initial, int pass)" <<std::endl;
    Car::Dashboard();
}

Car::~Car(void)
{
    Car::totalCnt --;
    std::cout << "Call ~Car" <<std::endl;
    Car::Dashboard();
    
}

void Car::FillFuel(float fuel_val)
{
    fuel += fuel_val;
}

void Car::Accelerate(void)
{
    speed += 1.0f;
    fuel -= 0.1f;
    std::cout << "Call Car::Accelerate:" <<std::endl;
    Car::Dashboard();
}

void Car::Brake(void)
{
    speed -= 1.0f;
}

void Car::AddPassengers(int num)
{
}

void Car::Dashboard(void) const
{
    std::cout << "---->" <<"[" <<speed <<", " <<fuel <<", " <<passengers <<"] total(" <<Car::totalCnt <<")" <<std::endl;
}

int Car::getTotalCnt(void)
{
    return Car::totalCnt;
}
