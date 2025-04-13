#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "procpeek.h"

void run_procpeek(const char *pid_str) {
    char path[256], line[256];
    FILE *fp;

    printf("\n🔍 Process Info for PID: %s\n", pid_str);
    printf("----------------------------------\n");

    snprintf(path, sizeof(path), "/proc/%s/status", pid_str);
    fp = fopen(path, "r");
    if (!fp) {
        perror("Error opening status");
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Name:", 5) == 0 ||
            strncmp(line, "State:", 6) == 0 ||
            strncmp(line, "Threads:", 8) == 0 ||
            strncmp(line, "VmSize:", 7) == 0 ||
            strncmp(line, "VmRSS:", 6) == 0) {
            printf("%s", line);
        }
    }
    fclose(fp);

    snprintf(path, sizeof(path), "/proc/%s/exe", pid_str);
    char exe_path[256];
    ssize_t len = readlink(path, exe_path, sizeof(exe_path) - 1);
    if (len != -1) {
        exe_path[len] = '\0';
        printf("Executable: %s\n", exe_path);
    } else {
        perror("Error reading exe path");
    }

    snprintf(path, sizeof(path), "/proc/%s/fd", pid_str);
    DIR *dir = opendir(path);
    int count = 0;
    if (dir) {
        while (readdir(dir)) count++;
        closedir(dir);
        printf("Open File Descriptors: %d\n", count - 2);
    } else {
        perror("Error opening fd directory");
    }
}
