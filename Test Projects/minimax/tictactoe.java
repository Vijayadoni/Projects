import java.util.*;
class tictactoe{
	boardtracker b = new boardtracker();
	algorithm comp = new algorithm();
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		System.out.println("Choose a game mode!\n1.Player vs Player\n2.Player vs Computer\n");
		int option = s.nextInt();
		tictactoe t = new tictactoe();
		switch(option){
			case 1: t.pvp(true,"none");
				break;
			case 2: t.pvp(false,"hard");
				break;
			default: System.out.println("please choose a valid option");
				break;
		}
	}
	private static boolean MakeMove(boardtracker b,int player, int square){
		if(b.setPlayerMove(player,square)) return true;
		else return false;
	} 
	private void pvp(boolean vspc,String mode){
		Scanner s = new Scanner(System.in);
		int count = 2;
		while(b.checkWin(b.getPlayer(1),b.getPlayer(2)).equals("None")){
			int turn = (count%2)+1;
			boolean flag = false;
			if(!vspc){
				if(turn == 1){
					flag = MakeMove(b,turn,comp.bestmove(b.getPlayer(1),b.getPlayer(2)));
				}else{
					System.out.println("player "+turn+"'s turn: ");
					int square = s.nextInt();
					flag = MakeMove(b,turn,square); 
				}
			}else{
				System.out.println("player "+turn+"'s turn: ");
				int square = s.nextInt();
				flag = MakeMove(b,turn,square);
			}
			if(flag) count++;
			b.printBoard();
		}
		if(!b.checkWin(b.getPlayer(1),b.getPlayer(2)).equals("Tie")) System.out.println(b.checkWin(b.getPlayer(1),b.getPlayer(2)) + " wins!");
		else System.out.println("Game Tied!");
	}

}
