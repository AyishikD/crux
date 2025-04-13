#include <stdio.h>
#include <string.h>
#include "sysmon.h"
#include "procpeek.h"
#include "fswatch.h"
#include "netspy.h"
#include "cmdspy.h"
#include "uptimewatch.h"
#include "logspy.h"
#include "diskspy.h"
#include "pingspy.h"
#include "procstat.h"
#include "cpuheat.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./crux <command>\nAvailable commands: sysmon, procpeek <pid>\n");
        return 1;
    }

    if (strcmp(argv[1], "sysmon") == 0) {
        run_sysmon();
    } else if (strcmp(argv[1], "procpeek") == 0) {
        if (argc < 3) {
            printf("Usage: ./crux procpeek <pid>\n");
            return 1;
        }
        run_procpeek(argv[2]);
    }
     else if (strcmp(argv[1], "fswatch") == 0) {
    if (argc < 3) {
        printf("Usage: ./crux fswatch <directory>\n");
        return 1;
    }
        run_fswatch(argv[2]);
    } else if (strcmp(argv[1], "netspy") == 0) {
        run_netspy();
    }
    else if (strcmp(argv[1], "cmdspy") == 0) {
        run_cmdspy();
    }
    else if (strcmp(argv[1], "uptimewatch") == 0) {
        run_uptimewatch();
    }
    else if (strcmp(argv[1], "logspy") == 0) {
        run_logspy();
    }
    else if (strcmp(argv[1], "procstat") == 0) {
        run_procstat();
    } else if (strcmp(argv[1], "cpuheat") == 0) {
        run_cpuheat();
    }
    else if (strcmp(argv[1], "diskspy") == 0) {
        run_diskspy();
    } else if (strcmp(argv[1], "pingspy") == 0) {
        if (argc < 3) {
            printf("Usage: %s pingspy <host>\n", argv[0]);
            return 1;
        }
        run_pingspy(argv[2]);
    }
    else {
        printf("Unknown command: %s\n", argv[1]);
    }

    return 0;
}