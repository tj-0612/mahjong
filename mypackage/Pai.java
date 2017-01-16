package mypackage;
/*
	1~9m:2~10
	1~9p:13~21
	1~9s:24~32
	1~7z:33~39
*/
public class Pai{
	public static int intPai(int i,char c){
		if(i<0||i>9){
			return -1;
		}
		switch(c){
		case 'm':
			return i+1;
		case 'p':
			return i+12;
		case 's':
			return i+23;
		case 'z':
			if(i>7)
				return -1;
			else
				return i+32;
		default:
			return -1;
		}
	}
	public static String stringPai(int pai){
		char kind;
		int num;
		if(pai==0){
			num=0;
			kind='?';
		}
		else if(pai<=10){
			num=pai%11-1;
			kind='m';
		}
		else if(pai<=21){
			num=pai%11-1;
			kind='p';
		}
		else if(pai<=32){
			num=pai%11-1;
			kind='s';
		}
		else{
			num=pai-32;
			kind='z';
		}
		String s = String.valueOf(num)+kind;
		return s;
	}
	public Pai(){
	}
}