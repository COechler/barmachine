<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 03.01.2005
 // Änderungsdatum: 01.04.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 
 // Fügt die Funktionsbibliotheken ein
 include("../system/functions.inc");
 include("functions.inc");
 
 // Erzeugt den HTML-Kopf
 echo create_htmlheader("Lichtverwaltung"); 
 
 // Erzeugt das Menü der Webseite
 echo create_sitemenu(array("Neues Lichtmodul","Lichtmodule anzeigen"),array("new","show"));
 
 echo "<br>\n";
 
 // Wählt den angeforderten Modus aus
 switch ($_GET[mode])
    {
     case "new":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // Überprüft, ob die eingegebenen Daten gültig sind
      if (check_lightmoduldatas() == true) {$error = false;} else {$error = true;}
     
      // Überprüft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben getätigt worden
      if ($error == false)
          {
	   // Erstellt eine neues Lichtmodul
	   new_lightmodul();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=new\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske für die Lichtmoduldaten
	   echo create_inputmasklightmoduls();
	  
	   echo "</form>\n";
	  }
      
      break;
     
      
     case "edit":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // Überprüft, ob die eingegebenen Daten gültig sind
      if (check_lightmoduldatas() == true) {$error = false;} else {$error = true;}
     
      // Überprüft, ob es einen Fehler bei den eingegebenen Daten gab
      if ($error == false)
          {
	   // Aktualisiert das angegebene Lichtmodul
	   update_lightmodul();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=edit&id=$_GET[id]\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske für die Lichtmoduldaten
	   echo create_inputmasklightmoduls();
	  
	   echo "</form>\n";
	  }
      
      break;
      
      
     case "delete":
     
      // Löscht das angegebene Lichtmodul
      delete_lightmodul();
     
      break;
      
      
     case "show":
     
      // Listet alle vorhanden Lichtmodule inklusive ihres Statuses auf
      echo list_lightmoduls();
      
      break;
      
      
     default:
     
      // Listet alle vorhanden Lichtmodule inklusive ihres Statuses auf
      echo list_lightmoduls();
    }
 
    
 // Erzeugt den HTML-Fuß   
 echo create_htmlfoot();
?>
