#include <array>
#include <stdio.h>
#include <variant>

struct Sauna;
struct Pool;  

struct SpaVisitor
{
  virtual ~SpaVisitor() = default;
  // the abstract Visitor class has a virtual method for each type of Element it can visit.
  virtual void Visit(const Sauna* element) = 0;
  virtual void Visit(const Pool* element) = 0;
};

struct SpaElement
{
  virtual ~SpaElement() = default;
};

class Sauna: public SpaElement
{
public:
  double GetPrice() const
  {
    return 1200;
  }

  unsigned int GetUsersNb() const 
  {
    return 1;
  }
};

class Pool: public SpaElement
{
public:
  double GetPrice() const
  {
    return 140000;
  }

  // each concrete element might have unique method that we can use 
  unsigned int GetUsersNbFromPool() const
  {
    return 2;
  }
};

class SpaPriceVisitor : public SpaVisitor
{
public:
  void Visit(const Sauna* element) override
  {
    printf("visit sauna from price visitor!\n");
    total_price_ += element->GetPrice();
  }

  void Visit(const Pool* element) override
  {
    printf("visit pool from price visitor!\n");
    total_price_ += element->GetPrice();
  }
private:
  double total_price_ = 0;
};

class SpaPeopleCounterVisitor : public SpaVisitor
{
public:
  void Visit(const Sauna* element) override
  {
    users_nb_ += element->GetUsersNb();
  }

  void Visit(const Pool* element) override
  {
    users_nb_ += element->GetUsersNbFromPool();
  }
private:
  unsigned int users_nb_ = 0;
};

int main()
{
  using Elements = std::variant<Pool*,Sauna*>;
  
  Pool pool;
  Sauna sauna;
  std::array<Elements,2> elements = {&pool, &sauna};
  SpaPriceVisitor visitor;
  for (const auto elem: elements)
  {
    std::visit([&visitor](auto&& arg){ visitor.Visit(arg); }, elem);
    // elem->Accept(&visitor);
  }

  return 0;
}