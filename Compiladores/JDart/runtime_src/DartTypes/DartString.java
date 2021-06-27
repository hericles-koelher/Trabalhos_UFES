package DartTypes;

public class DartString extends DartType{
	public DartString() {
		super(DartTypes.DartNull.getInstance());
	}
	public DartString(String value) {
		super(value);
	}

	@Override
	public String getTypeName() {
		return "String";
	}

	@Override
	public boolean equals(Object o) {
		if(o instanceof DartTypes.DartNull)
			return value.equals(((DartNull) o).value);
		return false;
	}

	@Override
	public int hashCode() {
		return value.hashCode();
	}
}