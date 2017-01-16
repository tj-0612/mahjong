import mypackage.Pai;
import java.util.Scanner;
public class Player{
	private static int tempid=0;
	int id;
	Hand hand;
	int jihuu; //0~3
	int point=25000;
	public void printPlayer(){
		switch(jihuu){
			case 0:
				System.out.print("東家");
				break;
			case 1:
				System.out.print("南家");
				break;
			case 2:
				System.out.print("西家");
				break;
			case 3:
				System.out.print("北家");
				break;
			default:
				return;
		}
		System.out.println("　点数:"+point);
		this.hand.printHand();
	}
	public void setJihuu(){
		jihuu++;
		jihuu = jihuu & 0x3;
	}
	public void tsumo(int tsumo){
		this.hand.myhand[hand.num_hand]=tsumo;
		hand.mainShanten();
		hand.num_hand++;
	}

	public boolean ronCheck(int nakuhai){
		int tempshanten=hand.shanten;
		boolean b;
		hand.myhand[hand.num_hand]=nakuhai;
		hand.mainShanten();
		if(hand.shanten==-1){
			b=true;
		}else{
			b=false;
		}
		hand.shanten=tempshanten;
		hand.myhand[hand.num_hand]=40;
		return b;
	}
	//ポン1チー2カン3ロン4
	public int nakiselect(int nakuhai,int seki){
		hand.chiireserve=0;
		int[] kindmyhand = new int[40];
		boolean ponflag=false,chiiflag=false,kanflag=false,ronflag=false;

		int i;
		if(seki == this.id)
			return 0;
		for(i=0;i<hand.num_hand;i++){
			kindmyhand[hand.myhand[i]]++;
		}

		if(id==((seki+1)&0x3) && nakuhai+2<=32 &&((kindmyhand[nakuhai-1]>=1&&kindmyhand[nakuhai+1]>=1) 
			|| (kindmyhand[nakuhai-2]>=1&&kindmyhand[nakuhai-1]>=1)
			|| (kindmyhand[nakuhai+1]>=1&&kindmyhand[nakuhai+2]>=1)) ){
			chiiflag=true;
		}
		if(kindmyhand[nakuhai]>=2){
			ponflag=true;
		}
		if(kindmyhand[nakuhai]==3){
			kanflag=true;
		}
		if(ronCheck(nakuhai)==true){
			ronflag=true;
		}

		if(chiiflag==false && ponflag==false && kanflag==false && ronflag==false){
			return 0;
		}

		System.out.print(this.id+":鳴きますか？(");
		if(ponflag==true){
			System.out.print("1:ポン ");
		}
		if(chiiflag==true){
			System.out.print("2:チー ");
		}
		if(kanflag==true){
			System.out.print("3:カン");
		}
		if(ronflag==true){
			System.out.print("4:ロン");
		}
		System.out.println(")");


		Scanner sc = new Scanner(System.in);
		try{
			int in = Integer.parseInt(sc.next());
			switch(in){
			case 1:
				if(ponflag==true)
					return 1;
				else
					return 0;
			case 2:
				if(chiiflag==true){
					int[] nakicase={-1,-1,-1};
					//13 2
					if(kindmyhand[nakuhai-1]>=1&&kindmyhand[nakuhai+1]>=1){
						nakicase[0]=nakuhai-1;
					}
					//12 3
					if(kindmyhand[nakuhai-2]>=1&&kindmyhand[nakuhai-1]>=1){
						nakicase[1]=nakuhai-2;
					}//1 23
					if(kindmyhand[nakuhai+1]>=1&&kindmyhand[nakuhai+2]>=1){
						nakicase[2]=nakuhai+1;
					}
					System.out.println("どれで鳴きますか");
					int j=0;
					for(i=0;i<3;i++){
						if(nakicase[i]!=-1){
							System.out.print(Pai.stringPai(nakicase[i])+" "+Pai.stringPai(nakicase[i]+1)+" "+Pai.stringPai(nakicase[i]+2));
							System.out.println(":"+i);
						}
					}
					sc = new Scanner(System.in);
					try{
						int select = Integer.parseInt(sc.next());
						if(select<3&&select>=0){
							if(nakicase[select]!=-1){
								hand.chiireserve=select;
								return 2;
							}
						}
						return 0;
					}catch (Exception e) {
						System.out.println("error");
					}
				}else
					return 0;
				break;
			case 3:
				if(kanflag==true)
					return 3;
				else
					return 0;
			case 4:
				if(ronflag==true)
					return 4;
				else
					return 0;
			default:
				return 0;
			}
		}catch(Exception e){
			e.printStackTrace();
			System.out.println("error");
		}
		return 0;
	}
	boolean ableToNaki(int nakuhai,int seki){
		int[] kindmyhand = new int[40];
		int i;
		if(seki == this.id)
			return false;
		for(i=0;i<hand.num_hand;i++){
			kindmyhand[hand.myhand[i]]++;
		}
		if(id==((seki+1)&0x3) && nakuhai+2<=32 &&((kindmyhand[nakuhai-1]>=1&&kindmyhand[nakuhai+1]>=1) 
			|| (kindmyhand[nakuhai-2]>=1&&kindmyhand[nakuhai-1]>=1)
			|| (kindmyhand[nakuhai+1]>=1&&kindmyhand[nakuhai+2]>=1)) ){
			return true;
		}

		if(kindmyhand[nakuhai]>=2){
			return true;
		}
		return false;
	}
	Player(int jihuu){
		hand = new Hand();
		id=tempid;
		tempid++;
		this.jihuu=jihuu;
	}
}