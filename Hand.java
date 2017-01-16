import java.util.ArrayList;
import java.util.Scanner;
import mypackage.Pai;

public class Hand{
	int[] myhand=new int[14];
	int num_hand=13;
	int shanten;
	int naki=0;
	int agariform;
	ArrayList<Integer> sutehai=new ArrayList<Integer>();
	int junme;
	int kan;
	int chiireserve=0;

	boolean richi=false;
	private int[] kindMyHand = new int[40];

	public void printHand(){
		int i;
		int sukima=0;
		System.out.print("捨て牌");
		for(i=0;i<sutehai.size();i++){
			if(i%6==0)
				System.out.print("\n");
			System.out.print(Pai.stringPai(sutehai.get(i))+"　");
		}
		System.out.print("\n");
		for(i=0;i<num_hand;i++){
			System.out.print(Pai.stringPai(myhand[i]));
		}
		if(naki>0){
			if(myhand[num_hand]==40)
				sukima=1;
			for(i=0;i<naki;i++){
				System.out.print(" "+Pai.stringPai(myhand[num_hand+sukima+3*i])
					+Pai.stringPai(myhand[num_hand+sukima+3*i+1])
					+Pai.stringPai(myhand[num_hand+sukima+3*i+2]));
			}
		}
		System.out.print("\n");
		System.out.println("シャンテン数:"+this.shanten);
	}
	public int select(boolean naki){
		int sutehai=-1;
		if(richi==true){
			sutehai = myhand[num_hand-1];
			num_hand--;
			return sutehai;
		}else{
			if(shanten==0 && naki==false && this.naki==0){
				System.out.println("リーチしますか");
				Scanner sc = new Scanner(System.in);
				try{
					int in = Integer.parseInt(sc.next());
					if(in == '1'){
						richi=true;
					}
				}catch(Exception e){
					System.out.println("error");
				}

				sc = new Scanner(System.in);
				try{
					int in = Integer.parseInt(sc.next());
					if(in>num_hand){
						in = num_hand;
					}
					sutehai=myhand[in-1];
					this.sutehai.add(sutehai);
					myhand[in-1]=myhand[num_hand-1];
					myhand[num_hand-1]=40;
					sortMyHand();
					num_hand--;
				}catch (Exception e) {
					System.out.println("error");
				}

			}else{
				Scanner sc = new Scanner(System.in);
				try{
					int in = Integer.parseInt(sc.next());
					if(in>num_hand){
						in = num_hand;
					}
					sutehai=myhand[in-1];
					this.sutehai.add(sutehai);
					myhand[in-1]=myhand[num_hand-1];
					myhand[num_hand-1]=40;
					sortMyHand();
					num_hand--;
				}catch (Exception e) {
					System.out.println("error1");
				}
			}
		}
		return sutehai;
	}
	public void naki(int sutehai,int... select){
		int i,count=0;
		switch(select[0]){
		case 1:
			for(i=0;i<num_hand-count;i++){
				if(count==2)
					break;
				if(sutehai==myhand[i]){
					myhand[i]=myhand[num_hand-1-count];
					myhand[num_hand-1-count]=sutehai;
					count++;
				}
			}
			myhand[num_hand]=sutehai;
			break;
		case 2:
			int flag1=0,flag2=0;
			for(i=0;i<num_hand-flag1-flag2;i++){
				if(flag1==1 && flag2==1)
					break;
				switch(select[1]){
				case 0:
					if(myhand[i]==sutehai-1 && flag1==0){
						flag1++;
						myhand[i]=myhand[num_hand-2];
						myhand[num_hand-2]=sutehai-1;
					}else if(myhand[i]==sutehai+1 && flag2==0){
						flag2++;
						myhand[i]=myhand[num_hand];
						myhand[num_hand]=sutehai+1;
					}
					break;
				case 1:
					if(myhand[i]==sutehai-2 && flag1==0){
						flag1++;
						myhand[i]=myhand[num_hand-2];
						myhand[num_hand-2]=sutehai-2;
					}else if(myhand[i]==sutehai-1 && flag2==0){
						flag2++;
						myhand[i]=myhand[num_hand-1];
						myhand[num_hand-1]=sutehai-1;
					}
					break;
				case 2:
					if(myhand[i]==sutehai+1 && flag1==0){
						flag1++;
						myhand[i]=myhand[num_hand-1];
						myhand[num_hand-1]=sutehai+1;
					}else if(myhand[i]==sutehai+2 && flag2==0){
						flag2++;
						myhand[i]=myhand[num_hand];
						myhand[num_hand]=sutehai+2;
					}
					 break;
				}
			}
			int j=select[1]+1;
			if(j==3)
				j=0;
			myhand[11+j]=sutehai;
			break;
		case 3:
			for(i=0;i<num_hand-count;i++){
				if(count==3)
					break;
				if(sutehai==myhand[i]){
					myhand[i]=myhand[num_hand-1-count];
					myhand[num_hand-1-count]=sutehai;
					count++;
				}
			}
			break;
		}
		num_hand-=2;
		this.naki++;
		sortMyHand();
	}

