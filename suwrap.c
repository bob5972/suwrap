// Copyright Michael Banack 2010

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "priv.h"
#include "env.h"

extern char **newenvp;
extern char **environ;
extern size_t newenvc;

void die(const char * str)
{
	fprintf(stderr, "suwrap: %s", str);
	if (errno != 0) {
		fprintf(stderr, ": (%d) %s\n", errno, strerror(errno));
	}
	fprintf(stderr, "\n");
	exit(1);
}

typedef struct passwd passwd;

/*
 * Remember kids:
 *   argv[0] = ./suwrap
 *   argv[1] = username
 *   argv[2] = command
 *   argv[3] = arg1
 *   argv[4] = arg2
 *    etc
 */

int main(int argc, char ** argv)
{	 
	const int USER_INDEX = 1;
	const int COMMAND_INDEX = 2;
	
	char *str;
	char *preserve[] = { "SHELL", "TERM", "COLORTERM",
	                    "DISPLAY", "XAUTHORITY", NULL };
	int x;
	
	uid_t uid;
	char **args;
	int status;
	passwd *p;
	int argsize;
	
	//sanitize_env();
	initenv();
	
	x=0;
	while(preserve[x] != NULL) {
		str = getenv(preserve[x]);
		if (str) {
			addenv(preserve[x], str);
		}
		x++;
	}
		
	if (USER_INDEX >= argc) {
		die("No user specified");
	}
	
	p = getpwnam(argv[USER_INDEX]);
	
	if (p == NULL) {
		die("No such user");
	}

	addenv("HOME", p->pw_dir);
	addenv("USER", p->pw_name);
	addenv("LOGNAME", p->pw_name);
	
	uid = p->pw_uid;
	
	if (drop_priv_perm(uid) != 0) {
		die("Unable to set user permissions");
	}
	
	if (COMMAND_INDEX >= argc) {
		die("No command specified");
	}
	
	argsize = argc-COMMAND_INDEX+1;
	args = malloc(argsize*sizeof(char*));
	
	for(int x=COMMAND_INDEX;x<argc;x++) {
		args[x-COMMAND_INDEX] = argv[x];
	}
		
	args[argsize-1] = NULL;
	
	//make new env active
	//environ = newenvp;
	
	status = execvpe(argv[COMMAND_INDEX], args, newenvp);
	
	if (status != 0) {
		die("Unable to run command");
	}
	
	//No one will ever see this...
	printf("\nDone!\n");
	return 0;
}
