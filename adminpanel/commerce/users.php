<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 26.12.2004
 // Änderungsdatum: 30.01.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 
 // Fügt die Funktionsbibliotheken ein
 include("../system/functions.inc");
 include("functions.inc");
 
 // Erzeugt den HTML-Kopf
 echo create_htmlheader("Benutzerverwaltung");
 
 // Erzeugt das Menü der Webseite
 echo create_sitemenu(array("Neuer Benutzer","Benutzer anzeigen"),array("new","show"));
 
 echo "<br>\n";
 
 // Wählt den angeforderten Modus aus
 switch ($_GET[mode])
    {
     case "new":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // Überprüft, ob die eingegebenen Daten gültig sind
      if (check_userdatas() == true) {$error = false;} else {$error = true;}
     
      // Überprüft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben getätigt worden sind
      if ($error == false)
          {
	   // Erstellt einen neuen Benutzer
	   new_user();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=new\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske für die Benutzerdaten
	   create_inputmaskuser();
	  
	   echo "</form>\n";
	  }
      
      break;
     
       
     case "edit":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // Überprüft, ob die eingegebenen Daten gültig sind
      if (check_userdatas() == true) {$error = false;} else {$error = true;}
     
      // Überprüft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben getätigt worden sind
      if ($error == false)
          {
	   // Aktualisiert den angegebene Benutzer
	   update_user();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=edit&id=$_GET[id]\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske für die Benutzerdaten
	   create_inputmaskuser();
	  
	   echo "</form>\n";
	  }
	  
      break;
      
      
     case "delete":
     
      // Löscht den angegebenen Benutzer
      delete_user();
      
      break;
     
       
     case "show":
     
      //Listet alle in der Datenbank vorhandenen Benutzer auf
      echo list_users();
      
      break;
      
     default:
     
      //Listet alle in der Datenbank vorhandenen Benutzer auf
      echo list_users();
    }
    
 echo create_htmlfoot();
?> 
