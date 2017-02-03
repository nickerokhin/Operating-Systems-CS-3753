#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(int argc, const char* argv[])
{
 int num1 = atoi(argv[1]);
 int num2 = atoi(argv[2]);
 int res;
 long int adder = syscall(327, num1, num2, &res);

printf("Testing system call: %ld", adder);

}
