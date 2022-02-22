<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 03.01.2005
 // �nderungsdatum: 01.04.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 
 // F�gt die Funktionsbibliotheken ein
 include("../system/functions.inc");
 include("functions.inc");
 
 // Erzeugt den HTML-Kopf
 echo create_htmlheader("Lichtverwaltung"); 
 
 // Erzeugt das Men� der Webseite
 echo create_sitemenu(array("Neues Lichtmodul","Lichtmodule anzeigen"),array("new","show"));
 
 echo "<br>\n";
 
 // W�hlt den angeforderten Modus aus
 switch ($_GET[mode])
    {
     case "new":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // �berpr�ft, ob die eingegebenen Daten g�ltig sind
      if (check_lightmoduldatas() == true) {$error = false;} else {$error = true;}
     
      // �berpr�ft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben get�tigt worden
      if ($error == false)
          {
	   // Erstellt eine neues Lichtmodul
	   new_lightmodul();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=new\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske f�r die Lichtmoduldaten
	   echo create_inputmasklightmoduls();
	  
	   echo "</form>\n";
	  }
      
      break;
     
      
     case "edit":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // �berpr�ft, ob die eingegebenen Daten g�ltig sind
      if (check_lightmoduldatas() == true) {$error = false;} else {$error = true;}
     
      // �berpr�ft, ob es einen Fehler bei den eingegebenen Daten gab
      if ($error == false)
          {
	   // Aktualisiert das angegebene Lichtmodul
	   update_lightmodul();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=edit&id=$_GET[id]\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske f�r die Lichtmoduldaten
	   echo create_inputmasklightmoduls();
	  
	   echo "</form>\n";
	  }
      
      break;
      
      
     case "delete":
     
      // L�scht das angegebene Lichtmodul
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
 
    
 // Erzeugt den HTML-Fu�   
 echo create_htmlfoot();
?>
