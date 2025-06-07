package lab1;

public class Main {
    public static void main(String[] args) {
        ExpressionParserUniversal parser_universal = new ExpressionParserUniversal(args);
        parser_universal.constructExpression();
        System.out.println(parser_universal.evaluateExpression());

        try {
            ExpressioParserOneOperation parser = new ExpressioParserOneOperation(args);
            parser.constructExpression();
            System.out.println(parser.evaluateExpression());
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}