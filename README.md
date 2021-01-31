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

## Language elements

### 1. Definition of JSON variable
```python
JSON(name) = value
```
Where name is the id of the defined variable.
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
| array| [ ] // Empty Array<br>[<br>&emsp;2020,<br>&emsp;"CoViD",<br>&emsp;{<br>&emsp;&emsp;"country" : "Greece", <br>&emsp;&emsp;"deaths" : 5598 <br>&emsp;}<br>]| ARRAY // Empty Array<br>ARRAY [<br>&emsp;NUMBER(2020),<br>&emsp;STRING("CoViD"),<br>&emsp;OBJECT {<br>&emsp;&emsp;KEY(country) : STRING("Greece"), <br>&emsp;&emsp;KEY(deaths) : NUMBER(5598) <br>&emsp;}<br>] |

#### Examples

```js
//define emptyObj json with empty object
JSON(emptyObj) = OBJECT {}

//define emptyArray json with empty array
JSON(emptyArray) = ARRAY

//define book json with an object containing data for a book
JSON(book) = OBJECT {
    KEY(title) : STRING("Gone Girl"),
    KEY(published) : NUMBER(2012),
    KEY(type) : STRING("Thriller"),
    KEY(author) : OBJECT {
        KEY(firstname) : STRING("GILLIAN"),
        KEY(surname) : STRING("FLYNN"),
        KEY(age) : NUMBER(45)
    }
}

//define week_temperatures json with an array of numbers
JSON(week_temperatures) = ARRAY [
    NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
    NUMBER(19), NUMBER(18.5), NUMBER(19)
]

//define students json with an array of objects representing students
JSON(students) = ARRAY [
    OBJECT {
        KEY(name) : STRING("Kevin Malone"),
        KEY(id) : NUMBER(4444),
        KEY(grades) : ARRAY [
            OBJECT { KEY(cs100) : NUMBER(9.5) },
            OBJECT { KEY(cs150) : NUMBER(9) },
            ...
        ]
    },
    ...
]
```
### 2. Editing of JSON variables and values

```python
SET json_value ASSIGN value 
```
Sets a value to an existing JSON variable.
<br> The value must be of the same type of the defined variable, except if value is contained in an ARRAY or an OBJECT.

```js
//change 3rd day temperature from 19 to 22
SET week_temperatures[2] ASSIGN NUMBER(22)

//change 3rd day temperature from 19 to "Unknown"
SET week_temperatures[2] ASSIGN STRING("Unknown")

//add email address for 1st student
SET students[0]["email"] ASSIGN STRING("kevin_m@hotmail.com")

//assign new object in emptyObj json
SET emptyObj ASSIGN OBJECT{ KEY(a) : STRING("alpha") }
```

```python
SET json_array APPEND value1, value2, …
```
Adds the values of the given arguments (value1, value2, ...) to the JSON value, which must be an ARRAY.

```js
//appends values 23, 22, 20 to the end of the temperature array
SET week_temperatures APPEND NUMBER(23), NUMBER(22), NUMBER(20)

//appends a grade for course cs255
SET students[0]["grades"] APPEND OBJECT { KEY(cs255) : NUMBER(9) }
```

```python
ERASE json_value_or_variable
```
Deletes inner values of JSON objects or arrays, in which they are contained. 
In case of JSON variable (which must be an object or an array), it just erases all its elements and becomes empty ({ } or [ ])

```js
ERASE book["author"]["age"] //removes age from author object of book
ERASE book["type"] //removes type of book
ERASE book //removes all book data, now book is an empty object
```




