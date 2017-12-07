#ifndef RANDOM_H
#define RANDOM_H

/* generate_random(uint32_t, uint32_t, uint32_t, uint32_t)
 * generate random in desgnated range
 * arg1: data
 * arg2: numbre of elements in data
 * arg3: minimun num to be generated
 * arg4: maximum num to be generated */
void generate_random( uint32_t data[], uint32_t element_num, uint32_t floor, uint32_t cieal);

#endif /* RANDOM_H */
