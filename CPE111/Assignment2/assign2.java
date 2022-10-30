import java.util.Arrays;

public class assign2 {

	public static void printOutput(double answer[][]) {
		String [] str = new String[] {"Scan Sort", "Selection Sort", "Insertion Sort", "Bubble Sort"};
		System.out.println("-----------------------------------------------------------------------------------------");
		System.out.println("|     Sort \t|\tRandom data\t|\tInsert data\t|\tDescending\t|");
		System.out.println("-----------------------------------------------------------------------------------------");
		for(int i=0;i<4;i++)
			System.out.printf("|%s\t| \t %.2f  \t|\t %.2f     \t|\t %.2f \t|\n", str[i], answer[i][0], answer[i][1], answer[i][2]);
		System.out.println("-----------------------------------------------------------------------------------------");
	}
	
	public static void main(String[] args) {
		int max = 100010;
		double answer[][] = new double[4][3];
		
		System.out.println("Sorting Comparison Program.");
		
		DataArray test = new DataArray(max);
		DataArray temp = new DataArray(10010);
		
		if(test.Load_File("D:\\CPE111\\Assignment2\\test.csv")>0)
		{
			System.out.println("Total read "+test.count+" records.");
			/*for(int i=0;i<10;i++)
				test.data[i].printData();*/
			
			/* Scan Sort */
			temp.data = Arrays.copyOf(test.data, 10010);
			answer[0][0] = temp.scan_sort(0, 10000, 0);
			answer[0][1] = temp.scan_sort(0, 10001, 0);
			answer[0][2] = temp.scan_sort(0, 10000, 1);
			
			/* Selection Sort */
			temp.data = Arrays.copyOf(test.data, 10010);
			answer[1][0] = temp.selection_sort(0,10000, 0);
			answer[1][1] = temp.selection_sort(0,10001, 0);
			answer[1][2] = temp.selection_sort(0,10000, 1);
			
			/* Insertion Sort */
			temp.data = Arrays.copyOf(test.data, 10010);
			answer[2][0] = temp.insertion_sort(0,10000, 0);
			answer[2][1] = temp.insertion_sort(0,10001, 0);
			answer[2][2] = temp.insertion_sort(0,10000, 1);		
			
			/* Bubble Sort */
			temp.data = Arrays.copyOf(test.data, 10010);
			answer[3][0] = temp.bubble_sort(0,10000, 0);
			answer[3][1] = temp.bubble_sort(0,10001, 0);			
			answer[3][2] = temp.bubble_sort(0,10000, 1);
			
			printOutput(answer);
		}
		else
			System.out.println("Error");
	}
}
