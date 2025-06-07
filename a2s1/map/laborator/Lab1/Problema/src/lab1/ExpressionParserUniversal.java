package lab1;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ExpressionParserUniversal {
    String[] args;
    private final ExpressionFactory expressionFactory;
    private TreeNode root;

    ExpressionParserUniversal(String[] args) {
        expressionFactory = ExpressionFactory.getInstance();
        this.args = args;
    }

    public void constructExpression() {
        String[] postfix = infixToPostfix(args);
        this.root = expressionTree(postfix);
    }

    public NumarComplex evaluateExpression() {
        return inorder(root);
    }



    class TreeNode {
        String element;
        TreeNode left, right;

        public TreeNode(String element) {
            this.element = element;
            left = right = null;
        }
    }

    private NumarComplex inorder(TreeNode root) {
        if (root == null) return new NumarComplex(1,1);
        switch (root.element) {
            case "+":
                NumarComplex stanga1 = inorder(root.left), dreapta1 = inorder(root.right);
                ComplexExpression r1 = expressionFactory.createComplexExpression(ComplexExpression.Operation.ADDITION, new NumarComplex[] {stanga1, dreapta1});
                NumarComplex n1 = r1.execute();
                return n1;
            case "-":
                NumarComplex stanga2 = inorder(root.left), dreapta2 = inorder(root.right);
                ComplexExpression r2 = expressionFactory.createComplexExpression(ComplexExpression.Operation.SUBTRACTION, new NumarComplex[] {stanga2, dreapta2});
                NumarComplex n2 = r2.execute();
                return n2;
            case "*":
                NumarComplex stanga3 = inorder(root.left), dreapta3 = inorder(root.right);
                ComplexExpression r3 = expressionFactory.createComplexExpression(ComplexExpression.Operation.MULTIPLICATION, new NumarComplex[] {stanga3, dreapta3});
                NumarComplex n3 = r3.execute();
                return n3;
            case "/":
                NumarComplex stanga4 = inorder(root.left), dreapta4 = inorder(root.right);
                ComplexExpression r4 = expressionFactory.createComplexExpression(ComplexExpression.Operation.DIVISION, new NumarComplex[] {stanga4, dreapta4});
                NumarComplex n4 = r4.execute();
                return n4;
            default:
                NumarComplex numarComplex = parseOneComplexNumber(root.element);
                return numarComplex;
        }
    }

    private TreeNode expressionTree(String[] postfix) {
        Stack<TreeNode> st = new Stack<>();
        TreeNode t1, t2, tmp;

        for (String token : postfix) {
            if ("+".equals(token) || "-".equals(token) || "*".equals(token) || "/".equals(token)) {
                t1 = st.pop();
                t2 = st.pop();
                tmp = new TreeNode(token);
                tmp.left = t2;
                tmp.right = t1;
                st.push(tmp);
            } else {
                tmp = new TreeNode(token);
                st.push(tmp);
            }
        }
        return st.pop();
    }

    private int priority(String c) {
        if ("/".equals(c) || "*".equals(c))
            return 2;
        else if ("-".equals(c) || "+".equals(c))
            return 1;
        else
            return -1;
    }

    private String[] infixToPostfix(String[] args) {
        List<String> result = new ArrayList<>();
        Stack<String> stack = new Stack<>();

        for (int i = 0; i < args.length; i++) {
            String c = args[i];
            if (!(("+".equals(c)) || ("-".equals(c)) || ("*".equals(c)) || ("/".equals(c)))) {
                result.add(c);
            } else {
                while (!stack.isEmpty() && (priority(c) < priority(stack.peek()) ||
                        priority(c) == priority(stack.peek()))) {
                    result.add(stack.pop());
                }
                stack.push(c);
            }
        }
        while(!stack.isEmpty()) {
            result.add(stack.pop());
        }
        args = result.toArray(new String[result.size()]);
        return args;
    }

    private NumarComplex[] parseAllComplex(String[] args) {
        int nr_args = args.length / 2 + 1;
        NumarComplex[] parsed = new NumarComplex[nr_args];
        int index = 0;
        for( int i = 0; i < args.length; i+=2 ) {
            NumarComplex aux = parseOneComplexNumber(args[i]);
            parsed[index++] = aux;
        }
        return parsed;
    }

    private NumarComplex parseOneComplexNumber(String arg) {
        String complexPattern = "([+-]?)(\\d+)?([+-]?)(\\d*)([*]?)i";
        Pattern pattern = Pattern.compile(complexPattern);
        Matcher matcher = pattern.matcher(arg.trim());

        if (matcher.matches()) {
            String sgn1 = matcher.group(1);
            String reString = matcher.group(2);
            String sgn2 = matcher.group(3);
            String imString = matcher.group(4);
            String star = matcher.group(5);

            int re = (reString == null || reString.isEmpty()) ? 0 : Integer.parseInt(reString);
            if("-".equals(sgn1)) {
                re = -re;
            }

            int im = (imString == null || imString.isEmpty()) ? 1 : Integer.parseInt(imString);
            if("-".equals(sgn2)) {
                im = -im;
            }

            return new NumarComplex(re, im);
        }
        return null;
    }
}
