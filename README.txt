  This C program is targeted at the Linux platform and through the use of a 
  Binary Seach checks whether a specified word, passed as an argument to the
  executable, exists in the dictionary or not. The specified test dictionary 
  is a text file "webster", however this can be replaced in the #define FILENAME
  (dictionary location) and #define SIZE (word length of dictionary) of ok.c by
  any text dictionary, provided:  
              -Format is 1 word per line, all lowercase
              -Lines are in ascending sorted order (i.e. A-Z)
              -Each line is SIZE characters/bytes long (i.e. if SIZE is 16, max
               word length in dictionary is 15, byte 16 is null term/newline)
   
  Example dictionary "tiny" of SIZE 16:

  line  offset  0  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15
   0      0     a  a  r  d  v  a  r  k                            \0
   1      16    b  e  a  r                                        \0
   2      32    c  a  t                                           \0
   3      48    d  o  g                                           \0
   4      64    e  l  e  p  h  a  n  t                            \0
   5      80    f  i  s  h                                        \0
   6      96    g  u  p  p  i  e                                  \0
   7      112   h  o  r  s  e                                     \0

  This program only uses i\o methods such as lseek, read, write, open, and close
  to interface with the file, however it also utilizes printf for debugging, 
  fprintf for error checking, tolower for command line input string manipulation,
  and strcmp for string comparison.
   
  A makefile is included with the following commands:
    -all   : compiles everything together and produces an executable
    -clean : removes all object and temporary files
    -run   : command for running executable with specified word,
             i.e. make run word="they're"  (search dictionary for they're),
             double quotes around the word string ensure symbols like ' are read

             ** can also be ran via command line with ./ok "they're", **
             ** if no ' in word, then can be ran with just ./ok they  **  

  Any entered word to be searched is truncated to SIZE - 1 characters (SIZE 16
  dictionary can hold up to 15 letter word with null term at end).

  Any errors that occur cause the program to print an appropriate error message
  containing the errno and the message produced by that error (unless its
  behavior that is not defined by an errno, then custom error message printed).

  In ok.c, debug printf statements are printed if #define DEBUG = 1,
  #define DEBUG = 0 will only output a yes/no if word is found/not found.
