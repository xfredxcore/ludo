#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

#define VERSION "1.0.0"
#define BOLD "\033[1m"
#define RESET "\033[0m"

const char *chance_path() {
    static char path[512];
    const char *home = getenv("HOME");
    if (!home) home = ".";
    snprintf(path, sizeof(path), "%s/.ludo_chance", home);
    return path;
}

int load_chance() {
    FILE *f = fopen(chance_path(), "r");
    int c = 50;
    if (f) {
        fscanf(f, "%d", &c);
        fclose(f);
    }
    if (c < 0) c = 0;
    if (c > 100) c = 100;
    return c;
}

void save_chance(int c) {
    FILE *f = fopen(chance_path(), "w");
    if (f) {
        fprintf(f, "%d", c);
        fclose(f);
    }
}

void show_version() {
    printf("%sludo%s version %s\n", BOLD, RESET, VERSION);
    printf("License: GPL v3\n");
    printf("by xfredxcore\n");
}

void show_chance() {
    printf("Current chance: %d%%\n", load_chance());
}

void show_help() {
    printf("ludo - a lightweight CLI tool for chance based operations\n\n");
    printf("Usage:\n");
    printf("  ludo [option]\n");
    printf("  ludo [command] [args...]\n\n");
    printf("Options:\n");
    printf("  -v   Show version information and license\n");
    printf("  -c   Show the current chance value\n");
    printf("  -h   Show this help message\n\n");
    printf("Commands:\n");
    printf("  roll            Roll based on current chance\n");
    printf("  set <n>         Set chance to n (0-100)\n");
    printf("  <cmd> [args]    Run external command with chance\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        show_help();
        return 0;
    }
    if (strcmp(argv[1], "-v") == 0) {
        show_version();
        return 0;
    }
    if (strcmp(argv[1], "-c") == 0) {
        show_chance();
        return 0;
    }
    if (strcmp(argv[1], "-h") == 0) {
        show_help();
        return 0;
    }
    if (strcmp(argv[1], "set") == 0 && argc >= 3) {
        int n = atoi(argv[2]);
        if (n < 0) n = 0;
        if (n > 100) n = 100;
        save_chance(n);
        printf("Chance set to %d%%\n", n);
        return 0;
    }
    if (strcmp(argv[1], "roll") == 0) {
        int chance = load_chance();
        srand((unsigned)time(NULL) ^ (unsigned)getpid());
        int r = rand() % 100;
        printf("Rolled %d (chance %d%%) -> %s\n", r, chance, r < chance ? "success" : "fail");
        return r < chance ? 0 : 1;
    }
    /* external command mode */
    int chance = load_chance();
    const char *spin = "-\\|/";
    for (int i = 0; i < 40; i++) {
        printf("\r %c ", spin[i % 4]);
        fflush(stdout);
        usleep(50000);
    }
    srand((unsigned)time(NULL) ^ (unsigned)getpid());
    int r = rand() % 100;
    if (r >= chance) {
        printf("\ryou suck :-)\n");
        return 1;
    }
    printf("\rsuccess ! ! !\n");
    fflush(stdout);
    execvp(argv[1], &argv[1]);
    perror("execvp");
    return 127;
}
