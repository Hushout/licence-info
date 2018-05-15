class ['a] file = 
object (self)
	val mutable contenu = []
	method isEmpty = (List.length contenu) = 0
	method push (element : 'a) = contenu <- (element :: contenu)
	method pop = let res = List.hd(contenu) in contenu <- List.tl(contenu); res
	method top = List.hd(contenu)
end;;


let p = new file;;

p#push "coucou";;
p#push "hello";;