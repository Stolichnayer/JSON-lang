#include "JSONlang.h"


PROGRAM_BEGIN

//define emptyObj json with empty object
JSON(emptyObj) = OBJECT{}
//define emptyArray json with empty array
JSON(emptyArray) = ARRAY
//define book json with an object containing data for a book
JSON(book) = OBJECT{
KEY(title) : STRING("Gone Girl"),
KEY(published) : NUMBER(2012),
KEY(type) : STRING("Thriller"),
KEY(author) : OBJECT{
 KEY(firstname) : STRING("GILLIAN"),
 KEY(surname) : STRING("FLYNN"),
 KEY(age) : NUMBER(45)
}
}

//define week_temperatures json with an array of numbers
JSON(week_temperatures) = ARRAY[
	NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
		NUMBER(19), NUMBER(18.5), NUMBER(19)
]

JSON(students) = ARRAY[
	OBJECT{
	KEY(name) : STRING("Kevin Malone"),
	KEY(id) : NUMBER(4444),
	KEY(grades) : ARRAY[
	OBJECT { KEY(hy100) : NUMBER(9.5) },
	OBJECT { KEY(hy150) : NUMBER(9) }
	]
	}

]

JSON(students2) = ARRAY[
	OBJECT{
	KEY(name) : STRING("Kevin Malone"),
	KEY(id) : NUMBER(4444),
	KEY(grades) : ARRAY[
	OBJECT { KEY(hy100) : NUMBER(9.5) },
	OBJECT { KEY(hy150) : NUMBER(9) }
	]
	}

]

JSON(t) = NUMBER(66)
JSON(t1) = NUMBER(55)


PRINT emptyObj
PRINT emptyArray
PRINT book
PRINT week_temperatures
PRINT students

//PRINT t, t1

PRINT t, t1, t, t1, t, t



PRINT SIZE_OF(book);
PRINT SIZE_OF(week_temperatures);
PRINT SIZE_OF(t);

PRINT IS_EMPTY(OBJECT{});

PRINT book
PRINT HAS_KEY(book, "author")


PRINT TYPE_OF(book)
PRINT TYPE_OF(week_temperatures)
PRINT TYPE_OF(emptyObj)
PRINT TYPE_OF(t)
PRINT TYPE_OF(TRUE)
PRINT TYPE_OF(FALSE)
PRINT TYPE_OF(STRING("xaxax"))
PRINT TYPE_OF(NULL)



		
PRINT students[0]["grades"][1]["hy150"]


PRINT week_temperatures 

PRINT t - t1
PRINT t * t1
PRINT t / t1
PRINT t % t1
PRINT t1 > t
PRINT t1 >= t
PRINT t1 <= t
PRINT t1 < t

PRINT !TRUE
;
std::cout << " nai\n\n";


PRINT students == students2


JSON(s1) = STRING("ena")
JSON(s2) = STRING("duo")

PRINT s1 + s2
PRINT STRING("ena") + STRING("duo")
PRINT NUMBER(10) + NUMBER(22)
PRINT t + t1

JSON(g) =  week_temperatures + week_temperatures



PRINT week_temperatures + week_temperatures


JSON(aaaaa) = ARRAY[
	NUMBER(20)
]

JSON(aaaaa2) = ARRAY[
	NUMBER(10)
]

PRINT aaaaa + aaaaa
PRINT week_temperatures + week_temperatures

PRINT week_temperatures + week_temperatures



JSON(asd) =
	OBJECT{
	KEY(name) : STRING("Kevin Malone"),
	KEY(id) : NUMBER(4444),
	KEY(grades) : ARRAY[
	OBJECT { KEY(hy100) : NUMBER(9.5) },
	OBJECT { KEY(hy150) : NUMBER(9) }
	]
	}

JSON(asd2) =
	OBJECT{
	KEY(name2) : STRING("Kevin Malone"),
	KEY(id2) : NUMBER(4444),
	KEY(grades2) : ARRAY[
	OBJECT { KEY(hy100) : NUMBER(9.5) },
	OBJECT { KEY(hy150) : NUMBER(9) }
	]
	}


