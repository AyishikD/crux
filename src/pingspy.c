#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void run_pingspy(char *host) {
    char command[256];
    sprintf(command, "ping -c 4 %s", host);  
    
    while (1) {
        system("clear");
        printf("\n🌐 Ping Latency Monitor\n");
        printf("------------------------\n");

        printf("Pinging %s...\n", host);
        system(command);

        sleep(5);  
    }
}
