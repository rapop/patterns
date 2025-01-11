#include <iostream>
#include <initializer_list>
#include <unordered_map>
#include <string>
#include <vector>

// the shared state, aka intrinsic state
// this is the flyweight object
struct DoorData
{
  // those are big objects
  std::string type;
  std::string mesh;
  std::vector<std::string> components_list;
};

// the flyweight factory creates and manages the flyweight objects.
class DoorDataFactory
{
public:
  DoorDataFactory(std::initializer_list<DoorData> door_datas)
  {
    for (const auto& door_data : door_datas)
    {
      door_datas_[door_data.type] = door_data;
    }
  }

  DoorData& getDoorData(const DoorData& door_data)
  {
    if (door_datas_.find(door_data.type) == door_datas_.end())
    {
      door_datas_[door_data.type] = door_data;
    }
    return door_datas_[door_data.type];
  }

private:
  std::unordered_map<std::string, DoorData> door_datas_;
};

// the extrinsic state, could be computed sometimes instead of being stored
// it's the unique state of an object
// When a context is paired with one of the flyweight objects, 
// it represents the full state of the original object.
// it give you the additional context in which you should use your shared state to do something
class DoorContext
{
public:
  DoorContext(const std::string& owner_name, 
              double price, 
              DoorDataFactory& door_data_factory,
              const DoorData& door_data)
  : owner_name_(owner_name), 
    price_(price),
    door_data_(door_data_factory.getDoorData(door_data)) 
  {}

  void renderDoor()
  {
    // do something with both intrinsic and extrinsic state.
    std::cout << door_data_.mesh + owner_name_ << std::endl; 
  }
private:  
  std::string owner_name_;
  double price_;
  DoorData& door_data_;
};

// client
struct SpaManager
{
  void Build(DoorContext* context)
  {
    context->renderDoor();
  }
};

int main()
{
  // big mesh is loaded only at one place and stored in the factory.
  static const std::string big_mesh = "big_mesh";
  // designated Initializers in C++ 20
  DoorDataFactory door_data_factory({{.type = "type1", 
                                    .mesh = big_mesh, 
                                    .components_list = {"a1", "b1", "c1"}},
                                     {.type = "type2", 
                                     .mesh = "mesh2", 
                                     .components_list = {"a2", "b2", "c2"}}});

  auto& door_data = door_data_factory.getDoorData({.type = "type1", 
                                                  .mesh = big_mesh, 
                                                  .components_list = {"a1", "b1", "c1"}});

  DoorContext door_context = DoorContext("owner_name", 12, door_data_factory, door_data);

  SpaManager spa_manager;
  spa_manager.Build(&door_context);

  return 0;
}