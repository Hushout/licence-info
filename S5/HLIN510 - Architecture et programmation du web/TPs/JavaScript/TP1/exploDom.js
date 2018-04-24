
function analyseDOM(noeud, indent, dest) {
  if (noeud == null  || noeud == dest) return; /* evite recursion infinie ! */
  var type = 'NiElemNiAttribNiText';
  switch (noeud.nodeType) {
  case 1 : type = 'Element';
    break;
  case 2 : type = 'Attribut';
    break;
  case 3 : type = 'Text';
    break;
  }
  var t = document.createTextNode('');
  for (var i=0; i < indent; i++) {
    t.appendData("___ ");
  }
  t.appendData(type+"-"+noeud.nodeName+" "+(noeud.nodeValue?'"'+noeud.nodeValue+'"':"")+" Enfants : "+noeud.childNodes.length);
  dest.appendChild(t);
  dest.appendChild(document.createElement("br"));
  for (var enfant=0; enfant < noeud.childNodes.length; enfant++) {
    analyseDOM(noeud.childNodes.item(enfant),indent+1,dest);
  }
}

function lanceAnalyseDOM() {
  var divDOM = document.createElement("div"); 
  /* division dans la quelle on va afficher le DOM */
  divDOM.appendChild(document.createTextNode(''));
   /* texte à afficher */
  divDOM.style.cssText = 'left:1500px; top:1500px; background:yellow;';
   /* style des textes dans divDOM (jaune) */
  document.body.appendChild(divDOM); /* ajout au body */
  analyseDOM(document, 0, divDOM); /* analyse de tout le doc */
}

//setTimeout('lanceAnalyseDOM()', 100);
// ou

 window.onload=function(){lanceAnalyseDOM();}
//window.onload=lanceAnalyseDOM; // ne pas mettre de guillemets !

// les deux fonctionnent