PRINT asd
;
std::cout << "\n\n\n";
PRINT OBJECT{
	KEY(name) : STRING("Kevin Malone"),
	KEY(id) : NUMBER(4444),
	KEY(grades) : ARRAY[
	OBJECT { KEY(hy100) : NUMBER(9.5) },
	OBJECT { KEY(hy150) : NUMBER(9) }
	]
	} 
+ 
	OBJECT{
	KEY(name2) : STRING("Kevin Malone"),
	KEY(id3) : NUMBER(4444),
	KEY(grades2) : ARRAY[
	OBJECT { KEY(hy100) : NUMBER(9.5) },
	OBJECT { KEY(hy150) : NUMBER(9) }
	]
	}

		PRINT asd + asd2

		; std::cout << "telos\n\n";

PRINT students
PRINT students[0]["grades"][1]["hy150"]
PRINT students[0]["grades"][1]
PRINT students[0]["grades"]
PRINT students[0]

PRINT "telos\n"

JSON(numx1) = NUMBER(students[0]["grades"][1]["hy150"])
JSON(numx2) = OBJECT(students[0]["grades"][1])
JSON(numx3) = ARRAY[ARRAY[ARRAY[students[0]["grades"], ARRAY[ARRAY[students[0]["grades"]]]]], ARRAY[ARRAY[students[0]["grades"]]]]
JSON(numx4) = OBJECT(students[0])


PRINT numx1
PRINT numx2
PRINT numx3
PRINT numx4

//JSON(numx12) = NUMBER(students[0]["grades"][1]) // Error. Cannot construct Number

JSON(hy352_ang) = OBJECT{ KEY(exam) : NUMBER(7), KEY(project) : NUMBER(8) }

// Definition of JSON object using operators +, *
JSON(class_students) = ARRAY[
	OBJECT{
   KEY(name) : STRING("Angela ") + STRING("Martin"),
   KEY(id) : NUMBER(4444),
   KEY(grades) : ARRAY[
	OBJECT {
   KEY(hy352) :
   hy352_ang["exam"] * NUMBER(0.75) + hy352_ang["project"] * NUMBER(0.25)
   }
	]
	}
]

PRINT "Hello from const* char!\n" // Printing a string (const char*)
PRINT hy352_ang // Print Object
PRINT class_students // Print Array

PRINT ARRAY[ARRAY[ARRAY, ARRAY]] // Array of Array of two empty Arrays
;

//JSON(ol) = ARRAY[ARRAY[ARRAY, ARRAY]]
//
//PRINT "\n\n\n"
//
//PRINT ol
//
PRINT "\n\n\n"
//
//ERASE ol[0][1]
//PRINT "\n\n\n"
//PRINT ol

//PRINT students
//
//ERASE students
//
//PRINT students


JSON(a1) = ARRAY[NUMBER(11), NUMBER(12), NUMBER(13), NUMBER(14), NUMBER(15)] + ARRAY[NUMBER(11), NUMBER(12), NUMBER(13), NUMBER(14), NUMBER(15)]

PRINT a1

ERASE a1[1]

PRINT a1


PRINT "\n\n\n"

JSON(class_students111) = ARRAY[
	OBJECT{
   KEY(name) : STRING("Angela ") + STRING("Martin"),
   KEY(id) : NUMBER(4444),
   KEY(grades) : ARRAY[
	OBJECT {
   KEY(hy352) :
   hy352_ang["exam"] * NUMBER(0.75) + hy352_ang["project"] * NUMBER(0.25)
   }
	]
	}
]

PRINT class_students111

ERASE class_students111[0]["grades"][0]

PRINT class_students111

PRINT "\n\n\n"

JSON(aoo) = ARRAY[OBJECT{ KEY(name) : STRING("Angela ") + STRING("Martin") },
NUMBER(100),
STRING("ste!!"),
TRUE,
FALSE,
NULL,
ARRAY[STRING("ARRAYINSIDE")]

]
PRINT aoo

PRINT "\n\n"
ERASE aoo[6]
ERASE aoo[1]


