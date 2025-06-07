package lab1;

public class ComplexExpressionAddition extends ComplexExpression {

    ComplexExpressionAddition(NumarComplex[] args) {
        super(Operation.ADDITION, args);
    }

    public NumarComplex executeOneOperation() {
        if (args != null && start < args.length)
            result = result.adunare(args[start++]);
        return result;
    }
}
