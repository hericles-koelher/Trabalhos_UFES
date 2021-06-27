package DartTypes;

public abstract class DartType {
	public Object value;

	public DartType(Object value){
		this.value = value;
	}

	public String toString() {
		return value.toString();
	}

	public DartBool eq(Object o) {
		if(o instanceof DartType)
			return new DartBool(value.equals(((DartType) o).value));
		return new DartBool(false);
	}

	public DartBool neq(Object o){
		return new DartBool(!((Boolean)eq(o).value));
	}

	public abstract String getTypeName();
	public abstract int hashCode();
}
