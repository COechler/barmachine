<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 31.12.2004
 // Änderungsdatum: 31.01.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 
 // Fügt die Funktionsbibliotheken ein
 include("../system/functions.inc");
 include("functions.inc");
 
 // Erzeugt den HTML-Kopf
 echo create_htmlheader("Flüssigkeitenverwaltung");
 
 // Erzeugt das Menü der Webseite
 echo create_sitemenu(array("Neue Flüssigkeit","Flüssigkeiten anzeigen"),array("new","show"));
 
 echo "<br>\n";
 
 // Wählt den angeforderten Modus aus
 switch ($_GET[mode])
    {
     case "new":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // Überprüft, ob die eingegebenen Daten gültig sind
      if (check_liquiddatas() == true) {$error = false;} else {$error = true;}
     
      // Überprüft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben getätigt worden sind
      if ($error == false)
          {
	   // Erstellt eine neue Flüssigkeit
	   new_liquid();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=new\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske für die Flüssigkeitsdaten
	   create_inputmaskliquid();
	  
	   echo "</form>\n";
	  }
   
      break;
     
      
     case "edit":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // Überprüft, ob die eingegebenen Daten gültig sind
      if (check_liquiddatas() == true) {$error = false;} else {$error = true;}
     
      // Überprüft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben getätigt worden sind
      if ($error == false)
          {
	   // Aktualisiert die angegebene Flüssigkeit
	   update_liquid();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=edit&id=$_GET[id]\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske für die Flüssigkeitsdaten
	   create_inputmaskliquid();
	  
	   echo "</form>\n";
	  }
     
      break;
     
      
     case "delete":
     
      // Löscht die angegebene Flüssigkeit
      delete_liquid();
      
      break;
     
      
     case "show":
     
     // Zeigt eine Liste der in der Datenbank vorhandenen Flüssigkeiten an
     list_liquids();
      
     break;
          
      
     default:
     
     // Zeigt eine Liste der in der Datenbank vorhandenen Flüssigkeiten an
     list_liquids();
    }
 
 // Erzeugt den HTML-Fuß   
 echo create_htmlfoot();
?> 