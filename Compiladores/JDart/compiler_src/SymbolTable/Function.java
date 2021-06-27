package SymbolTable;

import Types.Type;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

public class Function {
    public final Integer scopeId;
    public final int declarationLine;
    public final Type type;
    public final String name;
    public final LinkedList<Parameter> positionalParameters;
    public final LinkedList<Parameter> optionalPositionalParameters;
    public final HashMap<String, Parameter> namedParameters;

    public Function(Integer scopeId, int declarationLine, Type type,
                    String name, LinkedList<Parameter> positionalParameters,
                    LinkedList<Parameter> optionalPositionalParameters) {
        this.scopeId = scopeId;
        this.declarationLine = declarationLine;
        this.type = type;
        this.name = name;
        this.positionalParameters = positionalParameters;
        this.optionalPositionalParameters = optionalPositionalParameters;
        this.namedParameters = null;
    }

    public Function(Integer scopeId, int declarationLine, Type type,
                    String name, LinkedList<Parameter> positionalParameters,
                    HashMap<String, Parameter> namedParameters) {
        this.scopeId = scopeId;
        this.declarationLine = declarationLine;
        this.type = type;
        this.name = name;
        this.positionalParameters = positionalParameters;
        this.namedParameters = namedParameters;
        this.optionalPositionalParameters = null;
    }

    @Override
    public String toString() {
        return "Function{" +
                "scopeId=" + scopeId +
                ", type=" + type +
                ", name='" + name + '\'' +
                ", positionalParameters=" + positionalParameters +
                ", optionalPositionalParameters=" + optionalPositionalParameters +
                ", namedParameters=" + namedParameters +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Function)) return false;
        Function function = (Function) o;
        return scopeId.equals(function.scopeId) && name.equals(function.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, scopeId);
    }
}
