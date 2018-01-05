
public enum NiveauPrimaire{
	CP(1),
	CE1(2),
	CE2(3),
	CM1(4),
	CM2(5);

    private final int value;
    private NiveauPrimaire(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}
