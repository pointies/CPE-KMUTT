import java.util.Scanner;
import java.io.IOException;
import java.lang.System;

public class assign1 {

	static int getint(String msg, int min, int max) {
		int a = 0;
		boolean success = false;
		Scanner stdin = new Scanner(System.in);
		while (!success) {
			System.out.print(msg);
			try {
				a = stdin.nextInt();
				if (a >= min && a <= max)
					success = true;
				else
					System.out.printf("Input error, please enter between %d-%d\n", min, max);
			} 
			catch (Exception err) {
				System.out.printf("Input error, please enter between %d-%d\n", min, max);
				stdin.nextLine();
			}
		}
		return a;
	}

	static long factorial(long n, int count) {
		long x;
		if(n==0) { //base case
			System.out.printf("0! is base case return answer of 0! = 1\n");
			return 1;
		}
		else { //recursive case
			System.out.printf("***** Loop %d *****\n", count++);
			System.out.printf("%d! is recursive case. Answer = %d * recursion of %d!\n", n, n, n-1);
			System.out.printf("Recursion to calculate %d!\n", n-1);
			x = n * factorial(n-1, count);
			System.out.printf("Calculate %d! complete.\n", n-1);
			System.out.printf("Return answer from %d! = %d to calculate %d! = [%d * %d!] = %d * %d = %d\n", n-1, x/n, n, n, n-1, n, x/n, x);
			return x;
		}
	}
	
	public static void main(String[] args) {
		int n, count;
		long ans;
		char ch=0;
		Scanner in = new Scanner(System.in);
		System.out.printf("My Recursion Programs.\n");
		System.out.printf("Program calculate n! by recursion (n<=15)\n");
		do {
			count = 1;
			n = getint("Enter n = ", 0, 15);
			ans = factorial(n, count);
			if(n==0)
				System.out.printf("Calculate 0! complete.\n");
			System.out.printf("Complete calculation of %d!, answer = %d\n", n, ans);
			System.out.printf("press [y] to continue, others to exit.");
			if(in.hasNext())
				ch = in.next().charAt(0);
				System.out.print("------------------------------------------------------------------\n");
		} while (ch == 'y' || ch == 'Y');
		System.out.printf("End Program.\n");
		System.out.printf("Program writen by 63070501044 Parinda Kongwattanasin");
	}
}
