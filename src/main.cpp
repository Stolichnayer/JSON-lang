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


PROGRAM_END

