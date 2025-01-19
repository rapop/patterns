#include <array>
#include <stdio.h>

struct Sauna;
struct Pool;  

struct SpaVisitor
{
  virtual ~SpaVisitor() = default;
  // the abstract Visitor class has a virtual method for each type of Element it can visit.
  virtual void VisitSauna(const Sauna* element) = 0;
  virtual void VisitPool(const Pool* element) = 0;
};

struct SpaElement
{
  virtual ~SpaElement() = default;
  virtual void Accept(SpaVisitor* visitor) const = 0;
};

class Sauna: public SpaElement
{
public:
  void Accept(SpaVisitor* visitor) const override
  {
    // the concrete elements call directly the method with their specific name in the vistor
    // This way we let the visitor know the type of element it works with.
    visitor->VisitSauna(this);
  }

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
  void Accept(SpaVisitor* visitor) const override
  {
    visitor->VisitPool(this);
  }

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
  void VisitSauna(const Sauna* element) override
  {
    printf("visit sauna from price visitor!\n");
    total_price_ += element->GetPrice();
  }

  void VisitPool(const Pool* element) override
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
  void VisitSauna(const Sauna* element) override
  {
    users_nb_ += element->GetUsersNb();
  }

  void VisitPool(const Pool* element) override
  {
    users_nb_ += element->GetUsersNbFromPool();
  }
private:
  unsigned int users_nb_ = 0;
};

int main()
{
  Pool pool;
  Sauna sauna;
  std::array<SpaElement*,2> elements = {&pool, &sauna};
  SpaPriceVisitor visitor;
  for (const auto elem: elements)
  {
    elem->Accept(&visitor);
  }

  return 0;
}