#include <format>
#include <iostream>
#include <memory>
#include <vector>

template <typename Item>
class Iterator;

// this is the container, a.k.a the list that we will be iterating over
// it contains data/element/item type of objects
template <typename Item>
struct AbstractContainer
{
    virtual ~AbstractContainer() = default;
    // exposes some useful api that the iterator can use

    // lets say the the container is some kind of array now, 
    // we could implement our own data structure here
    virtual const Item& At(std::size_t index) const = 0;

    virtual std::size_t Size() const = 0;

    virtual void Add(Item) = 0;

    virtual std::unique_ptr<Iterator<Item>> CreateIterator() const = 0;
};

template <typename Item>
class SimpleIterator;

template <typename Item>
class Container : public AbstractContainer<Item>
{
public:
    // exposes some useful api that the iterator can use
    const Item& At(std::size_t index) const override
    {
        // the non-const operator[] return a T&
        // the const operator[] return a const T&
        // so if the method is const it must return a const T&
        return items_[index];
    }
    std::size_t Size() const override
    {
        return items_.size();
    }
    void Add(Item item) override
    {
        return items_.push_back(item);
    }

    // the container usually create its own iterator
    std::unique_ptr<Iterator<Item>> CreateIterator() const override
    {
        // the this pointer is const here because the method is const
        return std::make_unique<SimpleIterator<Item>>(this);
    }
private:
    // lets say the the container is some kind of array now, 
    // we could implement our own data structure here
    std::vector<Item> items_;
};

template <typename Item>
class Iterator
{
public:
    virtual ~Iterator() = default;
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual const Item& CurrentItem() const = 0;
protected:
    // dont let the client create an iterator by itself.
    Iterator()
    {}
};

template <typename Item>
class SimpleIterator : public Iterator<Item>
{
public:
    SimpleIterator(const AbstractContainer<Item>* container)
    : container_(container)
    {}
    void First() override
    {
        index_ = 0;
    }
    virtual void Next() override
    {
        ++index_;
    }
    virtual bool IsDone() const override
    {
        return index_ >= container_->Size() ? true : false;
    }
    // if we want currentItem to return a T& we need to make the container stored
    // in the iterator a non-const member
    virtual const Item& CurrentItem() const override
    {
        return container_->At(index_);
    }
private:
    const AbstractContainer<Item>* container_;
    std::size_t index_;
};

// the data
struct SpaItem
{
    std::string name;
    double price;
};

int main()
{   
    SpaItem sauna = {"sauna", 5999.99};
    SpaItem door = {"door", 59.99};

    Container<SpaItem> spa_items;
    spa_items.Add(sauna);
    spa_items.Add(door);

    const auto iterator = spa_items.CreateIterator();
    for (iterator->First(); !iterator->IsDone(); iterator->Next())
    {   
        const auto item = iterator->CurrentItem();
        std::cout << std::format("I have in my container a {} priced at {}!", item.name, item.price) 
                  << std::endl;
    }

    return 0;
}