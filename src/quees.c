#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<ceval/ceval.h>

#define VERSION "quees-v0.0.1"
int silent = 0;
void startup_msg(void) {
    printf(
        "------------------------------\n"
        "       %s", VERSION
        "\n------------------------------\n"
    );
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
        char * expr = readline(">> ");
	if(expr && *expr)
		add_history(expr);
	if(!strcmp(expr, "history")) {
		for(int i = 0; i < history_get_history_state()->length; i++)
			printf("    %d %s\n", i+history_base, history_list()[i]->line);
		goto interpreter_loop;
	}
        if(!strcmp(expr, "exit")) {
            exit(0);
        } else if (!strcmp(expr, "clear")) {
            system("clear");
            goto interpreter_loop;
        }
        printf("%f\n", ceval_result(expr));
        goto interpreter_loop; 
    }
}

int main(int argc, char ** argv) {
    if(argc == 1) {
        launch_interpreter();
    } else if(argc == 2 && 
              option("-s", "--silent", argv[1])) {
        silent = 1;
        launch_interpreter();
    }
    for(int i = 1; i < argc; i++) {
        char * arg = argv[i];
        if(option("-h", "--help", arg)) {
            usage();
        }
        if(option("-v", "--version", arg)) {
            printf(
            "%s", VERSION
            "\nLicense: GPL-v3\n"
            "This is free software: you are free to change and redistribute it.\n"
            "There is ABSOLUTELY NO WARRANTY.\n"
            "\n"
            "Developed by e_t <https://github.com/erstan>\n"
            );
            continue;
        }
        printf("%s = %f\n", arg, ceval_result(arg));
    }
}
