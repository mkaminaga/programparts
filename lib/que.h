#ifndef QUE_H
#define QUE_H

/* user stack size. default is 255 */
#ifndef QUE_DEPTH
# define QUE_DEPTH 255
#endif

/* put que. que size can be changed by QUE_DEPTH */
void put_que(uint32_t node, uint32_t* que);

/* take out que. que size can be changed by QUE_DEPTH */
uint32_t take_out_que(uint32_t* que);

/* clean the que */
void clean_que(uint32_t* que);

/* fill the que with specific value */
void fill_que(uint32_t value, uint32_t* que);

/* show the existence of specific value in the que in designated depth */
uint8_t exist_in_que(uint32_t value, uint32_t* que, uint32_t depth);

#endif /* QUE_H */
