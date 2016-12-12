#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
シャンテン数(一般系とチートイ)+のバグ
上がり時のセグフォ
*/
#define MAX_PAI 136
#define WANPAI 14
#define YAKUSTRLEN 30
#define YAKUMAX 23
enum Mentu{
	/*
	PON
	CHII,
	ANKAN,
	MINKAN,
	*/
	ANKO=0,
	SHUNTU,
	TOITU
};
enum Yaku{
	DABURI=0,
	RICHI,
	IPPATSU,
	TSUMO,
	HAITEI,
	RINSHANTSUMO,
	PINFU,
	TANYAO,
	IPEKO,
	YAKUHAI,
	SANSHOKUDOUJUN,
	SHANSHOKUDOUKO,
	ITTSU,
	SANANKO,
	TYANTA,
	TOITOI,
	HONITSU,
	JUNCHAN,
	RYANPE,
	HONROTO,
	SHOUSANGEN,
	CHINITSU
};
struct Agariyaku{
	int han;
	char yakuname[YAKUSTRLEN];
};
struct ConstitutionAgari{
	int kiriwake[10];
	int p_kiriwake;
	int tsumo;
	struct Agariyaku *yaku; //飜数
	int sumhan;
	int toitu[7]; //チートイ
	int kokushi[14]; //国士
	int Hand[38];
};

struct Myshanten
{
	int mentu;
	int toitu;
	int tatsu;
	int shanten;
	int tempMyHand[34];
	int kindMyHand[38];
	/*マンズ0~8
	ピンズ11~19
	ソーズ22~30
	字牌31~37
	9m1p2sでメンツにならないようにするため
	*/
};
int setPai();
void makeBoard();
void printBoard();
char classifyKind(int Pai);
void sortMyHand(int size);
int agari();
//int endJudge();
int judgecolor(int p);
int convert(int kind);
struct Myshanten ini_shanten();
int titoiShanten();
int kokushiShanten();
int normalShanten();
int mentuCut(struct Myshanten s,int i);
int tatsuCut(struct Myshanten s,int i);
int atamakiriwake();
int mentukiriwake(struct ConstitutionAgari ca);
void playGame();
void printagari(struct Agariyaku *yaku);
/*
マンズ:0~8
ピンズ:9~17
ソーズ:18~26
字牌:27~33 東南西北白発中の順
各種 4枚ずつ
*/
int pai[34];
int myHand[14];
int dora[5][2];//dora[0][0]をドラ表示牌、dora[0][1]をドラ表示牌の裏ドラ
int rinshan[4];
int suteHai[24];
int board[MAX_PAI-WANPAI];
int num_tsumo; //num_tsumo/4 = 実際の順目　つまりnum_tsumoは総ツモり数
int num_tehai;
int jihuu; //字風
int bahuu; //場風 1~4　東南西北の順
int agariform; //表示されたシャンテン数がどの形式の手か格納する 1:一般系 2:チートイ 3:国士 4:二盃口


