package AST;

public abstract class AbstractTwoChildNode extends AbstractExpressionNode {
    public AbstractExpressionNode left;
    public AbstractExpressionNode right;

    public AbstractTwoChildNode(){}

    public AbstractTwoChildNode(AbstractExpressionNode left, AbstractExpressionNode right) {
        this.left = left;
        this.right = right;
    }
}
