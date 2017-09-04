import java.util.*;
public class algorithm{
	public int bestmove(ArrayList<Integer> set1,ArrayList<Integer> set2){
		int bestmove = 1;
		int val = -100;
		for(int i = 1; i <= 9; i++){
			if(!(set1.contains(i) || set2.contains(i))){
				set1.add(i);
				int moveres = minimax(set1,set2,0,false);
				set1.remove(set1.size()-1);
				System.out.println("\n\n\n\n best!!  "+ moveres);
				if(moveres > val){
					val = moveres;
					bestmove = i;
				}
			}
		}
		return bestmove;
	}
	private int minimax(ArrayList<Integer> set1,ArrayList<Integer> set2, int depth, boolean comp){
		int score; 
		boardtracker c = new boardtracker();
		String res = c.checkWin(set1,set2);
		if(res.equals("player1")){
			return 10-depth;
		}else if(res.equals("player2")){
			return -10+depth;
		}else if(res.equals("None")){
			score = 0;
		}else return 0;
		if(comp){
			int best = -100;
			for(int i = 1 ; i <= 9; i++){
				if(!(set1.contains(i) || set2.contains(i))){
					set1.add(i);
					best = Math.max(best,minimax(set1,set2,depth+1, !comp));
					set1.remove(set1.size()-1);
				}
			}
			return best;
		}else{
			int best = 100;
			for(int i = 1 ; i <= 9; i++){
				if(!(set1.contains(i) || set2.contains(i))){
					set2.add(i);
					best = Math.min(best,minimax(set1,set2,depth+1,!comp));
					set2.remove(set2.size()-1);
				}
			}
			return best;
		}
	}
}