import java.io.*;
import java.util.Scanner;
import java.util.TreeSet;

public class assign7 {
    static TreeSet<DictNode> dict = new TreeSet<DictNode>(); // global

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
        if(dict.contains(x)) { // to check duplicate word in dict
            TreeSet<DictNode> z = (TreeSet<DictNode>)dict.subSet(x, true, x, true); // Bring that node to add meaning
            if(!z.first().mean.contains(x.mean.get(0))) // to check that node have duplicate meaning -> if no duplicate meaning
                z.first().mean.add(x.mean.get(0)); // Add only meaning to the variable mean
        } else // no duplicate word
            dict.add(x);
    }

    public static void dictSearch(String str) {
        str = str.trim().replaceAll("\\s+", " ");
        DictNode key = new DictNode(str);
        if(dict.contains(key)) {
            TreeSet<DictNode> z = (TreeSet<DictNode>)dict.subSet(key, true, key, true);
            System.out.println(str + " have " + z.first().mean.size() + " meaning.");
            int i = 0;
            for(String x  : z.first().mean)
                System.out.println((++i) + ") " + x);
        } else
            System.out.println(str + " not found");
    }

    public static void PrintStat() {
        System.out.println("Total Word size " + dict.size() + " words.");
        int sum = 0,  max = 0;
        DictNode z = new DictNode();
        for(DictNode itr : dict) {
            sum += itr.mean.size();
            if(max < itr.mean.size()) {
                max = itr.mean.size();
                z = itr;
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
