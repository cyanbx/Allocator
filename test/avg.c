#include <stdio.h>
#include <stdlib.h>

int main(){
    double a[10]={0.00427085 ,0.0052274 ,0.0046279 ,0.00428267 ,0.00494764 ,0.0042973 ,0.00535544 ,0.0054559 ,0.00564969 ,0.00540861};
    double sum;
    for (int i = 0; i < 10; i++) {
        sum += a[i];
    }
    double avg = sum / (10.0);
    printf("%.6f", avg);
}