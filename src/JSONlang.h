#include "JSONdata.h"

#define PROGRAM_BEGIN   int main() { 
#define PROGRAM_END	    ;}

// JSON Variable definition
#define JSON(name)		;Value& name

// Types
#define STRING			*new String
#define NUMBER			*new Number
#define TRUE			*new Boolean(true)
#define FALSE			*new Boolean(false)	
#define NULL			*new Null()
#define OBJECT			*new Object
#define ARRAY			(*(new Array))

// Stringify
#define KEY(text)		*new Key(#text), 0 ? (*new Value)

// Commands
#define PRINT			;std::cout , 
#define ERASE			;EraserManager::GetInstance() <<
#define SET				;&
#define APPEND			,
#define ASSIGN			<<

// static member initializer
EraserManager* EraserManager::eraser = nullptr;

