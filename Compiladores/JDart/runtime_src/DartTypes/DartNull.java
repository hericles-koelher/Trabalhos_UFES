package DartTypes;

public class DartNull extends DartType{

	private static DartNull instance;

	private DartNull() {
		super(null);
	}

	public static DartNull getInstance(){
		if(instance == null)
			instance = new DartNull();

		return instance;
	}

	@Override
	public String toString() {
		return "null";
	}

	@Override
	public String getTypeName() {
		return "Null";
	}

	@Override
	public boolean equals(Object o) {
		return o instanceof DartNull;
	}

	@Override
	public int hashCode() {
		return 0;
	}
}