package SymbolTable;

import java.util.HashMap;
import java.util.Stack;

// A ideia é que como durante a visitação a construção da AST
// é feita das folhas até a raiz, então durante a descida
// criamos os escopos, que são passados para os nós de função
// e declaração de variaveis.

public class ScopeManager {
    // A pilha vai ser util na hora de popular a tabela de simbolos
    private static final Stack<Integer> scopeStack = new Stack<>();
    // Já o hashmap vai ser util na hora da busca pelas referencias
    private static final HashMap<Integer, Scope> scopeHashMap = new HashMap<>();
    public static final Integer globalScopeId = 0;
    private static Integer id = globalScopeId;

    // Sempre lembrar de inicializar isso...
    // Poderia criar condições pra isso, mas não tô afim
    public static void init() {
        var globalScope = new Scope(id, null);
        scopeStack.push(id);
        scopeHashMap.put(id, globalScope);
        id++;
    }

    // Retorna o id do escopo em uso...
    public static Integer getScopeId() {
        return scopeStack.peek();
    }

    // Retorna null caso o parentId seja do escopo global
    public static Integer getScopeParentId(Integer scopeId) {
        return scopeHashMap.get(scopeId).parentId;
    }

    public static void createScope() {
        scopeHashMap.put(id, new Scope(id, getScopeId()));
        scopeStack.push(id);
        id++;
    }

    public static void removeScope() {
        scopeStack.pop();
    }
}

class Scope {
    public final Integer id;
    public final Integer parentId;

    Scope(Integer id, Integer parentId) {
        this.id = id;
        this.parentId = parentId;
    }
}
