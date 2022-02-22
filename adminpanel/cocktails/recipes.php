<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 01.01.2005
 // �nderungsdatum: 06.02.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 
 // F�gt die Funktionsbibliotheken ein
 include("../system/functions.inc");
 include("functions.inc");
 
 // Erzeugt den HTML-Kopf
 echo create_htmlheader("Rezeptverwaltung");
 
 // Erzeugt das Men� der Webseite
 echo create_sitemenu(array("Neuer Cocktail","Cocktails anzeigen"),array("new","show"));
 
 echo "<br>\n";
 
 // W�hlt den angeforderten Modus aus
 switch ($_GET[mode])
    {
     case "new":
      
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // �berpr�ft, ob die eingegebenen Daten g�ltig sind
      if (check_recipedatas() == true) {$error = false;} else {$error = true;}
     
      // �berpr�ft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben get�tigt worden sind
      if ($error == false)
          {
	   // Erstellt ein neues Cocktailrezept
	   new_recipe();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=new\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske f�r die Cocktaildaten
	   create_inputmaskrecipe();
	  
	   echo "</form>\n";
	  }
      
      break;
     
       
     case "edit":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // �berpr�ft, ob die eingegebenen Daten g�ltig sind
      if (check_recipedatas() == true) {$error = false;} else {$error = true;}
     
      // �berpr�ft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben get�tigt worden sind
      if ($error == false)
          {
	   // Aktualisiert das angegebene Cocktailrezept
	   update_recipe();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=edit&id=$_GET[id]\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske f�r die Cocktaildaten
	   create_inputmaskrecipe();
	  
	   echo "</form>\n";
	  }
           
      break;
     
      
     case "delete":
      
      // L�scht das angegebene Cocktailrezept
      delete_recipe();
      
      break;
     
     
     case "show":
     
      // Zeigt eine Liste der in der Datenbank vorhandenen Rezepte an
      echo list_recipes();
      
      break;
     
      
     default:
     
      // Zeigt eine Liste der in der Datenbank vorhandenen Rezepte an
      echo list_recipes();
    }
 
 // Erzeugt den HTML-Fu�   
 echo create_htmlfoot();
?>  
