import java.util.ArrayList;
import java.util.Random;
import mypackage.Pai;
public class Board{
	ArrayList<Integer> yama = new ArrayList<Integer>(136);
	ArrayList<Integer> doraomote = new ArrayList<Integer>(5);
	ArrayList<Integer> doraura = new ArrayList<Integer>(5);
	/*yama[0]~yama[121]までが山でyama[122]~yama[135]までが王牌
	**リンシャン牌はyama[122]~yama[125]までであるべきだが、簡単のため次のツモをリンシャン牌として考える
	**つまりyama[122]~yama[125]は使用されない
	**ドラはyama[126]~yama[130]が表yama[131]~yama[135]が裏
	*/
	int[] pai = new int[40];
	int num_tsumo=0;
	int sumkan=0;
	public int getpai(){
		if(num_tsumo>121)
			return -1;
		int p;
		num_tsumo++;
		p=yama.get(0);
		return yama.remove(0);
	}
	private int setPai(){
		Random rnd = new Random();
		while(true){
			int select = rnd.nextInt(40);
			//printf("test %d%c",select%9+1,classifyKind(select));
			if(!(select==0||select==1||select == 11||select==12||select==22||select==23)){
				if(this.pai[select]<4){
					this.pai[select]++;
					return select;
				}
			}

		}
	}
	public void addkan(){
		this.sumkan++;
		doraomote.add(yama.get(126+sumkan));
		doraura.add(yama.get(131+sumkan));
	}
	public void printDora(){
		System.out.print("ドラ表示牌:");
		int i;
		for(i=0;i<doraomote.size();i++){
			System.out.print(Pai.stringPai(doraomote.get(i))+" ");
		}
		System.out.print("\n");
	}

	Board(){
		int i;
		for(i=0;i<40;i++){
			this.pai[i]=0;
		}
		for(i=0;i<136;i++){
			this.yama.add(setPai());
		}
		doraomote.add(yama.get(126));
		doraura.add(yama.get(131));
	}
}