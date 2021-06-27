import AST.*;
import DartTypes.*;
import SymbolTable.FunctionSymbolTable;
import SymbolTable.VarSymbolTable;
import Types.Type;
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.Label;
import org.objectweb.asm.MethodVisitor;

import java.io.FileOutputStream;
import java.io.IOException;
import java.util.HashMap;
import java.util.LinkedList;

import static org.objectweb.asm.Opcodes.*;

public class AstVisitor {
	private final ClassWriter _cw;
	private final Node _ast;
	private final VarSymbolTable _varSymbolTable;
	private final FunctionSymbolTable _functionSymbolTable;
	private int newLocalVariableIndex = 0;
	private final HashMap<String, String> typeDescriptorMap;
	private final HashMap<String, String> internalNameMap;

	public AstVisitor(Node ast, VarSymbolTable varSymbolTable,
					  FunctionSymbolTable functionSymbolTable){
		_cw = new ClassWriter(ClassWriter.COMPUTE_FRAMES);
		_ast = ast;
		_varSymbolTable = varSymbolTable;
		_functionSymbolTable = functionSymbolTable;

		// Determinando os descriptors dos tipos existentes...
		typeDescriptorMap = new HashMap<>();
		typeDescriptorMap.put(Type.INT_NAME, org.objectweb.asm.Type.getDescriptor(DartInt.class));
		typeDescriptorMap.put(Type.DOUBLE_NAME, org.objectweb.asm.Type.getDescriptor(DartDouble.class));
		typeDescriptorMap.put(Type.BOOL_NAME, org.objectweb.asm.Type.getDescriptor(DartBool.class));
		typeDescriptorMap.put(Type.STRING_NAME, org.objectweb.asm.Type.getDescriptor(DartString.class));
		typeDescriptorMap.put(Type.NULL_NAME, org.objectweb.asm.Type.getDescriptor(DartNull.class));
		typeDescriptorMap.put("DartType", org.objectweb.asm.Type.getDescriptor(DartType.class));

		// Determinando internal name dos tipos existentes...
		internalNameMap = new HashMap<>();
		internalNameMap.put(Type.INT_NAME, org.objectweb.asm.Type.getInternalName(DartInt.class));
		internalNameMap.put(Type.DOUBLE_NAME, org.objectweb.asm.Type.getInternalName(DartDouble.class));
		internalNameMap.put(Type.BOOL_NAME, org.objectweb.asm.Type.getInternalName(DartBool.class));
		internalNameMap.put(Type.STRING_NAME, org.objectweb.asm.Type.getInternalName(DartString.class));
		internalNameMap.put(Type.NULL_NAME, org.objectweb.asm.Type.getInternalName(DartNull.class));
		internalNameMap.put("DartType", org.objectweb.asm.Type.getInternalName(DartType.class));
		internalNameMap.put("DartFunctions", org.objectweb.asm.Type.getInternalName(DartFunctions.class));
	}

	public void visit(){
		_cw.visit(V14, ACC_PUBLIC, "Main", null, "java/lang/Object", null);

		for (var childNode: _ast.getChildren()) {

			if(childNode instanceof FunctionDefinitionNode){
				visitFunctionDefinition((FunctionDefinitionNode) childNode);
			}

			// TODO: Implementar isso aqui depois
//			if(childNode instanceof GlobalVarNode){
//				visit(childNode);
//			}
		}

		// Como o nome do metodo já indica, sinaliza o final da classe.
		_cw.visitEnd();
	}

	private void visit(Node node){
		System.out.println("Ops, não era pra rodar isso!");
		System.out.println(node.getClass());
	}

	private void visitAssign(AssignNode node,
							 MethodVisitor mv, HashMap<String, Integer> varIndex){
		expressionSolver(node.right, mv, varIndex);

		int index = varIndex.get(node.left.name);

		mv.visitVarInsn(ASTORE, index);
	}

