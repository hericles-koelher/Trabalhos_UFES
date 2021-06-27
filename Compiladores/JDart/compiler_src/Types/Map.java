package Types;

final public class Map<T1 extends Type, T2 extends Type> extends Type {
    public final Type subType1;
    public final Type subType2;

    public Map(T1 subType1, T2 subType2) {
        super("Map<" + subType1 + ", " + subType2 + '>');
        this.subType1 = subType1;
        this.subType2 = subType2;
    }
}
