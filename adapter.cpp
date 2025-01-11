// target,
// is the interface that the client is already using
struct Door
{
  virtual ~Door() = default;
  virtual double GetArea(double width, double length) const
  {
    return width*length;
  }
};

// adaptee,
// contains some useful 
struct GlassDoor
{
  virtual ~GlassDoor() = default;
  virtual double GetDoorAreaInMillimeters(double width, double length) const
  {
    return width*length*1000;
  }
};

// This is the Class Adapter version which uses inheritance.
// The Adapter makes the Adaptee's interface compatible with the Target's
// interface
// private inheritance makes all members and methods inherited be private here, except those private who
// will not be accessible here
struct GlassDoorAdapter : public Door, private GlassDoor
{
  virtual double GetArea(double width, double length) const override
  {
    return GetDoorAreaInMillimeters(width, length);
  }
};

// This is the Object Adapter version which uses composition.
class GlassDoorAdapterObject : public Door
{
public:
  virtual double GetArea(double width, double length) const override
  {
    return glass_door_.GetDoorAreaInMillimeters(width, length);
  }
private:
  GlassDoor glass_door_;
};

class Spa 
{
public:
  void CreateSauna(const Door& door)
  {
    door.GetArea(10,10);
  }
};

int main()
{
  // client code was working fine with this before
  // Door door;

  // GlassDoorAdapter door;
  GlassDoorAdapterObject door;

  Spa spa;
  spa.CreateSauna(door);

  return 0;
}