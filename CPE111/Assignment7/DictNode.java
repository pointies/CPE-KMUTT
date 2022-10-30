import java.util.ArrayList;

public class DictNode implements Comparable<DictNode> {
    String word;
    ArrayList<String> mean;

    public DictNode() {
        word = "";
        mean = new ArrayList<String>();
    }

    public DictNode(String buff) {
        String[] str = buff.trim().replaceAll("\\s+", " ").split(",");
        word = str[0];
        String meaning;
        if(str.length == 1) // node only keyword
            meaning = "";
        else
            meaning = str[1] + " (" + str[2] + ")";
        mean = new ArrayList<String>();
        mean.add(meaning);
    }

    public int compareTo(DictNode x) {
        return (int) this.word.compareToIgnoreCase(x.word);
    }

}
