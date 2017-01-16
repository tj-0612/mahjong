import mypackage.Pai;
public class Game{
	Player[] player=new Player[4];
	Board b;
	int bahuu=0;
	int kyokunum=1;
	int honba=0;
	private void initialize(){
		int i,j,jihuu;
		b = new Board();
		for(i=0;i<4;i++){
			for(j=0;j<13;j++){
				player[i].hand.myhand[j]=b.getpai();
			}
			player[i].hand.num_hand++;
			player[i].hand.sortMyHand();
			player[i].hand.num_hand--;
			player[i].hand.mainShanten();
		}
	}
	public void printBoard(int player){
		String s;
		if(bahuu==0)
			s="東";
		else
			s="南";
		System.out.print("\n");
		System.out.println(s+kyokunum+"局　"+honba+"本場");
		b.printDora();
		int i;
		for(i=0;i<4;i++){
			if(i==player){
				System.out.println("*********************");
			}
			this.player[i].printPlayer();
			if(i==player){
				System.out.println("*********************");
			}
		}
	}
	public boolean endCheck(){
		int i;
		for(i=0;i<4;i++){
			if(player[i].hand.shanten==-1){
				return true;
			}
		}
		return false;
	}

	//1ポン2チー3カン
	public void playGame(){
		int i=0,j,sutehai=-1,suteseki=-1;
		boolean[] naki_flag=new boolean[4];
		int[] naki=new int[4];
		while(endCheck()==false){
			//鳴き処理
			int chiimati=-1;
			boolean skip_flag=false;
			for(j=0;j<4;j++){
				if(naki_flag[j]==true){
					if(naki[j]==2)	//鳴きがチーの時
						chiimati=j;
					else {
						//ポン,カンの時
						player[j].hand.naki(sutehai,naki[j]);
						if(naki[j]==3){	//鳴きがカンの時
							player[j].tsumo(b.getpai());
							b.addkan();
						}
						printBoard(i);
						sutehai=player[j].hand.select(true);
						skip_flag=true;
						chiimati=-1;
						suteseki=i;
						i=j;
						break;
					}
				}
			}
			//チー待ちがいてポンカンがいない時
			if(chiimati!=-1){
				player[chiimati].hand.naki(sutehai,naki[chiimati],player[chiimati].hand.chiireserve);
				printBoard(i);
				sutehai=player[chiimati].hand.select(true);
				skip_flag=true;
				suteseki=i;
				i=j;
			}

			//鳴きなし
			if(skip_flag==false){
				player[i].tsumo(b.getpai());
				printBoard(i);
				sutehai=player[i].hand.select(false);
				suteseki=i;
			}

			printBoard(i);

			//鳴きチェックと鳴き選択
			for(j=0;j<4;j++){
				naki[j]=player[j].nakiselect(sutehai,player[i].id);
				if(naki[j]!=0){
					naki_flag[j]=true;
				}else{
					naki[j]=-1;
					naki_flag[j] = false;
				}
			}

			i++;
			if(i==4)
				i=0;
		}
	}
	public void printAgari(){

	}

	public static void main(String args[]){
		Game g = new Game();
		int i,j;
		for(i=0;i<4;i++){
			g.player[i]=new Player(i);
		}

		while(true){
			g.initialize();
			g.playGame();
			g.printAgari();
		}
	

	}
	Game(){}
}