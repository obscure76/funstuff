#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char** argv)
{
	char *str1;
	char *str2;
	char sum[100], ch;
	int l1,l2,i,temppro,k=0, l, t, ccarry=0, pcarry =0;
	int tempsum=0, prod_len=0, scarry =0, j;
	
	if (argc<2)
	{
		printf("\n usage ./a.out num1 num2 ");
		exit(1);
	}

	str1 = argv[1];
	str2 = argv[2];
	l1= strlen(str1);
	l2= strlen(str2);

 
	
	for(i=0;i<l1/2;i++)
	{
		ch = str1[i];
		str1[i]=str1[l1-1-i];
		str1[l1-1-i]=ch;
	}
		
	for(i=0;i<l2/2;i++)
	{
		ch = str2[i];
		str2[i]=str2[l2-1-i];
		str2[l2-1-i]=ch;
	}
	printf("\n rev strings 1 = %s \t 2 = %s\n", str1, str2);	

	for(i=0;i<100;i++)
	{
		sum[k]='\0';
	
	}
	for (i=0; i<l1; i++)
	{
		// For each digit of smaller string multiple with larger string 
		t= (str1[i]-'0');
		for(j=0;j<l2;j++,k++)
		{
			temppro = (str2[j]-'0')*t;
			temppro+=pcarry;
//			printf("\t temp pro for %c %d is %d", str2[j], t, temppro);
			if (temppro<10)
			{
				if(isdigit(sum[k]))
				{
					tempsum = (sum[k]-'0')+temppro;
				} else {
					tempsum = temppro;
				}
				tempsum+=scarry;
				scarry = tempsum/10;
				tempsum = tempsum%10;
				sum[k]=tempsum+'0';
//				printf("\n the index %d tempsum %d temppro %d scarry%d", k, tempsum, temppro, scarry);
			} else {
				pcarry = temppro/10;
				temppro = temppro%10;
				if (isdigit(sum[k]))
				{
					tempsum = (sum[k]-'0')+temppro;
				} else {
					tempsum = temppro;
				}
				tempsum+=scarry;
				scarry = tempsum/10;
				tempsum = tempsum%10;
				sum[k]=tempsum+'0';
//				printf("\n the tempsum %d temppro %d scarry%d", tempsum, temppro, scarry);
			}
		}
		pcarry+=scarry;
		if(pcarry>0)
		{
			sum[k]=pcarry+'0';
			scarry=pcarry=0;
		} 
		k=i+1;
	}
	l = strlen(sum);
	for(i=0;i<l/2;i++)
	{
		ch = sum[i];
		sum[i]=sum[l-1-i];
		sum[l-1-i]=ch;
	}
	printf("\n The string sum is %s", sum);

	return 0;
}

