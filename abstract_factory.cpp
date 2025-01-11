#include <memory>

struct Door
{};

struct Floor
{};

struct WoodDoor: public Door
{};

struct WoodFloor: public Floor
{};

struct GlassDoor: public Door
{};

struct CeramicFloor: public Floor
{};

// The factory guarantees that resulting products are compatible.
struct SaunaFactory
{
  virtual ~SaunaFactory() = default;
  virtual std::unique_ptr<Door> MakeDoor() const = 0;
  virtual std::unique_ptr<Floor> MakeFloor() const = 0;
};

struct DrySaunaFactory : public SaunaFactory
{
  std::unique_ptr<Door> MakeDoor() const override
  {
    return std::make_unique<WoodDoor>();
  }
  std::unique_ptr<Floor> MakeFloor() const override
  {
    return std::make_unique<WoodFloor>();
  }
};

struct WetSaunaFactory : public SaunaFactory
{
  std::unique_ptr<Door> MakeDoor() const override
  {
    return std::make_unique<GlassDoor>();
  }
  std::unique_ptr<Floor> MakeFloor() const override
  {
    return std::make_unique<CeramicFloor>();
  }
};

class Spa 
{
public:
  // the client only depends on abstractions, not real objects
  void CreateSauna(SaunaFactory& factory)
  {
    sauna_floor_ = factory.MakeFloor();
    sauna_door_ = factory.MakeDoor();
  }
private:
  // the client only depends on abstractions, not real objects
  std::unique_ptr<Floor> sauna_floor_ = nullptr;
  std::unique_ptr<Door> sauna_door_ = nullptr;
};

int main()
{
  // only one instance of the concrete factory is created at runtime
  // thus, it can be implemented as a singleton
  WetSaunaFactory sauna_factory = WetSaunaFactory();
  // DrySaunaFactory sauna_factory = DrySaunaFactory();
  
  Spa spa;
  spa.CreateSauna(sauna_factory);

  return 0;
}