//牌を乱数から生成する	
int setPai(){

	while(1){
		int select = rand()%34;
		//printf("test %d%c",select%9+1,classifyKind(select));
		if(pai[select]>0)
			return select;
	}
}
//初期化
void makeBoard(){
	int i,j;

	num_tsumo = 0; //0巡目に戻す
	num_tehai = 14;
	jihuu = 1;
	bahuu = 1;
	//全ての牌を４枚ずつ用意する
	for(i=0;i<34;i++){
		pai[i]=4;
	}
	

	//山
	board[0]=33;
	board[1]=33;
	board[2]=32;
	board[3]=32;
	board[4]=32;
	board[5]=31;
	board[6]=31;
	board[7]=31;
	board[8]=0;
	board[9]=0;
	board[10]=0;
	board[11]=8;
	board[12]=8;
	board[13]=8;
	for(j=0;j<14;j++){
		pai[board[j]]--;
	}
	i=14;
	while(i<MAX_PAI - WANPAI){
		int select = setPai();
		if(select != -1){
			board[i]=select;
			pai[select]--;
			printf("%d%c ",select%9+1,classifyKind(select));
			i++;
		}
	}
	printf("\n");
	//王牌を作る
	//ドラ表示牌と裏ドラ
	i=0;
	for(j=0;j<2;j++){
		printf("王牌\n");
		i=0;
		while(i<5){
			int select = setPai();
			if(select != -1){
				dora[i][j]=select;
				pai[select]--;
				printf("%d%c ",select%9+1,classifyKind(select));
				i++;
			}
		}
	}
	printf("\n");
	//リンシャン牌
	i=0;
	while(i<4){
		int select = setPai();
		if(select != -1){
			rinshan[i]=select;
			pai[select]--;
			printf("%d%c ",select%9+1,classifyKind(select));
			i++;
		}
	}
	printf("\n");


	//捨て牌の初期化
	for(i=0;i<24;i++){
		suteHai[i]=-1;
	}
	//手牌の生成
	for(i=0;i<14;i++){
		myHand[i]=board[i];
		num_tsumo++;
	}
	sortMyHand(num_tehai);
}
void printBoard(){
	int i,j;
	printf("王牌:\n");
	for(j=0;j<2;j++){
		for(i=0;i<7;i++){
			int p;
			if(i<2)
				p = rinshan[i*2+j];
			else
				p = dora[i-2][j];
			printf(" %d%c",p%9+1,classifyKind(p));
		}
		printf("\n");
	}
	printf("手牌:");
	for(i=0;i<14;i++){
		int p = myHand[i];
		printf("%d%c",p%9+1,classifyKind(p));
	}
	printf("(ツモ牌:%d%c)\n",board[num_tsumo-1]%9+1,classifyKind(board[num_tsumo-1]));
	printf("\n");
	printf("捨て牌");
	for(i=0;i<num_tsumo-14;i++){
		if(i%6==0)
			printf("\n");
		int p = suteHai[i];
		printf(" %d%c",p%9+1,classifyKind(p));
	}
	printf("\n");
}

char classifyKind(int Pai){
	int kind = (int)(Pai/9);
	if(kind == 0)
		return 'm';
	else if(kind == 1)
		return 'p';
	else if(kind == 2)
		return 's';
	else if(kind == 3)
		return 'z';
	else
		return '?';
}

void playGame(){
	int select;
	printf("何を切りますか（左から順に1~14の番号で指定してください）");
	scanf("%d",&select);
	if(select>14||select<1){
		printf("範囲外です\n");
		return;
	}
	else{
		suteHai[num_tsumo-14]=myHand[select-1];
		myHand[select-1]=38;
		sortMyHand(num_tehai);
		myHand[num_tehai-1] = board[num_tsumo];
		num_tsumo++;
	}
}

