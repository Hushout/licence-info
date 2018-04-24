public interface IFileAttente {

    void entre(Personne p);
    
    Personne sort();

    boolean estVide();
    
    int taille();

    void vider();
}
