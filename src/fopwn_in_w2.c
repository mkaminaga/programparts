#include <stdio.h>

int main(int argc, char** argv){
    doublev1[3];
    doublev2[3];
    doubleproduct=0.0;
    inti=0;

    FILE*fp=NULL;

    /*open*/
    if((fp=fopen("data2.csv","w"))==NULL){
        printf("fopenfailed\n");
        return0;
    }

    printf("INPUT:\n");

    /*input*/
    for(i=0;i<3;i++){
        printf("v1[%d]=",i);
        scanf("%lf",&v1[i]);
    }

    for(i=0;i<3;i++){
        printf("v2[%d]=",i);
        scanf("%lf",&v2[i]);
    }

    /*mainprocess*/
    for(i=0;i<3;i++){
        product+=v1[i]*v2[i];
    }
    fprintf(fp,"%lf\n",product);

    printf("Thanks!\n");

    /*close*/
    fclose(fp);

    return0;
}
