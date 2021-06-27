package SymbolTable;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class VarSymbolTable {
    private final HashMap<Integer, Variable> vt = new HashMap<>();

    public void addVar(Variable v) throws RuntimeException {
        //Nem testei se tem alguma coisa nula...
        // Melhorar isso aqui
        if (lookup(v.name, v.scopeId))
            throw new RuntimeException("Variable " + v.name + " already declared.");

        vt.put(v.hashCode(), v);
    }

    public Variable getVar(String varName, Integer scopeId) {
        Variable v = vt.get(Objects.hash(varName, scopeId));
        if (v == null) {
            throw new RuntimeException("Variable " + varName + " not declared.");
        }

        return v;
    }

    public boolean lookup(String varName, Integer scopeId) {
        return vt.containsKey(Objects.hash(varName, scopeId));
    }

    public void print() {
        System.out.println("Variable Symbol Table:");
        for (Map.Entry<Integer, Variable> entry : this.vt.entrySet()) {
            Variable var = entry.getValue();
            System.out.printf("Entry hash %d -- " + var, entry.getKey());
            System.out.println();
        }
    }
}
