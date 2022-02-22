<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 09.01.2005
 // Änderungsdatum: 30.01.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 
 // Fügt die Funktionsbibliotheken ein
 include("../system/functions.inc");
 include("functions.inc");
 
 // Erzeugt den HTML-Kopf
 echo create_htmlheader("Kategorienverwaltung");
 
 // Erzeugt das Menü der Webseite
 echo create_sitemenu(array("Neue Kategorie","Kategorie anzeigen"),array("new","show"));
 
 echo "<br>\n";
 
 // Wählt den angeforderten Modus aus
 switch ($_GET[mode])
    { 
     case "new":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // Überprüft, ob die eingegebenen Daten gültig sind
      if (check_categorydatas() == true) {$error = false;} else {$error = true;}
     
      // Überprüft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben getätigt worden sind
      if ($error == false)
          {
	   // Erstellt eine neue Cocktailkategorie
	   new_category();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=new\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske für die Cocktailkategoriedaten
	   create_inputmaskcategory();
	  
	   echo "</form>\n";
	  }

     break;
     
     
     case "edit":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // Überprüft, ob die eingegebenen Daten gültig sind
      if (check_categorydatas() == true) {$error = false;} else {$error = true;}
     
      // Überprüft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben getätigt worden sind
      if ($error == false)
          {
	   // Aktualisiert die angegebene Cocktailkategorie
	   update_category();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=edit&id=$_GET[id]\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske für die Cocktailkategoriedaten
	   create_inputmaskcategory();
	  
	   echo "</form>\n";
	  }

     break;
     
     
     case "delete":
     
      // Löscht die angegebene Flüssigkeit
      delete_category();
      
     break;
     
     
     case "show":
      
      // Listet alle vorhandenen Kategorien auf
      echo list_categories();
      
     break;
     
     
     default:
      // Listet alle vorhandenen Kategorien auf
      echo list_categories();
    }
  
  // Erzeugt den HTML-Fuß   
  echo create_htmlfoot();
 ?>