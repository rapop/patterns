#include <string>
// high level modules should not depend on low level modules, but on abstractions!
// abstraction should not depend on details, details should depend on abstractions

struct EmployeesDatabase
{};

class SpaManager
{
public:
  SpaManager()
  {
    // no instantiation or dependency on concrete implementations. 
    db_ = EmployeesDatabase(); 
  }
private:
  EmployeesDatabase db_;
};

// fix
struct IEmployeesDatabase
{
  // this would make the abstraction depend on details: the type of the database
  //virtual void RecordToDabase(const std::string& database_type) = 0;
  virtual void Record() = 0;
};

// details depend on abstraction, not the other way around
class EmployeesDatabaseFixed : public IEmployeesDatabase
{
public:
  EmployeesDatabaseFixed(const std::string& database_type)
  :database_type_(database_type)
  {}
  void Record() override
  {
    // actually this would be fixed by the open closed principle
    // since this class method be closed to modifications 
    // that could be brought by adding a new db type 
    if (database_type_ == "sqlite")
    {
      //do something
    }
  }

private:
  const std::string database_type_;
};

// high level module depend on abstractions
class SpaManagerFixed
{
public:
  SpaManagerFixed(IEmployeesDatabase* db)
  : db_(db)
  {}
private:
  IEmployeesDatabase* db_;
};

int main()
{
  EmployeesDatabaseFixed db("sqlite");
  SpaManagerFixed m(&db);
  return 0;
}