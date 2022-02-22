<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 31.12.2004
 // Änderungsdatum: 13.04.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 
 // Funktion überprüft die eingegeben Kategoriedaten
 function check_categorydatas()
    {
     // Überprüft ob alle Inhalte der Eingabemaske gesendet wurden
     if (isset($_POST[name]) == true && isset($_POST[description]) == true)
        {
	 // Setzt die Fehlerzahlvariable auf 0
	 $errorcount = 0;
	 
	 // Überprüft, dass alle Pflichtangaben gemacht worden sind
	 if ($_POST[name] == "") {$errorcount++; $error[$errorcount] = "Der Name der Kategorie wurde nicht eingegeben!";}
	 
	 // Überprüft, dass die Eingaben nicht zu lang sind
	 if (strlen($_POST[name]) > 30) {$errorcount++; $error[$errorcount] = "Der eingegebene Kategoriename ist zu lang!";}
	 if (strlen($_POST[description]) > 65535) {$errorcount++; $error[$errorcount] = "Die eingegebene Beschreibung ist zu lang!";}
	 
	 // Überprüft, ob der 'new'-Modus ausgewählt worden ist und keine Kategorie-ID vorhanden ist
	 if ($_GET[mode] == "new" && isset($_GET[id]) == false && $_GET[id] == "")
	    {
	     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
             $conresult = db_connect("mixer");
	     
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
		 // Sendet eine SELECT-Anweisung an die Datenbank, um abzufragen ob die Cocktailkategorie schon in der Datenbank vorhanden ist
		 $sqlresult = mysql_query("SELECT NULL FROM categories WHERE category_name = TRIM('$_POST[name]') AND category_id != '$_GET[id]';");
		 
		 // Überprüft, ob es einen Fehler beim Abfragen der Flüssigkeiten gab
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
		     if (mysql_num_rows($sqlresult) != 0) {$errorcount++; $error[$errorcount] = "Es existiert bereits eine Kategorie mit dem selben Namen!";}
		    }
		 
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
 
 
 // Funktion überprüft die eingegeben Flüssigkeitsdaten
 function check_liquiddatas()
    {
     // Überprüft ob alle Inhalte der Eingabemaske gesendet wurden
     if (isset($_POST[name]) == true && isset($_POST[viscosity]) == true && isset($_POST[agereales]) == true)
        {
	 // Setzt die Fehlerzahlvariable auf 0
	 $errorcount = 0;
	 
	 // Überprüft, dass alle Pflichtangaben gemacht worden sind
	 if ($_POST[name] == "") {$errorcount++; $error[$errorcount] = "Der Name der Flüssigkeit wurde nicht eingegeben!";}
	 if ($_POST[viscosity] == "") {$errorcount++; $error[$errorcount] = "Die Viskosität wurde nicht eingegeben!";}
	 if ($_POST[agereales] == "") {$errorcount++; $error[$errorcount] = "Die Altersfreigabe wurde nicht eingegeben!";}
	 
	 // Überprüft, dass die Eingaben nicht zu lang sind
	 if (strlen($_POST[name]) > 30) {$errorcount++; $error[$errorcount] = "Der eingegebene Flüssigkeitsname ist zu lang!";}
	 
	 // Überprüft, ob die eingegebene Viskosität im gültigen Wertebreich ist
	 if (doubleval(str_replace(",",".",$_POST[viscosity])) < 0 || doubleval(str_replace(",",".",$_POST[viscosity])) > 9.9999) {$errorcount++; $error[$errorcount] = "Die eingegebene Viskosität ist ungültig!";}
	 
	 // Überprüft, ob die eingegebene Altersfreigabe im gültigen Wertebereich ist
	 if ($_POST[agereales] < 0 || $_POST[agereales] > 255) {$errorcount++; $error[$errorcount] = "Die eingegebene Altersfreigabe ist ungültig!";}
	 
	 // Überprüft, ob der 'new'-Modus ausgewählt worden ist, eine Flüssigkeits-ID vorhanden ist
	 if ($_GET[mode] == "new" && isset($_GET[id]) == false && $_GET[id] == "")
	    {
	     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
             $conresult = db_connect("mixer");
	     
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
		 // Sendet eine SELECT-Anweisung an die Datenbank, um abzufragen ob die Flüssigkeit schon in der Datenbank vorhanden ist
		 $sqlresult = mysql_query("SELECT NULL FROM liquids WHERE liquid_name = TRIM('$_POST[name]') AND liquid_id != '$_GET[id]';");
		 
		 // Überprüft, ob es einen Fehler beim Abfragen der Flüssigkeiten gab
		 if ($sqlresult == false)
		    {
		     // Zeigt eine Fehlermeldung an, dass keine Daten zur angegebenen Flüssigkeit abgerufen werden konnten
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
		     // Überprüft, dass noch keine Flüssigkeit mit dem selben Namen in der Datenbank eingetragen ist
		     if (mysql_num_rows($sqlresult) != 0) {$errorcount++; $error[$errorcount] = "Es existiert bereits eine Flüssigkeit mit dem selben Namen!";}
		    }
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
    
    
 // Funktion überprüft die eingegebenen Daten bei dem Cocktailrezept
 function check_recipedatas()
    {
     // Überprüft ob alle Inhalte der Eingabemaske gesendet wurden
     if (isset($_POST[name]) == true && isset($_POST[category]) == true && isset($_POST[price]) == true && isset($_POST[amount]) == true && isset($_POST[liquid]) == true && isset($_POST[priority]) == true)
        {
	 // Überprüft, dass alle Pflichtangaben gemacht worden sind
	 if ($_POST[name] == "") {$errorcount++; $error[$errorcount] = "Der Name des Cocktails wurde nicht eingegeben!";}
	 if ($_POST[price] == "") {$errorcount++; $error[$errorcount] = "Es wurde kein Preis für den Cocktail eingegeben!";}
	 
	 // Überprüft, dass die Eingaben nicht zu lang sind
	 if (strlen($_POST[name]) > 30) {$errorcount++; $error[$errorcount] = "Der eingegebene Cocktailname ist zu lang!";}
	 
	 // Überprüft, dass der eingegebene Preis nicht zu klein ist
	 if (doubleval(str_replace(",",".",$_POST[price])) < 0)  {$errorcount++; $error[$errorcount] = "Der eingegebene Preis ist zu klein!";}
	 
	 // Überprüft, dass der eingegebene Betrag nicht zu groß ist
	 if (doubleval(str_replace(",",".",$_POST[price])) > 9999.99)  {$errorcount++; $error[$errorcount] = "Der eingegebene Preis ist zu groß!";}
	 
	 // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("mixer");
	     
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
	     // Sendet eine SELECT-Anweisung an die Datenbank, um abzufragen ob die angegeben Kategorie in der Datenbank existiert
	     $sqlresult1 = mysql_query("SELECT NULL FROM categories WHERE category_id = TRIM('$_POST[category]');");
	     
	     // Überprüft, ob der 'new'-Modus ausgewählt worden ist und keine Cocktail-ID vorhanden ist
	     if ($_GET[mode] == "new" && isset($_GET[id]) == false && $_GET[id] == "")
	        {
	         // Sendet eine SELECT-Anweisung an die Datenbank, um abzufragen ob es schonen einen Cocktail mit dem Namen gibt
		 $sqlresult2 = mysql_query("SELECT NULL FROM cocktails WHERE cocktail_name = TRIM('$_POST[name]') AND cocktail_id != '$_GET[id]';");
		}
	     else
	        {
		 // Setzt die Variable auf den Wert 'true'
		 $sqlresult2 = true;
		}
	     
	     // Überprüft, ob es einen Fehler beim Abfragen der Kategorien gab
	     if ($sqlresult1 == false || $sqlresult2 == false)
		{
		 // Zeigt eine Fehlermeldung an, dass keine Daten zur angegebenen Kategorie abgerufen werden konnten
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
		 // Überprüft, dass die angegebene Kategorie in der Datenbank vorhanden ist
		 if (mysql_num_rows($sqlresult1) != 1) {$errorcount++; $error[$errorcount] = "Die angegebene Kategorie existiert nicht in der Datenbank!";}
		 
		 // Überprüft, ob der 'new'-Modus ausgewählt worden ist und keine Cocktail-ID vorhanden ist
		 if ($_GET[mode] == "new" && isset($_GET[id]) == false && $_GET[id] == "")
		    {
		     // Überprüft, dass der angegebene Cocktailname nicht schon in der Datenbank vorhanden ist
		     if (mysql_num_rows($sqlresult2) != 0) {$errorcount++; $error[$errorcount] = "Die angegebene Cocktailname existiert bereits in der Datenbank!";}
		    }
		}
	    }
	    
	 // Liest alle erlaubten eingegeben Zutaten inkl. Priorität und Menge ein
	 for ($count = 1;$count <= count_tanks();$count++)
	     {
	      // Überprüft, ob die eingegebene Zutat nicht leer ist
	      if ($_POST[amount][$count] != "" || $_POST[liquid][$count] != "" || $_POST[priority][$count] != "")
		 {
		  // Überprüft, dass alle Pflichtangaben gemacht worden sind
		  if ($_POST[amount][$count] == "") {$errorcount++; $error[$errorcount] = "Es wurde keine Mengenangabe für die $count. Zutat eingegen!";}
		  if ($_POST[priority][$count] == "") {$errorcount++; $error[$errorcount] = "Es wurde keine Priorität für die $count. Zutat eingegeben!";}
		  
		  // Überprüft, dass die eingegebene Menge nicht zu klein ist
		  if ($_POST[amount][$count] < 0)  {$errorcount++; $error[$errorcount] = "Der eingegebene Menge für die $count. Zutat darf nicht negativ sein!";}
		  
		  // Überprüft, dass die eingegebene Menge nicht zu groß ist
		  if ($_POST[amount][$count] > 65535)  {$errorcount++; $error[$errorcount] = "Der eingegebene Menge für die $count. Zutat ist zu groß!";}
		  
		  // Überprüft, dass die eingegebene Priorität nicht zu klein ist
		  if ($_POST[priority][$count] < 0)  {$errorcount++; $error[$errorcount] = "Der eingegebene Priorität für die $count. Zutat darf nicht negativ sein!";}
		  
		  // Überprüft, dass die eingegebene Priorität nicht zu groß ist
		  if ($_POST[priority][$count] > 255)  {$errorcount++; $error[$errorcount] = "Der eingegebene Priorität für die $count. Zutat ist zu groß!";}
		  
		  // Löscht den Inhalt der Variable mit der Flüssigkeits-ID
		  $liquid = "";
		  
		  // Schreibt die eingegebene Flüssigkeits-ID für die nachfolgende SELECT-Anweisung in die richtige Variable
		  $liquid = $_POST[liquid][$count];
		  
		  // Sendet eine SELECT-Anweisung an die Datenbank, um abzufragen ob die angegeben Kategorie in der Datenbank existiert
		  $sqlresult3 = mysql_query("SELECT NULL FROM liquids WHERE liquid_id = TRIM('$liquid');");
		  
		  // Überprüft, ob es einen Fehler beim Abfragen der Kategorien gab
	          if ($sqlresult3 == false)
		     {
		      // Zeigt eine Fehlermeldung an, dass keine Daten zur angegebenen Kategorie abgerufen werden konnten
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
		      // Überprüft, dass die angegebene Flüssigkeit in der Datenbank vorhanden ist
		      if (mysql_num_rows($sqlresult3) != 1) {$errorcount++; $error[$errorcount] = "Die angegebene Flüssigkeit für die $count. Zutat existiert nicht in der Datenbank!";}
		     }
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
 
 
 // Funktion erzeugt die Eingabemaske für Kategorien der Cocktails
 function create_inputmaskcategory()
    {
     // Überprüft, ob eine Kategorie-ID vorliegt, der Modus "edit" ausgewählt wurde und keine Werte übergeben worden sind
     if ($_GET[id] != "" && $_GET[mode] == "edit" && isset($_POST[name]) == false && isset($_POST[description]) == false)
        {
	 // Überprüft, ob die angegebene Kategorie-ID eine Zahl ist
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
		 $sqlresult = mysql_query("SELECT category_name, category_description FROM categories WHERE category_id = '$_GET[id]' LIMIT 1;");
		 
		 // Überprüft, ob es einen Fehler beim Abfragen der Daten der angegebenen Cocktailkategorie gab
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
		     // Überprüft ob wirklich nur die Daten von einer Kategorie abgefragt worden sind
		     if (mysql_num_rows($sqlresult) == 1)
		        {
			 // Liest die Werte zu der angegebenen Kategorie aus 
			 $row = mysql_fetch_array($sqlresult);     
		     
		         // Schreibt die Werte in die richtige Variable
			 $name = $row[category_name];
			 $description = $row[category_description];
			}
		     else
		        {
			 // Zeigt eine Fehlermeldung an, dass keine Daten zur angegebenen Kategorie abgerufen werden konnten
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
	 $name = $_POST[name];
	 $description = $_POST[description];
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
     $string .= " <td class=\"standard\">Name:&nbsp;&nbsp;(max. 30 Zeichen)</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input class=\"standard\" type=\"text\" name=\"name\" value=\"$name\" maxlength=\"30\"></td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">&nbsp;</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">Beschreibung:&nbsp;&nbsp;(max. 255 Zeichen)</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><textarea class=\"standard\" name=\"description\">$description</textarea></td>\n";
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
    
    
 // Funktion erzeugt die Eingabemaske für eine Flüssigkeit
 function create_inputmaskliquid()
    {
     // Überprüft, ob eine Flüssigkeits-ID vorliegt, der Modus "edit" ausgewählt wurde und keine Werte übergeben worden sind
     if ($_GET[id] != "" && $_GET[mode] == "edit" && isset($_POST[name]) == false && isset($_POST[viscosity]) == false && isset($_POST[agereales]) == false)
        {
	 // Überprüft, ob die angegebene Flüssigkeits-ID eine Zahl ist
	 if (ctype_digit($_GET[id]) == true)
	    {
	     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
	     $conresult = db_connect("mixer");
	     
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
		 $sqlresult = mysql_query("SELECT liquid_name, liquid_viscosity, liquid_minage FROM liquids WHERE liquid_id = '$_GET[id]';");
		 
		 // Überprüft, ob es einen Fehler beim Abfragen der Daten der angegebenen Flüssigkeit gab
		 if ($sqlresult == false)
		    {
		     // Zeigt eine Fehlermeldung an, dass keine Daten zur angegebenen Flüssigkeit abgerufen werden konnten
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
		     // Überprüft ob wirklich nur die Daten von einer Flüssigkeit abgefragt worden sind
		     if (mysql_num_rows($sqlresult) == 1)
		        {
			 // Liest die Werte zu der angegebenen Flüssigkeit aus 
			 $row = mysql_fetch_array($sqlresult);     
		     
		         // Schreibt die Werte in die richtige Variable
			 $name = $row[liquid_name];
			 $viscosity = $row[liquid_viscosity];
			 $agereales = $row[liquid_minage];
			 
			}
		     else
		        {
			 // Zeigt eine Fehlermeldung an, dass keine Daten zur angegebenen Flüssigkeit abgerufen werden konnten
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
	 $name = $_POST[name];
	 $viscosity = $_POST[viscosity];
	 $agereales = $_POST[agereales];
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
     $string .= " <td class=\"standard\">Name:&nbsp;&nbsp;(max. 30 Zeichen)</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input class=\"standard\" style=\"width:280px;\" type=\"text\" name=\"name\" value=\"$name\" maxlength=\"30\"></td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">&nbsp;</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">Mindestalter:&nbsp;&nbsp;(min. 0 bis max. 255 Jahren)</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input class=\"standard\" style=\"width:25px;\" type=\"text\" name=\"agereales\" value=\"$agereales\" maxlength=\"3\">&nbsp;&nbsp;Jahre</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">&nbsp;</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">Viskosit&auml;t:&nbsp;&nbsp;(min. 0 bis max. 9,9999)</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input class=\"standard\" style=\"width:40px;\" type=\"text\" name=\"viscosity\" value=\"$viscosity\" maxlength=\"6\"></td>\n";
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
 
 
 // Funktion erzeugt die Eingabemaske für Cocktailrezepte
 function create_inputmaskrecipe()
    {
     // Überprüft, ob eine Cocktail-ID vorliegt, der Modus "edit" ausgewählt wurde und keine Werte übergeben worden sind
     if ($_GET[id] != "" && $_GET[mode] == "edit" && isset($_POST[name]) == false && isset($_POST[category]) == false && isset($_POST[price]) == false && isset($_POST[liquid]) == false)
        {
	 // Überprüft, ob die angegebene Cocktail-ID eine Zahl ist
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
		 // Ermittelt die Anzahl von Tanks in der Maschine
		 $tankcount = count_tanks();
		 
		 // Sendet eine SELECT-Anweisung an die Datenbank
		 $sqlresult1 = mysql_query("SELECT COUNT('') AS liquid_count, cocktails.cocktail_id AS cocktail_id, cocktails.cocktail_name AS cocktail_name, cocktails.cocktail_price AS cocktail_price, cocktails.category_id AS category_id FROM cocktails INNER JOIN recipes ON cocktails.cocktail_id = recipes.cocktail_id WHERE cocktails.cocktail_id = '$_GET[id]' GROUP BY cocktails.cocktail_id LIMIT 1;");
		 $sqlresult2 = mysql_query("SELECT liquid_id, liquid_amount, liquid_priority FROM recipes WHERE cocktail_id = '$_GET[id]' LIMIT $tankcount;");
		 
		 // Überprüft, ob es einen Fehler beim Abfragen der Daten der angegebenen Cocktailkategorie gab
		 if ($sqlresult1 == false || $sqlresult2 == false)
		    {
		     // Gibt eine Fehlermeldung an, dass ein interner Verarbeitungsfehler aufgetreten
		     echo show_systemmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten!","error");
		     
		     // Gibt 'false' zurück
		     return false;
		     
		     // Beendet die Ausführung der Funktion
		     exit();
		    }
		 else
		    {
		     // Liest aus der Datenbank die Grundinformationen zum Cocktail aus
		     $row1 = mysql_fetch_array($sqlresult1);
		     
		     // Überprüft, ob die Anzahl der Flüssigkeiten maximal der vorhandenen Tanks entspricht
		     if ($row1[liquid_count] <= $tankcount)
		        {
			 $name = $row1[cocktail_name];
			 $category = $row1[category_id];
			 $price = $row1[cocktail_price];
			 
			 // Setzt die Zählervariable auf 1
			 $count = 1;
			 
			 // Liest die in die zugehörige Rezeptur zum angegebenen Cocktail aus
			 while ($row2 = mysql_fetch_array($sqlresult2))
			    {
			     $amount[$count] = $row2[liquid_amount];
			     $liquid[$count] = $row2[liquid_id];
			     $priority[$count] = $row2[liquid_priority];
			     
			     // Erhöht die Zählervariable
			     $count++;
			    }
			}
		     else
		        {
			 // Gibt eine Fehlermeldung an, dass ein interner Verarbeitungsfehler aufgetreten
			 echo show_systemmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten!","error");
			 
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
	     echo show_systemmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten!","error");
	     
	     // Gibt 'false' zurück
	     return false;
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	}
     else
        {
	 // Schreibt die Werte in die richtige Variable
	 $name = $_POST[name];
	 $category = $_POST[category];
	 $price = $_POST[price];
	 
	 // Liest alle Zutaten aus
         for ($count = 1;$count <= count_tanks();$count++)
             {
	      $amount[$count] = $_POST[amount][$count];
	      $liquid[$count] = $_POST[liquid][$count];
	      $priority[$count] = $_POST[priority][$count];
	     }
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
     $string .= " <td class=\"standard\">Cocktailname:</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input class=\"standard\" style=\"width:240px;\" type=\"text\" name=\"name\" value=\"$name\" maxlength=\"30\"></td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">&nbsp;</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">Cocktailkategorie:</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">".create_categoryselection($category,"category")."</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">&nbsp;</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">Preis:</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input class=\"standard\" style=\"width:60px;\" type=\"text\" name=\"price\" value=\"$price\" maxlength=\"7\">&nbsp;&euro;</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">&nbsp;</td>\n";
     $string .= " </tr>\n";
     
     // Schleife erzeugt dynamisch die mögliche Anzahl von Eingabefelder für die verschiedenen Flüssigkleiten
     for ($count = 1;$count <= count_tanks();$count++)
         {
	  $string .= " <tr>\n";
	  $string .= " <td class=\"standard\">$count Zutat:</td>\n";
	  $string .= " </tr>\n";
	  $string .= " <tr>\n";
	  $string .= " <td class=\"standard\">Menge:&nbsp;<input class=\"standard\" style=\"width:40px;\" type=\"text\" name=\"amount[$count]\" value=\"".$amount[$count]."\" maxlength=\"4\">&nbsp;ml&nbsp;&nbsp;&nbsp;Flüssigkeit:&nbsp;".create_liquidselection($liquid[$count],"liquid[$count]")."&nbsp;&nbsp;&nbsp;Priorität&nbsp;<input class=\"standard\" style=\"width:30px;\" type=\"text\" name=\"priority[$count]\" value=\"".$priority[$count]."\" maxlength=\"3\"></td>\n";
	  $string .= " </tr>\n";
	  $string .= " <tr>\n";
	  $string .= " <td>&nbsp;</td>\n";
	  $string .= " </tr>\n";
	 } 
     
     $string .= " <tr>\n";
     $string .= " <td><input type=\"image\" src=\"../system/$imagename\"></td>\n";
     $string .= " </tr>\n";
     $string .= "</table>\n";
     
     // Gibt die fertige Eingabemaske aus
     echo $string;
     
     // Gibt 'true' zurück
     return true;
    }
 
    
 // Funktion löscht die angegebene Kategorie
 function delete_category()
    {
     // Überprüft, ob die angegebene Kategorie-ID eine Zahl ist
     if (ctype_digit($_GET[id]) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
	 $conresult = db_connect("mixer");
	 
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
	     // Sendet eine DELETE-Anweisung an die Datenbank
	     $sqlresult = mysql_query("DELETE FROM categories WHERE category_id='$_GET[id]' LIMIT 1;");
	 
	     // Überprüft, ob es einen Fehler bei dem Löschen der Kategorie gab
	     if ($sqlresult == false)
	        {
	         // Zeigt eine Fehlermeldung an, dass die angegebene Kategorie nicht gelöscht werden konnte
	         echo show_systemmessage("Beim Löschen der Kategorie ist leider ein Fehler aufgetreten!","error");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zurück
		 return false;
		 
		 // Beendet die Ausführung der Funktion
		 exit();
	        }
	     else
	        {
		 // Zeigt eine Erfolgsmeldung an, dass die angegebene Kategorie erfolgreich gelöscht worden ist
		 echo show_systemmessage("Die Kategorie wurde erfolgreich gelöscht!","success");
		 
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
   
   
 // Funktion löscht die angegebene Flüssigkeit
 function delete_liquid()
    {
     // Überprüft, ob die angegebene Flüssigkeit-ID eine Zahl ist
     if (ctype_digit($_GET[id]) == true)
        {
         // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("mixer");
     
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
	     $sqlresult = mysql_query("DELETE FROM liquids WHERE liquid_id='$_GET[id]' LIMIT 1;");
	 
	     // Überprüft, ob es einen Fehler bei dem Löschen der Flüssigkeit gab
	     if ($sqlresult == false)
	        {
	         // Zeigt eine Fehlermeldung an, dass die angegebene Flüssigkeit nicht gelöscht worden konnte
	         echo show_systemmessage("Beim Löschen der Flüssigkeit ist leider ein Fehler aufgetreten!","error");
		
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zurück
		 return false; 
	        }
	     else
	        {
		 // Zeigt eine Erfolgsmeldung an, dass die angegebene Flüssigkeit erfolgreich gelöscht worden ist
		 echo show_systemmessage("Die Flüssigkeit wurde erfolgreich gelöscht!","success");
		 
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
    
    
 // Funktion löscht das angegebene Cocktailrezept
 function delete_recipe()
    {
     // Überprüft, ob die angegebene Cocktail-ID eine Zahl ist
     if (ctype_digit($_GET[id]) == true)
        {
         // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("mixer");
     
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
	     // Sendet eine DELETE-Anweisung an die Datenbank
	     $sqlresult1 = mysql_query("DELETE FROM cocktails WHERE cocktail_id='$_GET[id]' LIMIT 1;");
	 
	     // Überprüft, ob es einen Fehler bei dem Löschen des Cocktailrezeptes gab
	     if ($sqlresult1 == false)
	        {
	         // Zeigt eine Fehlermeldung an, dass das angegebene  Cocktailrezept nicht gelöscht werden konnte
	         echo show_systemmessage("Beim Löschen des Cocktailrezeptes ist leider ein Fehler aufgetreten!","error");
		
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zurück
		 return false; 
	        }
	     else
	        {
		 // Ermittelt die Anzahl der Tanks in der Maschine und schreibt die Anzahl in die Variable
		 $tankcount = count_tanks();
		 
		 // Sendet eine DELETE-Anweisung an die Datenbank um die Zutatenliste für das angegeben Cocktailrezept wieder zu löschen
		 $sqlresult2 = mysql_query("DELETE FROM recipes WHERE cocktail_id='$_GET[id]' LIMIT $tankcount;");
		 
		 // Überprüft, ob es einen Fehler bei dem Löschen der Zutatenliste gab
		 if ($sqlresult2 == false)
		    {
		     // Zeigt eine Fehlermeldung an, dass das neue Cocktailrezept nicht in die Datebank eingetragen werden konnte
		     echo show_systemmessage("Beim Löschen des Cocktailrezeptes ist leider ein Fehler aufgetreten! Die Datenbank könnte fehlerhafte Einträge aufweisen!","error");
		     
		     // Beendet die Verbindung zum Datenbankserver
		     mysql_close($conresult);
		      
		     // Gibt 'false' zurück
		     return false;
		      
		     // Beendet die Ausführung der Funktion
		     exit();
		    }
		 else
		    {
		     // Zeigt eine Erfolgsmeldung an, dass die angegebene Flüssigkeit erfolgreich gelöscht worden ist
		     echo show_systemmessage("Das Cocktailrezept wurde erfolgreich gelöscht!","success");
		     
		     // Beendet die Verbindung zum Datenbankserver
		     mysql_close($conresult);
		     
		     // Gibt 'true' zurück
		     return true;
		    }
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
 
 
 // Funktion listet alle vorhandenen Kategorien auf
 function list_categories()
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("mixer");
	 
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
	 // Sendet eine SELECT-Anweisung an die Datenbank
	 $sqlresult = mysql_query("SELECT category_id, category_name, category_description FROM categories ORDER BY category_name ASC;");
	 
	 // Überprüft, ob es einen Fehler bei der Erstellung eines neuen Cocktailrezeptes gab
	 if ($sqlresult == false)
	    {
	     // Gibt eine Erfolgsmeldung zurück
	     return show_systemmessage("Es ist leider ein technischer Fehler bei der Abfrage der Kategorien aus der Datenbank aufgetretten!","error");
	     
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	    }
	 else
	    {
	     // Überprüft, ob mindestens eine Kategorie in der Datenbank eingetragen ist
	     if (mysql_num_rows($sqlresult) > 0)
	        {
		 // Leert die Stringvariable
		 $string = "";
		 
		 $string .= "<table style=\"width:800px;\">\n";
		 
		 $string .= " <tr>\n";
		 $string .= "  <td class=\"head\">Name</td>\n";
		 $string .= "  <td class=\"head\">Beschreibung</td>\n";
		 $string .= "  <td class=\"head\" colspan=\"2\"><b>Aktionen</b></td>\n";
		 $string .= " </tr>\n";
		 
		 // Setzt die Anfangshintergrundfarbe
		 $color = "#E6E6E6";
		 
		 // Liest alle Werte der Benutzer aus der Datenbank aus
		 while ($row = mysql_fetch_array($sqlresult))
		    {
		     $string .= " <tr style=\"background-color:$color;\">\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:left;width:200px;\">$row[category_name]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"background-color:$color;\">$row[category_description]</td>\n";
		     $string .= "  <td class=\"action\" style=\"background-color:$color;\"><a href=\"$_SERVER[PHP_SELF]?mode=edit&id=$row[category_id]\"><img class=\"action\" src=\"../system/edit.png\" alt=\"&Auml;ndert die Kategorie\"></a></td>\n";
		     $string .= "  <td class=\"action\" style=\"background-color:$color;\"><a href=\"$_SERVER[PHP_SELF]?mode=delete&id=$row[category_id]\"><img class=\"action\" src=\"../system/delete.png\" alt=\"L&ouml;scht die Kategorie\"></a></td>\n";
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
	         return show_systemmessage("Es liegen keine Kategorien in der Datenbank vor","info");
		}
	    }
	}
    }
 
 
 // Funktion erzeugt eine Liste mit allen in der Datenbank vorhandenen Flüssigkeiten
 function list_liquids()
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("mixer");
	 
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
	 $sqlresult = mysql_query("SELECT liquid_id, liquid_name, liquid_viscosity, liquid_minage FROM liquids ORDER BY liquid_name ASC;");
	 
	 if ($sqlresult == false)
	    {
	     // Gibt eine Fehlermeldung zurück, dass es einen Fehler bei der Abfrage der Flüssigkeiten aus der Datenbank gab
	     echo show_systemmessage("Es ist ein Fehler bei der Abfrage der Flüssigkeiten aus der Datenbank aufgetreten","error");
	     
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Gibt 'false' zurück
	     return false;
     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Überprüft, ob mindestens eine Flüssigkeit in der Datenbank vorhanden ist
	     if (mysql_num_rows($sqlresult) > 0)
	        {
		 // Leert die Stringvariable
		 $string = "";
		 
		 $string .= "<table style=\"width:800px;\">\n";
		 
		 $string .= " <tr>\n";
		 $string .= "  <td class=\"head\">Name</td>\n";
		 $string .= "  <td class=\"head\">Viskosität</td>\n";
		 $string .= "  <td class=\"head\">Altersfreigabe ab</td>\n";
		 $string .= "  <td class=\"head\" colspan=\"2\"><b>Aktionen</b></td>\n";
		 $string .= " </tr>\n";
		 
		 // Setzt die Anfangshintergrundfarbe
		 $color = "#E6E6E6";
		 
		 // Liest alle Werte der Benutzer aus der Datenbank aus
		 while ($row = mysql_fetch_array($sqlresult))
		    {
		     $string .= " <tr style=\"background-color:$color;\">\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:left;\">$row[liquid_name]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:center;width:150px;\">$row[liquid_viscosity]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:center;width:150px;\">$row[liquid_agereales]</td>\n";
		     $string .= "  <td class=\"action\"><a href=\"$_SERVER[PHP_SELF]?mode=edit&id=$row[liquid_id]\"><img class=\"action\" src=\"../system/edit.png\" alt=\"&Auml;ndert die Fl&uuml;ssigkeit\"></a></td>\n";
		     $string .= "  <td class=\"action\"><a href=\"$_SERVER[PHP_SELF]?mode=delete&id=$row[liquid_id]\" onclick=\"return confirm('Soll die Flüssigkeit wirklich gelöscht werden?')\"><img class=\"action\" src=\"../system/delete.png\" alt=\"L&ouml;scht die Fl&uuml;ssigkeit\"></a></td>\n";
		     $string .= " </tr>\n";
		     
		     // Sorgt für eine immer wechselnde Hinterhintergrundfarbe der Zeilen
		     if ($color == "#E6E6E6") {$color = "#D5D6D5";} else {$color = "#E6E6E6";}
		    }
		    
		 $string .= "</table>\n";
		 
		 // Gibt die fertige Übersicht über alle in der Datenbank vorhanden Flüssigkeiten aus
		 echo $string;
		 
		 // Gibt 'true' zurück
		 return true;
		}
	     else
	        {
		 // Gibt eine Hinweismeldung zurück, dass keine Flüssigkeit in der Datenbank vorhanden ist
	         echo show_systemmessage("Es liegen keine Flüssigkeiten in der Datenbank vor","info");
		 
		 // Gibt 'true' zurück
		 return true;
		}
	    }
	}
    }
    
    
 // Funktion erzeugt eine Liste mit allen Rezepten aus der Datenbank
 function list_recipes()
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("mixer");
	 
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
	 // Sendet eine SELECT-Anweisung an die Datenbank
	 $sqlresult1 = mysql_query("SELECT cocktails.cocktail_id AS cocktail_id, cocktails.cocktail_name AS cocktail_name, cocktails.cocktail_price AS cocktail_price, categories.category_name AS category_name, IFNULL(max(liquids.liquid_minage),'0') AS cocktail_minage FROM cocktails LEFT JOIN categories ON cocktails.category_id = categories.category_id LEFT JOIN recipes ON cocktails.cocktail_id = recipes.cocktail_id LEFT JOIN liquids ON recipes.liquid_id = liquids.liquid_id GROUP BY cocktails.cocktail_id ORDER BY cocktails.cocktail_name;");
	 
	  if ($sqlresult1 == false)
	    {
	     // Gibt eine Fehlermeldung zurück
	     return show_systemmessage("Es ist leider ein technischer Fehler bei der Abfrage der Rezepturen aus der Datenbank aufgetretten","error");
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     if (mysql_num_rows($sqlresult1) > 0)
	        {
		 // Leert die Stringvariable
		 $string = "";
		 
		 $string .= "<table style=\"width:800px;\">\n";
		 
		 $string .= " <tr>\n";
		 $string .= "  <td class=\"head\">Cocktailname</td>\n";
		 $string .= "  <td class=\"head\">Kategorie</td>\n";
		 $string .= "  <td class=\"head\">Altersfreigabe ab</td>\n";
		 $string .= "  <td class=\"head\">Preis</td>\n";
		 $string .= "  <td class=\"head\" colspan=\"2\"><b>Aktionen</b></td>\n";
		 $string .= " </tr>\n";
		 
		 // Setzt die Anfangshintergrundfarbe
		 $color = "#E6E6E6";
		 
		 // Liest alle Werte der Benutzer aus der Datenbank aus
		 while ($row = mysql_fetch_array($sqlresult1))
		    {
		     $string .= " <tr style=\"background-color:$color;\">\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:left;\">$row[cocktail_name]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:left;\">$row[category_name]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:center;width:100px;\">$row[cocktail_minage]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:right;width:80px;\">$row[cocktail_price] &euro;</td>\n";
		     $string .= "  <td class=\"action\"><a href=\"$_SERVER[PHP_SELF]?mode=edit&id=$row[cocktail_id]\"><img class=\"action\" src=\"../system/edit.png\" alt=\"&Auml;ndert das Cocktailrezept\"></a></td>\n";
		     $string .= "  <td class=\"action\"><a href=\"$_SERVER[PHP_SELF]?mode=delete&id=$row[cocktail_id]\"onclick=\"return confirm('Soll das Cocktalrezept wirklich gelöscht werden?')\"><img class=\"action\" src=\"../system/delete.png\" alt=\"L&ouml;scht das Cocktailrezept\"></a></td>\n";
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
	         return show_systemmessage("Es liegen keine Cocktailrezepte in der Datenbank vor","info");
		}
	    }
	}
    }

 
 // Funktion erstellt eine neue Kategorie
 function new_category()
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("mixer");
	 
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
	 $sqlresult = mysql_query("INSERT INTO categories (category_name, category_description) VALUES (TRIM('$_POST[name]'),TRIM('$_POST[description]'));");
	 
	 // Überprüft, ob es einen Fehler bei der Erstellung einer neuen Cocktailkategorie gab
	 if ($sqlresult == false)
	    {
	     // Zeigt eine Fehlermeldung an, dass die neue Cocktailkategorie nicht in die Datebank eingetragen werden konnte
	     echo show_systemmessage("Beim Erstellen der neuen Kategorie ist leider ein Fehler aufgetretten!","error");
		 
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Gibt 'false' zurück
	     return false;
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Zeigt eine Erfolgsmeldung an, dass die neue Cocktailkategorie erfolgreich in die Datenbank eingetragen worden ist
	     echo show_systemmessage("Die neue Kategorie wurde erfolgreich erstellt!","success");
	     
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Gibt 'true' zurück
	     return true;
	    }
	}
    }
 
 
 // Funktion erstellt eine neue Flüssigkeit
 function new_liquid()
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("mixer");
	 
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
	 $sqlresult = mysql_query("INSERT INTO liquids (liquid_name, liquid_viscosity, liquid_minage) VALUES (TRIM('$_POST[name]'),TRIM(REPLACE('$_POST[viscosity]',',','.')),TRIM('$_POST[agereales]'));");
	     
	 // Überprüft, ob es einen Fehler bei der Erstellung einer neuen Flüssigkeit gab
	 if ($sqlresult == false)
	    {
	     // Zeigt eine Fehlermeldung an, dass die neue Flüssigkeit nicht in die Datebank eingetragen werden konnte
	     echo show_systemmessage("Beim Erstellen der neuen Flüssigkeit ist leider ein Fehler aufgetreten!","error");
		 
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Gibt 'false' zurück
	     return false;
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Zeigt eine Erfolgsmeldung an, dass die neue Flüssigkeit erfolgreich in die Datenbank eingetragen worden ist
	     echo show_systemmessage("Die neue Flüssigkeit wurde erfolgreich erstellt!","success");
	     
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Gibt 'true' zurück
	     return true;
	    }
	}
    }
 
 
 // Funktion erstellt ein neues Cocktailrezept
 function new_recipe()
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
	 $sqlresult1 = mysql_query("INSERT INTO cocktails (cocktail_name, cocktail_price, category_id) VALUES (TRIM('$_POST[name]'),TRIM(REPLACE('$_POST[price]',',','.')),TRIM('$_POST[category]'));");
	 
	 // Liefert die ID der vorherigen INSERT-Anweisung
	 $id = mysql_insert_id();
	 
	 // Überprüft, ob es einen Fehler bei der Erstellung eines neuen Cocktailrezeptes gab
	 if ($sqlresult1 == false || $id == "")
	    {
	     // Zeigt eine Fehlermeldung an, dass das neue Cocktailrezept nicht in die Datebank eingetragen werden konnte
	     echo show_systemmessage("Beim Erstellen des neuen Cocktailrezeptes ist leider ein Fehler aufgetreten!","error");
		 
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Gibt 'false' zurück
	     return false;
	     
	     // Beendet die Ausführung der Funktion
	     exit();
	    }
	 else
	    {
	     // Sendet eine DELETE-Anweisung an die Datenbank, um potentiel vorhandene Rezepturen mit der Cocktail-ID zu löschen
	     $sqlresult2 = mysql_query("DELETE FROM recipes WHERE cocktail_id='$id';");
	     
	     // Überprüft, ob es einen Fehler beim Löschen der unter Umständen vorhanden Zutatenliste gab
	     if ($sqlresult2 == false || $id == "")
	        {
		 // Sendet eine DELETE-Anweisung an die Datenbank, um potentiel vorhandene Rezepturen mit der Cocktail-ID zu löschen
		 $sqlresult3 = mysql_query("DELETE FROM cocktails WHERE cocktail_id='$id';");
		 
		 // Überprüft, ob es einen Fehler beim Löschen der unter Umständen vorhanden Zutatenliste gab
		 if ($sqlresult3 == false || $id = "")
		    {
		     // Zeigt eine Fehlermeldung an, dass das neue Cocktailrezept nicht in die Datebank eingetragen werden konnte
		     echo show_systemmessage("Beim Erstellen des neuen Cocktailrezeptes ist leider ein Fehler aufgetreten! Die Datenbank könnte fehlerhafte Einträge aufweisen!","error");
		     
		     // Beendet die Verbindung zum Datenbankserver
		     mysql_close($conresult);
		     
		     // Gibt 'false' zurück
		     return false;
		     
		     // Beendet die Ausführung der Funktion
		     exit();
		    }
		 else
		    {
		     // Zeigt eine Fehlermeldung an, dass das neue Cocktailrezept nicht in die Datebank eingetragen werden konnte
		     echo show_systemmessage("Beim Erstellen des neuen Cocktailrezeptes ist leider ein Fehler aufgetreten!","error");
		     
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
		 // Liest alle erlaubten eingegeben Zutaten inkl. Priorität und Menge ein
		 for ($count = 1;$count <= count_tanks();$count++)
		     {
		      // Überprüft, ob die eingegebene Zutat nicht leer ist
		      if ($_POST[amount][$count] != "" && $_POST[liquid][$count] != "" && $_POST[priority][$count] != "")
		         {
			  // Löscht den Inhalt der Variablen für die nächste SQL-Anweisung
			  $amount = "";
			  $liquid = "";
			  $priority = "";
			  
			  // Schreibt die eingetragenen Werte in die richtige Variable für die SQL-Anweisung
			  $amount = $_POST[amount][$count];
			  $liquid = $_POST[liquid][$count];
			  $priority = $_POST[priority][$count];
			  
		          $sqlresult3 = mysql_query("INSERT INTO recipes (cocktail_id, liquid_id, liquid_amount, liquid_priority) VALUES (TRIM('$id'),TRIM('$liquid'),TRIM('$amount'),TRIM('$priority'));");
			 }
		      
		      // Überprüft, ob es einen Fehler bei der Aktualisierung des Cocktails gab
		      if ($sqlresult3 == false) {$error = true;}
		     } 
		 
		 // Überprüft, ob es einen Fehler beim Erstellen der Zutatenliste gab
		 if ($error == true)
		    {
		     // Ermittelt die Anzahl der Tanks in der Maschine und schreibt die Anzahl in die Variable
		     $tankcount = count_tanks();
		     
		     // Sendet eine DELETE-Anweisung an die Datenbank um das angegebene Cocktailrezept wieder zu löschen
		     $sqlresult4 = mysql_query("DELETE FROM cocktails WHERE cocktail_id='$id' LIMIT 1;");
		     
		     // Sendet eine DELETE-Anweisung an die Datenbank um die Zutatenliste für das angegeben Cocktailrezept wieder zu löschen
		     $sqlresult5 = mysql_query("DELETE FROM recipes WHERE cocktail_id='$id' LIMIT $tankcount;");
		     
		     if ($sqlresult4 == false || $sqlresult5 == false)
		        {
			 // Zeigt eine Fehlermeldung an, dass das neue Cocktailrezept nicht in die Datebank eingetragen werden konnte
			 echo show_systemmessage("Beim Erstellen des neuen Cocktailrezeptes ist leider ein Fehler aufgetreten! Die Datenbank könnte fehlerhafte Einträge aufweisen!","error");
			  
			  // Beendet die Verbindung zum Datenbankserver
			  mysql_close($conresult);
			  
			  // Gibt 'false' zurück
			  return false;
			  
			  // Beendet die Ausführung der Funktion
			  exit();
			}
		     else
		        {
			 // Zeigt eine Fehlermeldung an, dass das neue Cocktailrezept nicht in die Datebank eingetragen werden konnte
			 echo show_systemmessage("Beim Erstellen des neuen Cocktailrezeptes ist leider ein Fehler aufgetreten!","error");
			 
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
		     // Zeigt eine Erfolgsmeldung an, dass die neue Flüssigkeit erfolgreich in die Datenbank eingetragen worden ist
		     echo show_systemmessage("Der neue Cocktail wurde erfolgreich erstellt!","success");
		     
		     // Beendet die Verbindung zum Datenbankserver
		     mysql_close($conresult);
		     
		     // Gibt 'true' zurück
		     return true;
		    }
		}
	    }
	}
    }
 
  
 // Funktion aktualisiert die angegebene Kategorie der Cocktails
 function update_category()
    {
     // Überprüft, ob die angegebene Flüssigkeit-ID eine Zahl ist
     if (ctype_digit($_GET[id]) == true)
        {
         // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("mixer");
     
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
	     $sqlresult = mysql_query("UPDATE categories SET category_name = TRIM('$_POST[name]'), category_description = TRIM('$_POST[description]') WHERE category_id = '$_GET[id]' LIMIT 1;");
	     
	     // Überprüft, ob es einen Fehler bei der Aktualisierung der Cocktailkategorie gab
	     if ($sqlresult == false)
	        {
	         // Zeigt eine Fehlermeldung an, dass die angegebene Cocktailkategorie nicht aktualisiert werden konnte
	         echo show_systemmessage("Beim Aktualisieren der Kategorie ist leider ein Fehler aufgetreten!","error");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zurück
	         return false;
	     
	         // Beendet die Ausführung der Funktion
	         exit();
	        }
	     else
	        {
		 // Zeigt eine Erfolgsmeldung an, dass die angegebene Kategorie erfolgreich aktualisiert worden ist
	         echo show_systemmessage("Die Kategorie wurde erfolgreich aktualisiert!","success");
		 
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
    
 
 // Funktion führt eine Aktualisierung bei der angegebenen Flüssigkeit durch
 function update_liquid()
    {
     // Überprüft, ob die angegebene Flüssigkeit-ID eine Zahl ist
     if (ctype_digit($_GET[id]) == true)
        {
         // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("mixer");
     
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
	     $sqlresult = mysql_query("UPDATE liquids SET liquid_name = TRIM('$_POST[name]'), liquid_viscosity = TRIM(REPLACE('$_POST[viscosity]',',','.')), liquid_minage = TRIM('$_POST[agereales]') WHERE liquid_id = '$_GET[id]' LIMIT 1;");
	     
	     // Überprüft, ob es einen Fehler bei der Aktualisierung der Flüssigkeit gab
	     if ($sqlresult == false)
	        {
	         // Zeigt eine Fehlermeldung an, dass die angegebene Flüssigkeit nicht aktualisiert werden konnte
	         echo show_systemmessage("Beim Aktualisieren der Flüssigkeit ist leider ein Fehler aufgetreten!","error");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zurück
	         return false;
	     
	         // Beendet die Ausführung der Funktion
	         exit();
	        }
	     else
	        {
		 // Zeigt eine Erfolgsmeldung an, dass die angegebene Flüssigkeit erfolgreich aktualisiert worden ist
	         echo show_systemmessage("Die Flüssigkeit wurde erfolgreich aktualisiert!","success");
		 
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
    
 
 // Funktion führ eine Aktualisierung bei dem angegebenen Cocktailrezept durch
 function update_recipe()
    {
     // Überprüft, ob die angegebene Cocktail-ID eine Zahl ist
     if (ctype_digit($_GET[id]) == true)
        {
         // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("mixer");
     
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
	     $sqlresult1 = mysql_query("UPDATE cocktails SET cocktail_name = TRIM('$_POST[name]'), cocktail_price = TRIM(REPLACE('$_POST[price]',',','.')), category_id = TRIM('$_POST[category]') WHERE cocktail_id = '$_GET[id]' LIMIT 1;");
	     
	     // Überprüft, ob es einen Fehler bei der Aktualisierung des Cocktailrezeptes gab
	     if ($sqlresult1 == false)
	        {
	         // Zeigt eine Fehlermeldung an, dass das angegebene Cocktailrezept nicht aktualisiert werden konnte
	         echo show_systemmessage("Beim Aktualisieren des Cocktailrezeptes ist leider ein Fehler aufgetreten!","error");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zurück
	         return false;
	     
	         // Beendet die Ausführung der Funktion
	         exit();
	        }
	     else
	        {
		 // Sendet eine DELETE-Anweisung an die Datenbank, um alle zum angegebenen Cocktailvorhandenen Zutaten zu löschen
		 $sqlresult2 = mysql_query("DELETE FROM recipes WHERE cocktail_id='$_GET[id]';");
		 
		 // Überprüft, ob es einen Fehler beim Löschen der Zutatenliste zum angegeben Cocktail gab
		 if ($sqlresult2 == false)
		    {
		     // Gibt eine Fehlermeldung an, dass ein interner Verarbeitungsfehler aufgetreten
		     echo show_sysetmmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten","error");
		     
		     // Beendet die Verbindung zum Datenbankserver
		     mysql_close($conresult);
		     
		     // Gibt 'false' zurück
		     return false;
		     
		     // Beendet die Ausführung der Funktion
		     exit();
		    }
		 else
		    {
		     // Liest alle erlaubten eingegeben Zutaten inkl. Priorität und Menge ein
		     for ($count = 1;$count <= count_tanks();$count++)
		         {
		          // Überprüft, ob die eingegebene Zutat nicht leer ist
		          if ($_POST[amount][$count] != "" && $_POST[liquid][$count] != "" && $_POST[priority][$count] != "")
		             {
			      // Löscht den Inhalt der Variablen für die nächste SQL-Anweisung
			      $amount = "";
			      $liquid = "";
			      $priority = "";

			      // Schreibt die eingetragenen Werte in die richtige Variable für die SQL-Anweisung
			      $amount = $_POST[amount][$count];
			      $liquid = $_POST[liquid][$count];
			      $priority = $_POST[priority][$count];

		              $sqlresult3 = mysql_query("INSERT INTO recipes (cocktail_id, liquid_id, liquid_amount, liquid_priority) VALUES (TRIM('$_GET[id]'),TRIM('$liquid'),TRIM('$amount'),TRIM('$priority'));");     
			     }

			 // Überprüft, ob es einen Fehler bei der Aktualisierung des Cocktails gab
		         if ($sqlresult3 == false) {$error = true;}
			}
		
		     // Überprüft, ob es einen Fehler beim Erstellen der Zutatenliste gab
		     if ($error == true)
		        {
			 // Zeigt eine Fehlermeldung an, dass das neue Cocktailrezept nicht in die Datebank eingetragen werden konnte
			 echo show_systemmessage("Beim Aktualisieren des Cocktailrezeptes ist leider ein Fehler aufgetreten! Die Datenbank könnte fehlerhafte Einträge aufweisen!","error");
			 
			 // Beendet die Verbindung zum Datenbankserver
			 mysql_close($conresult);
			 
			 // Gibt 'false' zurück
			 return false;
			 
			 // Beendet die Ausführung der Funktion
			 exit();
			}
		     else
		        {
			 // Zeigt eine Erfolgsmeldung an, dass die angegebene Kategorie erfolgreich aktualisiert worden ist
			 echo show_systemmessage("Das Cocktailrezept wurde erfolgreich aktualisiert!","success");
			 
			 // Beendet die Verbindung zum Datenbankserver
			 mysql_close($conresult);
			 
			 // Gibt 'true' zurück
			 return true;
			}
		    }
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
