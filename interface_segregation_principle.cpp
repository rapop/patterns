
// client shouldn't be forced to implement methods that it doesn't use.
// and he shouldn't depend on methods that it doesn't use

// basically means that we should split a big interface into smaller ones.

struct SpaEmployee
{
  virtual void ReportNumberOfUsers() = 0;
  virtual void WelcomeCustomer() = 0;
};

struct SpaEmployeeConcrete : SpaEmployee
{
  void ReportNumberOfUsers() override
  {}
  void WelcomeCustomer() override 
  {}
};

// SpaManager depends on the method WelcomeCustomer, that it doesn't use.
struct SpaManager
{
  void GenerateSpaReport(SpaEmployee* employee)
  {
    employee->ReportNumberOfUsers();
  }
};

int main()
{
  SpaEmployeeConcrete emp;
  SpaManager m;
  m.GenerateSpaReport(&emp);
  return 0;
}