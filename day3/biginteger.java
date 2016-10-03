import java.io.BufferedReader;
import java.io.InputStreamReader;

public class BigInteger
{
    public static final String QUIT_COMMAND = "quit";
    public static final String MSG_INVALID_INPUT = "wrong input";

    private char[] num;
    private String sign = null;

    public BigInteger(int i) {
        num = new char[i];
    }
    public BigInteger(String s) {
        num = s.toCharArray();
    }
    public void setSign(String s) {
        sign = s;
    }
    public String getSign() {
        return sign;
    }
    public char[] getNum() {
        return num;
    }
    public char getithnum(int i) {
        return num[i];
    }
    public int getLength() {
        return num.length;
    }

    public BigInteger add(BigInteger big, BigInteger result) {
        int c1 = 100 - num.length;
        int c2 = 100 - big.getLength();
        int x; int y;

        for (int i = 99; i>=c1; i--) {
            if (i-c2 < 0) {
                y = 0;
            }
            else {
                y =  char_to_int(big.getithnum(i-c2)); // in case secondarray is shorter than the first
            }

            if (char_to_int(num[i-c1]) + y < 10) {
                x = char_to_int(num[i-c1]) + y;
                result.getNum()[i+1]  = (char) ('0' + x);
            }
            else {
                x = char_to_int(num[i-c1]) + y - 10;
                result.getNum()[i+1] = (char) ('0' + x);
                if (i == c1)
                    result.getNum()[i] = (char) ('0' + 1);
                else
                    num[i-c1-1] += 1;
            }
        }
        return result;
    }

    public BigInteger subtract(BigInteger big, BigInteger result){
        int c1 = 100 - num.length;
        int c2 = 100 - big.getLength();
        int x; int y;

        for (int i = 99; i>=c1; i--) {
            if (i-c2 < 0) {
                y = 0;
            }
            else {
                y =  char_to_int(big.getithnum(i-c2)); // in case secondarray is shorter than the first
            }

            if (char_to_int(num[i-c1]) >= y) {
                x = char_to_int(num[i-c1]) - y;
                result.getNum()[i]  = (char) ('0' + x);
            }
            else {
                x = 10 + char_to_int(num[i-c1]) - y;
                num[i-c1-1] -= 1;
                result.getNum()[i] = (char) ('0' + x);
            }
        }
        return result;
    }

    public BigInteger multiply(BigInteger big, BigInteger result){
        int c1 = 100 - num.length;
        int c2 = 100 - big.getLength();
        int x; int y;

        for (int i = 99; i>=c2; i--)
        {
            for (int j=99; j>=c1; j--)
            {
                if (result.getNum()[i+j+1] == 0)
                    x = 0;
                else
                    x = char_to_int(result.getNum()[i+j+1]);

                if (result.getNum()[i+j] == 0)
                    y = 0;
                else
                    y = char_to_int(result.getNum()[i+j]);

                int helper = x + char_to_int(big.getithnum(i-c2)) * char_to_int(num[j-c1]);

                result.getNum()[i+j+1] = (char) ('0' + (helper % 10));
                result.getNum()[i+j] = (char) ('0' + (y + (int) (helper / 10)));
            }
        }
        if (result.getNum()[c1+c2] == 48)
            result.getNum()[c1+c2] = (char) 0;

        return result;
    }

    private static int char_to_int (char input){
        return input - 48;
    }

    @Override
    public String toString() {
        String result = "";
        if (sign == "zero") {
            return "0";
        }
        for (int i = 0; i<=200; i++){ // have to erase the unnecessary int 0 infront
            if (i==200)
                return "0";
            else {
                if (num[i]==0 || num[i]==48) {
                    num[i] = (char) 0;
                    continue;
                }
                else break;
            }
        }

        if (sign == "minus")
            result+= "-";
        for (int i = 0; i<=200; i++){
            if (i==200){
                return result;
            }
            else {
                if (num[i] == 0)
                    continue;
                else
                    result += num[i];
            }
        }
        return null; //expected not to happen
    }

    static BigInteger evaluate(String input) throws IllegalArgumentException {
        input = input.replaceAll(" ","");
        input = input.replaceAll("\t","");
        input = input.replaceAll("\n","");
        input = input.replace("++","+");
        input = input.replace("+-","-");
        input = input.replace("-+","-");
        input = input.replace("--","+");
        input = input.replace("*+","*");
        if (input.indexOf("+") == 0)
            input = input.substring(1, input.length());
        // front sign -, and "*-" is still present,

        BigInteger[] nums = divide_input(input);
        return find_op(input, nums[0], nums[1]);
    }

