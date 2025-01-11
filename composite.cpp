#include <list>
#include <memory>

struct SpaComponent
{
  virtual ~SpaComponent() = default;
  
  virtual double GetPrice() const = 0;
};

// the leaf doesnt have any children, and its the one that does the work
struct WoodDoor : public SpaComponent
{
  double GetPrice() const override
  {
    return 100;
  }
};

struct Sauna : public SpaComponent
{
  double GetPrice() const override
  {
    return 150;
  }
};

// this is the composite, which is a component also
class Spa : public SpaComponent
{
public:
// the compositie delegates the work to it's children
  double GetPrice() const override
  {
    double total_price = 0;
    for (const auto& component: components_)
    {
      // one component can also be a composite and delegate further
      total_price += component->GetPrice();
    }
    return total_price;
  }

  virtual void AddComponent(std::shared_ptr<SpaComponent> component)
  {
    components_.push_back(std::move(component));
  }

  virtual void Removecomponent(std::shared_ptr<SpaComponent> component)
  {
    components_.remove(std::move(component));
  }
private:
// the composite has a list of its children
  std::list<std::shared_ptr<SpaComponent>> components_;
};

// client can use the composite or the components interchangeably. 
class SpaManager
{
public:
  SpaManager(std::shared_ptr<SpaComponent> component) : component_(std::move(component))
  {}

  void Build()
  {
    component_->GetPrice();
  }
private:
  std::shared_ptr<SpaComponent> component_;
};

int main()
{
  // those are the leafs
  // better to use shared ptrs if you want to use the same leaf in multiple composites
  std::shared_ptr<WoodDoor> wood_door = std::make_shared<WoodDoor>();
  std::shared_ptr<Sauna> sauna = std::make_shared<Sauna>();

  // this is a branch
  std::shared_ptr<Spa> spa_component = std::make_shared<Spa>();
  spa_component->AddComponent(wood_door);
  spa_component->AddComponent(sauna);

  // this is a also a branch
  std::shared_ptr<Spa> spa_component2 = std::make_shared<Spa>();
  spa_component->AddComponent(wood_door);
  spa_component->AddComponent(sauna);

  std::shared_ptr<Spa> mega_spa = std::make_shared<Spa>();
  spa_component->AddComponent(spa_component);
  spa_component->AddComponent(spa_component2);

  SpaManager spa_manager = SpaManager(mega_spa);

  return 0;
}