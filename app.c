#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "devone_ioctl.h"

#define DEVFILE "/dev/devone0"

void read_buffer(int fd)
{
    unsigned char buf[64];
    int ret;
    int i;

    ret = read(fd, buf, sizeof(buf));
    if (ret == -1) {
        perror("read");
    }
    for (i = 0; i < ret; i++){
        printf("%02x ", buf[i]);
    }
    printf("\n");
}

int main(void)
{
    struct ioctl_cmd cmd;
    int ret;
    int fd;

    fd = open(DEVFILE, O_RDWR);
    if (fd == -1){
        perror("open");
        printf("cannnot allocate memory\n");
        exit(1);
    }

    printf("Test1 Read 1byte from the driver module(IOCTL_VALGET)\n");
    memset(&cmd, 0, sizeof(cmd));
    ret = ioctl(fd, IOCTL_VALGET, &cmd);
    if (ret == -1) {
        printf("IOCTL_VALGET1 error %d\n", errno);
        perror("ioctl");
    }
    printf("val Expect:255 Returned Value:%d\n\n", cmd.val);

    // read buffer
    printf("Test2 Read 64bytes from the driver module(devone_read)\n");
    printf("Expect:all 0xFF\n");
    read_buffer(fd);
    printf("\n");

    printf("Write 0xCC to the driver module(IOCTL_VALSET)\n");
    memset(&cmd, 0, sizeof(cmd));
    cmd.val = 0xCC;
    ret = ioctl(fd, IOCTL_VALSET, &cmd);
    if (ret == -1){
        printf("IOCTL_VALSET errno %d\n", errno);
        perror("ioctl");
    }
    printf("\n");

    printf("Test3 Read 1byte from the driver module(IOCTL_VALGET)\n");
    memset(&cmd, 0, sizeof(cmd));
    ret = ioctl(fd, IOCTL_VALGET, &cmd);
    if (ret == -1){
        printf("IOCTL_VALGET2 errno %d\n", errno);
        perror("ioctl");
    }
    printf("val Expect:204 Returned Value:%d\n\n", cmd.val);

    // read buffer
    printf("Test4 Read 64bytes from the driver module(devone_read)\n");
    printf("Expect:all 0xCC\n");
    read_buffer(fd);
    printf("\n");

    close(fd);

    return 0;
}