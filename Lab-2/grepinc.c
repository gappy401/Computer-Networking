#include <stdlib.h>
#include <stdio.h>
int main()
{
         
         system("cp test.txt test.txt.tmp");
         system("sort test.txt.tmp >test.txt");
}
