#include <memory>
#include <string>

struct DoorImpl
{
  virtual ~DoorImpl() = default;
  virtual int GetSize() const = 0;
};

// concrete implementations
struct WoodDoorImpl: public DoorImpl
{
  virtual int GetSize() const override
  {
    return 0;
  }
};

struct GlassDoorImpl: public DoorImpl
{
  virtual int GetSize() const override
  {
    return 0;
  }
};

// the abstraction used by the client
class Door
{
public:
  Door(std::unique_ptr<DoorImpl> impl): impl_(std::move(impl))
  {}
  virtual ~Door() = default;
  virtual std::string GetSizeStr() const
  {
    return std::to_string(impl_->GetSize());
  }

protected:
  std::unique_ptr<DoorImpl> impl_ = nullptr;
};

// extended abstraction
struct BlueDoor: public Door
{
  BlueDoor(std::unique_ptr<DoorImpl> impl): Door(std::move(impl))
  {}

  // extension is possible without changing the implementation
  virtual std::string GetSizeStr() const override
  {
    return std::to_string(impl_->GetSize()) + " blue";
  }
};

// the client 
class Spa 
{
public:
  void CreateSauna(const Door& door)
  {
    door.GetSizeStr();
  }
};

int main()
{ 
  std::unique_ptr<WoodDoorImpl> woodDoorImpl = std::make_unique<WoodDoorImpl>();
  BlueDoor door(std::move(woodDoorImpl));
  Spa spa;
  spa.CreateSauna(door);

  return 0;
}