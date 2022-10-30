import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

public class assign5 {
	static Stack<Double> numstack = new Stack<Double>();
	static Stack<String> oprstack = new Stack<String>();
	static ArrayList<String> postfix = new ArrayList<String>();

	static double ans = 0;

	public void Change_infix_to_postfix(String[] token) {
		int i, group, cur, prior = 0;
		String buff;
		postfix.clear();
		oprstack.clear();
		for (i = 0; i < token.length; i++) {
			group = TokenAnalysis.check_group(token[i]);
			if (group == 1) // number
				postfix.add(token[i]);
			else if (group >= 2 && group <= 6) // operator and function
			{
				do {
					cur = TokenAnalysis.check_group(token[i]);
					buff = oprstack.peek();
					prior = TokenAnalysis.check_group(buff);
					if (prior >= cur && prior <= 6) {
						buff = oprstack.pop();
						postfix.add(buff);
					}
				} while (prior >= cur && prior <= 6);
				oprstack.push(token[i]); // push
			} else if (group == 7) // open parenthesis
				oprstack.push(token[i]);
			else if (group == 8) { // closr parenthesis
				do {
					buff = oprstack.pop(); // pop
					if (!buff.equals("("))
						;
					postfix.add(buff);
				} while (!buff.equals("("));
			} else {
				System.out.printf("Postfix error %s \n", token[i]);
			}
		}
	}

	public double ValueOf(String str) {
		if (str.equalsIgnoreCase("pi"))
			return Math.PI;
		else if (str.equalsIgnoreCase("E"))
			return Math.E;
		else if (str.equalsIgnoreCase("ans"))
			return ans;
		else
			return Double.parseDouble(str);
	}

	public double Calculator_postfix() {
		double ans = 0, num, num1, num2;
		int i, group;
		String token = new String("");
		for (i = 0; i < postfix.size(); i++) {
			token = postfix.get(i);
			group = TokenAnalysis.check_group(token);
			if (group == 1) {
				num1 = ValueOf(token);
				numstack.push(num1);
			} else if (group >= 2 && group <= 4) {
				num1 = numstack.pop();
				num2 = numstack.pop();
				if (group == 2 && token.equals("+"))
					numstack.push(num2 + num1);
				else if (group == 2 && token.equals("-"))
					numstack.push(num2 - num1);
				else if (group == 3 && token.equals("*"))
					numstack.push(num2 * num1);
				else if (group == 3 && token.equals("/"))
					numstack.push(num2 / num1);
				else if (group == 4)
					numstack.push(Math.pow(num2, num1));
			} else if (group == 5) { // negative sign
				num1 = numstack.pop();
				numstack.push(-num1);
			} else if (group == 6) { // function
				if (token.equalsIgnoreCase("sin")) {
					num = Math.sin(numstack.pop() * Math.PI / 180);
					numstack.push(num);
				} else if (token.equalsIgnoreCase("cos")) {
					num = Math.cos(numstack.pop() * Math.PI / 180);
					numstack.push(num);
				} else if (token.equalsIgnoreCase("tan")) {
					num = Math.tan(numstack.pop() * Math.PI / 180);
					numstack.push(num);
				} else if (token.equalsIgnoreCase("asin")) {
					num = Math.asin(numstack.pop()) * 180 / Math.PI;
					numstack.push(num);
				} else if (token.equalsIgnoreCase("acos")) {
					num = Math.acos(numstack.pop()) * 180 / Math.PI;
					numstack.push(num);
				} else if (token.equalsIgnoreCase("atan")) {
					num = Math.atan(numstack.pop()) * 180 / Math.PI;
					numstack.push(num);
				} else if (token.equalsIgnoreCase("sqrt")) {
					num = Math.sqrt(numstack.pop());
					numstack.push(num);
				} else if (token.equalsIgnoreCase("log")) {
					num = Math.log10(numstack.pop());
					numstack.push(num);
				} else if (token.equalsIgnoreCase("exp")) {
					num = Math.exp(numstack.pop());
					numstack.push(num);
				} else if (token.equalsIgnoreCase("abs")) {
					num = Math.abs(numstack.pop());
					numstack.push(num);
				}
			}
		}
		ans = numstack.pop();
		return ans;
	}

	public static void main(String[] args) {
		assign5 calc = new assign5();
		Scanner in = new Scanner(System.in);
		String str;
		do {
			System.out.print("expression> ");
			str = in.nextLine();
			str = TokenAnalysis.Transform(str);
			if (str.trim().equalsIgnoreCase("help"))
				System.out.println("token = sin, cos, tan, asin, acos,"
									+" atan, sqrt, log, exp, abs");
			else {
				if (!str.equalsIgnoreCase("end")) {
					str = "(" + str + ")";
					str = TokenAnalysis.Transform(str);
					String[] token = str.trim().split("\\s+");
					TokenAnalysis.change_sign_operator(token);
					int state = TokenAnalysis.check_state(token);
					if (state == 1) {
						calc.Change_infix_to_postfix(token);
						// System.out.println("postfix queue = " + postfix);
						ans = calc.Calculator_postfix();
						// System.out.println("answer> " + ans);
						if (Double.isInfinite(ans))
							System.out.println("answer> error");
						else if (Double.isNaN(ans))
							System.out.println("answer> error");
						else
							System.out.println("answer> " + ans);
					} else
						System.out.println("answer> error");
				}
			}
		} while (!str.equalsIgnoreCase("end"));
		System.out.println("End Program");
		System.out.println("Program written by 63070501044 Parinda Kongwattanasin");
		in.close();
	}
}
