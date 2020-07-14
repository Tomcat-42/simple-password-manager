#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./lib/cJSON/cJSON.h"
#include "./lib/manager/manager.h"

int main(int argc, char **argv) {
    printf("%s\n", service_list());
}
