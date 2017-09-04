import java.util.*;
public class boardtracker{
	private ArrayList<Integer> player1 = new ArrayList<Integer>();
	private ArrayList<Integer> player2 = new ArrayList<Integer>();
	public void printBoard(){
		System.out.println("\n");
		for(int i = 0; i <= 6 ; i += 3){
			System.out.print("\t\t");
			for(int j = 1; j <= 3; j ++){
				if(player1.contains(i+j)){
					System.out.print("\tX\t");
				}else if(player2.contains(i+j)){
					System.out.print("\tO\t");
				}else{
					System.out.print("\t \t");
				}
				if(j < 3){
					System.out.print("|");
				}else System.out.println();
			}
			if(i < 6){
				System.out.print("\t\t------------------------------------------------\n");
			}
		}
	}
	public boolean setPlayerMove(int player, int square){
		if(square > 9 ||square< 1){
			System.out.println("Invalid move!");
			return false;
		}else{
			if(player == 1){
				if(!(player1.contains(square) || player2.contains(square))){
					player1.add(square);
					return true;
				} 
				else System.out.println("Invalid move!");
				return false;
			}else{
				if(!(player1.contains(square) || player2.contains(square))){
					player2.add(square);
					return true;
				} 
				else System.out.println("Invalid move!");
				return false;
			}
		} 
	}
	public ArrayList<Integer> getPlayer(int player){
		if(player == 1) return player1;
		else return player2;
	}
	public String checkWin(ArrayList<Integer> player1,ArrayList<Integer> player2){
		if((player1.contains(1) && player1.contains(2) && player1.contains(3))||(player1.contains(4) && player1.contains(5) && player1.contains(6))||(player1.contains(7) && player1.contains(8) && player1.contains(9))||(player1.contains(1) && player1.contains(5) && player1.contains(9))||(player1.contains(3) && player1.contains(5) && player1.contains(7))||(player1.contains(1) && player1.contains(4) && player1.contains(7))||(player1.contains(8) && player1.contains(5) && player1.contains(2))||(player1.contains(3) && player1.contains(6) && player1.contains(9))) return "player1";
		if((player2.contains(1) && player2.contains(2) && player2.contains(3))||(player2.contains(4) && player2.contains(5) && player2.contains(6))||(player2.contains(7) && player2.contains(8) && player2.contains(9))||(player2.contains(1) && player2.contains(5) && player2.contains(9))||(player2.contains(3) && player2.contains(5) && player2.contains(7))||(player2.contains(1) && player2.contains(4) && player2.contains(7))||(player2.contains(8) && player2.contains(5) && player2.contains(2))||(player2.contains(3) && player2.contains(6) && player2.contains(9))) return "player2";
		if(player1.size() + player2.size() == 9) return "Tie";
		return "None";
	}
}