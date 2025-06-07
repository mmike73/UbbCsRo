package lab1;

public class ExpressionFactory {
    private static final ExpressionFactory SINGLE_INSTANCESn = new ExpressionFactory();

    private ExpressionFactory() {}

    public static ExpressionFactory getInstance() {
        return SINGLE_INSTANCE;
    }

    public ComplexExpression createComplexExpression(ComplexExpression.Operation operation, NumarComplex[] args) {
        return switch (operation) {
            case ADDITION -> new ComplexExpressionAddition(args);
            case SUBTRACTION -> new ComplexExpressionSubstraction(args);
            case MULTIPLICATION -> new ComplexExpressionMultiplication(args);
            case DIVISION -> new ComplexExpressionDivision(args);
        };
    }
}
