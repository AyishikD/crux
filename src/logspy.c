#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>
#include "logspy.h"

void run_logspy() {
    int fd = inotify_init1(IN_NONBLOCK);
    if (fd < 0) {
        perror("inotify_init");
        return;
    }

    int wd = inotify_add_watch(fd, "/var/log", IN_CREATE | IN_MODIFY | IN_DELETE);
    if (wd < 0) {
        perror("inotify_add_watch");
        close(fd);
        return;
    }

    printf("📖 Monitoring system logs in /var/log...\nPress Ctrl+C to stop.\n");

    char buffer[4096] __attribute__((aligned(__alignof__(struct inotify_event))));
    ssize_t len, i = 0;

    while (1) {
        len = read(fd, buffer, sizeof(buffer));
        if (len <= 0) continue;

        i = 0;
        while (i < len) {
            struct inotify_event *event = (struct inotify_event *) &buffer[i];

            if (event->len) {
                printf("Log File %s: ", event->name);
                if (event->mask & IN_CREATE)
                    printf("created");
                else if (event->mask & IN_MODIFY)
                    printf("modified");
                else if (event->mask & IN_DELETE)
                    printf("deleted");
                printf("\n");
            }
            i += sizeof(struct inotify_event) + event->len;
        }
    }

    inotify_rm_watch(fd, wd);
    close(fd);
}
