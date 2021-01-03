#include <iostream>
#include <string>
#include <map>
#include <vector>

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
    virtual std::string ToString() const override
    {
        return "\"" + _data + "\""; 
    }
};

class Value : public Printable
{
public:
    virtual std::string ToString() const override
    {
        return "Value class";
    }

    std::string operator,(Value* v2)
    {
        std::cout << "operator,";
        return std::string("gamw");
    }

};

class String : public Value
{
private:
    std::string _data;
public:
    String(std::string data) : _data(data) {}
    virtual std::string ToString() const override 
    { 
        return "\"" + _data + "\"";
    }
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

class Number : public Value
{
private:
    double _data;
public:
    Number(double data) : _data(data) {}
    virtual std::string ToString() const override
    {
        double intpart;
        if (std::modf(_data, &intpart) == 0.0)
        {
            return std::to_string((int)_data);
        }
        else 
        {
            std::string str = std::to_string(_data);
            str.erase(str.find_last_not_of('0') + 1, std::string::npos); // Remove Trailing Zeros from double
            return str;
        }            
    }
};

class Boolean : public Value
{
private:
    bool _data;
public:
    Boolean(bool data) : _data(data) {}
    virtual std::string ToString() const override 
    { 
        return _data? "true" : "false"; 
    }
};

class Null : public Value
{
private:
    std::string _data = "null";
public:
    virtual std::string ToString() const override 
    { 
        return _data; 
    }
};


class Array : public Value
{
public:
    std::vector<int> _data;
public:
    Array() {}
    Array(std::initializer_list<int> data)
    {
        _data = data;
    }

    virtual std::string ToString() const override
    {
        return "";
    }


    int operator[](int index)
    {
        if (index >= _data.size()) {
            std::cout << "Error: Array index out of bound.";
            exit(0);
        }
        return _data[index];
    }

    void operator[](std::string str)
    {
        std::cout << "NAI re string";
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

/*
std::string operator,(Value& v1, Value& v2)
{
    std::cout << "operator,";
    return std::string("gamw");
}

*/