#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

void print_proc_stats(const char *pid) {
    char path[256];
    sprintf(path, "/proc/%s/stat", pid);
    FILE *fp = fopen(path, "r");
    if (!fp) return;

    char buffer[256];
    long utime, stime, rss;
    fscanf(fp, "%s %*s %*s %*s %*s %*s %*s %*s %*s %*s %ld %ld %ld", buffer, &utime, &stime, &rss);
    fclose(fp);

    long total_time = utime + stime;
    long memory = rss * sysconf(_SC_PAGESIZE) / 1024;  

    printf("PID: %s | CPU Time: %ld | Memory: %ld kB\n", pid, total_time, memory);
}

void run_procstat() {
    DIR *dir = opendir("/proc");
    struct dirent *entry;
    if (!dir) {
        perror("Error opening /proc");
        return;
    }

    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_DIR && atoi(entry->d_name) > 0) {
            print_proc_stats(entry->d_name);
        }
    }

    closedir(dir);
}
