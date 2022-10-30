import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class DataArray {
	info[] data;
	int count;

	public DataArray(int max) {
		data = new info[max];
		count = 0;
	}

	public void addData(int a, long b, String c, String d) {
		info x = new info(a, b, c, d);
		data[count++] = x;
	}

	public int Load_File(String filename) {
		int count = 0;
		int a;
		long b;
		String c, d;
		try {
			File fr = new File(filename);
			Scanner sc = new Scanner(fr);
			sc.useDelimiter(",|\n"); // | = or
			while (sc.hasNextInt()) {
				a = sc.nextInt();
				b = sc.nextLong();
				c = sc.next();
				d = sc.next();
				addData(a, b, c, d);
				count++;
			}
			sc.close();
		} catch (FileNotFoundException e) {
			System.out.println("Error, Can't open " + filename);
			return 0;
		}
		return count;
	}

	public void printTest(int start, int stop) {
		for (int i = start; i < stop; i++)
			data[i].printData();
	}

	public void swap(int i, int j) {
		info x = new info();
		x = data[i];
		data[i] = data[j];
		data[j] = x;
	}

	/* Scan Sort */
	public double scan_sort(int start, int stop, int de) {
		int i, j;
		long begin = System.nanoTime();
		if (de == 0) {
			for (i = start; i < stop; i++)
				for (j = i + 1; j <= stop; j++)
					if (data[j].num < data[i].num)
						swap(i, j);
		} else {
			for (i = start; i < stop; i++)
				for (j = i + 1; j <= stop; j++)
					if (data[j].num > data[i].num)
						swap(i, j);
		}
		long end = System.nanoTime();
		double time = (end - begin) / 1E6;
		return time;
	}

	/* Selection Sort */
	public double selection_sort(int start, int stop, int de) {
		int i, j, min, max;
		long begin = System.nanoTime();
		if (de == 0) {
			for (i = start; i < stop; i++) {
				min = i;
				for (j = i + 1; j <= stop; j++) {
					if (data[j].num < data[min].num)
						min = j;
				}
				swap(min, i);
			}
		} else {
			for (i = start; i < stop; i++) {
				max = i;
				for (j = i + 1; j <= stop; j++) {
					if (data[j].num > data[max].num)
						max = j;
				}
				swap(max, i);
			}
		}
		long end = System.nanoTime();
		double time = (end - begin) / 1E6;
		return time;
	}

	/* Insertion Sort */
	public double insertion_sort(int start, int stop, int de) {
		int i, j;
		long x = 0;
		info y = new info();
		long begin = System.nanoTime();
		if (de == 0) {
			for (i = start + 1; i <= stop; i++) {
				x = data[i].num;
				y = data[i];
				for (j = i; (j > start) && (x < data[j - 1].num); j--)
					data[j] = data[j - 1];
				data[j] = y;
			}
		} else {
			for (i = start + 1; i <= stop; i++) {
				x = data[i].num;
				y = data[i];
				for (j = i; (j > start) && (x > data[j - 1].num); j--)
					data[j] = data[j - 1];
				data[j] = y;
			}
		}
		long end = System.nanoTime();
		double time = (end - begin) / 1E6;
		return time;
	}

	/* Bubble Sort */
	public double bubble_sort(int start, int stop, int de) {
		int i, j;
		long begin = System.nanoTime();
		if (de == 0) {
			for (i = start; i <= stop - 1; i++)
				for (j = stop; j > i; j--)
					if (data[j].num < data[j - 1].num)
						swap(j, j - 1);
		} else {
			for (i = start; i <= stop - 1; i++)
				for (j = stop; j > i; j--)
					if (data[j].num > data[j - 1].num)
						swap(j, j - 1);
		}
		long end = System.nanoTime();
		double time = (end - begin) / 1E6;
		return time;
	}
}