	public void sortMyHand(){
		int i,j,temp,flag;
		for(i=0;i<num_hand-1;i++){
			flag=0;
			for(j=0;j<num_hand-1 -(i+1);j++){
				if(myhand[j]>myhand[j+1]){
					temp=myhand[j];
					myhand[j]=myhand[j+1];
					myhand[j+1]=temp;
					flag=1;
				}
			}
			if(flag==0)
				break;
		}
	}
	private int mentu;
	private int toitu;
	private int tatsu;
	private int tatsuCut(int j){
		int tempshanten=8;
		int i;
		for(i=j;i<40;i++){
			if(mentu+tatsu<4){
				if(kindMyHand[i]==2){
					tatsu++;
					kindMyHand[i]-=2;
					tempshanten=this.tatsuCut(i);
					kindMyHand[i]+=2;
					tatsu--;
				}
				if(i>32)
					break;
				else{
					if(kindMyHand[i]>=1&&kindMyHand[i+1]>=1&&i+1<=32){
						tatsu++;
						kindMyHand[i]--;
						kindMyHand[i+1]--;
						tempshanten=this.tatsuCut(i);
						kindMyHand[i]++;
						kindMyHand[i+1]++;
						tatsu--;
					}
					if(kindMyHand[i]>=1&&kindMyHand[i+2]>=1&&i+2<=32){
						tatsu++;
						kindMyHand[i]--;
						kindMyHand[i+2]--;
						tempshanten=this.tatsuCut(i);
						kindMyHand[i]++;
						kindMyHand[i+2]++;
						tatsu--;
					}
				}
			}
		}
		int temp = 8-(mentu+naki)*2-tatsu-toitu;
		if(tempshanten>temp)
			tempshanten=temp;
		return tempshanten;
	}
	private int mentuCut(int j){
		int tempshanten=8;
		int i;
		for(i=j;i<40;i++){
			//刻子
			if(kindMyHand[i]>=3){
				mentu++;
				kindMyHand[i]-=3;
				tempshanten=this.mentuCut(i);
				kindMyHand[i]+=3;
				mentu--;
			}
			//順子
			if(i+2>32)
				break;
			else if(kindMyHand[i]>=1&&kindMyHand[i+1]>=1&&kindMyHand[i+2]>=1){
				mentu++;
				kindMyHand[i]--;
				kindMyHand[i+1]--;
				kindMyHand[i+2]--;
				tempshanten=this.mentuCut(i);
				mentu--;
				kindMyHand[i]++;
				kindMyHand[i+1]++;
				kindMyHand[i+2]++;
			}
		}
		tempshanten=this.tatsuCut(1);
		return tempshanten;
	}
	private int normalShanten(){
		mentu=naki;
		toitu=0;
		tatsu=0;

		int i;
		for(i=0;i<40;i++){
			kindMyHand[i]=0;
		}
		for(i=0;i<num_hand;i++){
			kindMyHand[myhand[i]]++;
		}

		int tempshanten=8;
		int tempshanten2=8;
		for(i=33;i<40;i++){
			if(kindMyHand[i]==4){
				tempshanten++;
				break;
			}
		}
		for(i=2;i<40;i++){
			if(kindMyHand[i]>=2){
				toitu++;
				kindMyHand[i]-=2;
				tempshanten=mentuCut(0);
				if(tempshanten2>tempshanten)
					tempshanten2=tempshanten;
				toitu--;
				kindMyHand[i]++;
			}
		}
		tempshanten=mentuCut(0);
		if(tempshanten2>tempshanten)
			tempshanten2=tempshanten;
		return tempshanten2;
	}
	private int kokushiShanten(){
		int tempshanten=13;
		int temp=-1;
		int toitu=0;
		if(naki!=0)
			return 14;
		int i;
		for(i=0;i<38;i++){
			kindMyHand[i]=0;
		}
		for(i=0;i<14;i++){
			if((myhand[i]<31&&(myhand[i]%11==0||myhand[i]%11==8)) || myhand[i]>=31){
				if(temp!=myhand[i]){
					temp=myhand[i];
					tempshanten--;
				}else if(toitu==0){
					toitu=1;
					tempshanten--;
				}
			}
		}
		return tempshanten;
	}
	private int titoiShanten(){
		if(naki!=0)
			return 14;
		toitu=0;
		int i;
		for(i=0;i<38;i++){
			kindMyHand[i]=0;
		}
		for(i=0;i<14;i++){
			kindMyHand[myhand[i]]++;
		}

		int tempshanten=6;
		for(i=0;i<38;i++){
			if(kindMyHand[i]>=2){
				toitu++;
				kindMyHand[i]-=2;
				tempshanten--;
			}
		}
		return tempshanten;
	}
	public void mainShanten(){
		int nshanten = normalShanten();
		int titoi = titoiShanten();
		int kokushi = kokushiShanten();
		this.agariform = 1;
		
		//シャンテン数の更新
		shanten=nshanten;
		if(shanten>titoi){
			this.agariform=2;
			this.shanten=titoi;
		}else if(shanten==-1&&(titoi==-1))
			this.agariform=4;
		if(shanten>kokushi){
			this.agariform=3;
			this.shanten=kokushi;
		}
	}


	Hand(){

	}
}