#include "JSONlang.h"
#include <algorithm>



PROGRAM_BEGIN

auto myObject = new Object{ new Key("myKey1"), new Object{new Key("myKeyInside"), new String("myValueInside")}, new Key("myKey2"), new String("myValue2") };


auto a = []() { return new Key("myKey1"); }();


//std::cout << myObject << std::endl; 

String* s = new String("hehe");
Number* n = new Number(150.213);
Null* null = new Null();
Boolean* b = new Boolean(true);
Boolean* bb = new Boolean(false);




Array* arr1 = new Array;
Array* arr2 = new Array;
Array* arr3;

String* ss = (s, s);

(*(new Array))[ *s, s ];

//(*(new Array))[(new String("xaxa"), s)];



PROGRAM_END

