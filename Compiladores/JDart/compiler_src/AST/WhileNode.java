package AST;

import java.io.FileWriter;

public class WhileNode extends Node {
    public AbstractExpressionNode condition;
    public StatementsNode block;

    public WhileNode(AbstractExpressionNode condition,
                     StatementsNode block){
        this.condition = condition;
        this.block = block;
    }

    protected int printNode(FileWriter writer) throws Exception {
        Integer my_nr = nr++;

        writer.write(String.format("node%d[label=\"", my_nr));

        writer.write(this.nodeInfo());

        writer.write("\"];\n");

        Integer child_left = condition.printNode(writer);
        writer.write(String.format("node%d -> node%d;\n", my_nr, child_left));

        Integer child_right = block.printNode(writer);
        writer.write(String.format("node%d -> node%d;\n", my_nr, child_right));

        return my_nr;
    }
}
