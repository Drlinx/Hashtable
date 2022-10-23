Kassidy Maberry
Class: cse122
2022/10/23
Assignment: Hash tables

    This Assignment is a working program of a hash table. It allows you to
Add or remove elements at will as well as import an entire files contents.

    Coding this was fairly straight forward. I ran into two bugs the first
was caused by me not assigning a value for finding the radix which caused 
the keys to be randomly assigned. The other is a bug that is caused by the file
format. If you have an empty line at the end it causes the program to enter an
infinte read loop with the last line. The assignment does have a limiation for 
the radix due to how it is calculated. Words with the firt 4 characters are
effectively the same keys.