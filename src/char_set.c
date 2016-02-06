#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t temp = 0;

    /* show description */
    printf("Ascii char set. \"---\" indicates control charactor.\n");

    /* show column */
    printf("    "); //adjustment
    for(i = 0; i < 0x10; i++) printf("   %.2x", i);
    printf("\n");

    /* show row list */
    for(i = 0; i < 0x10; i++) {
        printf("0x%.2x", i);
        for(j = 0; j < 0x10; j++) {
            temp = i * 0x10 + j;
            if (temp < 0x20) {
                printf("  ---"); //control charactor
            } else {
                printf("    %c", i * 0x10 + j);
            }
        }
        printf("\n");
    }
}
