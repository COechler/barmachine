<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 04.01.2005
 // Änderungsdatum: 02.02.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 
 // Fügt die Funktionsbibliotheken ein
 include("../system/functions.inc");
 include("functions.inc");
 
 // Erzeugt den HTML-Kopf
 echo create_htmlheader("Transaktionsübersicht"); 
 
 // Erzeugt das Menü der Webseite
 echo create_sitemenu(array("Neue Transaktion","Transaktionen anzeigen"),array("new","show"));
 
 echo "<br>\n";
 
 // Wählt den angeforderten Modus aus
 switch ($_GET[mode])
    {
     case "new":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // Überprüft, ob die eingegebenen Daten gültig sind
      if (check_transactiondatas() == true) {$error = false;} else {$error = true;}
     
      // Überprüft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben getätigt worden sind
      if ($error == false)
          {
	   // Erstellt eine neue Transaktion
	   new_transaction();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=new\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske für die Transaktionsdaten
	   create_inputmasktransaction();
	  
	   echo "</form>\n";
	  } 
     
      break;
      
      
     case "edit":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // Überprüft, ob die eingegebenen Daten gültig sind
      if (check_transactiondatas() == true) {$error = false;} else {$error = true;}
     
      // Überprüft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben getätigt worden sind
      if ($error == false)
          {
	   // Aktualisiert die angegebene Transaktion
	   update_transaction();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=edit&id=$_GET[id]\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske für die Transaktionsdaten
	   create_inputmasktransaction();
	  
	   echo "</form>\n";
	  }
      
      break;
      
     
     case "delete":
     
      // Löscht die angegebene Transaktion
      delete_transaction();
      
      break;
      
      
     case "show":
     
       // Listet alle vorhandenen Transaktionen auf
       echo list_transactions();
       
      break;
      
      
     default:
      // Listet alle vorhandenen Transaktionen auf
      echo list_transactions();
    }

 // Erzeugt den HTML-Fuß   
 echo create_htmlfoot();
?>