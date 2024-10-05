#include <stdio.h>

void outputFactors (int a)
{
  int numberOfFactor = 0;
  int factors[10];
  for(int i=0;i<10;i++)
    factors[i] =0;
  int factorIndex =0;

  for(int i=2;i<a;i++)
  {
    if(a%i == 0)
    {
      numberOfFactor ++;
      factors[factorIndex] = i;
      factorIndex++;
    }
  }

  printf("%d has %d factors: ",a,numberOfFactor);

  for(int i =0;i<factorIndex;i++)
    printf("%d, ",factors[i] );

  printf("\n");
}

void main()
{
  int n;

  printf("How many integers? ");
  scanf("%d",&n);

  int a[n];
  int pos = 0;

  for(;pos<n;pos++)
  {
    printf("Enter a number: ");
    scanf("%d",&a[pos]);
  }

  do {
    if((a[pos] > 0) && (a[pos]%2 == 0))
    {
      outputFactors(a[pos]);
    }
    pos--;
  } while(pos>0);
}
