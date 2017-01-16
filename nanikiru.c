#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sortMyHand();
void printPai(int p);

int pai[14];

void inputtehai(){
	char tehai[28];
	int kind,position=-1;
	printf("配牌を指定してください（天鳳の牌理形式）\n");
	scanf("%s",tehai);
	int i,j,k=0;
	for(i=0;i<28;i++){
		if(k==14)
			break;
		if(tehai[i]=='m'||tehai[i]=='p'||tehai[i]=='s'||tehai[i]=='z'){
			switch(tehai[i]){
			case 'm':
				kind=0;
				break;
			case 'p':
				kind=1;
				break;
			case 's':
				kind=2;
				break;
			case 'z':
				kind=3;
				break;
			default :
				break;
			}
			for(j=position+1;j<i;j++){
				if(kind<=2){
					pai[k]=(int)(tehai[j]-'0'+1)+(kind*11);
				}else{
					pai[k]=(int)(tehai[j]-'0')+32;
				}
				k++;
			}
			position=i;
		}
	}
	sortMyHand();
}
void sortMyHand(){
	int i,j,temp,flag;
	for(i=0;i<13;i++){
		flag=0;
		for(j=0;j<13-(i+1);j++){
			if(pai[j]>pai[j+1]){
				temp=pai[j];
				pai[j]=pai[j+1];
				pai[j+1]=temp;
				flag=1;
			}
		}
		if(flag==0)
			break;
	}
}
int mentu;
int toitu;
int tatsu;
int kindMyHand[40];
int tempshanten=8;
int tatsuCut(int j){
	int temp=8;
	int i;
	for(i=j;i<40;i++){
		if(mentu+tatsu<4){
			if(kindMyHand[i]==2){
				tatsu++;
				kindMyHand[i]-=2;
				temp=tatsuCut(i);
				kindMyHand[i]+=2;
				tatsu--;
			}

			if(kindMyHand[i]>=1&&kindMyHand[i+1]>=1&&i+1<=32){
				tatsu++;
				kindMyHand[i]--;
				kindMyHand[i+1]--;
				temp=tatsuCut(i);
				kindMyHand[i]++;
				kindMyHand[i+1]++;
				tatsu--;
			}
			if(kindMyHand[i]>=1&&kindMyHand[i+2]>=1&&i+2<=32){
				tatsu++;
				kindMyHand[i]--;
				kindMyHand[i+2]--;
				temp=tatsuCut(i);
				kindMyHand[i]++;
				kindMyHand[i+2]++;
				tatsu--;
			}
			
		}
	}
	int calc = 8-mentu*2-tatsu-toitu;
	if(tempshanten>calc)
		tempshanten=calc;
	return tempshanten;
}
int mentuCut(int j){
	int temp=8;
	int i;
	for(i=j;i<40;i++){
		//刻子
		if(kindMyHand[i]>=3){
			mentu++;
			kindMyHand[i]-=3;
			temp=mentuCut(i);
			if(tempshanten>temp)
				tempshanten=temp;
			kindMyHand[i]+=3;
			mentu--;
		}
		//順子
		if(kindMyHand[i]>=1&&kindMyHand[i+1]>=1&&kindMyHand[i+2]>=1&&i+2<=32){
			mentu++;
			kindMyHand[i]--;
			kindMyHand[i+1]--;
			kindMyHand[i+2]--;
			temp=mentuCut(i);
			if(tempshanten>temp)
				tempshanten=temp;
			mentu--;
			kindMyHand[i]++;
			kindMyHand[i+1]++;
			kindMyHand[i+2]++;
		}
	}
	temp=tatsuCut(1);
	if(tempshanten>temp)
		tempshanten=temp;
	return tempshanten;
}
int normalShanten(){
	mentu=0;
	toitu=0;
	tatsu=0;
	tempshanten=8;
	int i;
	for(i=0;i<40;i++){
		kindMyHand[i]=0;
	}
	for(i=0;i<14;i++){
		kindMyHand[pai[i]]++;
	}
	int flag4=0;
	for(i=33;i<40;i++){
		if(kindMyHand[i]==4){
			flag4=1;
			break;
		}
	}
	int tempshanten2=8;

	for(i=2;i<40;i++){
		if(kindMyHand[i]>=2){
			toitu++;
			kindMyHand[i]-=2;
			tempshanten=mentuCut(0);
			toitu--;
			kindMyHand[i]+=2;
		}
	}
	tempshanten=mentuCut(0);
	return tempshanten+flag4;
}
int kokushiShanten(){
	int tempshanten=13;
	int temp=-1;
	int toitu=0;
	int i;
	for(i=0;i<40;i++){
		kindMyHand[i]=0;
	}
	for(i=0;i<14;i++){
		if((pai[i]<31&&(pai[i]%11==0||pai[i]%11==8)) || pai[i]>=31){
			if(temp!=pai[i]){
				temp=pai[i];
				tempshanten--;
			}else if(toitu==0){
				toitu=1;
				tempshanten--;
			}
		}
	}
	return tempshanten;
}
int titoiShanten(){
	toitu=0;
	int i;
	for(i=0;i<40;i++){
		kindMyHand[i]=0;
	}
	for(i=0;i<14;i++){
		kindMyHand[pai[i]]++;
	}

	int tempshanten=6;
	for(i=0;i<40;i++){
		if(kindMyHand[i]>=2){
			toitu++;
			kindMyHand[i]-=2;
			tempshanten--;
		}
	}
	return tempshanten;
}
int mainShanten(){
	int nshanten = normalShanten();
	int titoi = titoiShanten();
	int kokushi = kokushiShanten();
	int agariform;
	int shanten;
	agariform = 1;
	
	//シャンテン数の更新
	shanten=nshanten;
	if(shanten>titoi){
		agariform=2;
		shanten=titoi;
	}else if(shanten==-1&&(titoi==-1))
		agariform=4;

	if(shanten>kokushi){
		agariform=3;
		shanten=kokushi;
	}
	return shanten;
}

