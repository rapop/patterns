#include <stdio.h>
// subclasses should not modifiy the behavior of parent classes?

// a subclass should be able to be substituted for its parent class 
// without causing any errors or unexpected behavior

class SpaManager
{
public:
  virtual void Manage()
  {
    nb_employees_ = 10;
  }
  unsigned int GetNbEmployees() const
  {
    return nb_employees_;
  }
private:
  unsigned int nb_employees_ = 0;
};

class SpaPoolManager : SpaManager
{
public:
  void Manage() override
  {
    // calling the base class when overriding should solve the issue
    // SpaManager::Manage();

    // notice this manager doesnt count the number of employees...
    // but does other stuff.
  }
};

void GenerateManagementReport(SpaManager* manager)
{
  // calling this with the SpaPoolManager would give unexpected results.
  manager->Manage();
  printf("There are %i employees.\n", manager->GetNbEmployees());
}

int main()
{
  SpaManager manager;
  
  // substitution doesn't work.
  // SpaPoolManager manager;
  GenerateManagementReport(&manager);
  return 0;
}