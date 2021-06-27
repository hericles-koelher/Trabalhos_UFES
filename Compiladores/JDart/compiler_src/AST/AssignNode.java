package AST;

import java.io.FileWriter;

// Tratando somente atribuição simples
public class AssignNode extends AbstractExpressionNode{
	public VariableNode left;
	public AbstractExpressionNode right;

	public AssignNode(VariableNode left, AbstractExpressionNode right){
		this.left = left;
		this.right = right;
	}

	@Override
	protected String nodeInfo() {
		return String.format("%s", this.getClass().getSimpleName());
	}

	protected int printNode(FileWriter writer) throws Exception {
		Integer my_nr = nr++;

		writer.write(String.format("node%d[label=\"", my_nr));

		writer.write(this.nodeInfo());

		writer.write("\"];\n");

		Integer left_child = left.printNode(writer);
		writer.write(String.format("node%d -> node%d;\n", my_nr, left_child));

		Integer right_child = right.printNode(writer);
		writer.write(String.format("node%d -> node%d;\n", my_nr, right_child));

		return my_nr;
	}
}
