#include <stdio.h>

/*
if op = 1-4, do this operator.
quad nested loop;
print op1, op2, op3, op4
*/
#define opDef1 0x00000001
#define opDef2 0x00000002
#define opDef3 0x00000010
#define opDef4 0x00000020

int operate(int op, int a, int b){
	switch(op){
		case opDef1: 
			return a+b;
		case opDef2: 
			return a-b;
		case opDef3:
			return a*b;
		case opDef4:
			 return (int)a/b;

	}
	return 0;
}

char opChar(int op){
	switch(op){
		case 1:
			return '+';
		case 2:
			return '-';
		case 3:
			return '*';
		case 4:
			return '/';
	}
	return '?';
}

int getPriority(int op){
	switch(op){
		case 1:
			return opDef1;
		case 2:
			return opDef2;
		case 3:
			return opDef3;
		case 4:
			return opDef4;
	}
	return -1;
}

int calculate(int op1, int op2, int op3){
	/*
	111 011
	110 010
	101 001
	100 000
	*/
	op1 = getPriority(op1);
	op2 = getPriority(op2);
	op3 = getPriority(op3);

	int p1 = (op1 & 0x0F)==0;// = 1 for * or /
	int p2 = (op2 & 0x0F)==0;// else = 0
	int p3 = (op3 & 0x0F)==0;
	//4+4+4+4 or 4/4/4/4
	if(p1 == p2 && p2 == p3)
		return operate(op3, operate(op2, operate(op1, 4, 4), 4), 4);
	//4 + 4* 4 * 4
	if(!p1 && p2 && p3)
		return operate(op1,4,operate(op3, operate(op2,4,4),4));
	//4 * 4 * 4 + 4
	if(p1 && p2 && !p3)
		return operate(op3,operate(op2, operate(op1, 4, 4),4),4);
	//4 + 4 * 4 + 4
	if(!p1 && p2 && !p3)
		return operate(op3, operate (op1, 4, operate(op2, 4, 4)), 4);
	//4 * 4 + 4 * 4
	if(p1 && !p2 && p3)
		return operate(op2, operate(op1, 4, 4), operate(op3, 4, 4));
	//4 + 4 + 4 * 4
	if(!p1 && !p2 && p3)
		return operate(op1,4,operate(op2, operate(op3,4,4),4));
	//4 * 4 + 4 + 4
	if(p1 && !p2 && !p3)
		return operate(op3, operate(op2, operate(op1, 4, 4), 4), 4);

	return 0;
}

int main (){

	int n, i;
	int solCheck;
	int op1, op2, op3;
	int validSolution = 0;
	char op1Char, op2Char, op3Char;
	
	scanf("%d", &n);
	int sol[n];

	for(i = 0; i<n; i++){
			scanf("%d", &sol[i]);
	}

	for(i=0; i<n; i++){

	
		for(op1 = 4; op1 >0; op1--){
	
			for(op2 = 4; op2 >0; op2--){

				for(op3 = 4; op3 >0; op3--){
					solCheck = calculate(op1, op2, op3);

					op1Char = opChar(op1);
					op2Char = opChar(op2);
					op3Char = opChar(op3);
						//printf("4 %c 4 %c 4 %c 4 = %d\n", op1Char, op2Char, op3Char, solCheck);
					
					if (solCheck == sol[i]){
						validSolution = 1;

						op1Char = opChar(op1);
						op2Char = opChar(op2);
						op3Char = opChar(op3);

						printf("4 %c 4 %c 4 %c 4 = %d\n", op1Char, op2Char, op3Char, sol[i]);
						op1 = -1;
						op2 = -1;
						op3 = -1;
						break;
				
					}
				}
			}
		}
		if (!validSolution) printf("no solution\n");
		validSolution = 0;
	}
}