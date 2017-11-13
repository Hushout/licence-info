import static org.junit.Assert.*;
import org.junit.*;

public class TestOperation {

	public void setUp(){
		
	}

	@Test
	public void addition() {
		assertTrue(4 == Operation.addition(2, 2));
	}

	@Test
	public void soustraction() {
		assertTrue(0 == Operation.soustraction(2, 2));
	}

	@Test
	public void multiplication() {
		assertTrue(4 == Operation.multiplication(2, 2));
	}

	@Test
	public void division() {
		assertTrue(2 == Operation.division(4, 2));
	}

	@Test
	public void modulo() {
		assertTrue(0 == Operation.modulo(2, 2));
	}
}