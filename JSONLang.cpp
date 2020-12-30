#include "JSONlang.h"
#include <algorithm>



PROGRAM_BEGIN



auto myObject = new Object { new Key("myKey1"), new String("myValue1"), new Key("myKey2"), new String("myValue2") };

std::cout << myObject << myObject << std::endl;




PROGRAM_END