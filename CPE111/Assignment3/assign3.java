import java.util.Arrays;
import java.util.Comparator;

public class assign3 {

	public static void main(String[] args) {
		int max = 100000;
		long begin, end;
		double time[][] = new double[5][2];
		
		DataArray raw = new DataArray(max);
		DataArray test = new DataArray(max);
		DataArray temp = new DataArray(max);
		
		if(raw.Load_File("D:\\CPE111\\Assignment2\\test.csv")>0)
		{
			System.out.println("Sorting Comparison Program.");
			System.out.println("Total read "+raw.count+" records.");
			
			/* Arrays.sort */
			//number
			test.data = raw.data.clone();
			begin = System.nanoTime();
			Arrays.sort(test.data, new CmpNum());
			end = System.nanoTime();
			time[0][0] = (end-begin)/1E6;
			
			//string
			test.data = raw.data.clone();
			begin = System.nanoTime();
			Arrays.sort(test.data, new CmpStr());
			end = System.nanoTime();
			time[0][1] = (end-begin)/1E6;
			
			/* Merge Sort */
			//number
			test.data = raw.data.clone();
			time[1][0] = test.mergeSort_number(temp.data, 0, max-1);
			
			//string
			test.data = raw.data.clone();
			time[1][1] = test.mergeSort_string(temp.data, 0, max-1);
			
			/* Partition Sort */
			//number
			test.data = raw.data.clone();
			time[2][0] = test.partition_number(0, max-1);
			
			//string
			test.data = raw.data.clone();
			time[2][1] = test.partition_string(0, max-1);
			
			/* Middle Pivot Sort */
			//number
			test.data = raw.data.clone();
			time[3][0] = test.midPivot_number(0, max-1);
			
			//string
			test.data = raw.data.clone();
			time[3][1] = test.midPivot_string(0, max-1);
			
			printOutput(time);
			
			/*
			System.out.print("data[0] \t"+test.data[0].id+" "+test.data[0].num+" "+test.data[0].str1+" "+test.data[0].str2);
			System.out.print("data[49999] \t"+test.data[49999].id+" "+test.data[49999].num+" "+test.data[49999].str1+" "+test.data[49999].str2);
			System.out.print("data[99999] \t"+test.data[99999].id+" "+test.data[99999].num+" "+test.data[99999].str1+" "+test.data[99999].str2);
			*/
	}
		else
			System.out.println("Error");
	}
	
	public static void printOutput(double time[][]) {
		String [] str = new String[] {"Arrays.sort", "Merge Sort", "Partitioning", "Middle Pivot"};
		System.out.println("-----------------------------------------------------------------");
		System.out.println("|     Sort \t|\tNumber (ms)\t|\tString (ms)\t|\t\t");
		System.out.println("-----------------------------------------------------------------");
		for(int i=0;i<4;i++)
			System.out.printf("| %s\t| \t %.2f  \t|\t %.2f     \t|\n", str[i], time[i][0], time[i][1]);
		System.out.println("-----------------------------------------------------------------");
	}
}