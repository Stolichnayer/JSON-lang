#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <cmath> 

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
        std::cout << "Error: Cannot use operator '[\"string\"]' on this value.\n";
        exit(1);        
    }

    virtual Value& operator[](int index)
    {
        std::cout << "Error: Cannot use operator '[int]' on this value.\n";
        exit(1);
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
    std::vector<std::string> keyVector; // To keep order of insertion in map
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

                auto ret = _data.try_emplace(key->GetData(), val); // Check if emplace failed due to duplicate key
                if(ret.second)
                    keyVector.push_back(key->GetData());
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

        int iterationCount = 0;
        std::string str = "{ ";
        for (auto key : keyVector)
        {
            iterationCount++;
            str.append(key);
            str.append(" : ");
            str.append(_data.find(key)->second.get().ToString());

            if (iterationCount != _data.size())
                str.append(", ");
        }
        str.append(" }");

        return str;
    }   
    /*
    virtual std::string ToString() const override
    {
        if (_data.size() == 0)
            return "{}";

        int iterationCount = 0;
        std::string str = "{ ";
        for (auto itr = _data.begin(); itr != _data.end(); ++itr)
        {
            iterationCount++;
            str.append(itr->first);
            str.append(" : ");
            str.append((itr->second).get().ToString());

            if (iterationCount != _data.size())
                str.append(", ");
        }
        str.append(" }");

        return str;
    }*/

    std::string GetClassName() const override
    {
        return "object";
    }

    std::map<std::string, std::reference_wrapper<Value>>& GetData()
    {
        return _data;
    }

    std::vector<std::string>& GetKeyVector() 
    {
        return keyVector;
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

    double GetData() 
    {
        return _data;
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

    bool GetData() {
        return _data;
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

        int iterationCount = 0;
        std::string str = "[ ";       
        for (auto v : _data)
        {
            iterationCount++;
            str.append(v->ToString());

            if(iterationCount != _data.size())
                str.append(", ");
        }
        str.append(" ]");

        return str;
    }

    std::string GetClassName() const override
    {
        return "array";
    }

    std::vector<Value*>& GetData()
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

String& operator+(String& str1, String& str2)
{
    String* str = new String(str1.GetData() + str2.GetData());
    return *str;
}

Number& operator+(Number& num1, Number& num2) 
{
    Number* number = new Number(num1.GetData() + num2.GetData());
    return *number;
}

Array& operator+(Array& arr1, Array& arr2)
{
    Array* arr = new Array;
    auto& data = arr->GetData();
    auto& data1 = arr1.GetData();
    auto& data2 = arr2.GetData();

    for (auto i : data1)
    {
        data.push_back(i);
    }
    for (auto i : data2)
    {
        data.push_back(i);
    }

    return *arr;
}

Object& operator+(Object& obj1, Object& obj2)
{
    Object* obj = new Object{};

    auto& map  = obj->GetData();
    auto& keyVector = obj->GetKeyVector();

    auto& map1 = obj1.GetData();
    auto& keyVector1 = obj1.GetKeyVector();

    auto& map2 = obj2.GetData();
    auto& keyVector2 = obj2.GetKeyVector();

    for (auto key : keyVector1)
    {
        auto ret = map.try_emplace(key, map1.find(key)->second);
        if (ret.second) // if try_emplace doesn't fail
            keyVector.push_back(key);
    }

    for (auto key : keyVector2)
    {
        auto ret = map.try_emplace(key, map2.find(key)->second);
        if (ret.second) // if try_emplace doesn't fail
            keyVector.push_back(key);
    }

    return *obj;
}

Value& operator+(Value& val1, Value& val2)
{
    std::cout << "Error: operator '+' can only be used between Number, String, Array or Object objects.\n";
    exit(1);    
}

Number& operator-(Value& val1, Value& val2)
{
    std::string className1 = val1.GetClassName();
    std::string className2 = val2.GetClassName();

    if (className1 == "number" && className2 == "number")
    {
        Number *number = new Number( ((Number*)&val1)->GetData() - ((Number*)&val2)->GetData() );
        return *number;        
    }
    else
    {
        std::cout << "Error: operator '-' can only be used between Number objects.\n";
        exit(1);
    }
}

Number& operator*(Value& val1, Value& val2)
{
    std::string className1 = val1.GetClassName();
    std::string className2 = val2.GetClassName();

    if (className1 == "number" && className2 == "number")
    {
        Number* number = new Number( ((Number*)&val1)->GetData() * ((Number*)&val2)->GetData() );
        return *number;
    }
    else
    {
        std::cout << "Error: operator '*' can only be used between Number objects.\n";
        exit(1);
    }
}

Number& operator/(Value& val1, Value& val2)
{
    std::string className1 = val1.GetClassName();
    std::string className2 = val2.GetClassName();

    if (className1 == "number" && className2 == "number")
    {
        Number* number = new Number( ((Number*)&val1)->GetData() / ((Number*)&val2)->GetData() );
        return *number;
    }
    else
    {
        std::cout << "Error: operator '/' can only be used between Number objects.\n";
        exit(1);
    }
}

Number& operator%(Value& val1, Value& val2)
{
    std::string className1 = val1.GetClassName();
    std::string className2 = val2.GetClassName();

    if (className1 == "number" && className2 == "number")
    {
        Number* number = new Number( std::fmod(((Number*)&val1)->GetData(), ((Number*)&val2)->GetData()) );
        return *number;
    }
    else
    {
        std::cout << "Error: operator '%' can only be used between Number objects.\n";
        exit(1);
    }
}

Boolean& operator>(Value& val1, Value& val2)
{
    std::string className1 = val1.GetClassName();
    std::string className2 = val2.GetClassName();

    if (className1 == "number" && className2 == "number")
    {
        Boolean* boolean = new Boolean( ((Number*)&val1)->GetData() > ((Number*)&val2)->GetData() );
        return *boolean;
    }
    else
    {
        std::cout << "Error: operator '>' can only be used between Number objects.\n";
        exit(1);
    }
}

Boolean& operator<(Value& val1, Value& val2)
{
    std::string className1 = val1.GetClassName();
    std::string className2 = val2.GetClassName();

    if (className1 == "number" && className2 == "number")
    {
        Boolean* boolean = new Boolean( ((Number*)&val1)->GetData() < ((Number*)&val2)->GetData() );
        return *boolean;
    }
    else
    {
        std::cout << "Error: operator '<' can only be used between Number objects.\n";
        exit(1);
    }
}

Boolean& operator>=(Value& val1, Value& val2)
{
    std::string className1 = val1.GetClassName();
    std::string className2 = val2.GetClassName();

    if (className1 == "number" && className2 == "number")
    {
        Boolean* boolean = new Boolean( ((Number*)&val1)->GetData() >= ((Number*)&val2)->GetData() );
        return *boolean;
    }
    else
    {
        std::cout << "Error: operator '>=' can only be used between Number objects.\n";
        exit(1);
    }
}

Boolean& operator<=(Value& val1, Value& val2)
{
    std::string className1 = val1.GetClassName();
    std::string className2 = val2.GetClassName();

    if (className1 == "number" && className2 == "number")
    {
        Boolean* boolean = new Boolean( ((Number*)&val1)->GetData() <= ((Number*)&val2)->GetData() );
        return *boolean;
    }
    else
    {
        std::cout << "Error: operator '<=' can only be used between Number objects.\n";
        exit(1);
    }
}

Boolean& operator&&(Value& val1, Value& val2)
{
    std::string className1 = val1.GetClassName();
    std::string className2 = val2.GetClassName();

    if (className1 == "boolean" && className2 == "boolean")
    {
        Boolean* boolean = new Boolean( ((Boolean*)&val1)->GetData() && ((Boolean*)&val2)->GetData() );
        return *boolean;
    }
    else
    {
        std::cout << "Error: operator '&&' can only be used between Boolean objects.\n";
        exit(1);
    }
}

Boolean& operator||(Value& val1, Value& val2)
{
    std::string className1 = val1.GetClassName();
    std::string className2 = val2.GetClassName();

    if (className1 == "boolean" && className2 == "boolean")
    {
        Boolean* boolean = new Boolean( ((Boolean*)&val1)->GetData() || ((Boolean*)&val2)->GetData() );
        return *boolean;
    }
    else
    {
        std::cout << "Error: operator '||' can only be used between Boolean objects.\n";
        exit(1);
    }
}

Boolean& operator!(Value& val)
{
    std::string className1 = val.GetClassName();

    if (className1 == "boolean")
    {
        Boolean* boolean = new Boolean( !((Boolean*)&val)->GetData() );
        return *boolean;
    }
    else
    {
        std::cout << "Error: operator '!' can only be used with Boolean object.\n";
        exit(1);
    }
}

Boolean& operator==(Value& val1, Value& val2)
{
    std::string className1 = val1.GetClassName();
    std::string className2 = val2.GetClassName();

    if (className1 == className2)
    {
        Boolean* boolean = new Boolean( val1.ToString() == val2.ToString());
        return *boolean;
    }
    else
    {
        std::cout << "Error: operator '==' can only be used between same type objects.\n";
        exit(1);
    }
}

Boolean& operator!=(Value& val1, Value& val2)
{
    std::string className1 = val1.GetClassName();
    std::string className2 = val2.GetClassName();

    if (className1 == className2)
    {
        Boolean* boolean = new Boolean(val1.ToString() != val2.ToString());
        return *boolean;
    }
    else
    {
        std::cout << "Error: operator '!=' can only be used between same type objects.\n";
        exit(1);
    }
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


