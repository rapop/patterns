// This is a subsystem
struct WoodDoor
{
  void Build(double price)
  {}
};

struct WoodFloor
{
  void Build()
  {}
};

class SpaFacade
{
public:
  
  SpaFacade(): wood_floor_(), wood_door_()
  {
    // the objects can be create within the facade or passed to it by composition 
  }

  // the facade can take on parameters, but the more it takes, 
  // the more it will start to deviate from its initial purpose
  void Build(double wood_door_price)
  {
    wood_floor_.Build();
    wood_door_.Build(wood_door_price);
  }

private:
  WoodFloor wood_floor_;
  WoodDoor wood_door_;
};


// client uses only the facade
class SpaManager
{
public:
  SpaManager(SpaFacade& spa_facade) : spa_facade_(spa_facade)
  {}

  void Build()
  {
    // client can easily work with the facade as opposed to the subsystem components
    spa_facade_.Build(123);
  }
private:
  SpaFacade& spa_facade_;
};

int main()
{
  SpaFacade spa_facade;
  SpaManager spa_manager = SpaManager(spa_facade);
  spa_manager.Build();

  return 0;
}