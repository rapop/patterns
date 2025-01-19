#include <format>
#include <iostream>
#include <memory>
#include <vector>

class SpaCollegue;

// this is the abstract mediator/director
struct SpaManager
{
    virtual ~SpaManager() = default;
    virtual void Show() = 0;
    // We could also pass events as strings here for example.
    // In that case, we don't need the Mediator to create and manage all the collegues.
    // They could by passed in the ctor of the concrete mediator implementation.
    // They could also be pushed in a vector by a "Add" function...
    virtual void NotifyTaskCompleted(SpaCollegue* collegue) = 0;  
};

// this is the base object that the mediator manages
class SpaCollegue
{
public:
    // it's responsability is to store a mediator instance
    SpaCollegue(SpaManager* manager)
    : manager_(manager)
    {}
    virtual ~SpaCollegue() = default;
protected:
// its stores a ref to the Mediator
    SpaManager* manager_;
};

class SpaCook : public SpaCollegue
{
public:
    SpaCook(SpaManager* manager)
    : SpaCollegue(manager)
    {}

    void Cook()
    {
        this->manager_->NotifyTaskCompleted(this);
    }
};

class SpaCleaner : public SpaCollegue
{
public:
    SpaCleaner(SpaManager* manager)
    : SpaCollegue(manager)
    {}

    void Clean()
    {
        this->manager_->NotifyTaskCompleted(this);
    }
};

// the concrete implementation of the mediator
class SpaKitchenManager : public SpaManager
{
public:
    SpaKitchenManager()
    {
        CreateCollegues();
    }

    void NotifyTaskCompleted(SpaCollegue* collegue) override
    {
        if (collegue == cook_.get())
        {
            state_ = "cokking";
            std::cout << "Cooking, cleaning after!" << std::endl;
            cleaner_->Clean();
            state_ = "clean";
        }
        else if (collegue == cleaner_.get())
        {
            std::cout << "Kitchen cleaned!" << std::endl;
        }
    }

    void Show() override
    {
        std::cout << state_ << std::endl;
    }

    void Order()
    {
        cook_->Cook();
    }
protected:
    virtual void CreateCollegues()
    {
        cook_ = std::make_unique<SpaCook>(this);
        cleaner_ = std::make_unique<SpaCleaner>(this);
    }

private:
    std::unique_ptr<SpaCook> cook_;
    std::unique_ptr<SpaCleaner> cleaner_;
    std::string state_ = "Cleaned";
};

int main()
{   
    SpaKitchenManager manager;
    manager.Order();

    return 0;
}