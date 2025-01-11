#include <iostream>
#include <memory>

struct SpaComponent
{
  virtual ~SpaComponent() = default;
  
  virtual double GetPrice() const = 0;
};

// this is the basic component without decoration
struct WoodDoor : public SpaComponent
{
  double GetPrice() const override
  {
    return 100;
  }
};

class SpaDecorator : public SpaComponent
{
public:
  SpaDecorator(std::shared_ptr<SpaComponent> spa_component) 
  : spa_component_(std::move(spa_component))
  {}

  // the base decorator only forwards the request to the component
  double GetPrice() const override
  {
    return spa_component_->GetPrice();
  }
private:
  std::shared_ptr<SpaComponent> spa_component_;
};

class FancyDecorator : public SpaDecorator
{
public:
  FancyDecorator(std::shared_ptr<SpaComponent> spa_component) 
  : SpaDecorator(spa_component)
  {}

  // the concrete decorators adds additional functionalities
  double GetPrice() const override
  {
    return SpaDecorator::GetPrice() + 50;
  }
};

// we can add decorators on top of each others without 
// creating an explosion of classes because of all the possible functionality combinations
// i.e. no need to inherit from FancyDecorator for example
class DarkDecorator : public SpaDecorator
{
public:
  DarkDecorator(std::shared_ptr<SpaComponent> spa_component) 
  : SpaDecorator(spa_component)
  {}

  double GetPrice() const override
  {
    return SpaDecorator::GetPrice() + 1000;
  }
};


// client can use the decorators or the components interchangeably. 
class SpaManager
{
public:
  SpaManager(std::shared_ptr<SpaComponent> component) : component_(std::move(component))
  {}

  void Build()
  {
    std::cout << component_->GetPrice() << std::endl;
  }
private:
  std::shared_ptr<SpaComponent> component_;
};

int main()
{
  // decorations can be chained like this, creating any desired combination
  std::shared_ptr<WoodDoor> wood_door = std::make_shared<WoodDoor>();
  std::shared_ptr<FancyDecorator> fancy_wood_door = std::make_shared<FancyDecorator>(wood_door);
  std::shared_ptr<DarkDecorator> dark_fancy_wood_door = std::make_shared<DarkDecorator>(fancy_wood_door);

  // client code supports them all
  // SpaManager spa_manager = SpaManager(wood_door);
  // SpaManager spa_manager = SpaManager(fancy_wood_door);
  SpaManager spa_manager = SpaManager(dark_fancy_wood_door);
  spa_manager.Build();

  return 0;
}