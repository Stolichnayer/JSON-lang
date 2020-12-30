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
            _data.emplace((*itr)->ToString(), dynamic_cast<Value*> (*std::next(itr, 1)));
            ++itr;
        }
    }
    virtual std::string ToString() const override 
    {  
        std::string str = "{ ";
        
        for (auto itr = _data.begin(); itr != _data.end(); ++itr)
        {
            str.append(itr->first);
            str.append(" : ");
            str.append((itr->second)->ToString());

            if((++itr) != _data.end())
                str.append(", ");

            --itr;
        }        

        str.append(" }");

        return str;
    }
};





// Operator Overloads
std::ostream& operator<<(std::ostream& os, Value * val)
{
    os << val->ToString();
    return os;
}

std::ostream& operator<<(Value* val, std::ostream& os)
{
    os << val->ToString();
    return os;
}
