package AST;

import Types.Type;

import java.io.FileWriter;

public class VariableDefinitionNode extends Node {
	public Integer position;
	public Integer scopeId;
	public Type type;
	public String name;
	// TODO: era pra ser ExpressionNode, mas tá foda arrumar a hierarquia de classes
	public Node initializer;

	public VariableDefinitionNode(Integer scopeId, Type type,
								  String name, Node initializer,
								  Integer position){
		this.scopeId = scopeId;
		this.type = type;
		this.name = name;
		this.initializer = initializer;
		this.position = position;
	}

	protected String nodeInfo() {
		return String.format("%s (%s)%s@%d", this.getClass().getSimpleName(), type, name, position);
	}

	protected int printNode(FileWriter writer) throws Exception {
		Integer my_nr = nr++;

		writer.write(String.format("node%d[label=\"", my_nr));

		writer.write(this.nodeInfo());

		writer.write("\"];\n");

		if (initializer != null) {
			Integer child_nr = initializer.printNode(writer);
			writer.write(String.format("node%d -> node%d;\n", my_nr, child_nr));
		}

		return my_nr;
	}
}
