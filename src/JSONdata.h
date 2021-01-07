#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>

class Printable
{
public:
    virtual std::string ToString() const
    {
        return "Printable class";
    };
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

    std::string GetData()
    {
        return _data;
    }
};

class Value : public Printable
{
public:
    // This is needed to initialize arrays with the overloaded comma operator
    std::vector<Value*> _data;

    virtual std::string ToString() const override
    {
        return "Value class";
    }
    
    virtual std::string GetClassName() const
    {
        return "value";
    }

    virtual Value& operator[](std::string str)
    {
        std::cout << "VALUE OPERATOR[]";
        return *new Value;
    }
};

class String : public Value
{
private:
    std::string _data;
public:
    String(std::string data)
    {
        _data = data;
        Value::_data.push_back(this);
    }

    virtual std::string ToString() const override
    {
        return "\"" + _data + "\"";
    }

    std::string GetData()
    {
        return _data;
    }
    
    std::string GetClassName() const override
    {
        return "string";
    }
};

class Object : public Value
{
public:
    std::map<std::string, std::reference_wrapper<Value>> _data;
public:
    Object(std::initializer_list<std::reference_wrapper<Printable>> data)
    {
        Value::_data.push_back(this);

        for (auto itr = data.begin(); itr != data.end(); ++itr)
        {
            Key* key = dynamic_cast<Key*> (&(itr->get()));           
            if (key)
            {
                Value& val = *dynamic_cast<Value*> (&std::next(itr, 1)->get());
                _data.emplace(key->GetData(), val);
            }                
            else
            {
                std::cout << "Error: Wrong Object format (Must be key, value).\n";
                exit(1);
            }
                
            ++itr;
        }
    }

    virtual std::string ToString() const override
    {
        if (_data.size() == 0)
            return "{}";

        std::string str = "{ ";

        for (auto itr = _data.begin(); itr != _data.end(); ++itr)
        {
            str.append(itr->first);
            str.append(" : ");
            str.append((itr->second).get().ToString());

            if ((++itr) != _data.end())
                str.append(", ");

            --itr;
        }

        str.append(" }");

        return str;
    }

    std::string GetClassName() const override
    {
        return "object";
    }

    std::map<std::string, std::reference_wrapper<Value>>& GetData()
    {
        return _data;
    }

    Value& operator[](std::string str)
    {
        for (const auto& pair : _data)
        {
            if (pair.first == str)            
                return pair.second;            
        }

        std::cout << "Error: Key \"" << str << "\" was not found in object.\n";
        exit(1);
    }
};

class Number : public Value
{
private:
    double _data;
public:
    Number(double data)
    {
        _data = data;
        Value::_data.push_back(this);
    }

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

    std::string GetClassName() const override
    {
        return "number";
    }
};

class Boolean : public Value
{
private:
    bool _data;
public:
    Boolean(bool data)
    {
        _data = data;
        Value::_data.push_back(this);
    }

    virtual std::string ToString() const override
    {
        return _data ? "true" : "false";
    }

    std::string GetClassName() const override
    {
        return "boolean";
    }
};

class Null : public Value
{
private:
    std::string _data = "null";
public:
    Null()
    {
        Value::_data.push_back(this);
    }

    virtual std::string ToString() const override
    {
        return _data;
    }

    std::string GetClassName() const override
    {
        return "null";
    }
};


class Array : public Value
{
public:
    std::vector<Value*> _data;
public:
    Array()
    {
        Value::_data.push_back(this);
    }

    virtual std::string ToString() const override
    {
        if (_data.size() == 0)
            return "[]";

        std::string str = "[ ";
        for (auto v : _data)
        {
            str.append(v->ToString());

            if (v != _data[_data.size() - 1])
                str.append(", ");
        }
        str.append(" ]");

        return str;
    }

    std::string GetClassName() const override
    {
        return "array";
    }

    std::vector<Value*> GetData()
    {
        return _data;
    }

    Value& operator[](int index)
    {
        if (index >= _data.size()) {
            std::cout << "Error: Array index out of bound.";
            exit(0);
        }
        return *_data[index];
    }

    Array& operator[](Value& val)
    {
        _data = val._data;
        return *this;
    }
};


// Operator Overloads
std::ostream& operator<<(std::ostream& os, Value& val)
{
    os << val.ToString();
    return os;
}

std::ostream& operator<<(Value& val, std::ostream& os)
{
    os << val.ToString();
    return os;
}

Value& operator,(Value& val1, Value& val2)
{
    for (auto v : val2._data)
    {
        val1._data.push_back(v);
    }
    return val1;
}

std::ostream& operator,(std::ostream& os, Value& val)
{
    os << val.ToString() << std::endl;
    return os;
}

std::ostream& operator,(std::ostream& os, int var)
{
    os << var << std::endl;
    return os;
}

std::ostream& operator,(std::ostream& os, bool var)
{
    if (var)
        os << "true" << std::endl;
    else
        os << "false" << std::endl;
    return os;
}

std::ostream& operator,(std::ostream& os, std::string str)
{
    os << str << std::endl;
    return os;
}

// Functions
int SIZE_OF(Value& val)
{
    Object* obj = dynamic_cast<Object*>(&val);
    if (obj)
        return obj->GetData().size();

    Array* arr = dynamic_cast<Array*>(&val);
    if (arr)
        return arr->GetData().size();

    return 1;
}

bool IS_EMPTY(Value& val)
{
    Object* obj = dynamic_cast<Object*>(&val);
    if (obj)
        return (obj->GetData().size() == 0);

    Array* arr = dynamic_cast<Array*>(&val);
    if (arr)
        return (arr->GetData().size() == 0);

    return false;
}

bool HAS_KEY(Value& val, std::string key)
{
    Object* obj = dynamic_cast<Object*>(&val);
    if (obj)
    {
        for (const auto& i : obj->GetData())
        {
            if (i.first == key)
                return true;
        }
    }

    return false;        
}

std::string TYPE_OF(Value& val)
{
    return val.GetClassName();
}


