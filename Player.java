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
	Player(int jihuu){
		hand = new Hand();
		this.jihuu=jihuu;
	}
}