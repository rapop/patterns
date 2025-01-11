#include <iostream>
#include <memory>

class HelperHandler
{
public:
    HelperHandler(std::shared_ptr<HelperHandler> next = nullptr) 
    : next_(std::move(next))
    {}

    // this remove the need to pass next in the ctor of each object
    virtual std::shared_ptr<HelperHandler> setNext(std::shared_ptr<HelperHandler> next)
    {
        next_ = next;
        return next_;
    }

    virtual void HandleHelp(const std::string& request)
    {
        if (next_) 
        {
            next_->HandleHelp(request);
        }
    }

private:
    std::shared_ptr<HelperHandler> next_;
};

class SpaEmployee : public HelperHandler
{
public:
    SpaEmployee(std::shared_ptr<HelperHandler> next = nullptr)
    :  HelperHandler(std::move(next))
    {}

    // each specific type will handle a specific request that will be sent either via a
    // function call or a via string/topic name at construction
    void HandleHelp(const std::string& request) override
    {
        if (request == "serve") 
        {
            std::cout << "SpaEmployee has served" << std::endl;
        }
        else 
        {
            // forwards the request to the next handler
            HelperHandler::HandleHelp(request);
        }
    }

};

class SpaKitchen : public HelperHandler
{
public:
    SpaKitchen(std::shared_ptr<HelperHandler> next = nullptr)
    :  HelperHandler(std::move(next))
    {}

    void HandleHelp(const std::string& request) override
    {
        if (request == "menu") 
        {
            std::cout << "SpaKitchen can give menu" << std::endl;
        }
        else 
        {
            std::cout << "SpaKitchen: not for me" << std::endl;
            // forwards the request to the next handler
            HelperHandler::HandleHelp(request);
        }
    }

};

class Spa : public HelperHandler
{
public:
    Spa(std::shared_ptr<HelperHandler> next = nullptr)
    :  HelperHandler(std::move(next))
    {}

    void HandleHelp(const std::string& request) override
    {
        std::cout << "Spa can't do anything" << std::endl;
        HelperHandler::HandleHelp(request);
    }
};

int main()
{   
    // work like this also
    // std::shared_ptr<SpaEmployee> spa_e = std::make_shared<SpaEmployee>(nullptr);
    // std::shared_ptr<SpaKitchen> spa_k = std::make_shared<SpaKitchen>(spa_e);
    // std::shared_ptr<Spa> spa = std::make_shared<Spa>(spa_k);

    std::shared_ptr<SpaEmployee> spa_e = std::make_shared<SpaEmployee>();
    std::shared_ptr<SpaKitchen> spa_k = std::make_shared<SpaKitchen>();
    std::shared_ptr<Spa> spa = std::make_shared<Spa>();

    spa->setNext(spa_k)->setNext(spa_e);

    spa->HandleHelp("serve");

    return 0;
}