	private void getNull(MethodVisitor mv){
		mv.visitMethodInsn(INVOKESTATIC,
				internalNameMap.get(Type.NULL_NAME),
				"getInstance",
				"()" + typeDescriptorMap.get(Type.NULL_NAME),
				false);
	}

	private void visitLiteral(LiteralNode node, MethodVisitor mv){
		//TODO: devo deixar comentado msm?
		//newLocalVariableIndex++;

		if(node.type.name.equals(Type.NULL_NAME)){
			getNull(mv);
			return;
		}

		// Puta rolê pra criar um DartType ehhehueueuee
		mv.visitTypeInsn(NEW, internalNameMap.get(node.type.name));
		mv.visitInsn(DUP);

		String javaArgInternalName = null, javaPrimitive = null, dartArgTypeDescriptor = null;

		// Esse bagulho é um caso especial...
		switch (node.type.name){
			case Type.INT_NAME ->{
				javaArgInternalName = "java/lang/Integer";
				javaPrimitive = "I";
				dartArgTypeDescriptor = "Ljava/lang/Integer;";
			}
			case Type.DOUBLE_NAME ->{
				javaArgInternalName = "java/lang/Double";
				javaPrimitive = "D";
				dartArgTypeDescriptor = "Ljava/lang/Double;";
			}
			case Type.BOOL_NAME ->{
				javaArgInternalName = "java/lang/Boolean";
				javaPrimitive = "Z";
				dartArgTypeDescriptor = "Ljava/lang/Boolean;";
			}
			case Type.STRING_NAME ->{
				dartArgTypeDescriptor = "Ljava/lang/String;";
			}
		}

		// Caso caia em um dos casos especiais temos q executar isso antes...
		if(javaArgInternalName != null){
			// Criando arg do tipo necessario
			mv.visitTypeInsn(NEW, javaArgInternalName);
			mv.visitInsn(DUP);
			mv.visitLdcInsn(node.literal);

			mv.visitMethodInsn(INVOKESPECIAL,
					javaArgInternalName,
					"<init>",
					"(" + javaPrimitive + ")V",
					false);
		}else{
			mv.visitLdcInsn(node.literal);
		}

		// Criando a variavel local/temporaria
		mv.visitMethodInsn(INVOKESPECIAL,
				internalNameMap.get(node.type.name),
				"<init>",
				"("+ dartArgTypeDescriptor +")V",
				false);
	}

	private void visitFunctionCall(FunctionCallNode node,
								   MethodVisitor mv, HashMap<String, Integer> varIndex){

		// Poderia ser menos "hardcoded" ehuehuehuehuh
		if(node.name.equals("print")){

			Node arg = node.getChildren().get(0);

			if(arg instanceof LiteralNode){
				// Criando o literal do dart
				visitLiteral((LiteralNode) arg, mv);
			} else if (arg instanceof OperationNode) {
				expressionSolver((OperationNode) arg, mv, varIndex);
			} else{
				// Nesse caso arg é uma instancia de VariableNode
				int index = varIndex.get(((VariableNode) arg).name);

				mv.visitVarInsn(ALOAD, index);
			}

			mv.visitMethodInsn(INVOKESTATIC,
					internalNameMap.get("DartFunctions"),
					"print",
					"("+ typeDescriptorMap.get("DartType") +")V",
					false);
		}
	}

	// Responsavel por gerar o codigo de cada função
	// Não sei o motivo, mas se o corpo da função main for vazio da erro de execução
	private void visitFunctionDefinition(FunctionDefinitionNode node){

		HashMap<String, Integer> localVarIndex = new HashMap<>();
		this.newLocalVariableIndex = 0;

		MethodVisitor mv = null;

		try {
			// Por enquanto assumindo que a função não possui parametros
			String descriptor = "()" + typeDescriptorMap.get(node.type.name);

			if(node.name.equals("main")){
				// TODO: arrumar isso aqui dps
				descriptor = "([Ljava/lang/String;)V";
				// O indice 0 será para o array de args
				newLocalVariableIndex = 1;
			}

			mv = _cw.visitMethod(
					ACC_PUBLIC + ACC_STATIC,
					node.name, descriptor,
					null, null);
		} catch (Exception e) {
			// e.printStackTrace();
			System.out.println(e.getMessage());
			System.exit(1);
		}

		mv.visitCode();

		visitStatements(node.getChildren(), mv, localVarIndex);

		// Gambiarra temporaria
		// um retorno void no dart equivale a função retornar null
//		getNull(mv);
//		mv.visitInsn(ARETURN);
		mv.visitInsn(RETURN);

		// Chamando só por obrigação, pq o tamanho necessário para
		// stack, variaveis e mais já é calculado, pois a classe Main
		// foi definida utilizando a flag COMPUTE_FRAMES.
		mv.visitMaxs(-1,-1);
		mv.visitEnd();
	}

