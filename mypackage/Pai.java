package mypackage;

public class Pai{
	public String stringPai(int pai){
		char kind;
		int num;
		if(pai<=8){
			num=pai%11;
			kind='m';
		}
		else if(pai<=19){
			num=pai%11;
			kind='p';
		}
		else if(pai<=30){
			num=pai%11;
			kind='s';
		}
		else{
			num=pai-30;
			kind='z';
		}
		String s = String.valueOf(num)+kind;
		return s;
	}
	public Pai(){
	}
}