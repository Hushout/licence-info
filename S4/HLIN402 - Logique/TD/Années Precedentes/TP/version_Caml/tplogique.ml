#use "libtplog.ml" ;;


(*** Exercice 1 ***)

let unsymbole : symbole = "p";;
let uneformule : fbf = SYMB "p";; 
let f : fbf = NON(SYMB "p");;
let g : fbf = IMP ( SYMB "p", SYMB "q");;

(* let f1 : fbf = ... *)

