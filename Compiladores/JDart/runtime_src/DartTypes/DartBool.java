package DartTypes;

public class DartBool extends DartType{
	public DartBool() {
		super(false);
	}
	public DartBool(Boolean value) {
		super(value);
	}

	@Override
	public String getTypeName() {
		return "bool";
	}

	@Override
	public boolean equals(Object o) {
		if(o instanceof DartBool)
			return value.equals(((DartBool) o).value);
		return false;
	}

	@Override
	public int hashCode() {
		return value.hashCode();
	}
}