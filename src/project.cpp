#include "project.h"
#include <iostream>
#include "employee.h"
#include <vector>
#include <memory>

Project::Project(const std::string &name):m_name(name)
{
}

Project::~Project()
{
    std::cout << "[Project] = " << m_name << " Deleted" <<std::endl;
}

void Project::setName(const std::string &name)
{
    m_name = name;
}

void Project::showDetails(void) const
{
    std::cout << "[Project] = " << m_name << " employees:{";
    for (std::weak_ptr<Employee> e: m_employees) {
       if (!e.expired()) {
            auto e_lock = e.lock();
            std::cout << *(e_lock.get());
       }
    }
    std::cout <<"}"<<std::endl;
}

void Project::addEmployee(std::weak_ptr<Employee> new_employee)
{
    m_employees.push_back(new_employee);
}

void show_details(const std::shared_ptr<Employee> &pEmp)
{
    std::cout << "[Employee] = " << *pEmp << " ";
    pEmp->getProject()->showDetails();
}

/* This examples is left for comparison of raw pointers with shared_ptr: a Project is shared between many Employees*/
/*
void testProjectEmployee(void)
{
    // Project *p{new Project("Python project")};
    Project *p = new Project("Python project");
    Employee *vasya = new Employee("Vasya");
    Employee *petya = new Employee("Petya");
    Employee *katya = new Employee("Katya");

    vasya->setProject(p);
    petya->setProject(p);
    katya->setProject(p);

    show_details(vasya);
    show_details(petya);
    show_details(katya);

    p->showDetails();

    delete p;
    delete vasya;
    delete petya;
    delete katya;
}
*/

/* This examples shows using a shared_ptr: a Project is shared between many Employees*/
void testProjectEmployee(void)
{
    // Project *p{new Project("Python project")};
    std::shared_ptr<Project> p{new Project("Python project")};
    std::shared_ptr<Employee> vasya{new Employee("Vasya")};
    std::shared_ptr<Employee> petya{new Employee("Petya")};
    std::shared_ptr<Employee> katya{new Employee("Katya")};

    vasya->setProject(p);
    petya->setProject(p);
    katya->setProject(p);

    show_details(vasya);
    show_details(petya);
    show_details(katya);
    std::cout << "Reference count of project shared ptr: " << p.use_count() <<std::endl;
    p->showDetails();

    p->addEmployee(vasya);
    p->showDetails();
}