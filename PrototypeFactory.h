#ifndef PROTOTYPEFACTORY_H
#define PROTOTYPEFACTORY_H

#include <iostream>
#include <memory>

namespace PrototypeFactory
{

class Guitar
{
public:
    Guitar(){}
    Guitar(const std::string brand, const std::string model, const int price):
        m_brand(brand),
        m_model(model),
        m_price(price) {}

    friend std::ostream &operator << (std::ostream &os, Guitar &obj)
    {
        os << " Brand : " << obj.m_brand
           << " Model: " << obj.m_model
           << " Price: " << obj.m_price
           << std::endl;
        return os;
    }
    void setBrand (const std::string &brand) {m_brand = brand;}
    void serModel (const std::string &model) {m_model = model;}
    void setPrice (const int &price)         {m_price = price;}

    std::string getBrand() const {return m_brand;}
    std::string getModel() const {return m_model;}
            int getPrice() const {return m_price;}

private:
    std::string m_brand;
    std::string m_model;
    int m_price;
};

class Shop
{
public:
    Shop(){}
    Shop(Guitar *gt, const int amount) :
        m_gt(gt),
        m_amout(amount) {}
    ~Shop() {delete m_gt;}

    Shop& operator=(const Shop& other)
    {
        if (this == &other)
            return *this;
        m_gt = other.m_gt;
        m_amout = other.m_amout;
        return *this;
    }

    Shop(const Shop &shp) : m_amout(shp.m_amout)
    {
        m_gt = new Guitar(shp.m_gt->getBrand(),
                          shp.m_gt->getModel(),
                          shp.m_gt->getPrice());
    }

public:
    Guitar *m_gt;
    int m_amout;
};

class GuitarShopFactory
{
public:
    static Shop shopKyiv;
    static Shop shopLviv;

    static std::unique_ptr<Shop> newGuitarsInKyiv(int amount, int price)
    {
        return newShop(amount, price, shopKyiv);
    }

    static std::unique_ptr<Shop> newGuitarsInLviv(int amount, int price)
    {
        return newShop(amount, price, shopLviv);
    }

private:
    static std::unique_ptr<Shop> newShop(int amount, int price, Shop& proto)
    {
        auto result = std::make_unique<Shop>(proto);
        result->m_amout = amount;
        result->m_gt->setPrice(price);
        return result;
    }
};

Shop GuitarShopFactory::shopKyiv;
Shop GuitarShopFactory::shopLviv;

void runPrototypeFactory()
{
    auto fender = GuitarShopFactory::newGuitarsInKyiv(10, 1500);
    auto gibson = GuitarShopFactory::newGuitarsInLviv(4, 200);
    std::cout << fender << std::endl;
    std::cout << gibson << std::endl;
}
}

#endif // PROTOTYPEFACTORY_H
