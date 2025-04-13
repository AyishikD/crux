#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "cmdspy.h"

void run_cmdspy() {
    DIR *dir = opendir("/proc");
    if (!dir) {
        perror("Error opening /proc");
        return;
    }

    printf("\n🖥️  Running Commands\n");
    printf("-----------------------------\n");

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char *endptr;
            long pid = strtol(entry->d_name, &endptr, 10);
            if (*endptr == '\0' && pid > 0) {
                char cmd_path[256];
                snprintf(cmd_path, sizeof(cmd_path), "/proc/%ld/comm", pid);

                FILE *fp = fopen(cmd_path, "r");
                if (fp) {
                    char cmd[256];
                    if (fgets(cmd, sizeof(cmd), fp)) {
                        printf("PID: %ld  |  Command: %s", pid, cmd);
                    }
                    fclose(fp);
                }
            }
        }
    }

    closedir(dir);
}
