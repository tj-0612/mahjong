
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
		for(i=0;i<4;i++){
			player[i].tsumo(b.getpai());
			sutehai=player[i].hand.select();

			for(j=0;j<4;j++){
				if(j!=i){
					if(player[j].hand.ableToNaki(sutehai)==true){
						player[j].hand.naki(sutehai);
					}
				}
			}
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