import java.util.*;
class spiral{
	static point[][] p = new point[10][10];
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		System.out.println("Enter matrix size (n,m)");
		String[] st = s.nextLine().split(",");
		int n = Integer.parseInt(st[0]);
		int m = Integer.parseInt(st[1]);
		for(int i = 0; i < n; i++){
			System.out.println("Enter "+ i + "th row elements:  ");
			String[] temp = s.nextLine().split(" ");
			for(int j =0; j < m ; j++){
				p[i][j] = new point();
				p[i][j].setData(Integer.parseInt(temp[j]));
			}	
		}
		printSpiral(0,0);
	}
	static void printSpiral(int i , int j){
		if(i >= 0 && j >= 0 ){	
			if(p[i][j] == null || p[i][j].checkHit())return;
			p[i][j].setHit();
			System.out.print(p[i][j].getData()+" ");
			if(i > 0 && (p[i-1][j] == null || p[i-1][j].checkHit())|| i == 0) printSpiral(i,j+1);
			printSpiral(i+1,j);
			printSpiral(i,j-1);
			printSpiral(i-1,j);
		}else return;
	}
}
class point{
	boolean hit = false;
	int data;
	public void setData(int data){
		this.data = data;
	}
	public int getData(){
		return this.data;
	}
	public boolean checkHit(){
		return this.hit;
	}
	public void setHit(){
		this.hit = true;
	}
}