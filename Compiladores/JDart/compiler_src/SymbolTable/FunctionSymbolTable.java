package SymbolTable;

import java.util.HashMap;
import java.util.Objects;

public class FunctionSymbolTable {
    private final HashMap<Integer, Function> ft = new HashMap<>();

    public boolean lookup(String name, Integer scopeId) {
        return ft.containsKey(Objects.hash(name, scopeId));
    }

    public void addFunction(Function f) throws Exception {
        if (lookup(f.name, f.scopeId))
            throw new Exception("Function " + f.name + " already declared");

        ft.put(f.hashCode(), f);
    }

    public Function getFunc(String funcName, Integer scopeId) {
        Function f = ft.get(Objects.hash(funcName, scopeId));

        if (f == null) {
            throw new RuntimeException("Function " + funcName + " not declared.");
        }

        return f;
    }

    public void print() {
        System.out.println("---Function Symbol Table---");
        System.out.println(ft);
    }
}
