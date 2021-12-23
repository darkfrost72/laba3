#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<locale.h>
#include <stdbool.h>



double method_chord(double x1, double x2, double e, double iter);
double F(double x);
double ddF(double x);

double F(double x)
{
    return pow(x, 3) - 18 * x - 83;
}
double ddF(double x){
    return pow(3*x, 2) - 18;
}

double method_chord(double x1, double x2, double eps, double iter){
    int i = 0;
    do {
        x1 = (F(x2) * x1 - F(x1) * x2) / (F(x2) - F(x1));
        i++;
    } while (fabs(x2-x1) > eps && i <= iter);
    printf("Результат = %.2f\n",x1);
    return x1;
}

double poldel(double (*f)(double),double a,double b,double eps)
{
    double c;
    while((b-a)/2>eps){
        c=(a+b)/2;
        if((F(a)*F(c))>0) a=c;
        else b=c;
    }
    return c;
}

double newton(double x, double eps, double iter){
    double f;
    int i = 0;
    printf("X = %.4f \n",x);
    do{
        f = F(x);
        x = x - F(x)/ddF(x);
        i++;
    }while(fabs(f) > eps && i < iter);
    printf("Результат = %.4f\n",x);
    return x;
}

int main() {
    setlocale(LC_ALL, "Rus");
    double x1, x2, e, iter;
    unsigned int choice;
    printf("Введите вариант  \n");
    printf("1 - Метод хорд \n");
    printf("2 - Метод половинчатого деления \n");
    printf("3 - Метод Ньютона\n");
    scanf("%u", &choice);
    switch (choice) {
        case 1:
            printf("Введите X1\n");
            scanf("%lf", &x1);
            printf("Введите X2\n");
            scanf("%lf", &x2);
            printf("Введите предел количества итераций\n");
            scanf("%lf", &iter);
            e = 0.001;
            if (x2 > 0 && x1 > 0 || x2 < 0 && x1 < 0) {
                printf("Знаки должны быть различны");
            }
            else {
                x1 = method_chord(x1, x2, e, iter);
                return 0;
            }
        case 2:
            printf("Введите X1\n");
            scanf("%lf", &x1);
            printf("Введите X2\n");
            scanf("%lf", &x2);
            e = 0.001;
            double x=poldel(F, x1, x2, e);
        case 3:
            printf("Введите X1\n");
            scanf("%lf", &x1);
            e = 0.001;
            printf("Введите предел количества итераций\n");
            scanf("%lf", &iter);
            double y = newton(x1, e, iter);
    }
}