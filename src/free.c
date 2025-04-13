#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void format_size(long kbytes, char *out) {
    if (kbytes >= 1024 * 1024) {
        sprintf(out, "%.1fG", kbytes / (1024.0 * 1024.0));
    } else if (kbytes >= 1024) {
        sprintf(out, "%.1fM", kbytes / 1024.0);
    } else {
        sprintf(out, "%ldK", kbytes);
    }
}

void run_free() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/meminfo");
        return;
    }

    long mem_total = 0, mem_free = 0, buffers = 0, cached = 0;
    long swap_total = 0, swap_free = 0;

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "MemTotal: %ld kB", &mem_total)) continue;
        if (sscanf(line, "MemFree: %ld kB", &mem_free)) continue;
        if (sscanf(line, "Buffers: %ld kB", &buffers)) continue;
        if (sscanf(line, "Cached: %ld kB", &cached)) continue;
        if (sscanf(line, "SwapTotal: %ld kB", &swap_total)) continue;
        if (sscanf(line, "SwapFree: %ld kB", &swap_free)) continue;
    }
    fclose(fp);

    long used = mem_total - mem_free - buffers - cached;
    long swap_used = swap_total - swap_free;
    long buff_cache = buffers + cached;

    char t[10], u[10], f[10], b[10], st[10], su[10], sf[10];

    format_size(mem_total, t);
    format_size(used, u);
    format_size(mem_free, f);
    format_size(buff_cache, b);
    format_size(swap_total, st);
    format_size(swap_used, su);
    format_size(swap_free, sf);

    printf("              total        used        free     buff/cache\n");
    printf("Mem:     %10s %10s %10s %10s\n", t, u, f, b);
    printf("Swap:    %10s %10s %10s\n", st, su, sf);
}