PRINT aoo

PRINT "\n\n"

PRINT aoo
ERASE aoo
PRINT aoo

PRINT asd2
ERASE asd2
PRINT asd2

JSON(aoo2) = ARRAY[OBJECT{ KEY(name) : STRING("Angela ") + STRING("Martin") },
NUMBER(100),
STRING("ste!!"),
TRUE,
FALSE,
NULL,
ARRAY[STRING("ARRAYINSIDE")]

]
PRINT aoo2
ERASE aoo2[0]["name"]
PRINT aoo

JSON(xx) = ARRAY[OBJECT{ KEY(key1) : STRING("val"), KEY(key2) : STRING("val"), KEY(key3) : STRING("val"), KEY(key4) : STRING("val") }]

ERASE xx[0]["key1"]

PRINT xx

;

//currentlyAppending = (Value*)&week_temperatures; NUMBER(99), NUMBER(88), NUMBER(55)
//&week_temperatures , NUMBER(99), NUMBER(88), NUMBER(55)


JSON(week_temperatures1) = ARRAY[
	NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
		NUMBER(19), NUMBER(18.5), NUMBER(19)
]

// SET - APPEND COMMAND
PRINT week_temperatures1;

SET week_temperatures1 APPEND NUMBER(99), NUMBER(88), NUMBER(55)

PRINT week_temperatures1

ERASE week_temperatures1[0]
ERASE week_temperatures1[0]
ERASE week_temperatures1[0]
ERASE week_temperatures1[5]

PRINT week_temperatures1

//SET - ASSIGN COMMAND


//PRINT students
//
SET students[0]["grades"][1]["hy150"] ASSIGN STRING("csd404@csd.uoc.gr")

PRINT students

JSON(tt1) = NUMBER(10)

SET tt1 ASSIGN NUMBER(190)

PRINT tt1

JSON(st) = ARRAY[STRING("enaa")]

SET st[0] ASSIGN STRING("komple")

PRINT st

JSON(neo) = OBJECT{KEY(k1) : STRING("k111"), KEY(k2) : STRING("k222") }

SET neo["k1"] ASSIGN STRING("poutaniaaa?")

PRINT neo

JSON(neo2) = ARRAY[ STRING("444as"), STRING("asdsad"), STRING("k2342422"), STRING("asdasdnn") ]

PRINT neo2

SET neo2[1] ASSIGN OBJECT{ KEY(k1) : STRING("k111"), KEY(k2) : STRING("k222") }

ERASE neo2[1]
PRINT neo2

JSON(momo) = OBJECT{}

SET momo ASSIGN OBJECT{ KEY(a) : STRING("alpha") }

PRINT momo

JSON(ar) = STRING("11st")

SET ar ASSIGN STRING("lo")

PRINT ar


JSON(qwe) = ARRAY[
	NUMBER(20), NUMBER(19.5), NUMBER(19), NUMBER(20),
		NUMBER(19), NUMBER(18.5), NUMBER(19)
]

PRINT qwe + qwe

PRINT qwe 

ERASE qwe[5]

PRINT qwe


JSON(cl) = ARRAY[STRING("thesi1"), ARRAY[ARRAY[STRING("akomapiomesa"), FALSE], NUMBER(66), STRING("eswteriko")], TRUE, NULL]


JSON(cl2)= CloneArray(cl)

//ERASE cl2[2]

PRINT cl

PRINT cl2

PRINT "\n\n\n"


JSON(ki) = OBJECT{
	KEY(name) : STRING("Kevin Malone"),
	KEY(id) : NUMBER(4444),
	KEY(grades) : ARRAY[
	OBJECT { KEY(hy100) : NUMBER(9.5) },
	OBJECT { KEY(hy150) : NUMBER(9) }
	]
	}

JSON(ki2) = CloneObject(ki)

ERASE ki["grades"][0]["hy100"]

PRINT ki
PRINT ki2

PRINT "\n\n\n"




PROGRAM_END

/* TODO: 1) operator+ on arrays & objects with _parentContainer problem
*		 2) new approach with Value& instead of auto (?)
* 
*/