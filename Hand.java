import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Hand{
	int[] myhand=new int[14];
	int num_hand=14;
	int shanten;
	int naki=0;
	int agariform;
	int[] sutehai=new int[24];
	int junme;
	int kan;
	boolean richi;


	public int tsumogiri(){
		int sutehai;
		sutehai = myhand[num_hand-1];
		return sutehai;
	}
	public int select(){
		int sutehai;
		if(richi==true){
			sutehai=this.tsumogiri();
		}else{
			if(shanten==0 && naki==0){
				System.out.println("リーチしますか");
				InputStreamReader reader = new InputStreamReader(System.in);
				try{
					int in = reader.read();
					if(in == '1'){
						richi=true;
					}
				}catch(Exception e){

				}
				BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
				try{
					int in = Integer.parseInt(br.readLine());

					if(in>num_hand){
						in = num_hand;
					}
					sutehai=myhand[in-1];
					myhand[in-1]=myhand[num_hand-1];
					myhand[num_hand-1]=38;
					sortMyHand();
				}catch (Exception e) {
				}

			}
		}
		return sutehai;
	}
	public int naki(){
		InputStreamReader reader = new InputStreamReader(System.in);
		System.out.println("鳴きますか？(１：ポン　２：チー ３：カン");
		try{
			int in = reader.read();
			switch(in){
			case '1':

			case '2':
			case '3':
			default:
			}
		}catch(Exception e){
			e.printStackTrace();
		}
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
	private int[] kindMyHand = new int[38];
	private int tatsuCut(int i){
		int tempshanten;
		for(;i<38;i++){
			if(mentu+tatsu<4){
				if(kindMyHand[i]==2){
					tatsu++;
					kindMyHand[i]-=2;
					tempshanten=tatsuCut(i);
					kindMyHand[i]+=2;
					tatsu--;
				}
				if(kindMyHand[i]>=1&&kindMyHand[i+1]>=1&&i+1<=30){
					tatsu++;
					kindMyHand[i]--;
					kindMyHand[i+1]--;
					tempshanten=tatsuCut(i);
					kindMyHand[i]++;
					kindMyHand[i+1]++;
					tatsu--;
				}
				if(kindMyHand[i]>=1&&kindMyHand[i+2]>=1&&i+2<=30){
					tatsu++;
					kindMyHand[i]--;
					kindMyHand[i+2]--;
					tempshanten=tatsuCut(i);
					kindMyHand[i]++;
					kindMyHand[i+2]++;
					tatsu--;
				}
			}
		}
		int temp = 8-mentu*2-tatsu-toitu;
		if(tempshanten>temp)
			tempshanten=temp;
		return tempshanten;
	}
	private int mentuCut(int i){
		int tempshanten;
		for(;i<38;i++){
			//刻子
			if(kindMyHand[i]>=3){
				mentu++;
				kindMyHand[i]-=3;
				tempshanten=mentuCut(i);
				kindMyHand[i]+=3;
				mentu--;
			}
			//順子
			if(kindMyHand[i]>=1&&kindMyHand[i+1]>=1&&kindMyHand[i+2]>=1&&
				i+2<=30){
				mentu++;
				kindMyHand[i]--;
				kindMyHand[i+1]--;
				kindMyHand[i+2]--;
				tempshanten=mentuCut(i);
				mentu--;
				kindMyHand[i]++;
				kindMyHand[i+1]++;
				kindMyHand[i+2]++;
			}
		}
		if(i>=38)
			tempshanten=tatsuCut(1);
		return tempshanten;
	}
	private int normalShanten(){
		int i;
		int tempshanten=8;
		int tempshanten2=8;
		for(i=31;i<38;i++){
			if(kindMyHand[i]==4){
				tempshanten++;
				break;
			}
		}
		for(i=0;i<38;i++){
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
	public int mainShanten(){
		int nshanten = normalShanten();
		int titoi = titoiShanten();
		int kokushi = kokushiShanten();
		this.agariform = 1;
		System.out.println("シャンテン数:"+nshanten+" "+titoi+" "+kokushi);
		if(shanten>titoi){
			this.agariform=2;
			this.shanten=titoi;
		}else if(shanten==-1&&(titoi==-1))
			this.agariform=4;
		if(shanten>kokushi){
			this.agariform=3;
			this.shanten=kokushi;
		}
		System.out.println("agariform :"+agariform);
	}
	boolean ableToNaki(int pai){
		return false;
	}

	public Hand(){

	}
}