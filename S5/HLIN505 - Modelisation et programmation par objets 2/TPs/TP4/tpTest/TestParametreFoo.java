import java.util.*;

@RunWith(Parameterized.class)
public class TestParametreFoo {

	private static SUT sut;
	private int x;
	private int y;
	private int z;
	private int t;
	private int res;
	
	@Parameters
    public static Collection data() {
        return Arrays.asList(new Object[][]{
                {1, 3, 5, 2, 3},
                {5, 3, 1, 2, 5},
                {5, 1, 3, 2, 5},
                {3, 1, 5, 2, 3},
                {3, 5, 1, 2, 3},
                {1, 5, 3, 2, 5}
        });
    }
	
	
	public TestParametreFoo(int x, int y, int z, int t, int res) {
		this.x = x;
		this.y = y;
		this.z = z;
		this.res = res;
		this.t=t;
	}


	@Before
	public void setUp() throws Exception {
	}

	@Test
	public void testFoo() {
		sut=new SUT(x, y, z);
		assertThat(sut.foo(t), is(res));
	}

}
