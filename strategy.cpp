#include <stdio.h>
#include <string>

struct SpaContext;

// the strategy
struct LightDisplayer
{
  ~LightDisplayer() = default;
  virtual void Light(SpaContext* context) = 0;
};

class SpaContext
{
public:
  SpaContext(LightDisplayer* light_displayer)
  : light_displayer_(light_displayer)
  {}
  // work is delegated instead of implementing multiple versions on its own
  void Light()
  {
    // context can be passed to the strategy
    light_displayer_->Light(this);
  }
  void SetLightDisplayer(LightDisplayer* light_displayer)
  {
    light_displayer_ = light_displayer;
  }
  const std::string& GetZone()
  {
    return zone_;
  }
private:
  std::string zone_ = "left";
  LightDisplayer* light_displayer_;
};

class PartyLightDisplayer: public LightDisplayer
{
public:
  void Light(SpaContext* context) override
  {
    printf("We are lightning with party theme on the %s\n", context->GetZone().c_str());
  }
};

class DimmedLightDisplayer: public LightDisplayer
{
public:
  void Light(SpaContext* context) override
  {
    printf("We are lightning with dimmed theme on the %s\n", context->GetZone().c_str());
  }
};

int main()
{
  DimmedLightDisplayer dimmed_light_strategy;
  SpaContext context(&dimmed_light_strategy);
  context.Light();
  PartyLightDisplayer party_light_strategy;
  context.SetLightDisplayer(&party_light_strategy);
  context.Light();

  return 0;
}