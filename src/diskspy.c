#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_disk_usage() {
    system("df -h");
}

void print_disk_io() {
    FILE *fp = fopen("/proc/diskstats", "r");
    if (!fp) {
        perror("Error opening /proc/diskstats");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("Disk I/O: %s", buffer);
    }

    fclose(fp);
}

void run_diskspy() {
    while (1) {
        system("clear");
        printf("\n💾 Disk Usage and I/O Monitor\n");
        printf("----------------------------\n");

        print_disk_usage();
        print_disk_io();

        sleep(3);  
    }
}
