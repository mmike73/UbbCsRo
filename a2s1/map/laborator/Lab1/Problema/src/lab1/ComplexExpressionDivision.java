package lab1;

public class ComplexExpressionDivision extends ComplexExpression {
    ComplexExpressionDivision(NumarComplex[] args) {
        super(ComplexExpression.Operation.DIVISION, args);
    }

    public NumarComplex executeOneOperation() {
        if (args != null && start < args.length) {
            result = result.impartire(args[start++]);
        }
        return result;
    }
}
