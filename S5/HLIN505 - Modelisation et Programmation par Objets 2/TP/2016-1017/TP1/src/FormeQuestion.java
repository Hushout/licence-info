
public enum FormeQuestion{
	QCM(1),
	reponseTexteLibre(2),
	texteACompleter(3);
	
	private final int value;
    private FormeQuestion(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}
