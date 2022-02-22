<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 01.01.2005
 // Änderungsdatum: 12.04.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 // Funktion erstellt eine Auswahlbox mit allen verfügbaren Status
 function create_statusselection($status)
    {
     // Leert die Stringvariable
     $string = "";
     
     // Startet die Auswahlbox
     $string .= "<select size=\"1\" name=\"status\">";
      
     // Erzeugt ein leere Auswahloption
     $string .= " <option value=\"\">&nbsp;</option>";
     
     // Erzeugt die Auswahloption für den Status 'open' und überprüft dabei, ob der Status ausgewählt wurde
     if ($status == "open") {$string .= " <option value=\"open\" selected>open</option>";} else {$string .= " <option value=\"open\">open</option>";}
     
     // Erzeugt die Auswahloption für den Status 'open' und überprüft dabei, ob der Status ausgewählt wurde
     if ($status == "wait") {$string .= " <option value=\"wait\" selected>wait</option>";} else {$string .= " <option value=\"wait\">wait</option>";}
     
     // Erzeugt die Auswahloption für den Status 'open' und überprüft dabei, ob der Status ausgewählt wurde
     if ($status == "mix") {$string .= " <option value=\"mix\" selected>mix</option>";} else {$string .= " <option value=\"mix\">mix</option>";}
     
     // Erzeugt die Auswahloption für den Status 'open' und überprüft dabei, ob der Status ausgewählt wurde
     if ($status == "finished") {$string .= " <option value=\"finished\" selected>finished</option>";} else {$string .= " <option value=\"finished\">finished</option>";}
     
     // Erzeugt die Auswahloption für den Status 'open' und überprüft dabei, ob der Status ausgewählt wurde
     if ($status == "abort") {$string .= " <option value=\"abort\" selected>abort</option>";} else {$string .= " <option value=\"abort\">abort</option>";}
     
     // Beendet die Auswahlbox
     $string .= "</select>";
     
     // Gibt die fertig erzeugte Auswahlbox mit allen in der Datenbank vorhanden Cocktails zurück
     return $string;
    }
    
 
 // Funktion zeigt grafisch den Status des Tanks an
 function show_tankstatus()
    {
     // Erzeugt den Header für ein PNG-Bild
     header("Content-type: image/png");
     
     // Gibt dem Browser und dem Proxyserver die Anweisung, den Graphen nicht zu speichern
     header("Cache-Control: no-store, no-cache, must-revalidate");
     header("Cache-Control: post-check=0, pre-check=0", false);
     header("Pragma: no-cache");
     
     // Erstellt ein PNG-Bild mit der angegeben Größe
     $image = imagecreate(110,120);
     
     // Füllt das PNG-Bild mit der angegebenen Hintergrundfarbe aus
     imagefill($image,0,120,imagecolorallocate($image,255,255,255));

     // Überprüft, ob die angegebene Tank-ID eine Zahl ist und nicht leer ist
     if (ctype_digit($_GET[id]) == true && $_GET[id] != "")
        {
	 // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("mixer");
     
         // Überprüft, ob beim Verbinden ein Fehler aufgetreten ist
         if ($conresult == false)
	    {
	     imageTTFText($image,6,0,7,63,imagecolorallocate($image,0,0,0),$_SERVER[DOCUMENT_ROOT]."/system/verdana.ttf","Es gab leider einen Fehler!");
	    }
	 else
	    {
	     // Sendet eine SELECT-Anweisung an die Datenbank
	     $sqlresult = mysql_query("SELECT 10 + (100 - ROUND(tank_volume/10,0)) AS value FROM tanks WHERE tank_id = '$_GET[id]';");
	     
	     // Überprüft, ob es einen Fehler bei dem auslesen des Wertes des aktuellen Tankvolumens für den Graphen
	     if ($sqlresult == false)
	        {
		 imageTTFText($image,6,0,7,63,imagecolorallocate($image,0,0,0),$_SERVER[DOCUMENT_ROOT]."/system/verdana.ttf","Es gab leider einen Fehler!");
		}
	     else
	        {
		 // Zeichnet den Rahmen um die Bargraphanzeige
		 imageline ($image,9,9,41,9,imagecolorallocate($image,0,0,0));
		 imageline ($image,9,10,9,110,imagecolorallocate($image,0,0,0));
		 imageline ($image,41,10,41,110,imagecolorallocate($image,0,0,0));
		 imageline ($image,9,111,41,111,imagecolorallocate($image,0,0,0));
		 
		 // Zeichnet die Skalierung
		 imageline ($image,46,9,51,9,imagecolorallocate($image,0,0,0));
		 imageline ($image,46,35,51,35,imagecolorallocate($image,0,0,0));
		 imageline ($image,46,60,51,60,imagecolorallocate($image,0,0,0));
		 imageline ($image,46,85,51,85,imagecolorallocate($image,0,0,0));
		 imageline ($image,46,111,51,111,imagecolorallocate($image,0,0,0));
		 
		 // Erzeugt die Beschriftung für die Skalierung
		 imageTTFText($image,6,0,56,12,imagecolorallocate($image,0,0,0),$_SERVER[DOCUMENT_ROOT]."/system/verdana.ttf","1000 ml");
		 imageTTFText($image,6,0,61,38,imagecolorallocate($image,0,0,0),$_SERVER[DOCUMENT_ROOT]."/system/verdana.ttf","750 ml");
		 imageTTFText($image,6,0,61,63,imagecolorallocate($image,0,0,0),$_SERVER[DOCUMENT_ROOT]."/system/verdana.ttf","500 ml");
		 imageTTFText($image,6,0,61,88,imagecolorallocate($image,0,0,0),$_SERVER[DOCUMENT_ROOT]."/system/verdana.ttf","250 ml");
		 imageTTFText($image,6,0,71,114,imagecolorallocate($image,0,0,0),$_SERVER[DOCUMENT_ROOT]."/system/verdana.ttf","0 ml");
		 
		 // Liest den Wert des aktuellen Tankvolumens für den Graphen aus
		 $row = mysql_fetch_array($sqlresult);
		 
		 // Zeichnet den Balken für den Graphen
		 imagefilledrectangle ($image,10,$row[value],40,110,imagecolorallocate($image,49,48,156));
		}
	    }
	}
     else
        {
	 imageTTFText($image,6,0,7,63,imagecolorallocate($image,0,0,0),$_SERVER[DOCUMENT_ROOT]."/system/verdana.ttf","Es gab leider einen Fehler!");
	}
	
     // Gibt das Bild aus
     imagepng ($image);
    }
 
 
 // Funktion erzeugt eine Auswahlbox mit allen zur Verfügung stehenden Flüssigkeiten
 function create_liquidselection1($tankid,$liquidid)
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("mixer");
	 
     // Überprüft, ob beim Verbinden ein Fehler aufgetreten ist
     if ($conresult == false)
	{
	 // Gibt eine Fehlermeldung zurück
	 return show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten","error");
	     
	 // Beendet die Ausführung der Funktion
	 exit();
	}
     else
        {
	 // Sendet eine SELECT-Anweisung an die Datenbank
	 $sqlresult = mysql_query("SELECT liquid_id, liquid_name FROM liquids ORDER BY liquid_name ASC;");
	 
	 if ($sqlresult == false)
	    {
	     // Beendet die geöffnete Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Leert die Stringvariable
	     $string = "";
	     
	     $string .= "<select name=\"liquidname$tankid\" size=\"1\">";
	     $string .= "<option value=\"\"></option>";
	     
	     // Liest die Werte aus
	     while ($row = mysql_fetch_array($sqlresult))
	        {
		 // Überprüft, ob diese Flüssigkeit die aktuelle Flüssigkeit im Tank ist
		 if ($row[liquid_id] == $liquidid)
		    {
		     // Schreibt "selected" in die "selected"-Variable
		     $selected = "selected";
		    }

		 $string .= "<option value=\"$row[liquid_id]\" $selected>$row[liquid_name]</option>";
		 
		 // Löscht den Inhalt der "selected"-Variable
		 $selected = "";
		}
	     
	     $string .= "</select>";
	     
	     // Gibt die Auswahlbox mit den verfügbaren Flüssigkeiten zurück
	     return $string;
	    }
	}
    }
    
 
 // Funktion aktualisiert die Inhalte der Tanks
 function update_tank($tankid,$liquidid,$tankamount)
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("mixer");
	 
     // Überprüft, ob beim Verbinden ein Fehler aufgetreten ist
     if ($conresult == false)
	{
	 // Gibt eine Fehlermeldung zurück
	 return show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten","error");
	     
	 // Beendet die Ausführung der Funktion
	 exit();
	}
     else
        {
	 // Sendet eine UPDATE-Anweisung an die Datenbank
	 $sqlresult = mysql_query("UPDATE tanks SET liquid_id = TRIM('$liquidid'), tank_volume = TRIM('$tankamount') WHERE tank_id='$tankid' LIMIT 1;");
	}
    }
 
    
 // Funktion erzeugt eine Eingabemaske für Transaktionsdaten
 function create_inputmasktransaction()
    {
     // Überprüft, ob eine Transaktions-ID vorliegt, der Modus "edit" ausgewählt wurde und keine Werte übergeben worden sind
     if ($_GET[id] != "" && $_GET[mode] == "edit" && isset($_POST[cocktail]) == false && isset($_POST[status]) == false)
        {
	 // Überprüft, ob die angegebene Transaktions-ID eine Zahl ist
	 if (ctype_digit($_GET[id]) == true)
	    {
	     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
	     $conresult = db_connect("mixer");
	     
	     // Überprüft, ob beim Verbinden ein Fehler aufgetreten ist
	     if ($conresult == false)
	        {
		 // Zeigt eine Fehlermeldung an, dass ein Fehler beim Verbinden zur Datenbank aufgetreten ist
		 echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten!","error");
		 
		 // Gibt 'false' zurück
		 return false;
		 
		 // Beendet die Ausführung der Funktion
		 exit();
		}
	     else
	        {
		 // Sendet eine SELECT-Anweisung an die Datenbank
		 $sqlresult = mysql_query("SELECT cocktail_id, transaction_status FROM transactions WHERE transaction_id = '$_GET[id]';");
		 
		 // Überprüft, ob es einen Fehler beim Abfragen der Daten der angegebenen Transaktion gab
		 if ($sqlresult == false)
		    {
		     // Zeigt eine Fehlermeldung an, dass keine Daten zur angegebenen Transaktion abgerufen werden konnten
		     echo show_systemmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten!","error");
		     
		     // Beendet die Verbindung zum Datenbankserver
		     mysql_close($conresult);
		     
		     // Gibt 'false' zurück
		     return false;
		     
		     // Beendet die Ausführung der Funktion
		     exit();
		    }
		 else
		    {
		     // Überprüft ob wirklich nur die Daten von einer Transaktion abgefragt worden sind
		     if (mysql_num_rows($sqlresult) == 1)
		        {
			 // Liest die Werte zu der angegebenen Transaktion aus 
			 $row = mysql_fetch_array($sqlresult);     
		     
		         // Schreibt die Werte in die richtige Variable
			 $cocktail = $row[cocktail_id];
			 $status = $row[transaction_status];
			 
			}
		     else
		        {
			 // Zeigt eine Fehlermeldung an, dass keine Daten zur angegebenen Transaktion abgerufen werden konnten
			 echo show_systemmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten!","error");
			 
			 // Beendet die Verbindung zum Datenbankserver
			 mysql_close($conresult);
			 
			 // Gibt 'false' zurück
			 return false;
			 
			 // Beendet die Ausführung der Funktion
			 exit();
			}
		    }
		}
	    }
	 else
	    {
	     // Gibt eine Fehlermeldung an, dass ein interner Verarbeitungsfehler aufgetreten
	     echo show_sysetmmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten!","error");
	     
	     // Gibt 'false' zurück
	     return false;
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	}
     else
        {
	 // Schreibt die schon eingetragen Angaben in die richtigen Variablen
	 $cocktal = $_POST[cocktail];
	 $status = $_POST[status];
	}
	
     // Wählt die richtige Beschriftung für den Sendeknopf aus
     if	($_GET[id] != "" && $_GET[mode] == "edit")
        {
	 // Schreibt den Bildnamen für den Button in die entsprechende Variable
	 $imagename = "update.png";
	}
     else
        {
	 // Schreibt den Bildnamen für den Button in die entsprechende Variable
	 $imagename = "insert.png";
	}
	
     // Leert die Stringvariable
     $string = "";
     
     $string .= "<table>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">Cocktail:</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">".create_cocktailselection($cocktail,"cocktail")."</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">&nbsp;</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">Status:</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">".create_statusselection($status)."</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">&nbsp;</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input type=\"image\" src=\"../system/$imagename\"></td>\n";
     $string .= " </tr>\n";
     $string .= "</table>\n";
     
     // Gibt die fertige Eingabemaske aus
     echo $string;
     
     // Gibt 'true' zurück
     return true;
    }
   
 
 // Funktion überprüft die Daten für die eingegebene Transaktion
 function check_transactiondatas()
    {
     // Überprüft ob alle Inhalte der Eingabemaske gesendet wurden
     if (isset($_POST[cocktail]) == true && isset($_POST[status]) == true)
        {
	 // Setzt die Fehlerzahlvariable auf 0
	 $errorcount = 0;
	 
	 // Überprüf, dass ein gültiger Status ausgewählt worden ist
	 if (!($_POST[status] == "open" || $_POST[status] == "wait" || $_POST[status] == "mix" || $_POST[status] == "finished" || $_POST[status] == "abort")) {$errorcount++; $error[$errorcount] = "Der angegebene Status ist ungültig!";}
	 
	 // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("mixer");
	     
	 // Überprüft, ob beim Verbinden ein Fehler aufgetreten ist
	 if ($conresult == false)
	    {
	     // Zeigt eine Fehlermeldung an
	     echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten","error");
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Sendet eine SELECT-Anweisung an die Datenbank, um abzufragen ob der angegebene Cocktail in der Datenbank existiert
	     $sqlresult = mysql_query("SELECT NULL FROM cocktails WHERE cocktail_id = TRIM('$_POST[cocktail]');");
	     
	     // Überprüft, ob es einen Fehler beim Abfragen der Cocktails gab
	     if ($sqlresult == false)
		{
		 // Zeigt eine Fehlermeldung an, dass keine Daten zur angegebenen Cocktailkategorie abgerufen werden konnten
		 echo show_systemmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten!","error");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zurück
		 return false;
		 
		 // Beendet die Ausführung der Funktion
		 exit();
		}
	     else
	        {
		 // Überprüft, dass noch keine Cocktailkategorie mit dem selben Namen in der Datenbank eingetragen ist
		 if (mysql_num_rows($sqlresult) != 1) {$errorcount++; $error[$errorcount] = "Der angegeben Cocktail ist ungültig!";}
		}
	    }
	    
	 // Überprüft, ob mindestens ein Fehler bei der Überprüfung der Daten aufgetreten ist
	 if ($errorcount == 0)
	    {
	     // Es wird 'true' zurück gegebenen, da kein Fehler aufgetreten ist
	     return true;
	    }
	 else
	    {
	     // Gibt eine Liste mit Fehlermeldungen aus
	     create_errorlist($error);
	     
	     // Gibt 'false' zurück, da mindestens ein Fehler aufgetreten ist
	     return false;
	    } 
	}
     else
        {
	 // Gibt 'false' zurück
	 return false;
	}
    }
    
	 
 // Funktion erstellt eine neue Transaktion
 function new_transaction()
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("mixer");
	 
     // Überprüft, ob beim Verbinden ein Fehler aufgetreten ist
     if ($conresult == false)
	{
	 // Zeigt eine Fehlermeldung an, dass ein Fehler beim Verbinden zur Datenbank aufgetreten ist
	 echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten!","error");
	     
	 // Gibt 'false' zurück
	 return false;
	     
	 // Beendet die Ausführung der Funktion
	 exit();
	}
     else
	{
	 // Sendet eine INSERT-Anweisung an die Datenbank
	 $sqlresult = mysql_query("INSERT INTO transactions (cocktail_id, transaction_status) VALUES (TRIM('$_POST[cocktail]'),TRIM('$_POST[status]'));");
	 
	 // Überprüft, ob es einen Fehler bei der Erstellung einer neuen Transaktion gab
	 if ($sqlresult == false)
	    {
	     // Zeigt eine Fehlermeldung an, dass die neue Transaktion nicht in die Datebank eingetragen werden konnte
	     echo show_systemmessage("Beim Erstellen der neuen Transaktion ist leider ein Fehler aufgetreten!","error");
		 
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Gibt 'false' zurück
	     return false;
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Zeigt eine Erfolgsmeldung an, dass die neue Transaktion erfolgreich in die Datenbank eingetragen worden ist
	     echo show_systemmessage("Die neue Transaktion wurde erfolgreich erstellt!","success");
	     
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Gibt 'true' zurück
	     return true;
	    }
	}
    }
    
 
 // Funktion aktualisiert die angegebene Transaktion
 function update_transaction()
    {
     // Überprüft, ob die angegebene Transaktions-ID eine Zahl ist
     if (ctype_digit($_GET[id]) == true)
        {
         // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("mixer");
     
         // Überprüft, ob beim Verbinden ein Fehler aufgetreten ist
         if ($conresult == false)
	    {
	     // Zeigt eine Fehlermeldung an, dass ein Fehler beim Verbinden zur Datenbank aufgetreten ist
	     echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten!","error");
	     
	     // Gibt 'false' zurück
	     return false;
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Sendet eine UPDATE-Anweisung an die Datenbank
	     $sqlresult = mysql_query("UPDATE transactions SET cocktail_id = TRIM('$_POST[cocktail]'), transaction_status = TRIM('$_POST[status]') WHERE transaction_id = '$_GET[id]' LIMIT 1;");
	     
	     // Überprüft, ob es einen Fehler bei der Aktualisierung der Transaktion gab
	     if ($sqlresult == false)
	        {
	         // Zeigt eine Fehlermeldung an, dass die angegebene Transaktion nicht aktualisiert werden konnte
	         echo show_systemmessage("Beim Aktualisieren der Transaktion ist leider ein Fehler aufgetreten!","error");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zurück
	         return false;
	     
	         // Beendet die Ausführung der Funktion
	         exit();
	        }
	     else
	        {
		 // Zeigt eine Erfolgsmeldung an, dass die angegebene Transaktion erfolgreich aktualisiert worden ist
	         echo show_systemmessage("Die Transaktion wurde erfolgreich aktualisiert!","success");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'true' zurück
	         return true;
		}
	    }
	}
     else
        {
	 // Gibt eine Fehlermeldung an, dass ein interner Verarbeitungsfehler aufgetreten
	 echo show_sysetmmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten","error");
	 
	 // Gibt 'false' zurück
	 return false;
	  
	 // Beendet die Ausführung der Funktion
	 exit();
	}
    }
    
	 
 // Funktion löscht die angegebene Transaktion
 function delete_transaction()
    {
     // Überprüft, ob die angegebene Transaktions-ID eine Zahl ist
     if (ctype_digit($_GET[id]) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
	 $conresult = db_connect("mixer");
	 
	 // Überprüft, ob beim Verbinden ein Fehler aufgetreten ist
	 if ($conresult == false)
	    {
	     // Zeigt eine Fehlermeldung an, dass ein Fehler beim Verbinden zur Datenbank aufgetreten ist
	     echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten!","error");
	     
	     // Gibt 'false' zurück
	     return false;
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Sendet eine DELETE-Anweisung an die Datenbank
	     $sqlresult = mysql_query("DELETE FROM transactions WHERE transaction_id = '$_GET[id]' LIMIT 1;");
	     
	     // Überprüft, ob es einen Fehler bei dem Löschen der Transaktion gab
	     if ($sqlresult == false)
	        {
	         // Zeigt eine Fehlermeldung an, dass die angegebene Transaktion nicht gelöscht werden konnte
	         echo show_systemmessage("Beim Löschen der Transaktion ist leider ein Fehler aufgetreten!","error");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zurück
		 return false;
		 
		 // Beendet die Ausführung der Funktion
		 exit();
	        }
	     else
	        {
		 // Zeigt eine Erfolgsmeldung an, dass die angegebene Transaktion erfolgreich gelöscht worden ist
		 echo show_systemmessage("Die Transaktion wurde erfolgreich gelöscht!","success");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'true' zurück
		 return true;
		}
	    }
	}
     else
        {
	 // Gibt eine Fehlermeldung an, dass ein interner Verarbeitungsfehler aufgetreten
	 echo show_sysetmmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten","error");
	  
	 // Gibt 'false' zurück
	 return false;
	  
	 // Beendet die Ausführung der Funktion
	 exit();
	}
    }
    
    
 // Funktion listet alle vorhandenen Transaktionen auf
 function list_transactions()
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("mixer");
     
     // Überprüft, ob beim Verbinden ein Fehler aufgetreten ist
     if ($conresult == false)
	{
	 // Gibt eine Fehlermeldung zurück
	 return show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten","error");
	     
	 // Beendet die Ausführung der Funktion
	 exit();
	}
     else
        {
	 // Sendet eine SELECT-Anweisung an die Datenbank
	 $sqlresult = mysql_query("SELECT transactions.transaction_id AS transaction_id, IFNULL(cocktails.cocktail_name,\"(unbekannt)\") AS cocktail_name, DATE_FORMAT(transactions.transaction_timestamp,'%d.%m.%Y  %H:%i:%S') AS transaction_timestamp, transactions.transaction_status AS transaction_status FROM transactions LEFT JOIN cocktails ON transactions.cocktail_id = cocktails.cocktail_id;");
	 
	 if ($sqlresult == false)
	    {
	     // Gibt eine Fehlermeldung zurück
	     return show_systemmessage("Es ist ein Fehler bei der Abfrage der Transaktionen aus der Datenbank aufgetreten","error");
	     
	     // Beendet die geöffnete Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Leert die Stringvariable
	     $string = "";
	     
	     // Überprüft, ob mindestens eine Transaktion vorhanden ist
	     if (mysql_num_rows($sqlresult) > 0)
	        {
		 $string .= "<table style=\"width:800px;\">\n";
		 
		 $string .= " <tr>\n";
		 $string .= "  <td class=\"head\">ID</td>\n";
		 $string .= "  <td class=\"head\">Cocktailname</td>\n";
		 $string .= "  <td class=\"head\">Zeitstempel</td>\n";
		 $string .= "  <td class=\"head\">Status</td>\n";
		 $string .= "  <td class=\"head\" colspan=\"2\"><b>Aktionen</b></td>\n";
		 $string .= " </tr>\n";
		 
		 // Setzt die Anfangshintergrundfarbe
		 $color = "#E6E6E6";
		 
		 // Liest alle Werte der Lichtmodule aus der Datenbank aus
		 while ($row = mysql_fetch_array($sqlresult))
		    {
		     $string .= " <tr style=\"background-color:$color;\">\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:center;\">$row[transaction_id]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:left;\">$row[cocktail_name]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:center;width:150px;\">$row[transaction_timestamp]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:center;width:100px;\">$row[transaction_status]</td>\n";
		     $string .= "  <td class=\"action\"><a href=\"$_SERVER[PHP_SELF]?mode=edit&id=$row[transaction_id]\"><img class=\"action\" src=\"../system/edit.png\" alt=\"&Auml;ndert die Transaktion\"></a></td>\n";
		     $string .= "  <td class=\"action\"><a href=\"$_SERVER[PHP_SELF]?mode=delete&id=$row[transaction_id]\" onclick=\"return confirm('Soll die Transaktion (ID: $row[transaction_id]) wirklich gelöscht werden?')\"><img class=\"action\" src=\"../system/delete.png\" alt=\"L&ouml;scht die Transaktion\"></a></td>\n";
		     $string .= " </tr>\n";
		     
		     // Sorgt für eine immer wechselnde Hinterhintergrundfarbe der Zeilen
		     if ($color == "#E6E6E6") {$color = "#D5D6D5";} else {$color = "#E6E6E6";}
		    }
		    
		 $string .= "</table>\n";
		 
		 return $string;
		}
	     else
	        {
		 // Gibt eine Hinweismeldung zurück
	         return show_systemmessage("Es sind keine Transaktionen vorhanden!","info");
		}
	    }
	}
    }
?>