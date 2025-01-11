#include <iostream>

struct Command 
{
    virtual ~Command() = default;
    virtual void Execute() const = 0;
};

//Receiver
struct SpaManager
{
    void buy_door()
    {
        std::cout << "I need to buy!" << std::endl;
    }

    void sell_door()
    {
        std::cout << "I need to sell!" << std::endl;
    }
};

// the concrete commands
// thread the receiver differently
class SellDoorCommand : public Command
{
public:
    SellDoorCommand(SpaManager* manager)
    : manager_(manager)
    {}

    void Execute() const override
    {
        // can pass data stores in this command
        manager_->sell_door();
    }
    
private:
    SpaManager* manager_;
};

class BuyDoorCommand : public Command
{
public:
    BuyDoorCommand(SpaManager* manager)
    : manager_(manager)
    {}

    void Execute() const override
    {
        // can pass data stores in this command
        manager_->buy_door();
    }
    
private:
    SpaManager* manager_;
};

// Invoker
// sends a request to the command
class SpaDirector
{
public:
    void setOrder(Command* cmd)
    {
        cmd_ = cmd;
    }
    void decide()
    {
        // the invoker does depend on concrete cmds or the receiver to send requests
        cmd_->Execute();
    }
private:
    Command* cmd_;
};


int main()
{   
    SpaManager manager;
    BuyDoorCommand buy(&manager);
    SellDoorCommand sell(&manager);

    // The client code can parameterize an invoker with any commands.
    SpaDirector director;
    director.setOrder(&buy);
    director.decide();
    director.setOrder(&sell);
    director.decide();

    return 0;
}