#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <limits.h>
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif


int is_numeric(const char *str) {
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

void run_pgrep(const char *target_name) {
    DIR *proc = opendir("/proc");
    if (!proc) {
        perror("Failed to open /proc");
        return;
    }

    struct dirent *entry;
    char path[PATH_MAX]; 

    while ((entry = readdir(proc)) != NULL) {
        if (!is_numeric(entry->d_name)) continue;
        int written = snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);
        if (written < 0 || written >= sizeof(path)) continue;

        FILE *fp = fopen(path, "r");
        if (fp) {
            char name[256];
            if (fgets(name, sizeof(name), fp)) {
                name[strcspn(name, "\n")] = 0;
                if (strcmp(name, target_name) == 0) {
                    printf("%s\n", entry->d_name);
                }
            }
            fclose(fp);
        }
    }

    closedir(proc);
}
