#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sysmon.h"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"


void run_sysmon() {
    FILE *fp;
    char buffer[1024];
    long total_mem = 0, free_mem = 0;
    long total_cpu1 = 0, idle_cpu1 = 0, total_cpu2 = 0, idle_cpu2 = 0;

    fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        perror("fopen");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strncmp(buffer, "MemTotal:", 9) == 0)
            sscanf(buffer + 9, "%ld", &total_mem);
        if (strncmp(buffer, "MemAvailable:", 13) == 0)
            sscanf(buffer + 13, "%ld", &free_mem);
    }
    fclose(fp);

    fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("fopen");
        return;
    }

    fgets(buffer, sizeof(buffer), fp); 
    long user, nice, system, idle;
    sscanf(buffer, "cpu %ld %ld %ld %ld", &user, &nice, &system, &idle);
    total_cpu1 = user + nice + system + idle;
    idle_cpu1 = idle;
    fclose(fp);
    sleep(1); 

    fp = fopen("/proc/stat", "r");
    fgets(buffer, sizeof(buffer), fp);
    long user1, nice1, system1, idle1;
    sscanf(buffer, "cpu %ld %ld %ld %ld", &user1, &nice1, &system1, &idle1);
    total_cpu2 = user1 + nice1 + system1 + idle1;
    idle_cpu2 = idle1;
    fclose(fp);

    long diff_total = total_cpu2 - total_cpu1;
    long diff_idle = idle_cpu2 - idle_cpu1;
    float cpu_usage = 100.0 * (1.0 - ((float)diff_idle / diff_total));
    float mem_usage = 100.0 * (1.0 - ((float)free_mem / total_mem));

    printf(CYAN"\n📊 System Monitor\n");
    printf("----------------------------\n");
    printf(RED"CPU Usage: %.2f%%\n", cpu_usage);
    printf(RED"RAM Usage: %.2f%%\n", mem_usage);
    printf(RED"Total RAM: %ld kB\n", total_mem);
    printf(RED"Available RAM: %ld kB\n", free_mem);
}
