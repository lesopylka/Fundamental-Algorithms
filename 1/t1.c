#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

int toggles_h(unsigned number, unsigned kolvo_krat){
    if (kolvo_krat > 1){
        toggles_h(number, kolvo_krat - 1);
    }
    printf("%u ", number * (kolvo_krat));
}