void sortMyHand(int size){
	int i,j,temp,flag;
	for(i=0;i<size;i++){
		flag=0;
		for(j=0;j<size-(i+1);j++){
			if(myHand[j]>myHand[j+1]){
				temp=myHand[j];
				myHand[j]=myHand[j+1];
				myHand[j+1]=temp;
				flag=1;
			}
		}
		if(flag==0)
			break;
	}
}/*
int endJudge(){
	if(num_tsumo==MAX_PAI-WANPAI)
		return 1;
	else if(agari()>1)
		return 1;
	else
		return 0;
}*/
int tatsuCut(struct Myshanten s,int i){
	for(;i<38;i++){
		if(s.mentu+s.tatsu<4){
			if(s.kindMyHand[i]==2){
				s.tatsu++;
				s.kindMyHand[i]-=2;
				s.shanten = tatsuCut(s,i);
				s.tatsu--;
				s.kindMyHand[i]+=2;
			}
			if(s.kindMyHand[i]>=1&&s.kindMyHand[i+1]>=1&&i+1<=30){
				s.tatsu++;
				s.kindMyHand[i]--;
				s.kindMyHand[i+1]--;
				s.shanten = tatsuCut(s,i);
				s.kindMyHand[i]++;
				s.kindMyHand[i+1]++;
				s.tatsu--;
			}
			if(s.kindMyHand[i]>=1&&s.kindMyHand[i+2]>=1&&i+2<=30){
				s.tatsu++;
				s.kindMyHand[i]--;
				s.kindMyHand[i+2]--;
				s.shanten = tatsuCut(s,i);
				s.kindMyHand[i]++;
				s.kindMyHand[i+2]++;
				s.tatsu--;
			}
		}
	}
	if(i>=38){
		int temp = 8 - s.mentu*2 - s.tatsu - s.toitu;
		if(s.shanten>temp)
			s.shanten=temp;
	}
	return s.shanten;
}
int mentuCut(struct Myshanten s,int i){
	for(;i<38;i++){
		if(s.kindMyHand[i]>=3){
			s.mentu++;
			s.kindMyHand[i]-=3;
			s.shanten=mentuCut(s,i);
			s.kindMyHand[i]+=3;
			s.mentu--;
		}
		if(s.kindMyHand[i]>=1&&s.kindMyHand[i+1]>=1
			&&s.kindMyHand[i+2]>=1&&i+2<=30){
			s.mentu++;
			s.kindMyHand[i]--;
			s.kindMyHand[i+1]--;
			s.kindMyHand[i+2]--;
			s.shanten=mentuCut(s,i);
			s.mentu--;
			s.kindMyHand[i]++;
			s.kindMyHand[i+1]++;
			s.kindMyHand[i+2]++;
		}
	}
	if(i>=38){
		s.shanten = tatsuCut(s,1);
	}
	return s.shanten;
}
int convert(int kind){
	if(kind>=0&&kind<=8)
		return kind;
	else if(kind>8&&kind<=17)
		return kind+2;
	else if(kind>17&&kind<=26)
		return kind+4;
	else
		return kind+4;
}
struct Myshanten ini_shanten(){
	struct Myshanten s;
	s.mentu=0;
	s.toitu=0;
	s.tatsu=0;
	s.shanten=8;
	int i;
	for(i=0;i<38;i++){
		if(i<34){
			s.tempMyHand[i]=0;
		}
		s.kindMyHand[i]=0;
	}
	for(i=0;i<14;i++){
		s.tempMyHand[i]=myHand[i];
		int kind = convert(myHand[i]);
		s.kindMyHand[kind]++;
	}
	return s;
}
int normalShanten(){
	int i;
	struct Myshanten s;
	int shanten=8;;
	s = ini_shanten();
	for(i=31;i<38;i++){
		if(s.kindMyHand[i]==4){
			s.shanten++;
			break;
		}
	}
	for(i=0;i<38;i++){
		if(s.kindMyHand[i]>=2){
			s.toitu++;
			s.kindMyHand[i]-=2;
			s.shanten=mentuCut(s,0);
			if(shanten>s.shanten)
				shanten=s.shanten;
			s.toitu--;
			s.kindMyHand[i]+=2;
		}
	}
	s.shanten=mentuCut(s,0);
	if(shanten>s.shanten)
		shanten=s.shanten;
	return shanten;
}

