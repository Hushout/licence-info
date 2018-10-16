package substitution;
import java.lang.annotation.*; 

@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
public @interface substitutionComportementale {
	boolean isRespected();
}
