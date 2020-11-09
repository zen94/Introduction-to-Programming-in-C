#include <stdlib.h>
#include <stdio.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double calcbalance(int age, retire_info info, double balance){
  for (int i = 0; i < info.months; i++){
    printf("Age %3d month %2d you have $%.2lf\n",(age+i)/12,(age+i)%12,balance);
    balance = balance + balance * info.rate_of_return/12 + info.contribution;
  }
  return balance;
}

void retirement(int startAge,   //in months
		double initial, //initial savings in dollars
		retire_info working, //info about working
		retire_info retired) //info about being retired
{
  double account_balance;

  account_balance = calcbalance(startAge,working,initial);
  account_balance = calcbalance(startAge+working.months,retired,account_balance);
}

int main(void){
  retire_info work_info = {489,1000,0.045};
  retire_info reti_info = {384,-4000,0.01};
  retirement(327,21345,work_info,reti_info);
  return EXIT_SUCCESS;
}
