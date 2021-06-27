package SymbolTable;

import Types.Type;

public class Parameter {
    public final Type type;
    public final String name;

    public Parameter(Type type, String name) {
        this.type = type;
        this.name = name;
    }

    @Override
    public String toString() {
        return "Parameter{" +
                "type=" + type +
                ", name='" + name + '\'' +
                '}';
    }
}

