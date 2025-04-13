// pmap.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pmap.h"

void run_pmap(int pid) {
    char filename[256];
    FILE *file;
    char line[512];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    printf("%-20s %-10s %-8s %-8s %-10s %-20s\n", "Address", "Perms", "Offset", "Device", "Inode", "Path");

    while (fgets(line, sizeof(line), file)) {
        unsigned long addr_start, addr_end, offset;
        char perms[5], device[6], path[256];
        int inode;
        if (sscanf(line, "%lx-%lx %4s %lx %5s %d %s", &addr_start, &addr_end, perms, &offset, device, &inode, path) < 7) {
            continue;
        }

        if (strcmp(path, "") == 0) {
            strcpy(path, "[Anonymous]");
        }

        printf("%-20lx %-10s %-8lx %-8s %-10d %-20s\n", addr_start, perms, offset, device, inode, path);
    }

    fclose(file);
}
