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
};

class Object : public Value
{
private:
    std::map< std::string, std::reference_wrapper<Printable> > _data;
    //std::map< std::string, Printable* > _data;
public:
    /*
    Object(std::initializer_list<Printable*> data)
    {
        for (auto itr = data.begin(); itr != data.end(); ++itr) 
        {
            //_data.emplace((*itr)->ToString(), dynamic_cast<Value*> (*std::next(itr, 1)));
            //++itr;
        }
    }    */
    
    Object(std::initializer_list<std::reference_wrapper<Printable>> data)
    {
        Value::_data.push_back(this);

        for (auto itr = data.begin(); itr != data.end(); ++itr)
        {
            _data.emplace(  (itr)->get().ToString(),   *std::next(itr, 1)  );                       
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
        return _data? "true" : "false"; 
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

    Value* operator[](int index)
    {
        if (index >= _data.size()) {
            std::cout << "Error: Array index out of bound.";
            exit(0);
        }
        return _data[index];
    }

    std::string operator[](std::string str)
    {
        std::cout << "NAI re string";
        return "STRIGKOS";
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


std::ostream& operator,( std::ostream& os, Value& val)
{
    os << val.ToString() << std::endl;
    return os;
}



