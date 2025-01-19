#include <stdio.h>

class SpaService
{
public:
  // this is the template method
  // it provides the main skeleton for the algorithm
  void WelcomeClient()
  {
    GiveEquipement();
    GiveGift();
    ShowAround();
  }
// abstract methods of the algorithm and hooks are protected since
// they should only be available to subclasses for override
protected:
  virtual void GiveEquipement() = 0;
  virtual void ShowAround() = 0;
  //this is a Hook. It's an optional method that can be implemented by the subclass
  // by default it does nothing
  void GiveGift()
  {}
};

class SummerSpaService : public SpaService
{
protected:
  void GiveEquipement() override
  {
    printf("Give slippers and towel.\n");
  }
  void ShowAround() override
  {
    printf("Look at those beautiful flowers!\n");
  }
};

class WinterSpaService : public SpaService
{
protected:
  void GiveEquipement() override
  {
    printf("Give a bathrobe, it's freezing!\n");
  }
  void ShowAround() override
  {
    printf("Look at all this snow!\n");
  }
  void GiveGift()
  {
    printf("Give some tea!\n");
  }
};

struct Employee
{
  void ServeClient(SpaService* service)
  {
    // the client uses the template method
    service->WelcomeClient();
  }
};

int main()
{
  Employee employee;
  SummerSpaService spa_service; 
  employee.ServeClient(&spa_service);
  return 0;
}