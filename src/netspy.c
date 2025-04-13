#include <stdio.h>
#include "netspy.h"

void print_net_table(const char *title, const char *path) {
    printf("\n📡 %s Connections:\n", title);
    printf("--------------------------------------\n");

    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("Error reading network file");
        return;
    }

    char line[512];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (count++ == 0) continue;
        char local[64], remote[64];
        int dummy;
        unsigned int local_ip, local_port, remote_ip, remote_port;
        sscanf(line, "%d: %X:%X %X:%X", &dummy, &local_ip, &local_port, &remote_ip, &remote_port);

        sprintf(local, "%d.%d.%d.%d:%d",
                (local_ip & 0xFF), (local_ip >> 8) & 0xFF,
                (local_ip >> 16) & 0xFF, (local_ip >> 24) & 0xFF,
                local_port);

        sprintf(remote, "%d.%d.%d.%d:%d",
                (remote_ip & 0xFF), (remote_ip >> 8) & 0xFF,
                (remote_ip >> 16) & 0xFF, (remote_ip >> 24) & 0xFF,
                remote_port);

        printf("Local: %s\tRemote: %s\n", local, remote);
    }

    fclose(fp);
}

void run_netspy() {
    print_net_table("TCP", "/proc/net/tcp");
    print_net_table("UDP", "/proc/net/udp");
}
