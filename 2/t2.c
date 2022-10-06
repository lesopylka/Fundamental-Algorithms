#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>

int main() {

    char* parametrs [5] = {"-l", "-r", "-u", "-n", "-c"};
    int good_flag = 0, flag;

    for (flag = 0; flag < 5; ++flag) {
        if (!strcmp(parametrs[flag], argv[2])) {
            good_flag = 1;
            switch (parametrs[flag][1]) {
                case 'l':
                    printf("Length of string: %d\n", length(argv[1]));
                    break;
                case 'r':
                    reverse(argv[1]);
                    printf("Reverse: %s\n", argv[1]);
                    break;
                case 'u':
                    upper_register_through_2(argv[1]);
                    printf("Result: %s\n", argv[1]);
                    break;
                case 'n':
                    printf("Replaced: %s\n",replace(argv[1]));
                    break;
                case 'c':
                    if (argc >= 4) {
                        printf("%s", concat(argv[1], argv[3]));
                    } else {
                        printf("Need one more argument!");
                    }
                    break;
            }
            break;
        }
    }
}