	private void visitVariableDefinition(VariableDefinitionNode node,
										 MethodVisitor mv, HashMap<String, Integer> varIndex){

		int index = newLocalVariableIndex++;

		varIndex.put(node.name, index);

		if(node.initializer == null){
			// Instanciação do tipo utilizando o construtor vazio...

			mv.visitTypeInsn(NEW, internalNameMap.get(node.type.name));
			mv.visitInsn(DUP);
			mv.visitMethodInsn(INVOKESPECIAL,
					internalNameMap.get(node.type.name),
					"<init>",
					"()V",
					false);
			mv.visitVarInsn(ASTORE, index);
		}else{
			// Instanciar variaveis inicializadas...
			expressionSolver((AbstractExpressionNode) node.initializer, mv, varIndex);

			mv.visitVarInsn(ASTORE, index);
		}
	}

	private void boolEval(AbstractExpressionNode node,
						  MethodVisitor mv, HashMap<String, Integer> varIndex){
		expressionSolver(node, mv, varIndex);

		// Empilhando o java Object
		mv.visitFieldInsn(
				GETFIELD,
				"DartTypes/DartType",
				"value",
				"Ljava/lang/Object;"
		);

		// Fazendo cast pra Boolean
		mv.visitTypeInsn(CHECKCAST, "java/lang/Boolean");

		// Empilhando o valor boolean do Boolean
		mv.visitMethodInsn(
				INVOKEVIRTUAL,
				"java/lang/Boolean",
				"booleanValue",
				"()Z",
				false
		);
	}

	private void visitIf(IfNode node,
						 MethodVisitor mv,
						 HashMap<String, Integer> varIndex){
		Label _if = new Label(), _else = new Label();

		// Carrega um booleano da jvm no topo da stack
		boolEval(node.condition, mv, varIndex);

		// Pula para o label _if caso o valor empilhado por
		// expressionSolver seja equivalente a 1 (verdadeiro)
		mv.visitJumpInsn(IFNE, _if);
		// Faça coisas do else
		if(node.elseStatementsNode != null){
			visitStatements(node.elseStatementsNode.getChildren(), mv, varIndex);
		}

		// Pula para o final do else, ignorando todo o codigo dele completamente
		mv.visitJumpInsn(GOTO, _else);

		// Marca o local no bytecode correspondente ao label _else
		mv.visitLabel(_if);
		// Faça coisas do if
		visitStatements(node.ifStatementsNode.getChildren(), mv, varIndex);

		// Marca o local no bytecode correspondente ao label _if
		mv.visitLabel(_else);

	}

	private void visitWhile(WhileNode node,
							MethodVisitor mv, HashMap<String, Integer> varIndex){
		Label loop = new Label(), end = new Label();

		mv.visitLabel(loop);

		boolEval(node.condition, mv, varIndex);

		mv.visitJumpInsn(IFEQ, end);

		visitStatements(node.block.getChildren(), mv, varIndex);

		mv.visitJumpInsn(GOTO, loop);

		mv.visitLabel(end);
	}

