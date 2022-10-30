public class info {
	int id;
	long num;
	String str1,str2; 

	public info() {
		
	}
	public info(int a, long b,String c,String d) {
		id = a;
		num = b;
		str1 = c;
		str2 = d;
	}
	public void printData() {
		System.out.printf("%6d %d %s %s\n",id,num,str1,str2);
	}
}