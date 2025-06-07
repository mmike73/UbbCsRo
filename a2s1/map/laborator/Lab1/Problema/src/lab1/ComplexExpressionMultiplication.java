package lab1;

public class ComplexExpressionMultiplication extends ComplexExpression {
     ComplexExpressionMultiplication(NumarComplex[] args) {
         super(Operation.MULTIPLICATION, args);
     }

     public NumarComplex executeOneOperation() {
        if(args != null && start < args.length) {
            result = result.inmultire(args[start++]);
        }
        return result;
     }
}
