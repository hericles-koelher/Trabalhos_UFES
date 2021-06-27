package AST;

import Types.Type;

import java.util.LinkedList;

public class FunctionDefinitionNode extends Node {
    public final Type type;
    public final String name;

    public FunctionDefinitionNode(Type type, String name, LinkedList<Node> nodes) {
        this.type = type;
        this.name = name;
        this.addChildren(nodes);
    }

    @Override
    protected String nodeInfo() {
        return String.format("%s (%s) %s ", this.getClass().getSimpleName(), this.type, this.name);
    }
}
