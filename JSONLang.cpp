#include "JSONlang.h"
#include <algorithm>



PROGRAM_BEGIN



auto myObject = new Object{ new Key("myKey1"), new Object{new Key("myKeyInside"), new String("myValueInside")}, new Key("myKey2"), new String("myValue2") };

//std::cout << myObject << std::endl;

String* s = new String("hehe");
Number* n = new Number(150.213);
Null* null = new Null();
Boolean* b = new Boolean(true);
Boolean* bb = new Boolean(false);


std::cout << myObject << std::endl;
std::cout << n << std::endl;
std::cout << null << std::endl;
std::cout << b << std::endl;
std::cout << bb << std::endl;
std::cout << s << std::endl;

PROGRAM_END