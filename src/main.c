#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include "users.h"
#include "processes.h"
#include "logger.h"
#include "errors.h"
#include "help.h"

int main(int argc, char *argv[]) {
    int opt;
    char *log_path = NULL;
    char *error_path = NULL;

    bool users_flag = false;
    bool processes_flag = false;
    bool help_flag = false;

    // Определение длинных опций
    static struct option long_options[] = {
        {"users", no_argument, 0, 'u'},
        {"processes", no_argument, 0, 'p'},
        {"help", no_argument, 0, 'h'},
        {"log", required_argument, 0, 'l'},
        {"errors", required_argument, 0, 'e'},
        {0, 0, 0, 0}
    };

    int option_index = 0;

    while ((opt = getopt_long(argc, argv, "uph:l:e:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'u':
                users_flag = true;
                break;
            case 'p':
                processes_flag = true;
                break;
            case 'h':
                help_flag = true;
                break;
            case 'l':
                log_path = optarg;
                break;
            case 'e':
                error_path = optarg;
                break;
            default:
                print_help();
                return 1;
        }
    }

    if (log_path) {
        if (redirect_stdout(log_path) != 0) {
            fprintf(stderr, "Error: Cannot open log file %s\n", log_path);
            return 1;
        }
    }

    if (error_path) {
        if (redirect_stderr(error_path) != 0) {
            fprintf(stderr, "Error: Cannot open error file %s\n", error_path);
            return 1;
        }
    }

    if (help_flag) {
        print_help();
        return 0;
    }
    if (users_flag) {
        list_users();
    }
    if (processes_flag) {
        list_processes();
    }

    return 0;
}
