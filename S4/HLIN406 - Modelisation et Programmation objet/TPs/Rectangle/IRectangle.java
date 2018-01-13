public interface IRectangle extends IQuadrilatere {
	
	public static final float angle = 90;
	
	public float largeur();
	public float hauteur();
	public float aire();
	public IRectangle plusGrandRectangle();
}