#include <stdio.h>
#include <fcntl.h>
#include <sys/ptrace.h>

#define PROC_ID		1
#define PROC_ADDR	2
#define ARRY_SIZE	10

int main (int argc, char* argv[])
{
	char file[64];
	long pid = 0;
	int fd;
	int Ret;
	int target_addr;
	char flag[30] = "====================";
	char step_flag[30] = "--------------------";
	char target_value[ARRY_SIZE] = {0};
	char write_value[ARRY_SIZE] = "Hi, friend\0";
	off_t addr;


	// Convert input value
	pid = atoi(argv[PROC_ID]);
	target_addr = strtol(argv[PROC_ADDR], NULL, 16);


	printf("%s\n", flag); // Print start flag


	// Open memomy-file by using 'process ID'
	sprintf(file, "/proc/%ld/mem", pid);
	fd = open(file, O_RDWR);
	if(fd != -1)
		printf("File open OK.\n");
	else
		printf("File open Failed.\n");


	// Attatch memory
	Ret = ptrace(PTRACE_ATTACH, pid, 0, 0);
	if(Ret != -1)
		printf("ptrace() OK.\n");
	else
		printf("ptrace() Failed.\n");


	// Stopping target-process
	Ret = waitpid(pid, NULL, 0);
	if(Ret != -1)
		printf("waitpid(%ld) OK.\n", pid);
	else
		printf("waitpid() Failed.\n");

	
	// Read address of memory from target-process
	printf("%s\n", step_flag);
	addr = target_addr;
	printf("Targer Address: 0x%x\n", addr);
	Ret = pread(fd, target_value, sizeof(char)*8, addr);
	if(Ret != -1)
	{
		printf("pread() OK.\nRead Value: '%s'\n", target_value);
	}
	else
		printf("pread() Failed.\n");


	// Write to address write-value
	printf("%s\n", step_flag);
	Ret = pwrite(fd, write_value, sizeof(char)*8, addr);
	if(Ret != -1)
	{
		printf("pwrite() OK.\nWrite Value: '%s'\n", write_value);
	}
	else
		printf("pwrite() Failed.\n");


	// Read again address of memory from target-process
	printf("%s\n", step_flag);
	addr = target_addr;
	printf("Targer Address: 0x%x\n", addr);
	Ret = pread(fd, target_value, sizeof(char)*8, addr);
	if(Ret != -1)
	{
		printf("pread() OK.\nRead Value: '%s'\n", target_value);
	}
	else
		printf("pread() Failed.\n");

	printf("%s\n", flag); // Print end flag
	
	close(fd); // Close file descriptor
	


	return 0;
}
