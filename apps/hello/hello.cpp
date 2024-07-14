#if USE_STDIO
#include <cstdio>

int main(int argc, char** argv) {
  printf("Hello, world!\n");
  return 0;
}
#else
#include <stdlib.h>
#include <unistd.h>

int main() {
	const char buf[] = "Hello, world!\n";
	const unsigned int len = sizeof(buf);

	write(1, buf, len);
	return 0;
}
#endif
