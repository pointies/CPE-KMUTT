import java.io.*;
import java.util.Scanner;
import java.util.HashMap;

public class assign8 {
    static HashMap<String, DictNode> dict = new HashMap<String, DictNode>(); // global

    public static int ReadFile() {
        int count = 0;
        String str = null;
        try {
            FileInputStream fcsv = new FileInputStream("D:\\CPE111\\Assignment6\\utf8lexitron.csv"); // Read csv file
            InputStreamReader utf = new InputStreamReader(fcsv, "UTF-8"); // identify encoding "UTF-8"
            BufferedReader fbuff = new BufferedReader(utf);
            fbuff.read(); // Read BOM (Byte Order Marks)
            while ((str = fbuff.readLine()) != null) {
                LinkDictNode(str);
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

    public static void LinkDictNode(String buff) {
        DictNode x = new DictNode(buff);
        x.word = x.word.toLowerCase();
        if(dict.containsKey(x.word)) {
            DictNode z = dict.get(x.word);
            if(!z.mean.contains(x.mean.get(0))) {
                z.mean.add(x.mean.get(0));
                dict.put(x.word, z);
            }
        } else // no duplicate word
            dict.put(x.word, x);
    }

    public static void dictSearch(String str) {
        str = str.trim().replaceAll("\\s+", " ").toLowerCase();
        if(dict.containsKey(str)) { // search key in dictNode
            DictNode z = dict.get(str);
            System.out.println(str + " have " + z.mean.size() + " meaning.");
            int i = 0;
            for(String x : z.mean) // loop all the word in arrays of mean
                System.out.println((++i) + ") " + x);
        } else
            System.out.println(str + " not found");
    }

    public static void PrintStat() {
        System.out.println("Total Word size " + dict.size() + " words.");
        int sum = 0,  max = 0;
        DictNode z = new DictNode();
        for(String itr : dict.keySet()) {
            int count = dict.get(itr).mean.size();
            sum += count; // find the number of meaning
            if(max < count) { 
                max = count; // remember the word with maximum meaning
                z = dict.get(itr); // remember node with maximum meaning
            }
        }
        System.out.println("Total Meaning size " + sum + " words.");
        System.out.println(z.word + " have " + z.mean.size() + " meaning.\n");
        int i = 0;
        for(String x : z.mean) {
            System.out.println((++i) + ") " + x);
        }
    }

    public static void main(String[] args) {
        int count = ReadFile();
        System.out.println("Total Read " + count + " records.");
        PrintStat();
        Scanner input = new Scanner(System.in);
        String str = "";
        while (!str.equalsIgnoreCase("end")) {
            System.out.printf("\nEnter word: ");
            str = input.nextLine();
            dictSearch(str);
        }
        input.close();
        System.out.println("\nEnd Program");
        System.out.println("Program written by 63070501044 Parinda Kongwattanasin");
    }
}
