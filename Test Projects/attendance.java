import java.util.*;
class attendance{
	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		String[] str = s.nextLine().split(" ");
		int[] list = new int[10];
		int max = 0;
		
		int x2 = 0;
		for(int i = 0; i < str.length;i++) {
			list[i]=Integer.parseInt(str[i]);
			x2 = x2 ^ list[i];
		}
		
		String temp;
		int x1 = 0;
		while(true){
			String x = s.nextLine();
			if(x.equals("end") ) break;
			int y = Integer.parseInt(x);
			x1 = x1^y;
		}
		int k = x1^x2;
		System.out.println(k);
	}
}