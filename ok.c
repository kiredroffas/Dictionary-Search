/* Erik Safford
 * Searching Dictionary for a Specified Word
 * Spring 2019 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#define FILENAME "/home/erik/Desktop/Dictionary-Search/webster" //File for SIZE dictionary
#define SIZE 16 //number of bytes per word line entry of the dictionary file (including null term/newline)
#define DEBUG 0 //Debug print statements, 0 = OFF, 1 = ON

//Check if the word we want is in the dictionary
int check(int fd,char *want) {
	char have[SIZE]; //Buffer to hold a word entry line from the dictionary
        int bot = 0;
        int top = 0; //Keep track of bot,top,mid for Binary Search
        int mid;

	//Determine how many lines there are in the file (# word entries)
	if(fd < 0) {  //Exit if couldnt open the dictionary
        	fprintf(stderr,"err=%d: %s\n",errno,strerror(errno));
                exit(1);
        }
	int bytes = lseek(fd,0,SEEK_END); //Find total bytes in file
	if(bytes <= 0) { //If bytes can't be read from file for some reason
		fprintf(stderr,"No bytes can be read from file.\n");
                exit(1);
	}
	top = bytes / SIZE;  //Divide by SIZE to find # of lines (top)
	if(bytes % SIZE != 0) { //If total bytes didnt divide evenly by SIZE
		fprintf(stderr,"Words in file incorrectly formatted.\n");
                exit(1);
	}
	int closed = close(fd);
        if(closed != 0) { //If file did not close properly
                fprintf(stderr,"err=%d: %s\n",errno,strerror(errno));
                exit(1);
        }

	if(DEBUG == 1) {printf("word wanted=\"%s\"\n",want);}

	while(7 == 7) {  //Infinite loop, Uses binary search to search for matching word
		         //Returns 0 if word can't be found, 1 if word found
		if(DEBUG == 1) {printf("search range: bottom=%d, top=%d\n",bot,top);}

		int fd2 = open(FILENAME,O_RDONLY);
		if(fd2 < 0) {  //Exit if cant open the dictionary
                	fprintf(stderr,"err=%d: %s\n",errno,strerror(errno));
                	exit(1);
        	}

		if(bot >= top) {    //If we've searched through the whole dictionary and cant find the word
			return(0);  //Return word not found in dictionary
		}
		mid = (bot + top) / 2;         //Find middle line of current search
		int bitShift = mid * SIZE;     //Each line is SIZE bytes
		int seeked = lseek(fd2,bitShift,SEEK_SET);  //Go to the middle line
		if(seeked == -1) { //If error offsetting in file
			fprintf(stderr,"err=%d: %s\n",errno,strerror(errno));
                        exit(1);
		}
		int bytesRead = read(fd2,have,SIZE-1); //Read the word from that line
		if(bytesRead < 0) { //If we can't read from file for some reason
			fprintf(stderr,"err=%d: %s\n",errno,strerror(errno));
                        exit(1);
		}
		if(DEBUG == 1) {printf("middle=%d, word have=\"%s\"\n",mid,have);}

		int match = strcmp(have,want); //Compare word read with word we want
		if(match == 0) { //If words match, return word found in dictionary
			if(DEBUG == 1) {printf("test: want = have\n");}
			return(1); //We have a match!		
		}
		else if(match < 0) { //If word we want is closer to end of dictionary
			bot = mid + 1; //Binary search
			if(DEBUG == 1) {printf("test: want > have\n\n");}
		}
		else if(match > 0) { //If word we want is closer to beginning of dictionary
			top = mid;  //Binary search
			if(DEBUG == 1) {printf("test: want < have\n\n");}
		}
		closed = close(fd2);
		if(closed != 0) { //If file did not close properly
                	fprintf(stderr,"err=%d: %s\n",errno,strerror(errno));
                	exit(1);
        	}
	}
}

int main(int argc,char **argv) {
	if(argc != 2) { //Exit if command line isnt correct
		fprintf (stderr,"Invalid number of command line args\n"); 
		//No errno for invalid argc
		exit(1);
	}

	char *word = argv[1]; //Set word = argv[1]
	int i = strlen(word); //Set i to the length of the word to be searched	

	for(int j = 0;j < i;j++) { //Remove any capital letters from word if any
		word[j] = tolower(word[j]);
	}

	if(i >= SIZE-1) {  //Truncate entered word to SIZE-1 characters if necessary
		word[SIZE-1] = '\0'; 
	}
	else {             //Otherwise add spaces and null term to make word match length of dictionary
		for(i;i < SIZE-1;i++) {
			word[i] = ' ';
		}
		word[i] = '\0';
	}

	int fd;
	fd = open(FILENAME,O_RDONLY);  //Set fd by opening dictionary FILENAME
	if(fd < 0) {  //Exit if cant open the dictionary
		fprintf (stderr,"err=%d: %s\n",errno,strerror(errno));
		exit(1);
	}
	
	int inDict = check(fd,word); //Check if the word is in the dictionary

	if(inDict == 1) {
		write(1,"yes\n",4);
	}
	else {
		write(1,"no\n",3);
	}

	return(0);
}

