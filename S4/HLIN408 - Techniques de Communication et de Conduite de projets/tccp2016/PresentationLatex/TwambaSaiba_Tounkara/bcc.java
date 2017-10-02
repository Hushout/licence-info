import static org.junit.Assert.*;
import org.junit.Test;
import org.junit.*;
public class StringTest {
    private String foo;
    private String bar;
    @Before
//cette methode sera appelee avant chaque test
    public void setup() {
        foo = "abc";
        bar = "def"; }
    @After
    public void tearDown() {
//dans cet exemple, il n'y a rien a faire mais on peut,
//dans d'autres cas, avoir besoin de fermer une connexion
//a une base de donnees ou de fermer des fichiers
    }
    @Test
    public void testConcatenation() {
        assertEquals("abcdef", foo + bar); }
    @Test
    public void testStartsWith() {
        assertTrue(foo.startsWith("ab")); }
}
