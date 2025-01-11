#include <memory>

struct Sauna
{
  void AddHandle()
  {}

  void AddDoorWindow()
  {}

  void AddWoodFloor()
  {}

  void AddGlassWindow()
  {}

  void AddCeramicFloor()
  {}
};

class SaunaBuilder
{
public:
  virtual ~SaunaBuilder() = default;
  virtual SaunaBuilder& MakeDoor()
  {
    return *this;
  }
  virtual SaunaBuilder& MakeFloor() 
  {
    return *this;
  }
  virtual SaunaBuilder& MakePond() 
  {
    return *this;
  }

  virtual std::unique_ptr<Sauna> Build()
  {
    return nullptr;
  }

protected:
  SaunaBuilder() = default;

  virtual void Reset()
  {}
};

class DrySaunaBuilder : public SaunaBuilder
{
public:
  DrySaunaBuilder()
  {
    Reset();
  }

  SaunaBuilder& MakeDoor() override
  {
    // complexes building steps here
    sauna_->AddHandle();
    sauna_->AddDoorWindow();
    return *this;
  }

  SaunaBuilder& MakeFloor() override
  {
    sauna_->AddWoodFloor();
    return *this;
  }

  std::unique_ptr<Sauna> Build() override
  {
    // std::move cast sauna_ to an rvalue 
    // and the move assignment sets sauna_ in a valid state and sets it to nullptr;
    std::unique_ptr<Sauna> result = std::move(sauna_);
    Reset();
    return result;
  }

private:  
  std::unique_ptr<Sauna> sauna_ = nullptr;

  void Reset() override
  {
    sauna_ = std::make_unique<Sauna>();
  }
};

class WetSaunaBuilder : public SaunaBuilder
{
public:
  WetSaunaBuilder()
  {
    Reset();
  }

  SaunaBuilder& MakeDoor() override
  {
    // complexes building steps here
    sauna_->AddHandle();
    sauna_->AddGlassWindow();
    return *this;
  }

  SaunaBuilder& MakeFloor() override
  {
    sauna_->AddCeramicFloor();
    return *this;
  }

  std::unique_ptr<Sauna> Build() override
  {
    // std::move cast sauna_ to an rvalue 
    // and the move assignment sets sauna_ in a valid state and sets it to nullptr;
    std::unique_ptr<Sauna> result = std::move(sauna_);
    Reset();
    return result;
  }

private:  
  std::unique_ptr<Sauna> sauna_ = nullptr;

  void Reset() override
  {
    sauna_ = std::make_unique<Sauna>();
  }
};

struct SpaDirector 
{
  std::unique_ptr<Sauna> createSauna(SaunaBuilder& builder)
  {
    return builder.MakeDoor()
                  .MakeFloor()
                  .MakeDoor()
                  .Build();
  }
};

int main()
{
  // WetSaunaBuilder sauna_builder = WetSaunaBuilder();
  DrySaunaBuilder sauna_builder = DrySaunaBuilder();
  
  SpaDirector spa;
  const std::unique_ptr<Sauna> sauna = spa.createSauna(sauna_builder);

  return 0;
}