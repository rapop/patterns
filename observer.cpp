#include <cstdio>
#include <string>
#include <unordered_set>

class Manager;

// this is the observer
struct Employee
{
  virtual ~Employee() = default;
  virtual void Update(Manager* manager) = 0;
};

// this is the Subject
struct Manager
{
  virtual ~Manager() = default;
  virtual void Attach(Employee* employee) = 0;
  virtual void Detach(Employee* employee) = 0;
  virtual void Notify() = 0;
  virtual const std::string& GetPayState() = 0;
};

class KitchenEmployee : public Employee
{
public:
  KitchenEmployee() = delete;
  KitchenEmployee(Manager* manager)
  : manager_(manager)
  {
    manager_->Attach(this);
  }
  void Update(Manager* manager) override
  {
    if (manager == manager_)
    {
      // business logic
      printf("Manager sent update!\n");
      printf("My pay is ready: %s\n", manager->GetPayState().c_str());  
    }
  }
private:
  Manager* manager_;
};

class SpaManager : public Manager
{
public:
  void Attach(Employee* employee)
  {
    employees_.insert(employee);
  }
  void Detach(Employee* employee)
  {
    const auto it = employees_.find(employee);
    if (it != employees_.end())
    {
      employees_.erase(it);
    }
  }
  void Notify()
  {
    for (const auto employee : employees_)
    {
      // we can pass the context and information with the notification here from the subject
      employee->Update(this);
    }
  }

  // this sets the state of the subject
  void GivePay()
  {
    sent_pay_ = "true";
    Notify();
  }

  // state can be shared using this function
  const std::string& GetPayState()
  {
    return sent_pay_;
  }

private:
  std::string sent_pay_ = "false";
  std::unordered_set<Employee*> employees_;
};

int main()
{
  SpaManager manager;
  KitchenEmployee cook(&manager);
  KitchenEmployee busboy(&manager);

  // manager.Attach(&cook);
  // manager.Attach(&busboy);
  manager.GivePay();
  // manager.Notify();
  manager.Detach(&cook);
  printf("Detached cook!\n");
  manager.Notify();
  return 0;
}