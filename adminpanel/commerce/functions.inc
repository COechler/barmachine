<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 26.12.2004
 // Änderungsdatum: 12.04.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 
  // Funktion erzeugt eine Eingabemaske für Transaktionsdaten
 function create_inputmasktransaction()
    {
     // Überprüft, ob eine Transaktions-ID vorliegt, der Modus "edit" ausgewählt wurde und keine Werte eingegeben worden sind
     if ($_GET[id] != "" && $_GET[mode] == "edit" && isset($_POST[description]) == false && isset($_POST[amount]) == false && isset($_POST[userid]) == false)
        {
	 // Überprüft, ob die angegebene Transaktions-ID eine Zahl ist
	 if (ctype_digit($_GET[id]) == true)
	    {
	     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
	     $conresult = db_connect("commerce");
	     
	     // Überprüft, ob beim Verbinden ein Fehler aufgetretten ist
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
		 $sqlresult = mysql_query("SELECT transaction_description, transaction_amount, user_id FROM transactions WHERE transaction_id = '$_GET[id]' LIMIT 1;");
		 
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
			 $description = $row[transaction_description];
			 $amount = $row[transaction_amount];
			 $userid = $row[transaction_userid];
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
	     // Zeigt eine Fehlermeldung an, dass es einen internen Fehler gab
	     echo show_systemmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten!","error");
	     
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Gibt 'false' zurück
	     return false;
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	}
     else
        {
	 // Schreibt die schon eingetragen Angaben in die richtigen Variablen
	 $description = $_POST[description];
	 $amount = $_POST[amount];
	 $userid = $_POST[userid];
	}
	
     // Wählt die richtige Beschriftung für den Sendeknopf aus
     if	($_GET[id] != "" && $_GET[mode] == "edit")
        {
	 // Schreibt den Bildname für den Button in die entsprechende Variable
	 $imagename = "update.png";
	}
     else
        {
	 // Schreibt den Bildname für den Button in die entsprechende Variable
	 $imagename = "insert.png";
	}

     // Leert die Stringvariable
     $string = "";
     
     $string .= "<table>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">Beschreibung:&nbsp;&nbsp;(max. 255 Zeichen)</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input class=\"standard\" type=\"text\" name=\"description\" value=\"$description\" maxlength=\"255\"></td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"></td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">Betrag:&nbsp;&nbsp;(max. -9999,99 bis 9999,99)</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input class=\"standard\" style=\"width:50px;\" type=\"text\" name=\"amount\" value=\"$amount\" maxlength=\"8\">&nbsp;&nbsp;&euro;</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"></td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">Benutzer:</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">".create_userselection($userid,"userid")."</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"></td>\n";
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


 // Funktion erzeugt die Eingabemaske für die Benutzerdaten
 function create_inputmaskuser()
    {
     // Überprüft, ob eine Benutzer-ID vorliegt, der Modus "edit" ausgewählt wurde und keine Werte eingegeben worden sind
     if ($_GET[id] != "" && $_GET[mode] == "edit" && isset($_POST[firstname]) == false && isset($_POST[lastename]) == false && isset($_POST[birthday_day]) == false && isset($_POST[birthday_month]) == false && isset($_POST[birthday_year]) == false)
        {
	 // Überprüft, ob die angegebene Benutzer-ID eine Zahl ist
	 if (ctype_digit($_GET[id]) == true)
	    {
	     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
	     $conresult = db_connect("commerce");
	     
	     // Überprüft, ob beim Verbinden ein Fehler aufgetretten ist
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
		 $sqlresult = mysql_query("SELECT user_firstname, user_lastname, user_birthday FROM users WHERE user_id = '$_GET[id]' LIMIT 1;");
		 
		 // Überprüft, ob es einen Fehler beim Abfragen der Daten des angegebenen Benutzers gab
		 if ($sqlresult == false)
		    {
		     // Zeigt eine Fehlermeldung an, dass keine Daten zum angegebenen Benutzer abgerufen werden konnten
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
		     // Überprüft ob wirklich nur die Daten von einem Benutzer abgefragt worden sind
		     if (mysql_num_rows($sqlresult) == 1)
		        {
			 // Liest die Werte zu dem angegebenen Benutzer aus 
			 $row = mysql_fetch_array($sqlresult);     
		     
		         // Schreibt die Werte in die richtige Variable
			 $firstname = $row[user_firstname];
			 $lastname = $row[user_lastname];
			 $birthday = explode("-",$row[user_birthday]);
			}
		     else
		        {
			 // Zeigt eine Fehlermeldung an, dass keine Daten zum angegebenen Benutzer abgerufen werden konnten
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
	 $firstname = $_POST[firstname];
	 $lastname = $_POST[lastname];
	 $birthday[2] = $_POST[birthday_day];
	 $birthday[1] = $_POST[birthday_month];
	 $birthday[0] = $_POST[birthday_year];
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
     $string .= " <td class=\"standard\">Vorname:&nbsp;&nbsp;(max. 30 Zeichen)</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input class=\"standard\" style=\"width:280px;\" type=\"text\" name=\"firstname\" value=\"$firstname\" maxlength=\"30\"></td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"></td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">Nachname:&nbsp;&nbsp;(max. 30 Zeichen)</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input class=\"standard\" style=\"width:280px;\" type=\"text\" name=\"lastname\" value=\"$lastname\" maxlength=\"30\"></td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"></td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">Geburtsdatum:</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input class=\"standard\" style=\"width:20px;\" type=\"text\" name=\"birthday_day\" value=\"$birthday[2]\" maxlength=\"2\">&nbsp;.&nbsp;<input class=\"standard\" style=\"width:20px;\" type=\"text\" name=\"birthday_month\" value=\"$birthday[1]\" maxlength=\"2\">&nbsp;.&nbsp;<input class=\"standard\" style=\"width:40px;\" type=\"text\" name=\"birthday_year\" value=\"$birthday[0]\" maxlength=\"4\"></td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"></td>\n";
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

    
 // Funktion überprüft die eingegeben Flüssigkeitsdaten
 function check_transactiondatas()
    {
     // Überprüft ob alle Inhalte der Eingabemaske gesendet wurden
     if (isset($_POST[description]) == true && isset($_POST[amount]) == true && isset($_POST[userid]) == true)
        {
	 // Setzt die Fehlerzahlvariable auf 0
	 $errorcount = 0;
	 
	 // Überprüft, dass alle Pflichtangaben gemacht worden sind
	 if ($_POST[description] == "") {$errorcount++; $error[$errorcount] = "Es wurde keine Beschreibung eingegeben!";}
	 if ($_POST[amount] == "") {$errorcount++; $error[$errorcount] = "Es wurde kein Betrag eingegeben!";}
	 if ($_POST[userid] == "") {$errorcount++; $error[$errorcount] = "Es wurde kein Benutzer angegeben!";}
	 
	 // Überprüft, dass die Eingaben nicht zu lang sind
	 if (strlen($_POST[description]) > 255) {$errorcount++; $error[$errorcount] = "Die eingegebene Beschreibung ist zu lang!";}
	 
	 // Überprüft, dass der eingegebene Betrag nicht zu klein ist
	 if (doubleval(str_replace(",",".",$_POST[amount])) < -9999.99)  {$errorcount++; $error[$errorcount] = "Der eingegebene Betrag ist zu klein!";}
	 
	 // Überprüft, dass der eingegebene Betrag nicht zu groß ist
	 if (doubleval(str_replace(",",".",$_POST[amount])) > 9999.99)  {$errorcount++; $error[$errorcount] = "Der eingegebene Betrag ist zu groß!";}
	 
	 // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("commerce");
	     
	 // Überprüft, ob beim Verbinden ein Fehler aufgetretten ist
	 if ($conresult == false)
	    {
	     // Zeigt eine Fehlermeldung an
	     echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetretten","error");
	     
	     // Gibt 'false' zurück
	     return false;
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Sendet eine SELECT-Anweisung an die Datenbank, um abzufragen ob der angegeben Benutzer in der Datenbank existiert
	     $sqlresult = mysql_query("SELECT NULL FROM users WHERE user_id = TRIM('$_POST[userid]');");
	     
	     // Überprüft, ob es einen Fehler beim Abfragen der Benutzer gab
	     if ($sqlresult == false)
		{
		 // Zeigt eine Fehlermeldung an, dass keine Daten zum angegebenen Benutzer abgerufen werden konnten
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
		 // Überprüft, dass der angegebene Benutzer in der Datenbank vorhanden ist
		 if (mysql_num_rows($sqlresult) != 1) {$errorcount++; $error[$errorcount] = "Der angegebene Benutzer existiert nicht in der Datenbank!";}
		}
	    }
	    
	 // Überprüft, ob mindestens ein Fehler bei der Überprüfung der Daten aufgetretten ist
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
 
 
 // Funktion überprüft die eingegeben Benutzerdaten
 function check_userdatas()
    {
     // Überprüft ob alle Inhalte der Eingabemaske gesendet wurden
     if (isset($_POST[firstname]) == true && isset($_POST[lastname]) == true && isset($_POST[birthday_year]) == true && isset($_POST[birthday_month]) == true && isset($_POST[birthday_day]) == true)
        {
	 // Setzt die Fehlerzahlvariable auf 0
	 $errorcount = 0;
	 
	 // Überprüft, dass alle Pflichtangaben gemacht worden sind
	 if ($_POST[firstname] == "") {$errorcount++; $error[$errorcount] = "Es wurde kein Vorname angegeben!";}
	 if ($_POST[lastname] == "") {$errorcount++; $error[$errorcount] = "Es wurde kein Nachname angegeben!";}
	 
	 // Überprüft, dass die Eingaben nicht zu lang sind
	 if (strlen($_POST[name]) > 30) {$errorcount++; $error[$errorcount] = "Der eingegebene Vorname ist zu lang!";}
	 if (strlen($_POST[name]) > 30) {$errorcount++; $error[$errorcount] = "Der eingegebene Nachname ist zu lang!";}
	 
	 // Überprüft, ob das angegebene Geburtsdatum gültig ist
	 if (checkdate($_POST[birthday_month],$_POST[birthday_day],$_POST[birthday_year]) == false) {$errorcount++; $error[$errorcount] = "Das eingegebene Geburtsdatum ist ungültig!";}
	 
	 // Überprüft, ob das angegebene Geburtsdatum nicht in der Zukunft liegt
	 if (strtotime("$_POST[birthday_year]-$_POST[birthday_month]-$_POST[birthday_day]") > time()) {$errorcount++; $error[$errorcount] = "Das eingegebene Geburtsdatum liegt in der Zukunft!";}
	 
	 // Überprüft, ob mindestens ein Fehler bei der Überprüfung der Daten aufgetretten ist
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
 
       
 // Funktion erzeugt eine Liste aller Benutzer
 function list_users()
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("commerce");
	 
     // Überprüft, ob beim Verbinden ein Fehler aufgetretten ist
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
	 $sqlresult = mysql_query("SELECT user_id, user_firstname, user_lastname, DATE_FORMAT(user_birthday,'%d.%m.%Y') AS user_birthday, YEAR(NOW()) - YEAR(user_birthday) - IF(DATE_FORMAT(NOW(),'%m.%d') >= DATE_FORMAT(user_birthday,'%m.%d'),0,1) AS user_age, DATE_FORMAT(user_createdate,'%d.%m.%Y') AS user_createdate, DATE_FORMAT(user_timestamp,'%d.%m.%Y') AS user_timestamp FROM users ORDER BY user_lastname;");
	 
	 if ($sqlresult == false)
	    {
	     // Gibt eine Fehlermeldung zurück
	     return show_systemmessage("Es ist ein Fehler bei der Abfrage der Benutzer aus der Datenbank aufgetretten","error");
	     
	     // Beendet die geöffnete Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Leert die Stringvariable
	     $string = "";
	     
	     if (mysql_num_rows($sqlresult) > 0)
	        {
		 $string .= "<table style=\"width:800px;\">\n";
		 
		 $string .= " <tr>\n";
		 $string .= "  <td class=\"head\"><b>Vorname</b></td>\n";
		 $string .= "  <td class=\"head\"><b>Nachname</b></td>\n";
		 $string .= "  <td class=\"head\"><b>Geburtsdatum</b></td>\n";
		 $string .= "  <td class=\"head\"><b>Alter</b></td>\n";
		 $string .= "  <td class=\"head\"><b>Mitglied seit</b></td>\n";
		 $string .= "  <td class=\"head\"><b>Änderung am</b></td>\n";
		 $string .= "  <td class=\"head\" colspan=\"2\"><b>Aktionen</b></td>\n";
		 $string .= " </tr>\n";
		 
		 // Setzt die Anfangshintergrundfarbe
		 $color = "#E6E6E6";
		 
		 // Liest alle Werte der Benutzer aus der Datenbank aus
		 while ($row = mysql_fetch_array($sqlresult))
		    {
		     $string .= " <tr style=\"background-color:$color;\">\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:left;width:200px;\">$row[user_firstname]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:left;width:200px;\">$row[user_lastname]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:center;width:100px;\">$row[user_birthday]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:center;width:40px;\">$row[user_age]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:center;width:100px;\">$row[user_createdate]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:center;width:100px;\">$row[user_timestamp]</td>\n";
		     $string .= "  <td class=\"action\"><a href=\"$_SERVER[PHP_SELF]?mode=edit&id=$row[user_id]\"><img class=\"action\" src=\"../system/edit.png\" alt=\"&Auml;ndert den Benutzer\"></a></td>\n";
		     $string .= "  <td class=\"action\"><a href=\"$_SERVER[PHP_SELF]?mode=delete&id=$row[user_id]\" onclick=\"return confirm('Soll der Benutzer wirklich gelöscht werden?')\"><img class=\"action\" src=\"../system/delete.png\" alt=\"L&ouml;scht den Benutzer\"></a></td>\n";
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
		 return show_systemmessage("Es liegen keine Benutzer in der Datenbank vor","info");
		}

	     // Beendet die geöffnete Verbindung zum Datenbankserver
	     mysql_close($conresult);
	    }
	 
	 
	}
    }
       
 
    
    
    
 
    
    
 // Funktion legt einen neuen Benutzer an
 function new_user()
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("commerce");
     
     // Überprüft, ob beim Verbinden ein Fehler aufgetretten ist
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
	 $sqlresult = mysql_query("INSERT INTO users (user_firstname, user_lastname, user_birthday, user_createdate) VALUES ('$_POST[firstname]','$_POST[lastname]','$_POST[birthday_year]-$_POST[birthday_month]-$_POST[birthday_day]',NOW());");
	 
	 // Überprüft, ob es einen Fehler bei der Erstellung eines neuen Benutzer gab
	 if ($sqlresult == false)
	    {
	     // Zeigt eine Fehlermeldung an, dass der neue Benutzer nicht in die Datenbank eingetragen werden konnte
	     echo show_systemmessage("Beim Anlegen des neuen Benutzers ist leider ein Fehler aufgetreten!","error");
	     
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Gibt 'false' zurück
	     return false;
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Zeigt eine Erfolgsmeldung an, dass der neue Benutzer erfolgreich in die Datenbank eingetragen worde
	     echo show_systemmessage("Der Benutzer wurde erfolgreich erstellt!","success");
	     
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Gibt 'true' zurück
	     return true;
	    }
	}
    }

      
 // Funktion ändert den angegebenen Benutzer
 function update_user()
    {
     // Überprüft, ob die angegebene Benutzer-ID eine Zahl ist
     if (ctype_digit($_GET[id]) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
	 $conresult = db_connect("commerce");
	 
	 // Überprüft, ob beim Verbinden ein Fehler aufgetretten ist
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
	     $sqlresult = mysql_query("UPDATE users SET user_firstname = '$_POST[firstname]', user_lastname = '$_POST[lastname]', user_birthday = '$_POST[birthday_year]-$_POST[birthday_month]-$_POST[birthday_day]' WHERE user_id = '$_GET[id]' LIMIT 1;");
	     
	     // Überprüft, ob es einen Fehler beim Aktualisieren des Lichtmoduls gab
	     if ($sqlresult == false)
	        {
		 // Zeigt eine Fehlermeldung an, dass der angegebene Benutzer nicht aktualisiert worden konnte
		 echo show_systemmessage("Beim Aktualisieren des Benutzer ist leider ein Fehler aufgetreten!","error");
	 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zurück
		 return false;
		 
		 // Beendet die Ausführung der Funktion
		 exit();
		}
	     else
	        {
		 // Zeigt eine Erfolgsmeldung an, dass der angegebene Benutzer erfolgreich aktualisiert worden ist
		 echo show_systemmessage("Der Benutzer wurde erfolgreich aktualisiert!","success");
		 
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
    

 
    
    
    
    
    
       
 // Funktion erzeugt eine Liste der per Filteregel angegebenen Transaktionen
 function list_transactions()
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("commerce");
	 
     // Überprüft, ob beim Verbinden ein Fehler aufgetretten ist
     if ($conresult == false)
        {
	 // Gibt eine Fehlermeldung zurück
	 return show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetretten","error");
	     
	 // Beendet die Ausführung der Funktion
	 exit();
	}
     else
        {
	 // Überpüft, ob eine Benutzer ID zum Filtern angegeben wurde
	 if ($_POST[filterid] != "") {$filterid = "users.user_id='$_POST[filterid]'";} else {$filterid = "";}
	 
	 // Überprüft, ob Filterregeln bestehen
	 if ($filterid != "") {$where = "WHERE";} else {$where = "";}
	 
	 // Sendet eine SELECT-Anweisung an die Datenbank
	 $sqlresult = mysql_query("SELECT transactions.transaction_id AS transaction_id, transactions.transaction_description AS transaction_description, DATE_FORMAT(transactions.transaction_timestamp,'%d.%m.%Y') AS transaction_timestamp, users.user_firstname AS user_firstname, users.user_lastname AS user_lastname, transactions.transaction_amount AS transaction_amount FROM transactions LEFT JOIN users ON transactions.user_id = users.user_id
 $where $filterid;");
	 
	 if ($sqlresult == false)
	    {
	     // Gibt eine Fehlermeldung zurück
	     return show_systemmessage("Es ist ein Fehler bei der Abfrage der gewünschten Transaktionen aus der Datenbank aufgetretten","error");
	     
	     // Beendet die geöffnete Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     if (mysql_num_rows($sqlresult) > 0)
	        {
		 $string .= "<table style=\"width:800px;\">\n";
		 
		 $string .= " <tr>\n";
		 $string .= "  <td class=\"head\">ID</td>\n";
		 $string .= "  <td class=\"head\">Beschreibung</td>\n";
		 $string .= "  <td class=\"head\">Benutzer</td>\n";
		 $string .= "  <td class=\"head\">Auftragsdatum</td>\n";
		 $string .= "  <td class=\"head\">Betrag</td>\n";
		 $string .= "  <td class=\"head\" colspan=\"2\">Aktionen</td>\n";
		 $string .= " </tr>\n";
		 
		 // Setzt die Anfangshintergrundfarbe
		 $color = "#E6E6E6";
		 
		 // Liest alle Werte der Benutzer aus der Datenbank aus
		 while ($row = mysql_fetch_array($sqlresult))
		    {
		     $string .= " <tr style=\"background-color:$color;\">\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:center;\">$row[transaction_id]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:left;\">$row[transaction_description]</td>\n";
		     $string .= "  <td class=\"standard\">".check_user($row[user_firstname],$row[user_lastname])."</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:center;width:100px;\">$row[transaction_timestamp]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:right;width:80px;\">$row[transaction_amount] &euro;</td>\n";
		     $string .= "  <td class=\"action\"><a href=\"$_SERVER[PHP_SELF]?mode=edit&id=$row[transaction_id]\"><img class=\"action\" src=\"../system/edit.png\" alt=\"&Auml;ndert die Transaktion\"></a></td>\n";
		     $string .= "  <td class=\"action\"><a href=\"$_SERVER[PHP_SELF]?mode=delete&id=$row[transaction_id]\" onclick=\"return confirm('Soll die Transaktion wirklich gelöscht werden?')\"><img class=\"action\" src=\"../system/delete.png\" alt=\"L&ouml;scht die Transaktion\"></a></td>\n";
		     $string .= " </tr>\n";
		     
		     // Sorgt für eine immer wechselnde Hinterhintergrundfarbe der Zeilen
		     if ($color == "#E6E6E6") {$color = "#D5D6D5";} else {$color = "#E6E6E6";}
		    }
		 
		 // Überprüft, ob nach einem Benutzer gefilltert wurde
		 if ($_POST[filterid] != "")
		    {
		     // Sendet eine SELECT-Anweisung an die Datenbank
		     $sqlresult = mysql_query("SELECT sum(transaction_amount) as transaction_sum FROM transactions WHERE user_id = '$_POST[filterid]' LIMIT 1;");
		     
		     // Liest den Wert den Gesamtbetrag aus
		     $row = mysql_fetch_array($sqlresult);
		     
		     // Überprüft, ob die SELECT-Anweisung erfolgreich ausgeführt wurde
		     if ($sqlresult != false)
		        {
		         $string .= " <tr style=\"background-color:$color;\">\n";
		         $string .= "  <td class=\"standard\" colspan=\"4\">Kontostand:</td>\n";
		         $string .= "  <td class=\"standard\" style=\"text-align:right;width:80px;\">$row[transaction_sum] &euro;</td>\n";
		         $string .= "  <td class=\"standard\" colspan=\"2\">&nbsp;</td>\n";
			}
		    }
  
		 $string .= "</table>\n";
		 
		 // Beendet die geöffnete Verbindung zum Datenbankserver
		 //mysql_close($conresult);
		 
		 return $string;
		}
	     else
	        {
		 // Gibt eine Hinweismeldung zurück
		 return show_systemmessage("Es liegen noch keine Transaktionen zu den angegeben Suchkriterien vor!","info");
		}
	    }
	}
    }
 
       
 // Funktion erzuegt die Filtermaske für das Anzeigen der Transaktionen
 function create_filtermask()
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("commerce");
	 
     // Überprüft, ob beim Verbinden ein Fehler aufgetretten ist
     if ($conresult == false)
        {
	 // Gibt eine Fehlermeldung aus
	 return show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetretten","error");
	     
	 // Beendet die Ausführung der Funktion
	 exit();
	}
     else
	{
	 // Sendet eine SELECT-Anweisung an die Datenbank
	 $sqlresult = mysql_query("SELECT user_id, user_firstname, user_lastname FROM users ORDER BY user_lastname;");
	 
	 if ($sqlresult == false)
	    {
	     // Gibt eine Fehlermeldung zurück
	     return show_systemmessage("Es ist ein Fehler bei der Abfrage der Benutzer aus der Datenbank aufgetretten","error");
	     
	     // Beendet die geöffnete Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Leert die Auswahlbox Variable
	     $selection = "";
	     
	     // Generiert die Auswahlbox
	     $selection .= "<select class=\"standard\" style=\"width:300px;\" name=\"filterid\" size=\"1\">\n";
	     $selection .= "<option value=\"\"></option>\n";
	     
	     while ($row = mysql_fetch_array($sqlresult))
	        {
		 $selection .= "<option value=\"$row[user_id]\">".htmlentities($row[user_firstname])." ".htmlentities($row[user_lastname])."</option>";
		}

	     $selection .= "</select>\n";
	    }
	}
	
     // Leert die Stringvariable
     $string = "";
     
     $string .= "<form action=\"$_SERVER[PHP_SELF]?mode=show\" method=\"post\">\n";
     $string .= "<table style=\"background-color:#E6E6E6;width:300px;\">\n";
     $string .= " <tr>\n";
     $string .= "  <td colspan=\"2\" class=\"head\" style=\"background-color:#D5DEE6;\">Filtermaske</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= "  <td colspan=\"2\" class=\"standard\">Benutzer ausw&auml;hlen</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= "  <td colspan=\"2\" class=\"standard\">$selection</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"></td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input type=\"image\" src=\"../system/filter.png\"></td>\n";
     $string .= " </tr>\n";
     $string .= "</table>\n";
     $string .= "</form>\n";
     
     // Gibt die fertige Eingabemaske zurück
     return $string;
    }
    
    
 // Funktion überprüft, ob der Benutzer noch existiert
 function check_user($firstname,$lastname)
    {
     if ($firstname != "" && $lastname != "")
        {
	 // Gibt den Vor- und Nachnamen richtig formatiert zurück
	 return htmlentities($firstname)." ".htmlentities($lastname);
	}
     else
        {
	 // Gibt ein "unbekannt" zurück
	 return "(unbekannt)";
	}
    }
    
  
 // Funktion erstellt eine neue Transaktion
 function new_transaction()
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("commerce");
     
     // Überprüft, ob beim Verbinden ein Fehler aufgetretten ist
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
	 $sqlresult = mysql_query("INSERT INTO transactions (transaction_description, transaction_amount, user_id) VALUES (TRIM('$_POST[description]'),REPLACE(TRIM('$_POST[amount]'),',','.'),TRIM('$_POST[userid]'));");
	 
	 // Überprüft, ob es einen Fehler bei der Erstellung einer neuen Transaktion gab
	 if ($sqlresult == false)
	    {
	     // Zeigt eine Fehlermeldung an, dass die neue Transaktion nicht in die Datenbank eingetragen werden konnte
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
	     // Zeigt eine Erfolgsmeldung an, dass die neue Transaktion erfolgreich in die Datenbank eingetragen worde
	     echo show_systemmessage("Die Transaktion wurde erfolgreich erstellt!","success");
	     
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
	 $conresult = db_connect("commerce");
	 
	 // Überprüft, ob beim Verbinden ein Fehler aufgetretten ist
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
	     $sqlresult = mysql_query("UPDATE transactions SET transaction_description = TRIM('$_POST[description]'), transaction_amount = REPLACE(TRIM('$_POST[amount]'),',','.'), user_id = TRIM('$_POST[userid]') WHERE transaction_id = '$_GET[id]' LIMIT 1;");
	     
	     // Überprüft, ob es einen Fehler beim Aktualisieren des Lichtmoduls gab
	     if ($sqlresult == false)
	        {
		 // Zeigt eine Fehlermeldung an, dass die angegebene Transaktion nicht aktualisiert worden konnte
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
		 // Zeigt eine Erfolgsmeldung an, dass der angegebene Benutzer erfolgreich aktualisiert worden ist
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
    
 

    
    
    
    
    
     
    
    
    
    
  
 // Funktion löscht den angegebenen Benutzer
 function delete_user()
    {
     // Überprüft, ob die angegebene Benutzer-ID eine Zahl ist
     if (ctype_digit($_GET[id]) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
	 $conresult = db_connect("commerce");
	 
	 // Überprüft, ob beim Verbinden ein Fehler aufgetretten ist
	 if ($conresult == false)
	    {
	     // Zeigt eine Fehlermeldung an, dass ein Fehler beim Verbinden zur Datenbank aufgetreten ist
	     echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetretten!","error");
	     
	     // Gibt 'false' zurück
	     return false;
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Sendet eine DELETE-Anweisung an die Datenbank
	     $sqlresult = mysql_query("DELETE FROM users WHERE user_id='$_GET[id]' LIMIT 1;");
	     
	     // Überprüft, ob es einen Fehler beim Löschen des Benutzers gab
	     if ($sqlresult == false)
	        {
		 // Zeigt eine Fehlermeldung an, dass der angegebene Benutzer nicht gelöscht werden konnte
		 echo show_systemmessage("Beim Löschen des Benutzers ist leider ein Fehler aufgetretten","error");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zurück
		 return false; 
	    	}
	     else
	        {
		 // Zeigt eine Erfolgsmeldung an, dass der angegebene Benutzer erfolgreich gelöscht worden ist
		 echo show_systemmessage("Der Benutzer wurde erfolgreich gelöscht","success");
		 
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
	 $conresult = db_connect("commerce");
	 
	 // Überprüft, ob beim Verbinden ein Fehler aufgetretten ist
	 if ($conresult == false)
	    {
	     // Zeigt eine Fehlermeldung an, dass ein Fehler beim Verbinden zur Datenbank aufgetreten ist
	     echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetretten!","error");
	     
	     // Gibt 'false' zurück
	     return false;
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Sendet eine DELETE-Anweisung an die Datenbank
	     $sqlresult = mysql_query("DELETE FROM transactions WHERE transaction_id='$_GET[id]' LIMIT 1;");
	     
	     // Überprüft, ob es einen Fehler beim Löschen der Transaktion gab
	     if ($sqlresult == false)
	        {
		 // Zeigt eine Fehlermeldung an, dass die angegebene Transaktion nicht gelöscht worden konnte
		 echo show_systemmessage("Beim Löschen der Transaktion ist leider ein Fehler aufgetretten","error");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zurück
		 return false; 
	    	}
	     else
	        {
		 // Zeigt eine Erfolgsmeldung an, dass die angegebene Transaktion erfolgreich gelöscht worden ist
		 echo show_systemmessage("Die Transaktion wurde erfolgreich gelöscht","success");
		 
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
?> 