void printPai(int p){
	char pai[3];
	int i;
	int c;
	if(p<11){
		i=p-1;
		c=12;
	}else if(p<22){
		i=p-12;
		c=15;
	}else if(p<33){
		i=p-23;
		c=18;
	}else{
		i=p-32;
		c=25;
	}
	pai[0]=i+'0';
	pai[1]=c+'a';
	pai[2]='\0';
	printf("%s",pai);
}

void calcYukouhai(int s,int flag){
	int i,j,k,handnum=-1;
	int hand[14];
	int kind[40];
	int output[14][40];
	int yukouhai[14];
	int temp;
	int shanten;
	int outflag=0;
	for(i=0;i<40;i++){
		kind[i]=0;
	}
	for(i=0;i<14;i++){
		kind[pai[i]]++;
		yukouhai[i]=0;
	}
	for(i=0;i<14;i++){
		for(j=0;j<handnum;j++){
			if(pai[i]==hand[j])
				goto loop_exit;
		}
		handnum++;
		hand[handnum]=pai[i];
		temp=pai[i];

		outflag=0;
		k=0;
		for(j=2;j<40;j++){
			if(j!=11 && j!=12 && j!=22 && j!=23){
				pai[i]=j;
				if(flag == 0){
					shanten=mainShanten();
				}else if(flag == 1){
					shanten=titoiShanten();
				}else if(flag == 2){
					shanten=kokushiShanten();
				}else if(flag == 3){
					shanten=normalShanten();
				}
				if(s>shanten && 4-kind[j]>0){
					if(outflag==0){
						//printPai(hand[handnum]);
						//printf(":");
						outflag++;
					}
					output[handnum][k]=j;
					k++;
					yukouhai[handnum]+= 4 - kind[j];
					//printPai(j);
					//printf(" ");
				}
				pai[i]=temp;
			}
		}
		output[handnum][k]=-1;
		if(outflag==1)
			//printf("\n");
loop_exit: ;
	}
	int index[14]={0,1,2,3,4,5,6,7,8,9,10,11,12,13};
	for(i=0;i<handnum;i++){
		for(j=handnum;j>i;j--){
			if(yukouhai[j]>yukouhai[j-1]){
				temp = yukouhai[j];
				yukouhai[j]=yukouhai[j-1];
				yukouhai[j-1]=temp;

				temp=index[j];
				index[j]=index[j-1];
				index[j-1]=temp;
			}
		}
	}
	for(i=0;i<handnum+1;i++){
		printPai(hand[index[i]]);
		printf(":");
		for(j=0;output[index[i]][j]!=-1;j++){
			printPai(output[index[i]][j]);
			printf(" ");
		}
		printf("%d枚\n",yukouhai[i]);
	}
}
void mainYukouhai(int s){
	int normal,standard,flag=0;
	normal = normalShanten();
	standard = titoiShanten();
	if(standard>kokushiShanten()){
		standard=kokushiShanten();
		flag++;
	}
	if(normal - standard == 1 || normal - standard == 0){
		printf("一般系%dシャンテン\n",normal);
		printf("標準形%dシャンテン\n",standard);
		flag++;
	}else{
		flag=0;
	}
	if(flag!=0){
		printf("一般系\n");
		calcYukouhai(normal,3);
		printf("\n");
		printf("標準形\n");
		calcYukouhai(standard,flag);
	}else{
		calcYukouhai(s,0);
	}
}

int main(){
	int Shanten=0;
	inputtehai();
	Shanten=mainShanten();
	printf("シャンテン数:%d\n",Shanten);
	mainYukouhai(Shanten);
	return 0;
}