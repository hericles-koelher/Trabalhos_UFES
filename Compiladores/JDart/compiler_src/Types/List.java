package Types;

// Infelizmente acabou não saindo Lista e Mapa na geração de codigo :(

final public class List<T extends Type> extends Type {
    //vai ser util quando tiver de comparar com o tipo dos elementos da lista
    public final Type subType;

    public List(T subType) {
        super("List<" + subType + '>');
        this.subType = subType;
    }

    @Override
    public String toString() {
        return "List<" + subType + ">";
    }
}
