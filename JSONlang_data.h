#include <iostream>
#include <string>
#include <map>

class Printable
{
public:
    virtual std::string ToString() const = 0;
};

class Key : public Printable
{
private:
    std::string _data;
public:
    Key(std::string data) : _data(data) {}
    virtual std::string ToString() const override { return _data; }
};

class Value : public Printable
{

};

class String : public Value
{
private:
    std::string _data;
public:
    String(std::string data) : _data(data) {}
    virtual std::string ToString() const override { return _data; }
};

class Object : public Value
{
private:
    std::map<std::string, Value*> _data;
public:
    Object(std::initializer_list<Printable*> data) 
    {
        for (auto itr = data.begin(); itr != data.end(); ++itr) 
        {
            //_data.emplace(, (Value *)std::next(itr, 1));
            //_data.emplace("xaxa" , new String("xaxa"));
            std::cout << (*itr)->ToString() << ", " << (*std::next(itr, 1))->ToString() << std::endl;
            ++itr;
        }
    }
    virtual std::string ToString() const override 
    {  
        return "nulllll";
    }
};





// Operator Overloads
std::ostream& operator<<(std::ostream& os, Value * val)
{

    os << "{ ";


    os << " }";

    return os;
}
