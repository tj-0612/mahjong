import mypackage.Pai;
public class Game{
	Player[] player=new Player[4];
	Board b;
	int bahuu;
	private void initialize(){
		int i,j,jihuu;
		b = new Board();
		for(i=0;i<4;i++){
			for(j=0;j<13;j++){
				player[i].hand.myhand[j]=b.getpai();
			}
			player[i].hand.sortMyHand();
		}
	}

	public void playGame(){
		int i,j,sutehai;
		boolean end_flag=false;
		boolean[] naki_flag=new boolean[4];
		int[] naki=new int[4];
		while(end_flag!=true){
			//鳴き処理
			int chiimati=-1;
			boolean skip_flag=false;
			for(j=0;j<4;j++){
				if(naki_flag[j]==true){
					skip_flag=true;
					if(naki[j]==2)
						chiimati=j;
					else {
						player[j].hand.naki(sutehai,naki[j]);
						if(naki[j]==3)
							player[i].tsumo(b.getpai());
						sutehai=player[i].hand.select(true);
						chiimati=-1;
						break;
					}
				}
			}
			if(chiimati!=-1){
				player[chiimati].hand.naki(sutehai,naki[chiimati],player[chiimati].hand.chiireserve);
			}


			if(skip_flag==false){
				player[i].tsumo(b.getpai());
				sutehai=player[i].hand.select(false);
				printBoard();
			}

			for(j=0;j<4;j++){
				if(j!=i){
					if(player[j].hand.ableToNaki(sutehai)==true){
						naki_flag[i] = true;
						naki[j]=player[j].nakiselect(sutehai);
					}else{
						naki[j]=-1;
						naki_flag[i] = false;
					}
				}
			}
			i++;
			if(i==4)
				i=0;
		}
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
		}


	}
}