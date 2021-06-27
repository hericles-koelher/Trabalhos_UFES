package AST.operations;

public abstract class OperationManager {
    public static Operation getOperation(String symbol) {
        return switch (symbol) {
            case "+" -> Operation.Addition;
            case "-" -> Operation.Subtraction;
            case "*" -> Operation.Multiplication;
            case "/" -> Operation.Division;
            case "==" -> Operation.Equals;
            case "!=" -> Operation.NotEquals;
            case "<" -> Operation.Less;
            case ">" -> Operation.Greater;
            case "<=" -> Operation.LessOrEqual;
            case ">=" -> Operation.GreaterOrEqual;
            default -> throw new OperationNotSupportedException();
        };
    }
}
