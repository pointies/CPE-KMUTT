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

	public void printTest(int first, int last) {
		for (int i = first; i <= last; i++)
			data[i].printData();
	}

	public void swap(int i, int j) {
		info x = new info();
		x = data[i];
		data[i] = data[j];
		data[j] = x;
	}

	/* Merge Sort (number) */
	public void mergeData_number(info[] temp, int first, int mid, int last) {
		int i, i1, i2;
		i1 = first;
		i2 = mid + 1;
		for (i = 0; i <= last - first; i++) {
			if (i1 <= mid && i2 <= last) {
				if (data[i1].num < data[i2].num)
					temp[i] = data[i1++];
				else
					temp[i] = data[i2++];
			} else if (i1 > mid)
				temp[i] = data[i2++];
			else if (i2 > mid)
				temp[i] = data[i1++];
		}
		for (i = 0; i <= last - first; i++)
			data[first + i] = temp[i];
	}

	public double mergeSort_number(info[] temp, int first, int last) {
		int mid;
		long begin = System.nanoTime();
		if (first < last) {
			mid = (first + last) / 2;
			mergeSort_number(temp, first, mid);
			mergeSort_number(temp, mid + 1, last);
			mergeData_number(temp, first, mid, last);
		}
		long end = System.nanoTime();
		double time = (end - begin) / 1E6;
		return time;
	}

	/* Merge Sort (string) */
	public void mergeData_string(info[] temp, int first, int mid, int last) {
		int i, i1, i2;
		i1 = first;
		i2 = mid + 1;
		for (i = 0; i <= last - first; i++) {
			if (i1 <= mid && i2 <= last) {
				if (data[i1].str2.compareToIgnoreCase(data[i2].str2) < 0)
					temp[i] = data[i1++];
				else
					temp[i] = data[i2++];
			} else if (i1 > mid)
				temp[i] = data[i2++];
			else if (i2 > mid)
				temp[i] = data[i1++];
		}
		for (i = 0; i <= last - first; i++)
			data[first + i] = temp[i];
	}

	public double mergeSort_string(info[] temp, int first, int last) {
		int mid;
		long begin = System.nanoTime();
		if (first < last) {
			mid = (first + last) / 2;
			mergeSort_string(temp, first, mid);
			mergeSort_string(temp, mid + 1, last);
			mergeData_string(temp, first, mid, last);
		}
		long end = System.nanoTime();
		return (end - begin) / 1E6;
	}

	/* Middle Pivot (number) */
	public double midPivot_number(int first, int last) {
		int i = first;
		int j = last;
		long begin = System.nanoTime();
		if (first < last) {
			long pivot = data[(first + last) / 2].num;
			while (i < j) {
				while (data[i].num < pivot)
					i++;
				while (data[j].num > pivot)
					j--;
				if (i <= j)
					swap(i++, j--);
			}
			if (first < j)
				midPivot_number(first, j);
			if (i < last)
				midPivot_number(i, last);
		}
		long end = System.nanoTime();
		return (end - begin) / 1E6;
	}

	/* Middle Pivot (string) */
	public double midPivot_string(int first, int last) {
		int i = first;
		int j = last;
		long begin = System.nanoTime();
		if (first < last) {
			String pivot = data[(first + last) / 2].str2;
			while (i < j) {
				while (data[i].str2.compareTo(pivot) < 0)
					i++;
				while (data[j].str2.compareTo(pivot) > 0)
					j--;
				if (i <= j)
					swap(i++, j--);
			}
			if (first < j)
				midPivot_string(first, j);
			if (i < last)
				midPivot_string(i, last);
		}
		long end = System.nanoTime();
		return (end - begin) / 1E6;
	}

	/* Partition (number) */
	public double partition_number(int first, int last) {
		int i = first;
		int j = last;
		long begin = System.nanoTime();
		if (first < last) {
			do {
				while ((data[i].num <= data[j].num) && (i < j))
					j--;
				if (data[i].num > data[j].num) {
					swap(i, j);
					i++;
				}
				while ((data[i].num <= data[j].num) && (i < j))
					i++;
				if (data[i].num > data[j].num) {
					swap(i, j);
					j--;
				}
			} while (i < j);
			if (first < j - 1)
				partition_number(first, j - 1);
			if (i + 1 < last)
				partition_number(i + 1, last);
		}
		long end = System.nanoTime();
		return (end - begin) / 1E6;
	}

	/* Partition (string) */
	public double partition_string(int first, int last) {
		int i = first;
		int j = last;
		long begin = System.nanoTime();
		if (first < last) {
			do {
				while ((data[i].str2.compareTo(data[j].str2) <= 0) && (i < j))
					j--;
				if (data[i].str2.compareTo(data[j].str2) > 0) {
					swap(i, j);
					i++;
				}
				while ((data[i].str2.compareTo(data[j].str2) <= 0) && (i < j))
					i++;
				if (data[i].str2.compareTo(data[j].str2) > 0) {
					swap(i, j);
					j--;
				}
			} while (i < j);
			if (first < j - 1)
				partition_string(first, j - 1);
			if (i + 1 < last)
				partition_string(i + 1, last);
		}
		long end = System.nanoTime();
		return (end - begin) / 1E6;
	}
}
