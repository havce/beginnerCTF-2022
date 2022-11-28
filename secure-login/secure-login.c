#include "stdlib.h"
#include <stdio.h>
#include <string.h>

const char *banner = "                                 _             _       \n                                | |           (_)      \n ___  ___  ___ _   _ _ __ ___   | | ___   __ _ _ _ __  \n/ __|/ _ \\/ __| | | | '__/ _ \\  | |/ _ \\ / _` | | '_ \\ \n\\__ \\  __/ (__| |_| | | |  __/  | | (_) | (_| | | | | |\n|___/\\___|\\___|\\__,_|_|  \\___|  |_|\\___/ \\__, |_|_| |_|\n                                          __/ |        \n                                         |___/         \n";

int main (int argc, char *argv[])
{
    char username[32], password[32];
    puts(banner);
    printf("Insert your username: ");
    scanf("%31s", username);

    printf("Insert your password: ");
    scanf("%31s", password);

    if (!strncmp(password, "havceCTF{m4yb3_n0t_s0_s3cur3}", 26)) {
        printf("Well done! Nothing more here. Bye :)\n");
    } else {
        printf("\nNot this time, try again :c\n");
    }

    return 0;
}
