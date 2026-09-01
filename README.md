Hash Table Password Server

This project creates a hash table data structure implimentation in the hashtable class, then uses it with a passserver class to create a password server. The hash table implimentation follows standard guidelines of a hash table,
and the passserver class is used to manage encrypted usernames and passwords using the hash table.

hashtable.h is the header file that contains definitions for the functions used in the implimentation of the hash table.

hashtable.hpp contains the implimentations for the functions used by the hash table data structure defined in the header file.

passserver.h is the header file that contains the definitions for the functons used by the passserver class to create the password server. 

passserver.hpp contains the implimentations of the functions used for the password server.

main.cpp includes a main method that produces the menu displayed for the user as they navigate the password server.

xmain.cpp is a more advanced version of main.cpp which hides the users input for the password as it is input. This provides a more secure menu for the password server implimentation.

makefile creates two different executable files called main.x and xmain.x from using the make command. main.cpp and passserver.cpp are combined to create the main.x file. xmain.cpp and passserver.cpp are combined to create the xmain.x file.
these .x files can be run to use the password server.
