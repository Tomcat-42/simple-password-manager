#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./lib/cJSON/cJSON.h"
#include "./lib/manager/manager.h"

int main(int argc, char **argv) {
    Service *service = service_structify("Pablo2", "Tomcat", "senha", "outro");

    // printf("%d\n", service_upsert(service));
    printf("%d\n", service_delete("Pablo"));
    //printf("%s\n", service_show("Pablo2"));
    printf("%s\n", service_list());
}
