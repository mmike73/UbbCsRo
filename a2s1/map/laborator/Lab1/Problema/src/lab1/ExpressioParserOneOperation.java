package lab1;

import java.text.ParseException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ExpressioParserOneOperation {
    String[] args;
    private ExpressionFactory expressionFactory;
    private ComplexExpression expression;

    ExpressioParserOneOperation(String[] args) throws ParseException {
        expressionFactory = ExpressionFactory.getInstance();
        this.args = args;
        if (!verify()) {
            throw new ParseException("Format invalid!!!", 0);
        }
    }

    public void constructExpression() {
        NumarComplex[] parsed = parseAllComplex(args);
        switch (args[1]) {
            case "+" ->
                    expression = expressionFactory.createComplexExpression(ComplexExpression.Operation.ADDITION, parsed);
            case "-" ->
                    expression = expressionFactory.createComplexExpression(ComplexExpression.Operation.SUBTRACTION, parsed);
            case "*" ->
                    expression = expressionFactory.createComplexExpression(ComplexExpression.Operation.MULTIPLICATION, parsed);
            case "/" ->
                    expression = expressionFactory.createComplexExpression(ComplexExpression.Operation.DIVISION, parsed);
            default -> {
                return;
            }
        }
    }

    public NumarComplex evaluateExpression() {
        return expression.execute();
    }

    private boolean verify() {
        for (int i = 0; i < args.length; i += 2) {
            String complexPattern = "([+-]?\\d+)?([+-]?)(\\d*)([*]?)i";
            Pattern pattern = Pattern.compile(complexPattern);
            Matcher matcher = pattern.matcher(args[i].trim());
            if (!matcher.matches())
                return false;
        }
        return true;
    }

    private NumarComplex[] parseAllComplex(String[] args) {
        int nr_args = args.length / 2 + 1;
        NumarComplex[] parsed = new NumarComplex[nr_args];
        int index = 0;
        for (int i = 0; i < args.length; i += 2) {
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
            if ("-".equals(sgn1)) {
                re = -re;
            }

            int im = (imString == null || imString.isEmpty()) ? 1 : Integer.parseInt(imString);
            if ("-".equals(sgn2)) {
                im = -im;
            }

            return new NumarComplex(re, im);
        }
        return null;
    }
}