int titoiShanten(){
	struct Myshanten s;
	s = ini_shanten();
	s.shanten=6;
	int i;
	for(i=0;i<38;i++){
		if(s.kindMyHand[i]>=2){
			s.toitu++;
			s.kindMyHand[i]-=2;
			s.shanten--;
		}
	}
	return s.shanten;
}
int kokushiShanten(){
	struct Myshanten s;
	s = ini_shanten();
	int i;
	s.shanten=13;
	s.shanten -= (s.kindMyHand[0]>0) + (s.kindMyHand[8]>0) + (s.kindMyHand[11]>0)
				 + (s.kindMyHand[19]>0) + (s.kindMyHand[22]>0) + (s.kindMyHand[30]>0)
				 + (s.kindMyHand[31]>0) + (s.kindMyHand[32]>0) + (s.kindMyHand[33]>0) 
				 + (s.kindMyHand[34]>0) + (s.kindMyHand[35]>0) + (s.kindMyHand[36]>0) 
				 + (s.kindMyHand[37]>0);
	s.shanten -= (s.kindMyHand[0]==2) || (s.kindMyHand[8]==2) || (s.kindMyHand[11]==2)
				 + (s.kindMyHand[19]==2) || (s.kindMyHand[22]==2) || (s.kindMyHand[30]==2)
				 + (s.kindMyHand[31]==2) || (s.kindMyHand[32]==2) || (s.kindMyHand[33]==2) 
				 + (s.kindMyHand[34]==2) || (s.kindMyHand[35]==2) || (s.kindMyHand[36]==2) 
				 + (s.kindMyHand[37]==2);
	return s.shanten;
}
int mainShanten(){
	int shanten = normalShanten();
	int titoi = titoiShanten();
	int kokushi = kokushiShanten();
	agariform = 1;
	printf("シャンテン数:%d %d %d\n",shanten,titoi,kokushi);
	if(shanten>titoi){
		agariform=2;
		shanten=titoi;
	}else if(shanten==-1&&(titoi==-1))
		agariform=4;
	if(shanten>kokushi){
		agariform=3;
		shanten=kokushi;
	}
	printf("agariform : %d\n",agariform);
	return shanten;
}
int atamakiriwake(){
	int yaku;
	struct ConstitutionAgari ca;
	int flag;
	int i;
	int temp;
	//初期化
	ca.p_kiriwake=0;
	ca.tsumo=-1;
	for(i=0;i<38;i++){
		ca.Hand[i]=0;
	}
	for(i=0;i<10;i++){
		ca.kiriwake[i]=-1;
	}
	//ここまで
	for(i=0;i<14;i++){
		ca.Hand[convert(myHand[i])]++;
		if(i==13){
			ca.tsumo=convert(myHand[i]);
		}
	}
	//頭
	for(i=0;i<38;i++){
		if(ca.Hand[i]>=2){
			ca.Hand[i]-=2;
			ca.kiriwake[ca.p_kiriwake]= TOITU;
			ca.kiriwake[ca.p_kiriwake+1]=i;
			ca.p_kiriwake+=2;
			temp=mentukiriwake(ca);
			if(temp>yaku)
				yaku=temp;
			ca.p_kiriwake-=2;
			ca.Hand[i]+=2;
			ca.kiriwake[ca.p_kiriwake]= -1;
			ca.kiriwake[ca.p_kiriwake+1]=-1;
		}
	}
	return yaku;
}
int mentukiriwake(struct ConstitutionAgari ca){
	int yaku;
	int i;
	for(i=0;i<38;i++){
		if(ca.Hand[i]>=3){
			ca.Hand[i]-=3;
			ca.kiriwake[ca.p_kiriwake]=ANKO;
			ca.kiriwake[ca.p_kiriwake+1]=i;
			ca.p_kiriwake+=2;
			yaku=mentukiriwake(ca);
			ca.p_kiriwake-=2;
			ca.Hand[i]+=3;
			ca.kiriwake[ca.p_kiriwake]=-1;
			ca.kiriwake[ca.p_kiriwake+1]=-1;
			
		}
		if(ca.Hand[i]&&ca.Hand[i+1]&&ca.Hand[i+2]&&i<=30){
			ca.Hand[i]--; ca.Hand[i+1]--; ca.Hand[i+2]--;
			ca.kiriwake[ca.p_kiriwake]=SHUNTU;
			ca.kiriwake[ca.p_kiriwake+1]=i;
			ca.p_kiriwake+=2;
			yaku=mentukiriwake(ca);
			ca.p_kiriwake-=2;
			ca.Hand[i]++; ca.Hand[i+1]++; ca.Hand[i+2]++;
			ca.kiriwake[ca.p_kiriwake]=-1;
			ca.kiriwake[ca.p_kiriwake+1]=-1;
			
		}
	}
	if(ca.kiriwake[9]!=-1){
		int temp = agari(ca);


		if(temp>yaku)
			yaku = temp;
		return yaku;
	}else{
		return yaku;
	}
}
void strassign(char *str,char *in){
	int i=0;
	while(in[i]!='\0'){
		str[i]=in[i];
		i++;
	}
	str[i]='\0';
}
int yakuhai(struct ConstitutionAgari ca){
	int yaku=0;
	int i;
	for(i=0;i<=8;i+=2){
		if(ca.kiriwake[i]==ANKO /* && ca.kiriwake[i]==PON*/ ){
			if(ca.kiriwake[i+1]==31+jihuu-1)
				yaku++;
			if(ca.kiriwake[i+1]==31+bahuu-1)
				yaku++;
			if(ca.kiriwake[i+1]>=35)
				yaku++;
		}
	}
	return yaku;
}

