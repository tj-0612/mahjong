import mypackage.Pai;
import java.io.InputStreamReader;
public class Player{
	Hand hand;
	int jihuu; //0~3
	int point=25000;
	public void setJihuu(){
		jihuu++;
		jihuu = jihuu & 0x3;
	}
	public void tsumo(int tsumo){
		this.hand.myhand[hand.num_hand-1]=tsumo;
		hand.mainShanten();
	}
	//ポン1チー2カン3
	public int nakiselect(int nakuhai){
		hand.chiireserve=0;
		int[] kindmyhand = new int[38];
		int i;
		for(i=0;i<hand.num_hand;i++){
			kindmyhand[hand.myhand[i]]++;
		}
		InputStreamReader reader = new InputStreamReader(System.in);
		System.out.println("鳴きますか？(１：ポン　２：チー ３：カン");
		try{
			int in = reader.read();
			switch(in){
			case '1':
				if(kindmyhand[nakuhai]>=2)
					return 1;
				else
					return 0;
			case '2':
				if((kindmyhand[nakuhai-1]>=1&&kindmyhand[nakuhai+1]>=1) 
					|| (kindmyhand[nakuhai-2]>=1&&kindmyhand[nakuhai-1]>=1)
					|| (kindmyhand[nakuhai+1]>=1&&kindmyhand[nakuhai+2]>=1) ){
					int[] nakicase={-1,-1,-1};

					if(kindmyhand[nakuhai-1]>=1&&kindmyhand[nakuhai+1]>=1){
						nakicase[0]=nakuhai-1;
					}
					if(kindmyhand[nakuhai-2]>=1&&kindmyhand[nakuhai-1]>=1){
						nakicase[1]=nakuhai-2;
					}
					if(kindmyhand[nakuhai+1]>=1&&kindmyhand[nakuhai+2]>=1){
						nakicase[2]=nakuhai+1;
					}
					System.out.println("どれで鳴きますか");
					int j=0;
					for(i=0;i<3;i++){
						if(nakicase[i]!=-1){
							j++;
							Pai p = new Pai();
							System.out.print(p.stringPai(nakicase[i])+" "+p.stringPai(nakicase[i]+1)+" "+p.stringPai(nakicase[i]+2));
							System.out.println(":"+j);
						}
					}
					reader = new InputStreamReader(System.in);
					try{
						int select = reader.read()-'0';
						if(select>j||select<=0){
							return 0;
						}else{
							hand.chiireserve=select;
							return 1;
						}
					}catch (Exception e) {
					}
				}else
					return 0;
				break;
			case '3':
				if(kindmyhand[nakuhai]==3)
					return 2;
				else
					return 0;
			default:
				return 0;
			}
		}catch(Exception e){
			e.printStackTrace();
		}
		return 0;
	}
	Player(int jihuu){
		hand = new Hand();
		this.jihuu=jihuu;
	}
}