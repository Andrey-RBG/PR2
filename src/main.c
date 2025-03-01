#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "users.h"
#include "processes.h"
#include "logger.h"
#include "errors.h"

void print_help() {
    printf("Usage: console_tool [OPTIONS]\n");
    printf("Options:\n");
    printf("  -u, --users         Show list of users and their home directories\n");
    printf("  -p, --processes     Show list of running processes\n");
    printf("  -h, --help          Display this help message\n");
    printf("  -l PATH, --log PATH Redirect output to file\n");
    printf("  -e PATH, --errors PATH Redirect stderr to file\n");
}

int main(int argc, char *argv[]) {
    int opt;
    char *log_path = NULL;
    char *error_path = NULL;

    while ((opt = getopt(argc, argv, "uph:l:e:")) != -1) {
        switch (opt) {
            case 'u':
                list_users();
                break;
            case 'p':
                list_processes();
                break;
            case 'h':
                print_help();
                return 0;
            case 'l':
                log_path = optarg;
                if (redirect_stdout(log_path) != 0) {
                    fprintf(stderr, "Error: Cannot open log file %s\n", log_path);
                    return 1;
                }
                break;
            case 'e':
                error_path = optarg;
                if (redirect_stderr(error_path) != 0) {
                    fprintf(stderr, "Error: Cannot open error file %s\n", error_path);
                    return 1;
                }
                break;
            default:
                print_help();
                return 1;
        }
    }
    
    return 0;
}
