import java.util.Scanner;

public class TokenAnalysis {
    public static String Transform(String x) {
        x = x.replace("+", " + ");
        x = x.replace("-", " - ");
        x = x.replace("*", " * ");
        x = x.replace("/", " / ");
        x = x.replace("^", " ^ ");
        x = x.replace("(", " ( ");
        x = x.replace(")", " ) ");

        return x;
    }

    public static boolean isNumber(String str) {
        boolean check = true;
        try {
            Double.parseDouble(str); // แปลง String เป็น double
        } catch (Exception e) {
            check = false;
        }
        return check;
    }

    public static boolean isConstant(String str) {
        String[] myconst = { "pi", "e", "ans" };
        boolean ans = false;
        for (int i = 0; i < myconst.length; i++)
            if (myconst[i].equalsIgnoreCase(str))
                ans = true;
        return ans;
    }

    public static int check_Function(String str) {
        String[] myfunc = { "help", "sin", "cos", "tan", "asin", "acos", 
                            "atan", "sqrt", "exp", "log", "abs" };
        int ans = -1;
        for (int i = 0; i < myfunc.length; i++)
            if (myfunc[i].equalsIgnoreCase(str))
                ans = i;
        return ans;
    }

    public static int check_group(String str) {
        if (isNumber(str))
            return 1;
        else if (isConstant(str))
            return 1;
        else if (str.matches("[+-]"))
            return 2;
        else if (str.matches("[*/]"))
            return 3;
        else if (str.equals("^"))
            return 4;
        else if (str.equals("!"))
            return 5;
        else if (str.equals("("))
            return 7;
        else if (str.equals(")"))
            return 8;
        else if (check_Function(str) > 0)
            return 6;
        else
            return 0;
    }

    public static int check_state(String[] token) {
        int state = 0, next = 0, b = 0, i;
        for (i = 0; i < token.length && state >= 0; i++) {
            state = next;
            next = check_group(token[i]);
            if (next == 0)
                state = -1;
            else if (next >= 2 && next <= 4)
                next = 2;
            if (next == 7) // count (
                b++;
            else if (next == 8) // found )
                b--;
            if (b < 0) // more )
                state = -1;
            else if (state == 0 && (next == 2 || next == 8))
                state = -1;
            else if (state == 1 && (next == 1 || next == 6 || next == 7))
                state = -1;
            else if (state == 2 && (next == 2 || next == 8))
                state = -1;
            else if (state == 5 && (next == 2 || next == 8))
                state = -1;
            else if (state == 6 && (next != 7))
                state = -1;
            else if (state == 7 && (next == 2 || next == 8))
                state = -1;
        }
        if (b != 0 || state == -1)
            return -1;
        else {
            if (next == 1 || next == 8)
                return 1;
            else
                return -1;
        }
    }

    public static void change_sign_operator(String token[]) {
        int i;
        if (token[0].equals("-"))
            token[0] = "!";
        for (i = 0; i < token.length - 1; i++)
            if (token[i + 1].equals("-") && token[i].matches("[-+/(*\\^)]"))
                token[i + 1] = "!";
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String str;
        do {
            System.out.print("expression> ");
            str = in.nextLine();
            str = Transform(str);
            if (!str.equalsIgnoreCase("end")) {
                if (str.equalsIgnoreCase("help"))
                    System.out.println("token = sin, cos, tan, asin, acos,"+
                    " atan, sqrt, log, exp, abs, +, -, *, /, ^, (, ), pi, ans");
                else {
                    String[] token = str.trim().split("\\s+");
                    change_sign_operator(token);
                    int state = check_state(token);
                    if (state == 1)
                        System.out.println("answer> OK");
                    else
                        System.out.println("answer> error");
                }
            }
        } while (!str.equalsIgnoreCase("end"));
        System.out.println("End Program");
        System.out.println("Program is written by 63070501044 Parinda Kongwattanasin\n");
        in.close();
    }
}
