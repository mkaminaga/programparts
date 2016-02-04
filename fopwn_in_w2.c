#include <stdio.h>

int main(int argc, char** argv){
 double v1[3];
 double v2[3];
 double product = 0.0;
 int i = 0;

 FILE* fp = NULL;

 /* open */ 
 if((fp = fopen("data2.csv", "w")) == NULL){
  printf("fopen failed\n");
  return 0;
 }

 printf("INPUT:\n");

 /* input */
 for(i=0; i<3; i++){
  printf("v1[%d] = ", i);
  scanf("%lf", &v1[i]);
 }
 
 for(i=0; i<3; i++){
  printf("v2[%d] = ", i);
  scanf("%lf", &v2[i]);
 }
 
 /* main process */
 for(i=0; i<3; i++){
  product += v1[i] * v2[i];
 }
 fprintf(fp, "%lf\n", product);

 printf("Thanks!\n");

 /* close */
 fclose(fp);
 
 return 0;
}