    private static BigInteger[] divide_input(String input) {
        if (input.indexOf("-") == 0 & input.contains("+")) {
            BigInteger num1 = new BigInteger(input.substring(input.indexOf("+")+1, input.length()));
            BigInteger num2 = new BigInteger(input.substring(1, input.indexOf("+")));
            BigInteger[] nums = {num1, num2};
            return nums;
        } // converted -A+B to B-A

        else {
            if (input.indexOf("-") == 0)
                input = input.substring(1, input.length());
            // only the op in the middle is left, just for dividing
            if (input.contains("*-"))
                input = input.replace("*-","|");
            else if (input.contains("+"))
                input = input.replace("+","|");
            else if (input.contains("-"))
                input = input.replace("-","|");
            else if (input.contains("*"))
                input = input.replace("*","|");

            BigInteger num1 = new BigInteger(input.substring(0, input.indexOf("|")));
            BigInteger num2 = new BigInteger(input.substring(input.indexOf("|")+1, input.length()));
            BigInteger[] nums = {num1, num2};
            return nums;
        }
    }

    private static BigInteger find_op (String input, BigInteger num1, BigInteger num2) {
        if (input.indexOf("-")==0 & input.contains("+")) {
            return find_sign(num1, num2);
            //num1.subtract(num2);
        }
        else if (input.indexOf("-")==0 & input.contains("*-")) {
            BigInteger result = new BigInteger(200);
            result.setSign("plus");
            return num1.multiply(num2, result);
        }
        else if (input.indexOf("-")==0 & input.contains("*")){
            BigInteger result = new BigInteger(200);
            result.setSign("minus");
            return num1.multiply(num2, result);
        }
        else if (input.indexOf("-")==0 & input.lastIndexOf("-")!=0) {
            BigInteger result = new BigInteger(200);
            result.setSign("minus");
            if (num1.getLength() >= num2.getLength())
                return num1.add(num2, result);
            else return num2.add(num1, result);
        }
        else if (input.indexOf("-")!=0 & input.contains("+")) {
            BigInteger result = new BigInteger(200);
            result.setSign("plus");
            if (num1.getLength() >= num2.getLength())
                return num1.add(num2, result);
            else return num2.add(num1, result);
       }
        else if (input.indexOf("-")!=0 & input.contains("*-")){
            BigInteger result = new BigInteger(200);
            result.setSign("minus");
            return num1.multiply(num2, result);
        }
        else if (input.indexOf("-")!=0 & input.contains("*")){
            BigInteger result = new BigInteger(200);
            result.setSign("plus");
            return num1.multiply(num2, result);
        }
        else if (input.indexOf("-")!=0 & input.contains("-")){
            return find_sign(num1, num2);
            //num1.subtract(num2);
        }
        else
            return null; //expected not to happen
    }

    private static BigInteger find_sign(BigInteger num1, BigInteger num2) {
        int length1 = num1.getLength();
        int length2 = num2.getLength();
        BigInteger result = new BigInteger(200);

        if (length1 > length2){
            result.setSign("plus");
            return num1.subtract(num2, result);
        }

        else if (length1 < length2) {
            result.setSign("minus"); //have to change the order
            return num2.subtract(num1, result);
        } // ex. 1-10 -> -(10-1)

        else {
            for (int i = 0; i <= length1; i++) {
                if (i == length1){
                    result.setSign("zero");
                    return num1.subtract(num2, result);
                }
                else {
                    if (num1.getithnum(i)>num2.getithnum(i)){
                        result.setSign("plus");
                        return num1.subtract(num2, result);
                    }
                    else if (num1.getithnum(i)<num2.getithnum(i)){
                        result.setSign("minus"); //have to change the order
                        return num2.subtract(num1, result);
                    }
                    else
                        continue;
                }
            }
        }
        return null; //expected not to happen
    }


    public static void main(String[] args) throws Exception {
        try (InputStreamReader isr = new InputStreamReader(System.in)) {
            try (BufferedReader reader = new BufferedReader(isr)){
                boolean done = false;
                while (!done){
                    String input = reader.readLine();

                    try{
                        done = processInput(input);
                    }
                    catch (IllegalArgumentException e){
                        System.err.println(MSG_INVALID_INPUT);
                    }
                }
            }
        }
    }

    static boolean processInput(String input) throws IllegalArgumentException {
        boolean quit = isQuitCmd(input);

        if (quit) {
            return true;
        }
        else {
            BigInteger result = evaluate(input);
            System.out.println(result.toString());
            return false;
        }
    }

    static boolean isQuitCmd(String input) {
        return input.equalsIgnoreCase(QUIT_COMMAND);
    }
}



/*  99/100
case:
+8710102468267593042568736151371487840963678616656752197943827823317080188487090729389469813367247412++3062872521071967196379127301778973914872307951034503915906546359666232418115603917376965124660227029

expected output:
11772974989339560238947863453150461755835986567691256113850374182983312606602694646766434938027474441

mine:
arrayoutofboundsexception

- fixed.

*/