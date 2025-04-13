#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <limits.h>
#include <string.h>
#include "fswatch.h"

void run_fswatch(const char *path) {
    int fd = inotify_init1(IN_NONBLOCK);
    if (fd < 0) {
        perror("inotify_init");
        return;
    }

    int wd = inotify_add_watch(fd, path, IN_CREATE | IN_DELETE | IN_MODIFY);
    if (wd < 0) {
        perror("inotify_add_watch");
        close(fd);
        return;
    }

    printf("👁️  Watching '%s' for changes...\nPress Ctrl+C to stop.\n", path);

    char buffer[4096] __attribute__((aligned(__alignof__(struct inotify_event))));
    ssize_t len, i = 0;

    while (1) {
        len = read(fd, buffer, sizeof(buffer));
        if (len <= 0) continue;

        i = 0;
        while (i < len) {
            struct inotify_event *event = (struct inotify_event *) &buffer[i];

            if (event->len) {
                printf("📁 %s: ", event->name);
                if (event->mask & IN_CREATE)
                    printf("created");
                else if (event->mask & IN_DELETE)
                    printf("deleted");
                else if (event->mask & IN_MODIFY)
                    printf("modified");
                printf("\n");
            }
            i += sizeof(struct inotify_event) + event->len;
        }
    }

    inotify_rm_watch(fd, wd);
    close(fd);
}
