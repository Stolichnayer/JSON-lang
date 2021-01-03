#include "JSONlang_data.h"

#define PROGRAM_BEGIN   int main() {
#define PROGRAM_END	    ;}

#define JSON(name) auto name

// Types
#define NUMBER(num)		num
#define STRING			std::string
#define TRUE			true
#define FALSE			false
#define OBJECT			Object
// Stringify
#define KEY(text)		std::string(#text)
	