import java.util.Random;
public class Board{
	int[] yama=new int[136];
	/*yama[0]~yama[121]までが山でyama[122]~yama[135]までが王牌
	**リンシャン牌はyama[122]~yama[125]までであるべきだが、簡単のため次のツモをリンシャン牌として考える
	**つまりyama[122]~yama[125]は使用されない
	**ドラはyama[126]~yama[130]が表yama[131]~yama[135]が裏
	*/
	int[] pai=new int[38];
	int num_tsumo=0;
	public int getpai(){
		num_tsumo++;
		return yama[num_tsumo-1];
	}
	private int setPai(){
		Random rnd = new Random();
		while(true){
			int select = rnd.nextInt(37);
			//printf("test %d%c",select%9+1,classifyKind(select));
			if(!(select == 9||select==10||select==20||select==21)){
				if(this.pai[select]<4){
					this.pai[select]++;
					return select;
				}
			}

		}
	}
	public void makeYama(){
		int i;
		for(i=0;i<136;i++){
			this.yama[i]=setPai();
		}
	}

	Board(){
		int i;
		for(i=0;i<38;i++){
			this.pai[i]=0;
		}
		makeYama();
	}
}