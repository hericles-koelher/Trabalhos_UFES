package Types;

import java.util.HashMap;

// Era mais util quando ainda tinhamos esperança de implementar List e Map...
public class TypeManager {
    private static final HashMap<String, Type> compositeTypes = new HashMap<>();

    // Permitindo somente variações de list e map...
    public static void addType(Type type) throws Exception {
        switch (type.toString()) {
            case Type.INT_NAME:
            case Type.DOUBLE_NAME:
            case Type.BOOL_NAME:
            case Type.STRING_NAME:
            case Type.DYNAMIC_NAME:
            case Type.NULL_NAME:
                throw new Exception("Cannot add type " + type.name + " !");
            default:
                compositeTypes.put(type.toString(), type);
        }
    }

    public static boolean lookup(String typeName) {
        switch (typeName) {
            case Type.INT_NAME:
            case Type.DOUBLE_NAME:
            case Type.BOOL_NAME:
            case Type.STRING_NAME:
            case Type.DYNAMIC_NAME:
            case Type.NULL_NAME:
                return true;
            default:
                return compositeTypes.containsKey(typeName);
        }
    }

    public static Type getType(String typeName) {
        switch (typeName) {
            case Type.INT_NAME:
                return Type.TYPE_INT;
            case Type.DOUBLE_NAME:
                return Type.TYPE_DOUBLE;
            case Type.BOOL_NAME:
                return Type.TYPE_BOOL;
            case Type.STRING_NAME:
                return Type.TYPE_STRING;
            case Type.DYNAMIC_NAME:
                return Type.TYPE_DYNAMIC;
            case Type.NULL_NAME:
                return Type.TYPE_NULL;
            default:
                return compositeTypes.get(typeName);
        }
    }
}
