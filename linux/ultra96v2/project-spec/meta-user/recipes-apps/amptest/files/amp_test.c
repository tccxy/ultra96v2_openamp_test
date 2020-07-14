

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <linux/rpmsg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <byteswap.h>
#include <stdint.h>
#include <errno.h>
#include <sys/mman.h>


/* Shutdown message ID */

struct _payload {
	unsigned long num;
	unsigned long size;
	char data[];
};

static int charfd = -1, fd = -1, err_cnt;

struct _payload *i_payload;
struct _payload *r_payload;

#define RPMSG_GET_KFIFO_SIZE 1
#define RPMSG_GET_AVAIL_DATA_SIZE 2
#define RPMSG_GET_FREE_SPACE 3

#define RPMSG_HEADER_LEN 16
#define MAX_RPMSG_BUFF_SIZE (512 - RPMSG_HEADER_LEN)
#define PAYLOAD_MIN_SIZE	1
#define PAYLOAD_MAX_SIZE	(MAX_RPMSG_BUFF_SIZE - 24)
#define NUM_PAYLOADS		(PAYLOAD_MAX_SIZE/PAYLOAD_MIN_SIZE)

int rpmsg_create_ept(int rpfd, struct rpmsg_endpoint_info *eptinfo)
{
	int ret;

	ret = ioctl(rpfd, RPMSG_CREATE_EPT_IOCTL, eptinfo);
	if (ret)
		perror("Failed to create endpoint.\n");
	return ret;
}

char *get_rpmsg_ept_dev_name(char *rpmsg_char_name, char *ept_name,
			char *ept_dev_name)
{
	char sys_rpmsg_ept_name_path[64];
	char svc_name[64];
	char *sys_rpmsg_path = "/sys/class/rpmsg";
	FILE *fp;
	int i;
	int ept_name_len;

	for (i = 0; i < 128; i++) {
		sprintf(sys_rpmsg_ept_name_path, "%s/%s/rpmsg%d/name",
			sys_rpmsg_path, rpmsg_char_name, i);
		printf("checking %s\n", sys_rpmsg_ept_name_path);
		fp = fopen(sys_rpmsg_ept_name_path, "r");
		if (!fp) {
			printf("failed to open %s\n", sys_rpmsg_ept_name_path);
			break;
		}
		fgets(svc_name, sizeof(svc_name), fp);
		fclose(fp);
		printf("svc_name: %s.\n",svc_name);
		ept_name_len = strlen(ept_name);
		if (ept_name_len > sizeof(svc_name))
			ept_name_len = sizeof(svc_name);
		if (!strncmp(svc_name, ept_name, ept_name_len)) {
			sprintf(ept_dev_name, "rpmsg%d", i);
			return ept_dev_name;
		}
	}

	printf("Not able to RPMsg endpoint file for %s:%s.\n",
	       rpmsg_char_name, ept_name);
	return NULL;
}

int main(int argc, char *argv[])
{
	int cmd, ret, i;
	int size, bytes_rcvd, bytes_sent;
	char *rpmsg_dev="/dev/rpmsg0";
	int uses_rpmsg_char = 0;
	char *rpmsg_char_name;
	struct rpmsg_endpoint_info eptinfo;
	char test[] = "hello amp";
	char test_rcv[20] = "init ";
	static int inum =1;

	printf("\r\n Echo test start \r\n");

	printf("\r\n Open rpmsg dev %s! \r\n", rpmsg_dev);

	fd = open(rpmsg_dev, O_RDWR | O_NONBLOCK);

	if (fd < 0) {
		perror("Failed to open rpmsg device.");
		return -1;
	}

	rpmsg_char_name = strstr(rpmsg_dev, "rpmsg_ctrl");
	if (rpmsg_char_name != NULL) {
		char ept_dev_name[16];
		char ept_dev_path[32];

		uses_rpmsg_char = 1;
		strcpy(eptinfo.name, "rpmsg-openamp-demo-channel");
		eptinfo.src = 0;
		eptinfo.dst = 0xFFFFFFFF;
		ret = rpmsg_create_ept(fd, &eptinfo);
		if (ret) {
			printf("failed to create RPMsg endpoint.\n");
			return -1;
		}
		charfd = fd;

		if (!get_rpmsg_ept_dev_name(rpmsg_char_name, eptinfo.name,
					   ept_dev_name))
			return -1;
		sprintf(ept_dev_path, "/dev/%s", ept_dev_name);
		fd = open(ept_dev_path, O_RDWR | O_NONBLOCK);
		if (fd < 0) {
			perror("Failed to open rpmsg device.");
			close(charfd);
			return -1;
		}
	}
	bytes_sent = write(fd, test,sizeof(test));
	printf("write success \r\n");
	bytes_rcvd = read(fd, test_rcv,sizeof(test_rcv));

	printf("test rcv is %s\r\n",test_rcv);

	while(1)
	{
		//bytes_sent = write(fd, test,sizeof(test));
		//printf("write success \r\n");
		//printf("wait rcv msg\r\n");
		bytes_rcvd = read(fd, test_rcv,sizeof(test_rcv));
		//printf("wait rcv msg bytes_rcvd %d\r\n",bytes_rcvd);
		if( (bytes_rcvd > 0) && (bytes_rcvd < 20))
		{
			//printf("rcv msg is \r\n");
			//for(i=0; i< bytes_rcvd; i++)
			//{
			//	printf("%x ",test_rcv[i]);
			//}
			//printf("R %d\r\n",inum);

			if(inum%50 == 0)
			{
				printf("R %d\r\n",inum);
			}
			inum++;
		}
		//sleep(3);
	};
	close(fd);
	if (charfd >= 0)
		close(charfd);
	return 0;
}
