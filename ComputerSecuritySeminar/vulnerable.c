#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h> // call debugger
#include <fcntl.h>


#define LIBC_BASE_ADDR 0x03000000
#define LIBC_PATH_SO "/lib/x86_64-linux-gnu/libc.so.6"
#define STACK_BASE_ADDR 0x04f000000
#define STACK_SIZE 0x001000000

void do_map_libc(void);
void do_map_stack(void);
void overflow(char *);
void move_stack(char *);

void do_map_libc(void)
{
	int fd;
	struct stat sb;

	fd = open(LIBC_PATH_SO, O_RDONLY, 0);
	fstat(fd, &sb);
	mmap((void *)LIBC_BASE_ADDR, sb.st_size,
		PROT_READ|PROT_EXEC, MAP_FIXED|MAP_SHARED, fd, 0);

}

void do_map_stack(void)
{
	int fd;
	
	fd = open("/dev/zero", O_RDONLY, 0);
	mmap((void *)STACK_BASE_ADDR, STACK_SIZE,
		PROT_READ|PROT_WRITE, MAP_FIXED|MAP_PRIVATE, fd, 0);	
}

void overflow(char *arg)
{
	char buf[64];
	//strcpy(buf, arg); // vuln. is here, no bounds checking
	//memcpy(buf, arg, 128);
	//gets(buf);
	read(0, buf, 128);
	//printf("Your buf: %s\n", buf);
}

void move_stack(char *arg)
{
	__asm("mov $0x04fffff00, %esp\n");
	overflow(arg); // trigger the overflow
	//_exit(0);
}

int main(int argc, char *argv[])
{
	sleep(5);
	//raise(SIGINT);
	do_map_libc();
	do_map_stack();
	move_stack(argv[1]);
	return 0;
}

