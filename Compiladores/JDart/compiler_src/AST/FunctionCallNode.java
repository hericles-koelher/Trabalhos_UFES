package AST;

import Types.Type;

import java.util.LinkedList;

public class FunctionCallNode extends AbstractExpressionNode {
    public String name;

    public FunctionCallNode(String name, LinkedList<Node> args, Type type) {
        this.name = name;
        this.type = type;
        addChildren(args);
    }

    protected String nodeInfo() {
        return String.format("%s %s", this.getClass().getSimpleName(), this.name);
    }
}
