#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <iostream>
#include <memory>

namespace Prototype
{

// CREATE AN INTERFACE FOR PROTOTYPE WITH CLONE() TO COPY
class Parent
{
public:
    Parent(){}
    virtual ~Parent(){}
    virtual std::unique_ptr<Parent> clone(std::string name, int id) = 0;
    virtual void doStuff() = 0;
};

// CREATE A CLASS THAT USE AS A PROTOTYPE
class Child_01 : public Parent
{
public:
    Child_01() {}
    Child_01(std::string name, int id) : name_(name), id_(id){}

    std::unique_ptr<Parent> clone(std::string name, int id) override
    {
        return std::make_unique<Child_01>(name, id);
    }
    void doStuff() override
    {
        std::cout << "\nPrototype : Child 01 = " << name_ << " id = " << id_ << " - do Stuff" << std::endl;
    }

private:
    std::string name_;
    int id_;

};

void runPrototype()
{
    // CREATE A PROTOYPE
    std::unique_ptr<Parent> prototype = std::make_unique<Child_01>("Prototype", 0);
    prototype->doStuff();

    // CREATE A OBJECTS USING A CLONE() METHOD
    std::unique_ptr<Parent> cloneObject_01 = prototype->clone("New Child 01", 1);
    cloneObject_01->doStuff();

    std::unique_ptr<Parent> cloneObject_02 = prototype->clone("New Child 02", 2);
    cloneObject_02->doStuff();
}
}

#endif // PROTOTYPE_H
