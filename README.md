## Language for JSON (JavaScript Object Notation)

In this project, a specific-purpose language is implemented for definitions and usage
of data in JSON format. This language is compiled to C++ by including only the "JSONlang.h"
header file.

Language Format:
```cpp
#include "JSONlang.h"
json variable definition1
json variable definition2
…
PROGRAM_BEGIN
    json variable definition3
    …
    json editing statement1
    json variable definitionk
    …
    json editing statement2 
    … 
    json editing statementn 
PROGRAM_END
```
#### NOTE: No semicolon is used.

### Language elements

#### Definition of JSON variable
  - JSON(name) = value
<br> Where name is the id of the defined variable.
<br> Value can be a string, number, object, array, true, false, null
<br> <br> 

| Value Type | Example | Syntax |
| --- | --- | --- | 
| string | "example" | STRING("example") |
| number | 34 | NUMBER(34) |
| true | true | TRUE |
| false | false | FALSE |
| null | null | NULL |
| object | {<br>&emsp;"title" : "C++14",<br>&emsp;"year" : 2014<br>}| OBJECT {<br>&emsp;KEY(title) : STRING("C++14"),<br>&emsp;KEY(year) : NUMBER(2014)<br>} |
| array| [] // Empty Array<br>[<br>&emsp;2020,<br>&emsp;"CoViD",<br>&emsp;{<br>&emsp;&emsp;"country" : "Greece", <br>&emsp;&emsp;"deaths" : 5598 <br>&emsp;}<br>]| ARRAY // Empty Array<br>ARRAY [<br>&emsp;NUMBER(2020),<br>&emsp;STRING("CoViD"),<br>&emsp;OBJECT {<br>&emsp;&emsp;KEY(country) : STRING("Greece"), <br>&emsp;&emsp;KEY(deaths) : NUMBER(5598) <br>&emsp;}<br>] |






