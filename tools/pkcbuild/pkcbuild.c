#include <stdio.h>
#include <stdlib.h>

int main()
{
system("test -d src/pkc/build || mkdir -p src/pkc/build");
system("cd src/pkc/build && cmake .. && make");
}
