package AST;

import Types.Type;

public class LiteralNode extends AbstractExpressionNode {
	public Object literal;

	public LiteralNode(Type type, Object literal){
		this.type = type;
		this.literal = literal;
	}

	@Override
	protected String nodeInfo() {
		return String.format("%s literal: %s", this.getClass().getSimpleName(), this.literal);
	}
}
