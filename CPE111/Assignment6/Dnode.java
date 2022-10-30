public class Dnode implements Comparable<Dnode> {
    String word, mean, type;

    public Dnode() { // constructor สร้าง node เปล่า
        word = "";
        mean = "";
        type = "";
    }

    public Dnode(String buff) {
        buff = buff.trim().replaceAll("\\s+", " ");
        String[] str = buff.split(",");
        word = str[0];
        mean = str[1];
        type = str[2];
    }

    public int compareTo(Dnode x) {
        return (int) this.word.compareToIgnoreCase(x.word); // this ตัวมันเอง
    }

    public boolean compareAll(Dnode x) {
        if(this.word.equalsIgnoreCase(x.word) && this.mean.equalsIgnoreCase(x.mean) && this.type.equalsIgnoreCase(x.type))
            return true;
        else
            return false;
    }

    void print(int i) {
        System.out.printf("%d) %-13s %s (%s)\n", i, word, mean, type);
    }
}
