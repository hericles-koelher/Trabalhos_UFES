package SymbolTable;

import Types.Type;

import java.util.Objects;

public class Variable {
    public Type type;
    public String name;
    public Integer scopeId;
    public int declarationLine;

    public Variable(Type type, String name, Integer scopeId, int declarationLine) {
        this.type = type;
        this.name = name;
        this.scopeId = scopeId;
        this.declarationLine = declarationLine;
    }

    @Override
    public String toString() {
        return "Variable{" +
                "type=" + type +
                ", name='" + name + '\'' +
                ", scopeId=" + scopeId +
                ", declarationLine=" + declarationLine +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Variable)) return false;
        Variable variable = (Variable) o;
        return name.equals(variable.name) && scopeId.equals(variable.scopeId);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, scopeId);
    }
}