int pinfu(struct ConstitutionAgari ca){
	int yaku=0;
	int i;
	if(ca.kiriwake[1]==31+jihuu-1 || ca.kiriwake[1]==31+bahuu-1 || ca.kiriwake[1]>=35)
		return yaku;
	for(i=2;i<=8;i+=2){
		if(ca.kiriwake[i]!=SHUNTU)
			return yaku;
		else if(ca.kiriwake[i+1] + 1 == ca.tsumo 
			|| (ca.kiriwake[i+1]%11==0 && ca.tsumo%11==2) 
			|| (ca.kiriwake[i+1]%11==6 && ca.tsumo%11==6)){
				return yaku;
		}
	}
	yaku=1;
	return yaku;
}
int tanyao(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	int i;
	for(i=0;i<14;i++){
		if(myHand[i]%9==0||myHand[i]%9==8||myHand[i]>=31)
			return yaku;
	}
	yaku=1;
	return yaku;
}
int ipeko(struct ConstitutionAgari ca){
	int yaku;

	yaku=0;
	if(agariform==4)
		return yaku;
	int i;
	for(i=3;i<=7;i+=2){
		if(ca.kiriwake[i]==ca.kiriwake[i+2] && ca.kiriwake[i-1]==ca.kiriwake[i+1]==SHUNTU){
			yaku=1;
			return yaku;
		}
	}
	return yaku;
}
int haitei(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	if(num_tsumo==MAX_PAI-WANPAI){
		yaku=1;
		return yaku;
	}
	else
		return yaku;
}
int toitoi(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	int i;
	for(i=2;i<=8;i+=2){
		if(ca.kiriwake[i]==SHUNTU)
			return yaku;
	}
	yaku=2;
	return yaku;
}
//食い下がりの実装をすること
int sanshokudoujun(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	int i,j;
	int temp;
	int flag;
	for(i=3;i<=5;i+=2){
		if(ca.kiriwake[i-1]==SHUNTU){
			temp=ca.kiriwake[i];
			flag = 0;
			for(j=i+2;j<=9;j++){
				if(temp + 11 ==ca.kiriwake[i] && ca.kiriwake[i-1]==SHUNTU){
					flag++;
					temp = ca.kiriwake[i];
				}
			}
		}
	}
	if(flag==2){
		yaku=2;
		return yaku;
	}
	else
		return yaku;
}
//食い下がり
int ittsu(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	int i;
	int color=-1;
	int num=0;
	for(i=3;i<=9;i+=2){
		if(ca.kiriwake[i]%11==num&&ca.kiriwake[i]<31&&ca.kiriwake[i-1]==SHUNTU){
			if(num==0){
				color = judgecolor(ca.kiriwake[i]);
				num+=3;
			}
			else if(color==judgecolor(ca.kiriwake[i])){
				num+=3;
			}
		}
		if(color!=judgecolor(ca.kiriwake[i])){
			color=judgecolor(ca.kiriwake[i]);
			num=0;
		}
	}
	if(num==9){
		yaku=2;	
	}
	return yaku;
}
int sananko(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	int i;
	int flag=0;
	for(i=2;i<=8;i+=2){
		if(ca.kiriwake[i] == ANKO /*||ca.kiriwake[i]==ANKAN*/)
			flag++;
	}
	if(flag==3){
		yaku=2;
		return yaku;
	}
	else
		return yaku;
}
int junchan(struct ConstitutionAgari ca);
int tyanta(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	int i;
	int temp;
	int flag=0;
	for(i=1;i<=9;i+=2){
		temp = ca.kiriwake[i]%11;
		if(temp!=0 && temp!=8 &&ca.kiriwake[i]<31){
			if(!(temp==6 && ca.kiriwake[i-1] ==SHUNTU))
				return yaku;
		}
		if(ca.kiriwake[i-1]==ANKO)
			flag++;
	}

	if(flag == 4||junchan(ca)>0)
		return yaku;
	else{
		yaku=2;
		return yaku;
	}
}
int sanshokudouko(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	int i,j;
	int temp;
	int flag;
	for(i=3;i<=5;i+=2){
		if(ca.kiriwake[i-1]==ANKO){
			temp=ca.kiriwake[i];
			flag = 0;
			for(j=i+2;j<=9;j++){
				if(temp + 11 ==ca.kiriwake[i] && ca.kiriwake[i-1]==ANKO){
					flag++;
					temp = ca.kiriwake[i];
				}
			}
		}
	}
	if(flag==2){
		yaku=2;
		return yaku;
	}
	else
		return yaku;
}
//マンズ1 ピンズ2 ソーズ3 字牌4
int judgecolor(int p){
	if(p>=0&&p<=8)
		return 1;
	else if(p>=11&&p<=19)
		return 2;
	else if(p>=22&&p<=30)
		return 3;
	else
		return 4;
}
int honitsu(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	int i;
	int color=-1;
	int temp;
	int flag = 0;
	for(i=1;i<=9;i+=2){
		temp = judgecolor(ca.kiriwake[i]);
		if(temp==4)
			flag=1;
		if(color==-1 && temp<=3)
			color = temp;
		else if(color!=0 && temp!=color && temp<=3)
			return yaku;
	}
	if(flag==1){
		yaku=3;
		return yaku;
	}else
	return yaku;
}
int junchan(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	int i;
	int temp;
	int flag=0;
	for(i=1;i<=9;i+=2){
		temp = ca.kiriwake[i]%11;
		if(ca.kiriwake[i]>=31)
			return yaku;
		if(temp!=0 && temp!=8 &&ca.kiriwake[i]<31){
			if(!(temp==6 && ca.kiriwake[i-1] ==SHUNTU))
				return yaku;
		}
		if(ca.kiriwake[i-1]==ANKO)
			flag++;
	}

	if(flag == 4)
		return yaku;
	else{
		yaku=3;
		return yaku;
	}
}
int ryanpe(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	if(agariform==4){
		yaku=3;
		return yaku;
	}
	else
		return yaku;
}
int shousangen(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	int i;
	int flag =0;
	if(ca.kiriwake[1]<35)
		return yaku;
	for(i=3;i<=9;i+=2){
		if(ca.kiriwake[i]>=35){
			flag++;
		}
	}
	if(flag==2){
		yaku=2;
		return yaku;
	}
	else
		return yaku;
}
int honroto(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	int i;
	int temp;
	int flag=0;
	
	if(!(ca.kiriwake[1]%11==0||ca.kiriwake[1]%11==9||ca.kiriwake[1]>=31))
		return yaku;
	for(i=3;i<=9;i+=2){
		temp = ca.kiriwake[i]%11;
		if(ca.kiriwake[i]>=31 || (ca.kiriwake[i-1]==ANKO&& (temp==0 || temp==8))){
			flag++;
		}
	}
	if(flag == 4){
		yaku=2;
		return yaku;
	}
	else
		return yaku;
}
int chinitsu(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	int i;
	int color=-1;
	int temp;
	for(i=1;i<=9;i+=2){
		temp = judgecolor(ca.kiriwake[i]);
		if(color==-1)
			color = temp;
		else if(color!=0 && temp!=color)
			return yaku;
		if(temp==4)
			return yaku;
	}
	yaku=6;
	return yaku;
}
int daburi(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	return yaku;
}
int richi(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	return yaku;
}
int tsumo(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	return yaku;
}
int ippatsu(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	return yaku;
}
int rinshantsumo(struct ConstitutionAgari ca){
	int yaku;
	yaku=0;
	return yaku;
}
int agari(struct ConstitutionAgari ca){
	int yaku = daburi(ca)+richi(ca)+tsumo(ca)+haitei(ca)+
	rinshantsumo(ca)+ippatsu(ca)+pinfu(ca)+tanyao(ca)+yakuhai(ca)+
	ipeko(ca)+sanshokudoujun(ca)+sanshokudouko(ca)+ittsu(ca)+
	sananko(ca)+tyanta(ca)+toitoi(ca)+honitsu(ca)+junchan(ca)+
	ryanpe(ca)+shousangen(ca)+honroto(ca)+chinitsu(ca);
	return yaku;
}
int titoi(){
	int i;
	int tanyaoflag=1,chinitsuflag=6,honitsuflag=3,honrotoflag=2;
	int color=-1;
	for(i=0;i<14;i++){
		if(myHand[i]%9==0||myHand[i]%9==8||myHand[i]>=31)
			tanyaoflag=0;

		if(myHand[i]<31&&color==-1)
			color=(int)(myHand[i]/9);
		if((int)(myHand[i]/9)!=color){
			chinitsuflag=0;
			if(myHand[i]<31){
				honitsuflag=0;
				break;
			}
		}

		if(myHand[i]<31&&(myHand[i]%9!=0||myHand[i]%9!=8))
			honrotoflag=0;
	}
	if(chinitsuflag==6)
		honitsuflag=0;
	return 2+tanyaoflag+chinitsuflag+honitsuflag+honrotoflag;
	
}

int main(){
	int yaku;
	srand((unsigned)+time(NULL));
	makeBoard();
	int shanten;
	while(1){
		sortMyHand(num_tehai-1);
		shanten = mainShanten();
		printf("シャンテン数：%d\n",shanten);
		if(shanten == -1){
			switch(agariform){
			case 1:
			case 4:
				yaku=atamakiriwake();
				break;
			case 2:
				yaku=titoi();
				break;
			/*
			case 3:
				kokushihogehoge();
				break;*/
			default:
				break;
			}
			break;
		}
		printBoard();
		playGame();
	}
	printf("役数 %d\n",yaku);
	printBoard();
	printf("和了\n");
	//free(yaku);
	return 0;

}