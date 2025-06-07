package lab1;

public abstract class ComplexExpression {
    public enum Operation {
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION
    }

    Operation operation;
    NumarComplex[] args;
    int start;
    NumarComplex result;

    ComplexExpression(Operation operation, NumarComplex[] args) {
        this.operation = operation;
        this.result = new NumarComplex(args[0].re, args[0].im);
        this.start = 1;
        this.args = args;
    }

    public NumarComplex execute() {
        for(int i = start; i < args.length; i++) {
            executeOneOperation();
        }
        return result;
    }

    public abstract NumarComplex executeOneOperation();
}