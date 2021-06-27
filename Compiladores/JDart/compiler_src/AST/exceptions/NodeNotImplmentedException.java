package AST.exceptions;

import org.antlr.v4.runtime.tree.ParseTree;

public class NodeNotImplmentedException extends RuntimeException {

    public NodeNotImplmentedException() {
    }

    public NodeNotImplmentedException(ParseTree ruleNode) {
        super(ruleNode.getClass().getSimpleName());
    }
}
