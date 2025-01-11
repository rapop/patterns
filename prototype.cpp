#include <memory>

struct Door
{
  virtual std::unique_ptr<Door> Clone() const = 0;
};

class WoodDoor: public Door
{
public:
  WoodDoor() = default;
  WoodDoor(const WoodDoor& other)
  {
    number_ = other.number_;
  }
  virtual std::unique_ptr<Door> Clone() const override
  {
    return std::make_unique<WoodDoor>(*this);
  }
private:
  int number_ = 0;
};

class GlassDoor: public Door
{
public:
  GlassDoor(const GlassDoor& other)
  {
    number_ = other.number_;
  }
  // sometimes a shallow copy is enough but sometimes we need a deep copy
  // it makes you think about when it's acceptable share references to objects for each object of this type.
  virtual std::unique_ptr<Door> Clone() const override
  {
    return std::make_unique<GlassDoor>(*this);
  }
private:
  int number_;
};

struct SaunaFactory
{
  virtual ~SaunaFactory() = default;
  virtual std::unique_ptr<Door> MakeDoor() const = 0;
};

// enum class Type
// {
//   WoodDoor = 0,
//   GlassDoor
// };

class SaunaPrototypeFactory: public SaunaFactory
{
public:
  SaunaPrototypeFactory(std::unique_ptr<Door> door)
  : prototype_door_(std::move(door))
  {
    // instead of being passed, they can be created and stored in a map here (prototype manager)
    // and they can be cloned by passing and id
    //prototypes_[Type::WoodDoor] = std::make_unique<WoodDoor>();
    //prototypes_[Type::GlassDoor] = std::make_unique<GlassDoor>();
  }
  virtual std::unique_ptr<Door> MakeDoor() const
  {
    return prototype_door_->Clone();
  }
private:
  std::unique_ptr<Door> prototype_door_ = nullptr;
  // std::unordered_map<Type, std::unique_ptr<Door> *, std::hash<int>> prototypes_;
};

class Spa 
{
public:
  void CreateSauna(SaunaFactory& factory)
  {
    sauna_door_ = factory.MakeDoor();
  }
private:
  std::unique_ptr<Door> sauna_door_ = nullptr;
};

int main()
{
  // its more dynamic, as it allows you to define a system using composition instead of inheritance like
  // the abstract factory

  // to change the type that is create we just need to initialize it with a different set of prototypes
  SaunaPrototypeFactory sauna_factory = SaunaPrototypeFactory(std::make_unique<WoodDoor>());
  // SaunaPrototypeFactory sauna_factory = SaunaPrototypeFactory(std::make_unique<GlassDoor>());
  
  Spa spa;
  spa.CreateSauna(sauna_factory);

  return 0;
}