#include <iostream>
#include <string>

#define PROGRAM_BEGIN int main() {
#define PROGRAM_END	  ;}

#define JSON(name) auto name

// Types
#define NUMBER(num)		num
#define STRING			std::string
#define TRUE			true
#define FALSE			false


#define OBJECT (test)



class Object
{
	int x; int y;
public:
	Object() {
		x = 0; y = 0;
	}
};

