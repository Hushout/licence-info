(* $Id$ *)

(**** Exercice 1 ****)

class min (xi : int) =
object (self)
  val mutable x = xi
  method get = x
  method set n = x <- n
  method min y = if self#get < y then self#get else y
end;;

class min_zero xi =
object
  inherit min xi
  method get = 0
end;;

let o1 = new min 4;;
let o2 = new min_zero 4;;
o1#min 2;;
o1#min 7;;
o2#min 2;;
o2#min (-2);;

(**** Exercice 2 ****)

(* Q1 *)

class account b =
object (self)
  val mutable balance = 0.0
  method get = balance
  method deposit a = balance <- balance +. a
  method withdraw a = balance <- balance -. a
  method print = print_float balance; print_newline ()
  initializer self#deposit b
end;;

class interest_account b =
object
  inherit account b
  method interest =
    balance <- balance +. 5. *. balance /. 100.
end;;

class secure_account b =
object
  inherit account b as super
  method withdraw a =
    if (balance -. a) >= 0. then super#withdraw a
    else failwith "Not enough money!"
end;;

class bank =
object
  val mutable acc_list = []
  method add (a : account) = acc_list <- a::acc_list
  method balance = List.fold_left (fun a b -> a +. b#get) 0. acc_list
  method print = List.iter (fun a -> a#print) acc_list
  method fees = List.iter (fun a -> a#withdraw (a#get *. 5. /. 100.)) acc_list
end;;

let a = new account 50.;;
let i = new interest_account 100.;;
let s = new secure_account 150.;;
let b = new bank;;
b#add a;;
b#add (i:>account);;
b#add s;;
b#balance;;
b#print;;
b#fees;;
b#print;;

(* Q2 *)

class ['a] collection =
object
  val mutable acc_list = []
  method add (a : 'a) = acc_list <- a::acc_list
end;;

class bank2 =
object
  inherit [account] collection
  method balance = List.fold_left (fun a b -> a +. b#get) 0. acc_list
  method print = List.iter (fun a -> a#print) acc_list
  method fees = List.iter (fun a -> a#withdraw (a#get *. 5. /. 100.)) acc_list
end;;

let b = new bank2;;
b#add a;;
b#add (i:>account);;
b#add s;;
b#balance;;
b#print;;
b#fees;;
b#print;;

(**** Exercice 3 ****)

class cte n =
object
  val content = n
  method eval = content
  method print = print_int n
end;;

class inv (e : inv) =
object
  val content = e
  method eval = -e#eval
  method print =
    print_string "(-";
    content#print;
    print_endline ")"
end;;

class add (l : add) (r : add) =
object
  val left = l
  val right = r
  method eval = left#eval + right#eval
  method print =
    print_string "(";
    left#print;
    print_string " + ";
    right#print;
    print_endline ")"
end;;

class sub (l : sub) (r : sub) =
object
  val left = l
  val right = r
  method eval = left#eval - right#eval
  method print =
    print_string "(";
    left#print;
    print_string " - ";
    right#print;
    print_endline ")"
end;;

class mul (l : mul) (r : mul) =
object
  val left = l
  val right = r
  method eval = left#eval * right#eval
  method print =
    print_string "(";
    left#print;
    print_string " * ";
    right#print;
    print_endline ")"
end;;

class div (l : div) (r : div) =
object
  val left = l
  val right = r
  method eval = left#eval / right#eval
  method print =
    print_string "(";
    left#print;
    print_string " / ";
    right#print;
    print_endline ")"
end;;

let e = new add (new cte 1) (new cte 2);;
e#eval;;
e#print;;

(**** Exercice 4 ****)

class virtual ['a] abr =
object
  method virtual insert : 'a -> 'a abr
  method virtual find : 'a -> bool
end;;

class ['a] empty =
object
  inherit ['a] abr
  method insert n = new node n (new empty) (new empty)
  method find n = false
end

and ['a] node n (l : 'a abr) (r : 'a abr) =
object (self)
  inherit ['a] abr
  val value = n
  val mutable left = l
  val mutable right = r
  method insert (n : 'a) =
    (if n < value then left <- left#insert n
     else if n > value then right <- right#insert n);
    (self :> 'a abr)
  method find (n : 'a) =
    if n == value then true
    else if n < value then left#find n
    else right#find n
end;;

let t = ((((new empty)#insert 8)# insert 3)# insert 10)#insert 6;;
t#find 8;;
t#find 2;;
