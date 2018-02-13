/*
 qwery - A horrible micro-utility for searching the web from the command line.
 Cass Smith
 February 2018
 Basically, concats all arguments into a single string, then execs an external
 program with that string as an argument. The external program in this case is
 w3m, a text-mode web browser.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char** argv) {
	//Make sure we have some arguments
	if (argc <= 1) {
		fprintf(stderr, "Too few arguments.\n");
		exit(-1);
	}

	//Define prefix and suffix for the master string
	char 	*urlStart 	= "https://start.duckduckgo.com/?q=";
	char 	*urlEnd		= "";

	//Copy prefix into master string
	char *stringToPass = strdup(urlStart);
	//strdup preforms a malloc. Check that the pointer we get is valid
	if (stringToPass == NULL) {
		fprintf(stderr, "Malloc failure!\n");
		exit(-1);
	}

	//Tack each argument onto the end of the master string
	for (int i = 1; i < argc; i++) {
		//This realloc thing is awful. Don't do this.
		stringToPass = realloc(stringToPass, strlen(stringToPass) + strlen(argv[i]) + ((i==1) ? 1 : 2));
		//Add a '+' to the front of every argument except the first
		if (i != 1) {
			strcat(stringToPass, "+");
		}
		//Perform the tack
		strcat(stringToPass, argv[i]);
	}
	//Append the suffix to the master string
	stringToPass = realloc(stringToPass, strlen(stringToPass)+strlen(urlEnd)+1);
	strcat(stringToPass, urlEnd);
	//printf("%s\n", stringToPass); //Debugging crap.
	//Invoke w3m
	execlp("w3m", "w3m", stringToPass, (char*) NULL);
	//I'm pretty sure execution never reaches here, but it's good form to
	//clean up after yourself nevertheless.
	free(stringToPass);
	exit(0);
}
