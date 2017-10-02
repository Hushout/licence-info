import static org.junit.Assert.*;
import org.junit.Test;

public class StringTest {

    @Test
    public void testConcatenation() {
	String foo = "abc";
	String bar = "def";
	assertEquals("abcdef", foo + bar); }

    @Test
    public void testStartsWith() {
        String foo = "abc";
        assertTrue(foo.startsWith("ab")); }
}
