#include <string>
#include <stdio.h>

// you shoudle write code that parametrizes it's behavior

// if case statements is often a smell
struct SpaManager
{
  void PrepareSpa(const std::string& season)
  {
    if (season == "winter") {
      printf("Prepare for winter!\n");
    }
    else if (season == "summer") {
      printf("Prepare for summer!\n");
    }
  }
};

// fix 
// use interfaces 
// inheritance is more suboptimal approach
struct SeasonPreparator
{
  virtual void Prepare() = 0;
};

struct WinterPreparator : public SeasonPreparator
{
  void Prepare() override
  {
    printf("Prepare for winter!\n");
  }
};

struct SummerPreparator : public SeasonPreparator
{
  void Prepare() override
  {
    printf("Prepare for summer!\n");
  }
};

// extension can easily be added by creating a new preparator (spring for example)
// and inject that one instead.
// the SpaManager class remains closed to modifications as much as possible
class SpaManagerFixed
{
public:
  SpaManagerFixed(SeasonPreparator* preparator)
  : preparator_(preparator)
  {}
  void Prepare()
  {
    preparator_->Prepare();
  }
private:
  SeasonPreparator* preparator_;
};

int main()
{
  WinterPreparator preparator;
  SpaManagerFixed manager(&preparator);
  manager.Prepare();
  return 0;
}

