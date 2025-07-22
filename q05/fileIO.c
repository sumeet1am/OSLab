#include <unistd.h>
#include <stdio.h>
#define BUFFER_SIZE 30
int main() {
// ssize_t read(int fd, void *buf, size_t count);
// ssize_t write(int fd, const void *buf, size_t count);
char buffer[BUFFER_SIZE];
int n = read(0, buffer, BUFFER_SIZE); // 0 is the file discriptor for stdin
printf("Number of characters read: %d\n", n);
write(1, buffer, n); // 1 is the file discriptor for stdout
return 0;
}
