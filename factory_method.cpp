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

class SaunaFactory
{
public:
  virtual ~SaunaFactory(){};
  void CreateSauna()
  {
    // the difference with the abstract factory is that we don't inject and use a factory,
    // we simply use methods that we override. 
    sauna_floor_ = MakeFloor();
    sauna_door_ = MakeDoor();
  }
protected:
  // those are the factory methods
  virtual std::unique_ptr<Door> MakeDoor() const = 0;
  virtual std::unique_ptr<Floor> MakeFloor() const = 0;
private:
  std::unique_ptr<Floor> sauna_floor_ = nullptr;
  std::unique_ptr<Door> sauna_door_ = nullptr;
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

int main()
{
  // DrySaunaFactory sauna_factory = DrySaunaFactory();
  WetSaunaFactory sauna_factory = WetSaunaFactory();
  sauna_factory.CreateSauna();

  return 0;
}