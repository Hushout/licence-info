class C1	
{	
protected: 	virtual	void f(){}	
	friend class A;	
	friend class B;
public:	
	virtual	void mc1();	
};	

class C2 : public virtual C1	
{
/*protected:
	virtual void f(){}*/
public:	
	virtual	void mc2();
	/*friend class D;	*/
};	

void C1::mc1() {C1 *c1;	c1->f(); C2	*c2; c2->f();}

//a) C1* c1; c1->f(); error: 'f' is a protected member of 'C1'
//Une propriété proteced héritée de C1 est accessible dans une 
//méthode de C2 mais uniquement pour une instance de C2, donc 
//pas pour une instance de C1	

void C2::mc2() {C1 *c1;	c1->f(); C2	*c2; c2->f();}	

class A
{
public:	
	virtual	void ma() {C1 *c1; c1->f(); C2 *c2; c2->f();}	
};	

class B : public virtual A
{
public:	
	virtual	void mb() {C1 *c1; c1->f(); C2 *c2; c2->f();}	
};	

class D
{
public:	
	virtual	void md(){C1 *c1; c1->f(); C2 *c2; c2->f();}	
};	

int	main(){C1 *c1; c1->f(); C2 *c2; c2->f();}


