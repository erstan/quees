#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ceval/ceval.h>
#define VERSION "quees-v0.0.1"
int silent = 0;
void startup_msg(void) {
    printf(
        "------------------------------\n"
        VERSION
        "\n------------------------------\n"
    );
}
void config_info(void) {
    printf("---------quees macro values----------\n");
    printf("CEVAL_MAX_DIGITS : %d\n", (int)CEVAL_MAX_DIGITS);
    printf("CEVAL_EPSILON : %f\n", (double)CEVAL_EPSILON);
    printf("CEVAL_DELTA : %f\n", (double)CEVAL_DELTA);
    printf("CEVAL_STOICAL : ");
    #ifdef CEVAL_STOICAL 
        printf("defined\n");
    #else 
        printf("not defined\n");
    #endif
    printf("-------------------------------------\n");
    printf("These macros can be modified/defined before the ceval include directive\n");
    exit(0);
}
void version_info(void) {
    printf(
    "%s", VERSION
    "\nLicense: GPL-v3\n"
    "This is free software: you are free to change and redistribute it.\n"
    "There is ABSOLUTELY NO WARRANTY.\n"
    "\n"
    "Developed by e_t <https://github.com/erstan>\n"
    );
    exit(0);
}
void usage(void) {
    printf(
        "\n"
        " Usage: \n"
        "        quees [OPTION]... (interactive mode)\n"
        "        quees EXPRESSION... (non-interactive mode)\n"
        "\n"
        " Options:\n"
        "\n"
        "     -s, --silent       no startup messages\n"
        "     -v, --version      quees version information\n"
        "     -h, --help         quees help information\n"
	"     -c, --config       quees config information\n"
        "\n"
    );
    exit(0);
}

int option(char * small, char * large, char * arg) {
    if(!strcmp(small, arg) ||
       !strcmp(large, arg)) return 1;
return 0;
}

void launch_interpreter(void) {
    if(!silent) {
        startup_msg();
    }
    interpreter_loop: {
        char expr[100];
        printf(">> ");
        fgets(expr, 100, stdin);
        if(!strcmp(expr, "exit\n")) {
            exit(0);
        } else if (!strcmp(expr, "clear\n")) {
            system("clear");
            goto interpreter_loop; 
	}
	printf("%f\n", ceval_result(expr));
        goto interpreter_loop; 
    }
}

int main(int argc, char ** argv) {
    if(argc == 1) {
	// no arguments have been passed
        launch_interpreter();
    } else if(argc == 2) {
	// one of the allowed arguments (-s, -c, -h, -v)
	if(option("-s", "--silent", argv[1])) {
	    silent = 1;
	    launch_interpreter();
	} else if(option("-c", "--config", argv[1])) {
	    config_info();
	} else if(option("-h", "--help", argv[1])) {
	    usage();
	} else if(option("-v", "--version", argv[1])) {
	    version_info();
	} else {
		// might be a single expression passed as an argument to quees
		printf("%s = %f\n", argv[1], ceval_result(argv[1]));
	}
    } else {
        for(int i = 1; i < argc; i++) {
	    // successive evaluation of series of expressions
	    // passed as arguments to quees
            char * arg = argv[i];
            printf("%s = %f\n", arg, ceval_result(arg));
        }
    }
}
