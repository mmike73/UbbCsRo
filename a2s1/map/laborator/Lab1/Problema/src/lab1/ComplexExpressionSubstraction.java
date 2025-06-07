package lab1;

public class ComplexExpressionSubstraction extends ComplexExpression {
    ComplexExpressionSubstraction(NumarComplex[] args) {
        super(Operation.SUBTRACTION, args);
    }

    public NumarComplex executeOneOperation() {
        if(start < args.length) {
            result =  result.scadere(args[start++]);
        }
        return result;
    }
}
