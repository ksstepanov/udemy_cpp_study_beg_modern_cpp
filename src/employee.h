#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <string>
#include <memory>

class Project;

class Employee
{
    std::string m_name;
    std::shared_ptr<Project> m_project;

public:
    Employee(const std::string &name);
    ~Employee();
    void setProject(std::shared_ptr<Project> &new_proj);
    const std::shared_ptr<Project> &getProject(void) const;
    friend std::ostream & operator <<(std::ostream &out, const Employee &e);
};

std::ostream & operator <<(std::ostream &out, const Employee &e);

#endif /* EMPLOYEE_H_ */