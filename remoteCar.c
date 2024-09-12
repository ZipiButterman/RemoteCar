#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/lirc.h>
#include <sys/ioctl.h>
#include <string.h>

#define LIRC_DEVICE "/dev/lirc0"
#define BUFFER_SIZE 256

int main(void) {
    int lirc_fd;
    struct lirc_config *config;
    if ((lirc_fd = open(LIRC_DEVICE, O_RDONLY)) == -1) {
        perror("Failed to open LIRC device");
        return 1;
    }
    if (ioctl(lirc_fd, LIRC_SET_REC_MODE, LIRC_MODE_MODE2) == -1) {
        perror("Failed to set LIRC mode");
        close(lirc_fd);
        return 1;
    }
    printf("Awaiting IR signal...\n");
    char buffer[BUFFER_SIZE];
    int code;
    while (read(lirc_fd, buffer, sizeof(buffer)) > 0) {
        sscanf(buffer, "%x", &code); 
        printf("Received IR code: 0x%x\n", code);
        if(code == 0xFF629D) {
            printf("Press UP\n");
        } else {
            if(code == 0xFFA857) {
                printf("Press DOWN\n");
            } 
            else {
                if(code == 0xFF22DD) {
                    printf("Press LEFT\n");
                } 
                else {
                    if(code == 0xFFC23D) {
                        printf("Press RIGTH\n");
                    } 
                    else {
                        if(code == 0xFF02FD) {
                            printf("Press STOP\n");
                        }
                    }
                }
            }
        }
    }
    close(lirc_fd);
    return 0;
}