<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 04.01.2005
 // �nderungsdatum: 02.02.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 
 // F�gt die Funktionsbibliotheken ein
 include("../system/functions.inc");
 include("functions.inc");
 
 // Erzeugt den HTML-Kopf
 echo create_htmlheader("Transaktions�bersicht"); 
 
 // Erzeugt das Men� der Webseite
 echo create_sitemenu(array("Neue Transaktion","Transaktionen anzeigen"),array("new","show"));
 
 echo "<br>\n";
 
 // W�hlt den angeforderten Modus aus
 switch ($_GET[mode])
    {
     case "new":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // �berpr�ft, ob die eingegebenen Daten g�ltig sind
      if (check_transactiondatas() == true) {$error = false;} else {$error = true;}
     
      // �berpr�ft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben get�tigt worden sind
      if ($error == false)
          {
	   // Erstellt eine neue Transaktion
	   new_transaction();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=new\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske f�r die Transaktionsdaten
	   create_inputmasktransaction();
	  
	   echo "</form>\n";
	  } 
     
      break;
      
      
     case "edit":
     
      // Setzt die Fehlervariable auf "true"
      $error = true;
      
      // �berpr�ft, ob die eingegebenen Daten g�ltig sind
      if (check_transactiondatas() == true) {$error = false;} else {$error = true;}
     
      // �berpr�ft, ob es einen Fehler bei den eingegebenen Daten gab bzw. ob schon Eingaben get�tigt worden sind
      if ($error == false)
          {
	   // Aktualisiert die angegebene Transaktion
	   update_transaction();
	  }
       else
          {
	   echo "<form action=\"$_SERVER[PHP_SELF]?mode=edit&id=$_GET[id]\" method=\"post\">\n";
	  
	   // Generiert die Eingabemaske f�r die Transaktionsdaten
	   create_inputmasktransaction();
	  
	   echo "</form>\n";
	  }
      
      break;
      
     
     case "delete":
     
      // L�scht die angegebene Transaktion
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

 // Erzeugt den HTML-Fu�   
 echo create_htmlfoot();
?>