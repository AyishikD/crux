#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/sysinfo.h>
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"


void print_uptime() {
    FILE *fp = fopen("/proc/uptime", "r");
    if (!fp) {
        perror(RED"Error opening /proc/uptime");
        return;
    }

    float uptime;
    fscanf(fp, "%f", &uptime);
    fclose(fp);

    printf(GREEN"⏳ System Uptime: %.2f seconds\n", uptime);
}

void print_cpu_usage() {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("Error opening /proc/stat");
        return;
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);

    long user, nice, system, idle;
    sscanf(buffer, "cpu %ld %ld %ld %ld", &user, &nice, &system, &idle);

    long total = user + nice + system + idle;
    long used = total - idle;

    printf("💻 CPU Usage: %.2f%%\n", (double)used / total * 100);
}

void print_memory_usage() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        perror("Error opening /proc/meminfo");
        return;
    }

    char buffer[256];
    long total_mem = 0, avail_mem = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (sscanf(buffer, "MemTotal: %ld kB", &total_mem) == 1)
            continue;
        if (sscanf(buffer, "MemAvailable: %ld kB", &avail_mem) == 1)
            break;
    }

    fclose(fp);

    long used_mem = total_mem - avail_mem;
    double usage = (double)used_mem / total_mem * 100.0;

    printf(CYAN"🧠 Memory Usage: %.2f%%\n", usage);
    printf("🔢 Total RAM: %ld kB\n", total_mem);
    printf("🧮 Available RAM: %ld kB\n", avail_mem);
}

void run_uptimewatch() {
    while (1) {
        system("clear"); 
        printf(GREEN"\n📊 Uptimewatch - System Performance\n");
        printf("-----------------------------------\n");

        print_uptime();
        print_cpu_usage();
        print_memory_usage();

        sleep(2); 
    }
}
