#include <stdio.h>

int main(int argc, char** argv){
 double v1[2] = {2.0, 0.5};
 double v2[2] = {3.0, -1.0};
 double product = 0.0;
 int i = 0;

 FILE* fp = NULL;

 /* open */ 
 if((fp = fopen("data.csv", "w")) == NULL){
  printf("fopen failed\n");
  return 0;
 }

 /* main process */
 for(i=0; i<2; i++){
  product += v1[i] * v2[i];
 }
 fprintf(fp, "%lf\n", product);

 /* close */
 fclose(fp);
 
 return 0;
}
