#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_cpu_temperature() {
    FILE *fp = popen("sensors | grep 'Core 0' | awk '{print $3}'", "r");
    if (!fp) {
        printf("🌡️ CPU Temperature: Not available on this system\n");
        return;
    }

    char temp[16];
    fgets(temp, sizeof(temp), fp);
    pclose(fp);  

    printf("🌡️ CPU Temperature: %s", temp);
}

void print_cpu_load() {
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

    printf("💻 CPU Load: %.2f%%\n", (double)used / total * 100);
}

void run_cpuheat() {
    while (1) {
        system("clear");
        printf("\n🔥 CPU Heat Monitor\n");
        printf("--------------------\n");

        print_cpu_temperature();
        print_cpu_load();

        sleep(2); 
    }
}
