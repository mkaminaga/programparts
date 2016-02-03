#include <stdio.h>
#include <stdint.h>

/* sort given data.
 * arg1: given data
 * arg2: key of sorting
 * arg2: ascending(=1) and decending(=0)
 * arg3: depth of index to be sorted
 * */
void bubble_sort_2d(
        uint32_t data[][2], uint8_t key, uint8_t way, uint32_t depth);

int main(int argc, char const* argv[]) {
    uint32_t data[][2] = {
        {'A', 0}, {'B', 1}, {'J', 9}, {'D', 3}, {'I', 8},
        {'G', 6}, {'C', 2}, {'H', 7}, {'F', 5}, {'E', 4}
    };

    uint32_t i = 0;

    for (i = 0; i < 8; i++) {
        printf("/**** %u ****/\n", i);

        printf("before:%c ,%c ,%c ,%c ,%c ,%c ,%c ,%c ,%c ,%c\n",
            data[0][0], data[1][0], data[2][0], data[3][0], data[4][0],
            data[5][0], data[6][0], data[7][0], data[8][0], data[9][0]);
        printf("       %u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
            data[0][1], data[1][1], data[2][1], data[3][1], data[4][1],
            data[5][1], data[6][1], data[7][1], data[8][1], data[9][1] );

        switch (i) {
            case 0:
                printf("sort: index 0 ~ 9, key 1, ascending\n");
                bubble_sort_2d(data, 1, 1, 10);
                break;
            case 1:
                printf("sort: index 0 ~ 9, key 1, decending\n");
                bubble_sort_2d(data, 1, 0, 10);
                break;
            case 2:
                printf("sort: index 0 ~ 4, key 1, ascending\n");
                bubble_sort_2d(data, 1, 1, 5);
                break;
            case 3:
                printf("sort: index 0 ~ 4, key 1, decending\n");
                bubble_sort_2d(data, 1, 0, 5);
                break;
            case 4:
                printf("sort: index 0 ~ 9, key 0, ascending\n");
                bubble_sort_2d(data, 0, 1, 10);
                break;
            case 5:
                printf("sort: index 0 ~ 9, key 0, decending\n");
                bubble_sort_2d(data, 0, 0, 10);
                break;
            case 6:
                printf("sort: index 0 ~ 4, key 0, ascending\n");
                bubble_sort_2d(data, 0, 1, 5);
                break;
            case 7:
                printf("sort: index 0 ~ 4, key 0, decending\n");
                bubble_sort_2d(data, 0, 0, 5);
                break;
            default:
                break;
        }

        printf("after :%c ,%c ,%c ,%c ,%c ,%c ,%c ,%c ,%c ,%c\n",
            data[0][0], data[1][0], data[2][0], data[3][0], data[4][0],
            data[5][0], data[6][0], data[7][0], data[8][0], data[9][0]);
        printf("       %u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u ,%u\n",
            data[0][1], data[1][1], data[2][1], data[3][1], data[4][1] ,
            data[5][1], data[6][1], data[7][1], data[8][1], data[9][1] );
        printf("\n");
    }

    return 0;
}

/* sort given data.
 * arg1: given data
 * arg2: key of sorting
 * arg2: ascending(=1) and decending(=0)
 * arg3: depth of index to be sorted
 * */
void bubble_sort_2d(
        uint32_t data[][2], uint8_t key, uint8_t way, uint32_t depth) {
    uint8_t end_flag = 1;
    uint32_t i = 0;
    uint32_t temp = 0;
    uint32_t temp2 = 0;

    /* exception */
    if (depth < 1) {
        return;
    }

    end_flag = 0;

    while (end_flag == 0) {
        end_flag = 1;

        if (way == 1) {
            /* ascending order */
            for (i = 0; i < depth - 1; i++) {
                if(data[i][key] > data[i + 1][key]) {
                    temp = data[i + 1][0];
                    temp2 = data[i + 1][1];
                    data[i + 1][0] = data[i][0];
                    data[i + 1][1] = data[i][1];
                    data[i][0] = temp;
                    data[i][1] = temp2;
                    end_flag = 0;
                }
            }
        } else {
            /* decending order */
            for (i = 0; i < depth - 1; i++) {
                if(data[i][key] < data[i + 1][key]) {
                    temp = data[i + 1][0];
                    temp2 = data[i + 1][1];
                    data[i + 1][0] = data[i][0];
                    data[i + 1][1] = data[i][1];
                    data[i][0] = temp;
                    data[i][1] = temp2;
                    end_flag = 0;
                }
            }
        }
    }
}


