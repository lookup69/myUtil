/*
 * The following license idents are currently accepted as indicating free
 * software 
 *
 *  "GPL"               [GNU Public License v2 or later]
 *
 *
 * @Author	Archer Chang
 * @file
 * date
 *
 */

#include "debugUtility.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


int debug_write_log(char *file, char *log)
{
    struct tm *t;
    time_t time_;
    char *line;
    FILE *fp;

    line = (char *) malloc(strlen(log) + 20);
    if(line){
        memset(line, 0, strlen(log) + 20);
    } else {
        return -1;
    }

    fp = fopen(file, "a+");
    if(!fp) {
        free(line);
        return -1;
    }
    time(&time_);
    t = gmtime(&time_);
    sprintf(line, "[%2d:%2d:%2d] %s\n", t->tm_hour, t->tm_min, t->tm_sec, log);
    fwrite(line, 1, strlen(line), fp);
    fflush(fp);
    fclose(fp);
    free(line);

    return 0;
}

void memory_dump(const unsigned char *mem, size_t size)
{
    size_t i, j;
    int padding;

    for(i = 0; i < size; i += 16 ) {
        printf("[0x%05X]: ", i);
        for(j = 0; (j < 16) && ((j + i) < size); ++j) {
            printf("%02X ", mem[j + i]);
        }
        padding = (j + i) % 16;
        if(padding == 0) 
            printf(": ");
        else {
            int k = 0;
            padding = 16 - padding;
            for(k = 0; k < padding; ++k) 
                printf("   ");
            printf(": ");
        }
        for(j = 0; (j < 16) && ((j + i) < size); ++j) {
            if((mem[j + i] >= 0x20) && (mem[j + i] <= 0x7E)) 
                printf("%c", mem[j + i]);
            else
                printf(".");
        }
        printf("\n");
    }
}

