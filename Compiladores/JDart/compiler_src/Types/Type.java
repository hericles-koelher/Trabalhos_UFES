package Types;

import java.util.Objects;

public class Type {

    public static final String INT_NAME = "int";
    public static final String DOUBLE_NAME = "double";
    public static final String BOOL_NAME = "bool";
    public static final String STRING_NAME = "String";
    public static final String DYNAMIC_NAME = "dynamic";
    public static final String NULL_NAME = "Null";

    public static final Type TYPE_INT = new Type(INT_NAME);
    public static final Type TYPE_DOUBLE = new Type(DOUBLE_NAME);
    public static final Type TYPE_BOOL = new Type(BOOL_NAME);
    public static final Type TYPE_STRING = new Type(STRING_NAME);
    public static final Type TYPE_DYNAMIC = new Type(DYNAMIC_NAME);
    public static final Type TYPE_NULL = new Type(NULL_NAME);
    public String name;

    protected Type(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Type)) return false;
        Type type = (Type) o;
        return name.equals(type.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name);
    }
}
