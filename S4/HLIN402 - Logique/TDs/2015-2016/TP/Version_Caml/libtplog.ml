open List;;

(*********************************** GENERIC TYPE : SET *************************************)
   
Printf.printf "\n\n\n\n\n     ********** definition type generique ensemble **********\n";;

module type ELT =
  sig
    type t
    val equal: t * t -> bool
(*  val compare: t -> t -> int *)
  end 


 module SET = functor (DefinedELT : ELT) ->
  struct
    type elt = DefinedELT.t
    type t = elt list

    let empty : t = []

    let is_empty : t -> bool = fun(s) -> s=[]
 
    let rec cardinal : t -> int = fun(s) ->
      if s=[] then 0 else 1 + cardinal(tl(s))

    let rec member : elt * t -> bool = fun(e,s) ->
      if s=[] then false else DefinedELT.equal(e,hd(s)) || member(e,tl(s))

    let rec subset : t * t -> bool = fun(s1,s2) ->
      if s1=[] then true else member(hd(s1),s2) && subset(tl(s1),s2)
	
    let equal : t * t -> bool = fun(s1,s2) ->
      subset(s1,s2) && subset(s2,s1)

    let rec add : elt * t -> t = fun(e,s) -> 
      if member(e,s) then s else e::s

    let rec remove : elt * t -> t = fun(e,s) ->
      if s=[] then s else
	if DefinedELT.equal(e,hd(s)) then tl(s) else hd(s)::remove(e,tl(s))

    let choice : t -> elt = fun(s) ->
      if s=[] then failwith "choice function on empty set" else hd(s)

    let rec union : t * t -> t = fun(s1,s2) ->
      if s1=[] then s2 else union(tl(s1), add(hd(s1),s2))

    let rec inter : t * t -> t = fun(s1,s2) ->
      if s1=[] then [] else
	if member(hd(s1),s2) then hd(s1)::inter(tl(s1),s2) else inter(tl(s1),s2)

    let rec diff : t * t -> t = fun(s1,s2) ->
       if s1=[] then [] else
	if member(hd(s1),s2) then diff(tl(s1),s2) else hd(s1)::diff(tl(s1),s2)
  end 



(******************************* TYPE : FBF ******************************************************)

;;Printf.printf "\n\n     ********** definition type fbf  **********\n";;


type symbole = string

type fbf = SYMB of symbole | VRAI | FAUX | NON of fbf | ET of fbf * fbf | OU of fbf * fbf | IMP of fbf * fbf | EQU of fbf * fbf 
       
let is_atom : fbf -> bool = fun(f) ->
  match f with 
    SYMB _ -> true
  | VRAI -> true 
  | FAUX -> true
  | _ -> false
  
let is_symb : fbf -> bool = fun(f) -> 
  match f with 
    SYMB _ -> true
  | _ -> false
  
let is_cst_vrai : fbf -> bool = fun(f) ->
  match f with 
    VRAI -> true
  | _ -> false
  
let is_cst_faux : fbf -> bool = fun(f) ->
  match f with
    FAUX -> true
  | _ -> false
      
let is_neg : fbf -> bool = fun(f) ->
  match f with
    NON _ -> true
  | _ -> false
      
let is_bin : fbf -> bool = fun(f) ->
  match f with 
    ET _ -> true
  | OU _ -> true
  | IMP _ -> true
  | EQU _ -> true
  | _ -> false
  
let is_conj : fbf -> bool = fun(f) ->
  match f with
    ET _  -> true
  | _ -> false 
  
let is_disj : fbf -> bool = fun(f) -> 
  match f with 
    OU _  -> true
  | _ -> false 
  
let is_impl : fbf -> bool = fun(f) ->
  match f with 
    IMP _  -> true
  | _ -> false 
  
let is_equi : fbf -> bool = fun(f) ->
  match f with 
    EQU _  -> true
  | _ -> false 
  
let symb : fbf -> symbole = fun(f) ->
  (* only for symbol atom *)
  match f with
    SYMB x -> x  
  | _ -> failwith "not a symbol atom" (*to suppress warning*) 
      
let ssfbf : int * fbf -> fbf = fun(i,f) ->
  (* only for non atomic proposition *) 
  match (i,f) with
    1, NON x -> x
  | 1, ET (x,y) -> x
  | 1, OU (x,y) -> x 
  | 1, IMP (x,y) -> x
  | 1, EQU (x,y) -> x
  | 2, ET (x,y) -> y
  | 2, OU (x,y) -> y 
  | 2, IMP (x,y) -> y
  | 2, EQU (x,y) -> y
  | _ -> failwith ("no such ssfbf") (*to suppress warning*) 

(*************************** Diverses fonctions utiles *********************************)

;;Printf.printf "\n\n     ********** definition fonctions diverses **********\n";;

(**** fonction maximum ****)

let maximum : int * int -> int = fun(a,b) ->
  if a>b then a else b

(**** concatenation de 2 chaines ****)

let concatener : string * string -> string = fun(s1,s2) -> String.concat "" [s1;s2]


(***************************************************************************************)

;;

Printf.printf "\n\n\n\n     ********** FIN CHARGEMENT libtplog.ml **********\n";;
