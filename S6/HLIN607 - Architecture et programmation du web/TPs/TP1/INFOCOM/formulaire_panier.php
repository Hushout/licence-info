<!DOCTYPE html>
<html>
    <body>
        <?php
            //On affiche toutes les variables une par une
            foreach($_GET as $key=>$get_data){
                //Si on tombe sur une variable tableau, on affiche son contenu de façon lisible
                if( is_array( $get_data ) ){
                    $array = $get_data;
                    foreach($array as $key=>$value){
                        echo $key . " is " . $value . "<br>";
                    }
                }
                else{
                    echo $key . " = " . $get_data . "<br>";
                }
            }
        ?>
    </body>
</html>
