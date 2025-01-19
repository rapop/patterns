#include <string>
#include <vector>

struct SpaDatabase
{
  // has 2 responsabilities, 
  // 1. cleanup the names
  // 2. keep track of them in a database
  void RegisterUser(const std::string& name)
  {
    auto cleaned = name;
    std::erase_if(cleaned, [](char x) {return x == '/';});
    users_.push_back(cleaned);
  }
std::vector<std::string> users_; 
};


// or create an abstraction that can be injected and modified without touching the implementation
// or the class that's uing it at all
inline std::string Cleanup(const std::string& name)
{
  auto cleaned = name;
  std::erase_if(cleaned, [](char x) {return x == '/';});
  return cleaned;
}

// fix
class SpaDatabaseFixed
{
public:
  void RegisterUser(const std::string& name)
  {
    users_.push_back(Cleanup(name));
  }
private:
  std::vector<std::string> users_; 
};

int main()
{
  SpaDatabaseFixed db;
  db.RegisterUser("my_name/");
  return 0;
}