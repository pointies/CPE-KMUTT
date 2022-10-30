import java.util.Comparator;

public class info {
	int id;
	long num;
	String str1,str2; 

	public int compareTo(info x) {
		if(num - x.num > 0)
			return 1;
		else if(num - x.num == 0)
			return 0;
		else
			return -1;
	}
	
	public info() {
		
	}
	
	public info(int a, long b,String c,String d) {
		id = a;
		num = b;
		str1 = c;
		str2 = d;
	}
	
	public void printData() {
		System.out.printf("%6d %d %s %s\n", id, num, str1, str2);
	}
}

class CmpNum implements Comparator<info> {
	
	public int compare(info x, info y) {
		if(x.num == y.num)
			return 0;
		else if(x.num > y.num)
			return 1;
		else
			return -1;
	}
}

class CmpStr implements Comparator<info> {
	
	public int compare(info x, info y) {
		return (int) x.str2.compareToIgnoreCase(y.str2);
	}
}