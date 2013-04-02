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

#include "procutil.h"

#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>


int is_process_exist(const char *proc_name)
{
    DIR *dir;
    int instanceCnt = 0;

    dir = opendir("/proc");
    
    if(dir != NULL) {
        struct dirent *dirEntry;

        while(((dirEntry = readdir(dir)) != NULL)) {
            FILE *fp = NULL;
            char fpath[1024];

            memset(fpath, 0, sizeof(fpath));
            if(dirEntry->d_type == DT_DIR){
                sprintf(fpath, "%s", "/proc/");
                strcat(fpath, dirEntry->d_name); 
                strcat(fpath, "/comm");
            }

            if((fp = fopen(fpath, "r")) != NULL) {
                char commandLine[256];
                
                memset(commandLine, 0, sizeof(commandLine));
                fread(commandLine, 1, sizeof(commandLine), fp);
                if(strstr(commandLine, proc_name) != NULL) {
                    instanceCnt++;
                }
            }
            if(fp) {
                fclose(fp);
                fp = NULL;
            }
        }
        closedir(dir);

        if(instanceCnt > 1) 
            return 1;
    }
    
    return 0;
}