<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 31.12.2004
 // �nderungsdatum: 31.01.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 
 // F�gt die Funktionsbibliotheken ein
 include("../system/functions.inc");
 include("functions.inc");
 
 // Erzeugt den HTML-Kopf
 echo create_htmlheader("Fl�ssigkeitenverwaltung");
 
 // Erzeugt das Men� der Webseite
 echo create_sitemenu(array("Neue Fl�ssigkeit","Fl�ssigkeiten anzeigen"),array("new","show"));
 
 echo "<br>\n";
 
 // W�hlt den angeforderten Modus aus
 switch ($_GET[mode])
    {
     case "new":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // �berpr�ft, ob die eingegebenen Daten g�ltig sind
      if (check_liquiddatas() == true) {$error = false;} else {$error = true;}
     
      // �berpr�ft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben get�tigt worden sind
      if ($error == false)
          {
	   // Erstellt eine neue Fl�ssigkeit
	   new_liquid();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=new\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske f�r die Fl�ssigkeitsdaten
	   create_inputmaskliquid();
	  
	   echo "</form>\n";
	  }
   
      break;
     
      
     case "edit":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // �berpr�ft, ob die eingegebenen Daten g�ltig sind
      if (check_liquiddatas() == true) {$error = false;} else {$error = true;}
     
      // �berpr�ft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben get�tigt worden sind
      if ($error == false)
          {
	   // Aktualisiert die angegebene Fl�ssigkeit
	   update_liquid();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=edit&id=$_GET[id]\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske f�r die Fl�ssigkeitsdaten
	   create_inputmaskliquid();
	  
	   echo "</form>\n";
	  }
     
      break;
     
      
     case "delete":
     
      // L�scht die angegebene Fl�ssigkeit
      delete_liquid();
      
      break;
     
      
     case "show":
     
     // Zeigt eine Liste der in der Datenbank vorhandenen Fl�ssigkeiten an
     list_liquids();
      
     break;
          
      
     default:
     
     // Zeigt eine Liste der in der Datenbank vorhandenen Fl�ssigkeiten an
     list_liquids();
    }
 
 // Erzeugt den HTML-Fu�   
 echo create_htmlfoot();
?> 