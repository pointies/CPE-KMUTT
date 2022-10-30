import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class assign6 {
    static ArrayList<Dnode> dict = new ArrayList<Dnode>(); // global

    public static int ReadFile() {
        int count = 0;
        String str = null;
        try {
            FileInputStream fcsv = new FileInputStream("D:\\CPE111\\Assignment6\\utf8lexitron.csv"); // Read csv file
            InputStreamReader utf = new InputStreamReader(fcsv, "UTF-8"); // identify encoding "UTF-8"
            BufferedReader fbuff = new BufferedReader(utf);
            fbuff.read(); // Read BOM (Byte Order Marks)
            while ((str = fbuff.readLine()) != null) {
                Dnode x = new Dnode(str); // create node
                dict.add(x); // add x to ArrayList of dict
                count++;
            }
            fbuff.close();
        } catch (FileNotFoundException e) {
            System.out.println("Error, file not found.");
            return 0;
        } catch (Exception e) {
            System.out.println("Error, can't open file.");
            return 0;
        }
        return count;
    }
    
    public static void RemoveDuplicate() { // compare data next to each other
        int count = 0;
        for (int i = 0; i < dict.size()-1; i++)
            while (dict.get(i).compareAll(dict.get(i+1))) { // if it is same data, remove them
                dict.remove(i+1);
                count++; // count the same data
            }
        System.out.println("Total duplicate found " + count + " records.");
        // return count;
    }

    public static int CountMaxMeaning() {
        int j = 1, max = 0, index = 0;
        for (int i = 0; i < dict.size() - 1; i++)
            if (dict.get(i).compareTo(dict.get(i + 1)) == 0) { // if it is same words, remove them
                j++; // count the same words
                if (max < j) {
                    max = j;
                    index = i; // start position of max meaning
                }
            } else
                j = 1;
        System.out.println("Maximum Meaning token get off have " + max + " meaning.\n");
        return index;
    }

    public static void dictList(int start, int stop) { // print all data
        for (int i = start; i <= stop; i++)
            dict.get(i).print(i-start+1); // e.g. 23963-23963+1 = 1 -> 1) ตัวที่ 1
    }

    public static int dictSearch(String str) {
        int start = 0, stop = 0;
        Dnode key = new Dnode(); // create node name key
        key.word = str; // Put search words in node
        int j = Collections.binarySearch(dict, key); // found return address, not found return -1
        if (j >= 0) {// เจอตัวตรงกลาง แต่เราต้องการทุกตัว
            for(start = j; (start > 0) && (dict.get(start - 1).compareTo(key) == 0); start--)
                {} // เปรียบกับตัวที่อยู่ก่อนหน้าเพื่อหาตัวแรก
            for(stop = j; (stop < dict.size() - 1) && (dict.get(stop + 1).compareTo(key) == 0); stop++) 
                {} // เปรียบกับตัวที่อยู่ถัดไปเพื่อหาตัวสุดท้าย
        }
        if (j >= 0) { // print all data
            System.out.println("found " +str+ " " +(stop-start+1)+ " token at " +start+ " - " +stop);
            dictList(start, stop);
        } else // key not found
            System.out.println(str+ " not found");
        return start;
    }

    public static void PrintStat() {
        System.out.println("Total remaining size " + dict.size() + " records.");
        int j = CountMaxMeaning();
        Dnode x = new Dnode();
        x = dict.get(j);
        j = dictSearch(x.word);
    }

    public static void main(String[] args) {
        int count = ReadFile();
        System.out.println("Total Read " + count + " records.");
        Collections.sort(dict); // sort data before remove duplicate cuz file does not sort data
        RemoveDuplicate();
        // System.out.println("Total remaining size " +dict.size()+ " records.");
        PrintStat();
        Scanner input = new Scanner(System.in);
        String str = "";
        while (!str.equalsIgnoreCase("end")) {
            System.out.printf("\nEnter word: ");
            str = input.nextLine();
            str = str.trim().replaceAll("\\s+", " ");
            dictSearch(str);
        }
        input.close();
        System.out.println("\nEnd Program");
        System.out.println("Program written by 63070501044 Parinda Kongwattanasin");
    }
}
