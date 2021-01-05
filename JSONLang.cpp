#include "JSONlang.h"
#include <algorithm>



PROGRAM_BEGIN

auto myObject = *new Object { *new Key("myKey1"), *new Object { *new Key("myKeyInside"),  *new String("myValueInside")}, *new Key("myKey2"), *new String("myValue2") };


//auto myObject2 = Object{ * new Key("xaxa333x") , * new String("OMGOMGOGMOMGOMG") };

std::cout << myObject << std::endl;

//auto a = []() { return new Key("myKey1"); }(); // Lambda



Array arr;
Value val1;
Value val2;

//std::cout << arr[*new String("prlp"), *new String("xexe"), *new String("asdad"), *new String("nhnhnhn")];



auto aasd = (*(new Array))[ *new String("11111"), *new Object { *new Key("myKeyInside"),  *new String("myValueInside")}, *new String("33333"), *new String("4444")];

std::cout << aasd;


Value* val33 = new String("lp");
//(*(new Array))[(new String("xaxa"), s)];

//std::string ss = (new String("xaxa")) + (new String("xaxa"));

//std::cout << ss << std::endl;

PROGRAM_END

