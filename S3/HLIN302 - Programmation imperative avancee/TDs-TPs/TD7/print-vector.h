#ifndef __PRINT_VECTOR_H
#define __PRINT_VECTOR_H

template<typename Vector>	
void read(std::istream& is, Vector& T){  
  for(size_t i=0;i<T.size();i++)
     {is>>T.at(i);}  	     
}

template<typename Vector>
void write(std::ostream& os, const Vector& T){
  os<<"code generique: ";
  for(size_t i=0;i<T.size();i++)
  {os<<T.at(i)<<(i!=T.size()-1?",":"");}
  os<<std::endl;				
} 	     				     


#endif
