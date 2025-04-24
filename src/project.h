#ifndef PROJECT_H_
#define PROJECT_H_
#include <string>
#include <memory>
#include <vector>

class Employee;

class Project
{
    std::string m_name;
    std::vector<std::weak_ptr<Employee>> m_employees;
public:

    Project(const std::string &name);
    ~Project();
    void setName(const std::string &name);
    void showDetails(void) const;

    void addEmployee(std::weak_ptr<Employee> new_employee);
};

void testProjectEmployee(void);

#endif /* PROJECT_H_ */