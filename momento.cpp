#include <cstdio>
#include <format>
#include <iostream>
#include <list>
#include <memory>

struct SpaState
{
    unsigned int nb_doors = 0;
    unsigned int nb_pools = 0;
};

// struct AbstractSpaMomento
// {
//     virtual ~AbstractSpaMomento() = default;
//     virtual unsigned int getNbDoors() const = 0;
//     virtual unsigned int getNbPools() const = 0;
// };

// the momento stores a state
class SpaMomento
{
    // Preserved encapsulation by letting only the originator modify the momento.
    // The pattern with "friend" doesn't work with an abstract momento
    friend class Spa;

    SpaMomento(std::shared_ptr<SpaState> state)
    : state_(std::move(state))
    {}

    // virtual void SetState(SpaState* state)
    // {
    //     state_ = *state;
    // }
    virtual std::shared_ptr<SpaState> GetState()
    {
        return state_;
    }

    // shared ownership of the SpaState between the momento and the originator
    std::shared_ptr<SpaState> state_;
};

// This is the originator, it stores states that might change over time.
// It's responsible of creating momentos and restoring them.
class Spa 
{
public:
    Spa(std::shared_ptr<SpaState> state)
    : state_(std::move(state))
    {}
    // the save method creates a momento from a state
    SpaMomento Save() const
    {
        // deep copy
        std::shared_ptr<SpaState> new_state = std::make_shared<SpaState>(*state_);
        printf("Saved doors=%i, pools=%i\n", new_state->nb_doors, new_state->nb_pools);
        
        // shared_ptr does work with friend...
        return SpaMomento(new_state);
    }
    void Restore(SpaMomento momento)
    {
        state_ = momento.GetState();
    }
    // sometimes all the business logic can happen in the originator 
    // and we don't need a bookeeping for example
    void BuyDoor()
    {
        ++state_->nb_doors;
    }
    void BuyPool()
    {
        ++state_->nb_pools;
    }
    void PrintState()
    {
        printf("State is doors=%i, pools=%i\n", state_->nb_doors, state_->nb_pools);
    }
private:
    // the originator also stores a state
    std::shared_ptr<SpaState> state_;
};

// This is the Caretaker that does the bookeeping.
// It can also be a class that just execute/unexecutes.
class SpaManager
{
public:
    SpaManager(Spa* spa)
    : spa_(spa)
    {}
    void Save()
    {
        momentos_.push_back(spa_->Save());
        std::cout << "Save!" << std::endl;
    }
    void Undo()
    {
        std::cout << "Undo!" << std::endl;
        if (!momentos_.empty())
        {
            SpaMomento last_state = momentos_.back();
            spa_->Restore(last_state);
            momentos_.pop_back();
        }
    }
    void AddDoor()
    {
        spa_->BuyDoor();
    }
    void AddPool()
    {
        spa_->BuyPool();
    }
    void PrintLast()
    {
        // We could use the momentos here if there would not be with the "friend" pattern
        // std::cout << std::format("doors={} pools={}",momentos_.back()->getNbDoors(), momentos_.back()->getNbPools()) << std::endl;

        spa_->PrintState();
    }
private:
    Spa* spa_;
    std::list<SpaMomento> momentos_;
};

int main()
{   
    std::shared_ptr<SpaState> state = std::make_shared<SpaState>(0, 0);
    Spa spa(state);
    SpaManager manager(&spa);
    manager.AddDoor();
    manager.AddDoor();
    manager.AddDoor();
    manager.PrintLast();
    // save current design
    manager.Save();
    manager.AddPool();
    manager.AddPool();
    manager.AddPool();
    manager.PrintLast();
    manager.Undo();
    manager.PrintLast();

    return 0;
}