	private void visitStatements(LinkedList<Node> nodes,
								 MethodVisitor mv,
								 HashMap<String, Integer> varIndex){

		for (var childNode: nodes) {
			// System.out.println("Statement Type: " + childNode.getClass().getName());
			switch (childNode.getClass().getSimpleName()){
				case "WhileNode" -> visitWhile((WhileNode) childNode, mv, varIndex);
				case "AssignNode" -> visitAssign((AssignNode) childNode, mv, varIndex);
				case "LiteralNode" -> visitLiteral((LiteralNode) childNode, mv);
				case "IfNode" -> visitIf((IfNode) childNode, mv, varIndex);
				case "FunctionCallNode" -> visitFunctionCall((FunctionCallNode) childNode, mv, varIndex);
				case "VariableDefinitionNode" -> visitVariableDefinition((VariableDefinitionNode) childNode, mv, varIndex);
				default -> visit(childNode);
			}
		}

	}

	private void visitOperation(OperationNode node,
								MethodVisitor mv,
								HashMap<String, Integer> varIndex){

		expressionSolver(node.left, mv, varIndex);
		expressionSolver(node.right, mv, varIndex);

		String methodName;
		String paramDescriptor = typeDescriptorMap.get(node.left.type.name);
		String functionDescriptor = "(" + paramDescriptor + ")" + typeDescriptorMap.get(node.type.name);
		String methodOwner = internalNameMap.get(node.left.type.name);

		switch (node.operation) {
			case Addition -> {
				methodName = "add";
			}
			case Subtraction -> {
				methodName = "sub";
			}
			case Multiplication -> {
				methodName = "mul";
			}
			case Division -> {
				methodName = "div";
			}
			case Less -> {
				methodName = "lt";
				functionDescriptor = "(" + paramDescriptor + ")" + typeDescriptorMap.get(Type.BOOL_NAME);
			}
			case Greater -> {
				methodName = "gt";
				functionDescriptor = "(" + paramDescriptor + ")" + typeDescriptorMap.get(Type.BOOL_NAME);
			}
			case LessOrEqual -> {
				methodName = "lte";
				functionDescriptor = "(" + paramDescriptor + ")" + typeDescriptorMap.get(Type.BOOL_NAME);
			}
			case GreaterOrEqual -> {
				methodName = "gte";
				functionDescriptor = "(" + paramDescriptor + ")" + typeDescriptorMap.get(Type.BOOL_NAME);
			}
			case Equals -> {
				methodName = "eq";
				functionDescriptor = "(Ljava/lang/Object;)" + typeDescriptorMap.get(Type.BOOL_NAME);
			}
			case NotEquals -> {
				methodName = "neq";
				functionDescriptor = "(Ljava/lang/Object;)" + typeDescriptorMap.get(Type.BOOL_NAME);
			}
			default -> {
				System.out.println("Mehhh deu ruim!");
				return;
			}
		}

		mv.visitMethodInsn(INVOKEVIRTUAL,
				methodOwner,
				methodName,
				functionDescriptor,
				false);
	}

	private void expressionSolver(AbstractExpressionNode node,
								  MethodVisitor mv,
								  HashMap<String, Integer> varIndex){

		if(node instanceof LiteralNode) {
			visitLiteral((LiteralNode) node, mv);
			return;
		}

		if(node instanceof VariableNode){
			VariableNode v = (VariableNode) node;

			int index = varIndex.get(v.name);

			mv.visitVarInsn(ALOAD, index);
			return;
		}

		if(node instanceof FunctionCallNode){
			visitFunctionCall((FunctionCallNode) node, mv, varIndex);
		}

		if(node instanceof AssignNode){
			visitAssign((AssignNode) node, mv, varIndex);
		}

		// Estamos assumindo que todas as operações
		// são feitas entre variaveis de  tipos iguais :(
		if(node instanceof OperationNode){
			visitOperation((OperationNode) node, mv, varIndex);
		}
	}

	public void write(FileOutputStream fileOutputStream){
		try {
			fileOutputStream.write(_cw.toByteArray());
		} catch (IOException e) {
			// e.printStackTrace();
			System.out.println(e.getMessage());
			System.out.println("\nDeu Ruim :)\n");
		}
	}
}
