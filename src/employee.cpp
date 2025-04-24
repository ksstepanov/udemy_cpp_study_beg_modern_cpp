#include "employee.h"
#include "project.h"
#include <iostream>

Employee::Employee(const std::string &name): m_name(name)
{
}

Employee::~Employee()
{
    std::cout << "[Employee] = " << m_name << " Deleted" <<std::endl;
}

void Employee::setProject(std::shared_ptr<Project> &new_proj)
{
    m_project = new_proj;
}

const std::shared_ptr<Project> &Employee::getProject(void) const
{
    return m_project;
}

std::ostream &operator<<(std::ostream &out, const Employee &e)
{
    out << e.m_name;
    return out;
}
