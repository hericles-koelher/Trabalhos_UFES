package AST;

// Para operações unarias
public abstract class AbstractOneChildNode extends AbstractExpressionNode {
    public AbstractExpressionNode child;

    public AbstractOneChildNode(AbstractExpressionNode child) {
        this.child = child;
    }
}

