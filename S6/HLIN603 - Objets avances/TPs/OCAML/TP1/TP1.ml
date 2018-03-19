let list1 = [1;2;3;4;5]
let list2 = [6;7;8;9;10]
let list3 = [-1;-3;-4;-2;4]

let rec l_inverse l =
	if List.length l = 0 then []
	else List.append (l_inverse (List.tl l)) ((List.hd l)::[]);;

let rec l_nbocc l e =
	if List.length l = 0 then 0
	else if List.hd l = e then 1 + l_nbocc (List.tl l) e
	else l_nbocc (List.tl l) e

let rec l_est_triee l =
	if List.length l = 0 || List.length l = 1 then true 
	else if List.hd l <= List.hd (List.tl l) then l_est_triee (List.tl l)
	else false

let rec l_insert l e =
	if List.length l = 0 || e <= List.hd l then e::l
	else (List.hd l)::(l_insert (List.tl l) e) 

let rec l_sort l =
	if List.length l = 0 then []
	else l_insert (l_sort (List.tl l)) (List.hd l)

let l_somme l = (List.fold_right (+) l 0)

let l_pos l = (List.for_all (fun x -> x > 0) l)

let l_pos_filter l = (List.filter (fun x -> x >= 0) l)

let l_inverse_left l = (List.fold_left (fun x y ->  y::x) [] l)

let l_map_left func l = (List.fold_left (fun x y -> x @ [func y]) [] l)


type 'a abr =
	| Empty
	| Node of 'a * 'a abr * 'a abr;;


let value x = function
	| Empty -> Empty
 	| Node (y, l, r) -> y;;

let rec insert x = function
	| Empty -> Node(x, Empty, Empty) 
	| Node (y, l, r) ->
		if x <= y then Node(y, (insert x l), r)
		else Node(y, l, (insert x r));;


let abr1 = insert 1 (insert 3 (insert 4 (insert 5 (insert 8 (insert 7 (insert 5 Empty)))))) 

let rec find x = function
	| Empty -> Empty
	| Node (y, l, r) -> 
		if x = y then Node(y, l, r)
		else if x < y then find x l
		else find x r;; 

let rec remove x = function
	| Empty -> Empty
	| Node (y, l, r) -> 
		if x = y then remove x (insert y l)
		else if x < y then Node(y, (remove x l) , r)
		else Node(y, l, (remove x r));; 