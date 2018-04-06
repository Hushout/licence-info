(* $Id$ *)

(**** Exercice 1 ****)

(* Q1 *)

let rec rev = function
  | [] -> []
  | e :: tl -> (rev tl) @ [e];;

let l = [1; 2; 3; 4; 5];;
rev l;;

(* Q2 *)

let rec count x = function
  | [] -> 0
  | e :: tl ->
    if e = x then 1 + (count x tl)
    else count x tl;;

let l = [1; 2; 1; 3; 4];;
count 1 l;;
count 2 l;;
count 5 l;;

(* Q3 *)

let rec is_sorted = function
  | [] -> true
  | [e] -> true
  | a :: b :: tl -> (a <= b) && (is_sorted (b :: tl));;

let l = [1; 2; 3; 4; 5];;
let l'= [5; 4; 3; 2; 1];;
is_sorted l;;
is_sorted l';;

(* Q4 *)

let rec insert x = function
  | [] -> [x]
  | e :: tl ->
    if x <= e then x :: e :: tl
    else e :: (insert x tl);;

let l = [1; 3; 4; 5];;
insert 2 l;;
insert 6 l;;

(* Q5 *)

let rec insertion_sort = function
  | [] -> []
  | e :: tl -> insert e (insertion_sort tl);;

let l = [5; 4; 3; 2; 1];;
insertion_sort l;;

(**** Exercice 2 ****)

(* Q1 *)

type form =
  | Top | Bot
  | Var of string
  | Not of form
  | And of form * form
  | Or of form * form
  | Imp of form * form
  | Equ of form * form;;

(* Q2 *)

let rec string_of_form = function
  | Top -> "true"
  | Bot -> "false"
  | Var n -> n
  | Not f -> "~" ^ (string_of_form f)
  | And (f1, f2) ->
    "(" ^ (string_of_form f1) ^ "/\\" ^ (string_of_form f2) ^ ")"
  | Or (f1, f2) ->
    "(" ^ (string_of_form f1) ^ "\\/" ^ (string_of_form f2) ^ ")"
  | Imp (f1, f2) ->
    "(" ^ (string_of_form f1) ^ "->" ^ (string_of_form f2) ^ ")"
  | Equ (f1, f2) ->
    "(" ^ (string_of_form f1) ^ "<->" ^ (string_of_form f2) ^ ")";;

let f = Imp (And (Var "A", Var "B"), Or (Not (Var "C"), Top));;
print_endline (string_of_form f);;

(* Q3 *)

let simplif_and = function
  | (f, Top) | (Top, f) -> f
  | (_, Bot) | (Bot, _) -> Bot
  | _ -> assert false;;

let simplif_or = function
  | (_, Top) | (Top, _) -> Top
  | (f, Bot) | (Bot, f) -> f
  | _ -> assert false;;

let simplif_imp = function
  | (_, Top) | (Bot, _) -> Top
  | (f, Bot) -> Not f
  | (Top, f) -> f
  | _ -> assert false;;

let simplif_equ = function
  | (f, Top) | (Top, f) -> f
  | (_, Bot) | (Bot, _) -> Bot
  | _ -> assert false;;

let rec simplif_form = function
  | And (f1, f2) ->
     let f1' = simplif_form f1
     and f2' = simplif_form f2 in
     simplif_and (f1', f2')
  | Or (f1, f2) ->
     let f1' = simplif_form f1
     and f2' = simplif_form f2 in
     simplif_or (f1', f2')
  | Imp (f1, f2) ->
     let f1' = simplif_form f1
     and f2' = simplif_form f2 in
     simplif_imp (f1', f2')
  | Equ (f1, f2) ->
     let f1' = simplif_form f1
     and f2' = simplif_form f2 in
     simplif_equ (f1', f2')
  | f -> f;;

let f = And (Var "A", Or (Var "B", Top));;
let f' = simplif_form f;;
print_endline (string_of_form f);;
print_endline (string_of_form f');;

(* Q4 *)

let rec eval_form l = function
  | Top -> true
  | Bot -> false
  | Var n ->
     (try List.assoc n l
      with Not_found -> failwith (n ^ " not in the assignment!"))
  | Not f -> not (eval_form l f)
  | And (f1, f2) ->
     let f1' = eval_form l f1
     and f2' = eval_form l f2 in
     f1' && f2'
  | Or (f1, f2) ->
     let f1' = eval_form l f1
     and f2' = eval_form l f2 in
     f1' || f2'
  | Imp (f1, f2) ->
     let f1' = eval_form l f1
     and f2' = eval_form l f2 in
     (not f1') || f2'
  | Equ (f1, f2) ->
     let f1' = eval_form l f1
     and f2' = eval_form l f2 in
     f1' = f2';;

let f = Imp (Var "A", Imp (Var "B", Var "A"));;
let l = [("A", true); ("B", true)];;
eval_form l f;;

(* Q5 *)

let rec get_vars l = function
  | Var n -> if not(List.mem n l) then l @ [n] else l
  | Not f -> get_vars l f
  | And (f1, f2) ->
     let l1 = get_vars l f1 in
     let l2 = get_vars l1 f2 in l2
  | Or (f1, f2) ->
     let l1 = get_vars l f1 in
     let l2 = get_vars l1 f2 in l2
  | Imp (f1, f2) ->
     let l1 = get_vars l f1 in
     let l2 = get_vars l1 f2 in l2
  | Equ (f1, f2) ->
     let l1 = get_vars l f1 in
     let l2 = get_vars l1 f2 in l2
  | _ -> l;;

let rec is_tauto f asg = function
  | [] -> eval_form asg f
  | v :: tl ->
     (is_tauto f (asg @ [(v, true)]) tl) &&
       (is_tauto f (asg @ [(v, false)]) tl);;

let f = Imp (Var "A", Imp (Var "B", Var "A"));;
let l = get_vars [] f;;
is_tauto f [] l;;
let f = Imp (Var "A", Imp (Var "B", Var "C"));;
let l = get_vars [] f;;
is_tauto f [] l;;

(**** Exercice 3 ****)

(* Q1 *)

let list_sum l = List.fold_right (fun a b -> a + b) l 0;;
let l = [1; 2; 3; 4; 5];;
list_sum l;;

(* Q2 *)

let list_is_pos = List.for_all (fun a -> a >= 0);;
let l1 = [1; 2; 3; 4; 5];;
let l2 = [1; 2; -3; 4; 5];;
list_is_pos l1;;
list_is_pos l2;;

(* Q3 *)

let list_pos = List.filter (fun a -> a >= 0);;
let l1 = [1; 2; 3; 4; 5];;
let l2 = [1; 2; -3; 4; 5];;
list_pos l1;;
list_pos l2;;

(* Q4 *)

let list_rev = List.fold_left (fun a b -> b::a) [];;
let l = [1; 2; 3; 4; 5];;
list_rev l;;

(* Q5 *)

let list_map f = List.fold_left (fun a b -> a @ [(f b)]) [];;
let l = [1; 2; 3; 4; 5];;
list_map (fun a -> a + 1) l;;

(**** Exercice 4 ****)

type abr = Empty | Node of int * abr * abr;;

let rec insert n = function
  | Empty -> Node (n, Empty, Empty)
  | Node (m, l, r) as abr ->
    if n < m then Node (m, insert n l, r)
    else if n > m then Node (m, l, insert n r)
    else abr;;

insert 6 (insert 10 (insert 3 (insert 8 Empty)));;
