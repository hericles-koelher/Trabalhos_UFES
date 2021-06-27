package AST;

import java.io.FileWriter;

public class IfNode extends Node{
    public AbstractExpressionNode condition;
    public StatementsNode ifStatementsNode;
    public StatementsNode elseStatementsNode;

    public IfNode(AbstractExpressionNode condition,
                  StatementsNode ifStatementsNode,
                  StatementsNode elseStatementsNode){

        this.condition = condition;
        this.ifStatementsNode = ifStatementsNode;
        this.elseStatementsNode = elseStatementsNode;
    }

    protected int printNode(FileWriter writer) throws Exception {
        Integer my_nr = nr++;

        writer.write(String.format("node%d[label=\"", my_nr));

        writer.write(this.nodeInfo());

        writer.write("\"];\n");

        Integer child_left = condition.printNode(writer);
        writer.write(String.format("node%d -> node%d;\n", my_nr, child_left));

        if(this.ifStatementsNode != null) {
            Integer child_right = ifStatementsNode.printNode(writer);
            writer.write(String.format("node%d -> node%d;\n", my_nr, child_right));
        }
        if(this.elseStatementsNode != null) {
            Integer child_right = elseStatementsNode.printNode(writer);
            writer.write(String.format("node%d -> node%d;\n", my_nr, child_right));
        }

        return my_nr;
    }
}
