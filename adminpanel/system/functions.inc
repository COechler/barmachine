<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 26.12.2004
 // Änderungsdatum: 08.04.2004
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 

 // Funktion stellt eine Verbindung zur angegebenen Datenbank her
 function db_connect($database)
    {
     // Stellt eine Verbindung zum Datenbankserver her
     $conresult = @mysql_connect("","","");
     
     // Wählt die richtige Datenbank aus
     $selectresult = mysql_select_db($database);
     
     // Gibt den Erfolgstatus der Aktionen zurück
     if ($conresult == false || $selectresult == false) {return false;} else {return $conresult;}
    }
    
  
 // Funktion gibt eine formatierte Systemmeldung aus
 function show_systemmessage($message,$kind)
    {
     // Leert die String Variable
     $string = "";
     
     if ($kind == "error")
        {
	 $string .= "<table style=\"width:300px;\">\n";
	 $string .= " <tr>\n";
	 $string .= "  <td class=\"standard\" style=\"background-color:#FF0000;color:#FFFFFF;font-weight:bold;\">Fehler</td>\n";
	 $string .= " </tr>\n";
	 $string .= " <tr>\n";
	 $string .= "  <td class=\"standard\" style=\"background-color:#FFFFCD;height:200px;vertical-align:top;\">".htmlentities($message)."</td>\n";
	 $string .= " </tr>\n";
	 $string .= "</table>\n";
	}

     if ($kind == "info")
        {
	 $string .= "<table style=\"width:300px;\">\n";
	 $string .= " <tr>\n";
	 $string .= "  <td class=\"standard\" style=\"background-color:#D5DEE6;color:#000000;font-weight:bold;\">Information</td>\n";
	 $string .= " </tr>\n";
	 $string .= " <tr>\n";
	 $string .= "  <td class=\"standard\" style=\"background-color:#FFFFCD;height:200px;vertical-align:top;\">".htmlentities($message)."</td>\n";
	 $string .= " </tr>\n";
	 $string .= "</table>\n";
	}
	
     if ($kind == "success")
        {
	 $string .= "<table style=\"width:300px;\">\n";
	 $string .= " <tr>\n";
	 $string .= "  <td class=\"standard\" style=\"background-color:#008D00;color:#FFFFFF;font-weight:bold;\">Erfolg</td>\n";
	 $string .= " </tr>\n";
	 $string .= " <tr>\n";
	 $string .= "  <td class=\"standard\" style=\"background-color:#FFFFCD;height:200px;vertical-align:top;\">".htmlentities($message)."</td>\n";
	 $string .= " </tr>\n";
	 $string .= "</table>\n";
	}
     
     // Gibt die formatierte Systemmeldung zurück
     return $string;
    }
 
 
 // Funktion erzeugt den HTML-Kopf der Webseite
 function create_htmlheader($name)
    {
     // Leert die Stringvariable
     $string = "";
     
     $string .= "<html>\n";
     $string .= " <head>\n";
     
     // Gibt den Titel der Webseite an
     $string .= "  <title>".htmlentities($name)."</title>\n";
     
     // Bindet das Standard-Stylesheet ein
     $string .= "  <link rel=\"stylesheet\" type=\"text/css\" href=\"../system/standard.css\">\n";
     
     // Gibt den Zeichensatz der Webseite an
     $string .= "  <meta http-equiv=\"content-type\" content=\"text/html; charset=ISO-8859-1\">\n";
     
     // Erzeugt die Meta-Angabe mit dem Titel der Webseite
     $string .= "  <meta name=\"DC.Title\" content=\"".htmlentities($name)."\">\n";
     
     // Erzeugt die Meta-Angabe mit dem Urheber der Webseite
     $string .= "  <meta name=\"DC.Creator\" content=\"Name\">\n";
     
     // Erzeugt die Meta-Angabe wann die Datei erstellt worden ist
     $string .= "  <meta name=\"DC.Date\" content=\"[Hier kommt das Dateidatum hin]\">\n";
     
     // Erzeugt die Meta-Angabe mit dem Dokumententyp
     $string .= "  <meta name=\"DC.Type\" content=\"Service\">\n";
     
     // Erzeugt die Meta-Angabe mit dem Mime-Typ der Webseite
     $string .= "  <meta name=\"DC.Format\" content=\"application/x-httpd-php\">";
     
     // Erzeugt die Meta-Angabe mit der Landessprache des Inhalts auf der Webseite
     $string .= "  <meta name=\"DC.Language\" content=\"de\">\n";
     
     // Erzeugt die Meta-Angabe mit dem Copyright der Webseite
     $string .= "  <meta name=\"DC.Rights\" content=\"&copy; [Jahr der Erzeugung] Christian Oechler\">\n";
     
     // Erzeugt die Meta-Angabe mit dem Verbot, die Seite in einem Suchindex aufzunehmen
     $string .= "  <meta name=\"robots\" content=\"noindex\">\n";
     
     // Gibt die Defaultsprachen der Webseite an
     $string .= "  <meta http-equiv=\"Content-Script-Type\" content=\"text/javascript\">\n";
     $string .= "  <meta http-equiv=\"Content-Style-Type\" content=\"text/css\">\n";
     
     // Verbietet es, die Webseite zwischenzuspeichern
     $string .= "  <meta http-equiv=\"expires\" content=\"0\">\n";
     $string .= "  <meta http-equiv=\"cache-control\" content=\"no-cache\">\n";
     $string .= "  <meta http-equiv=\"pragma\" content=\"no-cache\">\n";
     
     $string .= " </head>\n";
     
     $string .= " \n<body class=\"standard\">\n";
     
     // Gibt den HTML-Kopf zurück
     return $string;
    }
    
    
 // Funktion erzeugt den HTML-Fuß
 function create_htmlfoot()
    {
     // Leert die Stringvariable
     $string = "";
     
     $string .= " </body>\n";
     $string .= "</html>\n";
     
     // Gibt den HTML-Fuß zurück
     return $string;
    }
    
 
 // Funktion erzeugt das Menü auf der Webseite
 function create_sitemenu($entries,$modes)
    {
     // Überprüft, ob die Menüpunktvariable genausoviele Elemente hat wie die Modusvariable
     if (sizeof($entries) == sizeof($modes) && (sizeof($entries) > 0 && sizeof($modes) > 0))
        {
	 // Setzt die Zählervariable auf 0
	 $count = 0;
	 
	 // Leert die Stringvariable
	 $string = "";
	 
	 $string .= "<table>\n";
	 $string .= " <tr>\n";
	 
	 while (sizeof($entries) > $count)
	    {
	     $string.= "<td class=\"sitemenu\"><a class=\"sitemenu\" href=\"$_SERVER[PHP_SELF]?mode=$modes[$count]\">$entries[$count]</a></td>\n";
	     
	     // Erhöht die Zählervariable um 1
	     $count++;
	    }
	 
	 $string .= " <tr>\n";
	 $string .= "</table>\n";
	    
	 // Gibt das generierte Seitenmenu zurück
	 return $string;
	}
     else
        {
	 // Gibt eine Fehlermeldung zurück
	 return show_systemmessage("Das Menü konnte leider aus technischen Gründen nicht erzeugt werden","error");
	 
	 // Beendet die Ausführung der Funktion
	 exit();
	}
    }
    
    
 // Funktion erstellt eine Liste von Fehlern bei der Datenüberprüfung
 function create_errorlist($error)
    {
     // Leert die Stringvariable
     $string = "";
	     
     foreach ($error as $value) 
       {
        $string .= $value."\n";
       }
	          
     // Zeigt die Fehlermeldungen an
     echo show_systemmessage($string,"error");
    }
    
    
 // Funktion erstellt eine Auswahlbox mit allen in der Datenbank vorhandenen Cocktailkategorien
 function create_categoryselection($id,$name)
    {
     // Überprüft, ob entweder die übergebene Kategorie-ID leer ist oder eine Zahl ist
     if ($id == "" || ctype_digit($id) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("mixer");
	 
	 // Überprüft, ob beim Verbinden kein Fehler aufgetreten ist
         if ($conresult == true)
	    {
	     // Sendet eine SELECT-Anweisung an die Datenbank
	     $sqlresult = mysql_query("SELECT category_id, category_name FROM categories ORDER BY category_name ASC;");
	     
	     // Überprüft, ob es keinen Fehler bei der Abfrage der Cocktailkategorien gab
	     if ($sqlresult == true)
	        {
		 // Leert die Stringvariable
		 $string = "";
		 
		 // Startet die Auswahlbox
		 $string .= "<select class=\"standard\" style=\"width:240px;\" size=\"1\" name=\"$name\">";
		 
		 // Erzeugt ein leere Auswahloption
		 $string .= " <option value=\"\">&nbsp;</option>";
		 
		 // Setzt den Standardwert der 'selected'-Variable
		 $selected = "";
		 
		 // Liest die Kategorie-ID und den Kategorienamen aus der Datenbank aus
		 while ($row = mysql_fetch_array($sqlresult))
		    {
		     // Überprüf, ob die übergebene Kategorie-ID gleich der aus der Datenbank ausgelesenen ist
		     if ($id == $row[category_id])
		        {
			 // Schreib in die 'selected'-Variable
			 $selected = " selected";
			}
		
		     // Erzeugt eine Auswahloption mit der aus der Datenbank ausgelesenen Kategorie
		     $string .= " <option value=\"$row[category_id]\"$selected>$row[category_name]</option>";
		     
		     // Setzt die 'selected'-Variable wieder auf den Standardwert
		     $selected = "";
		    }
		    
		 // Beendet die Auswahlbox
		 $string .= "</select>";
		 
		 // Gibt die fertig erzeugte Auswahlbox mit allen in der Datenbank vorhanden Cocktailkategorien zurück
		 return $string;
		}
	    }
	}
    }
    
    
 // Funktion erstellt eine Auswahlbox mit allen in der Datenbank vorhandenen Cocktails
 function create_cocktailselection($id,$name)
    {
     // Überprüft, ob entweder die übergebene Cocktail-ID leer ist oder eine Zahl ist
     if ($id == "" || ctype_digit($id) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("mixer");
	 
	 // Überprüft, ob beim Verbinden kein Fehler aufgetreten ist
         if ($conresult == true)
	    {
	     // Sendet eine SELECT-Anweisung an die Datenbank
	     $sqlresult = mysql_query("SELECT cocktail_id, cocktail_name FROM cocktails ORDER BY cocktail_name ASC;");
	     
	     // Überprüft, ob es keinen Fehler bei der Abfrage der Cocktails gab
	     if ($sqlresult == true)
	        {
		 // Leert die Stringvariable
		 $string = "";
		 
		 // Startet die Auswahlbox
		 $string .= "<select class=\"standard\" style=\"width:240px;\" size=\"1\" name=\"$name\">";
		 
		 // Erzeugt ein leere Auswahloption
		 $string .= " <option value=\"\">&nbsp;</option>";
		 
		 // Setzt den Standardwert der 'selected'-Variable
		 $selected = "";
		 
		 // Liest die Cocktail-ID und den Cocktailnamen aus der Datenbank aus
		 while ($row = mysql_fetch_array($sqlresult))
		    {
		     // Überprüf, ob die übergebene Cocktail-ID gleich der aus der Datenbank ausgelesenen ist
		     if ($id == $row[cocktail_id])
		        {
			 // Schreib in die 'selected'-Variable
			 $selected = " selected";
			}
		
		     // Erzeugt eine Auswahloption mit der aus der Datenbank ausgelesenen Kategorie
		     $string .= " <option value=\"$row[cocktail_id]\"$selected>$row[cocktail_name]</option>";
		     
		     // Setzt die 'selected'-Variable wieder auf den Standardwert
		     $selected = "";
		    }
		    
		 // Beendet die Auswahlbox
		 $string .= "</select>";
		 
		 // Gibt die fertig erzeugte Auswahlbox mit allen in der Datenbank vorhanden Cocktails zurück
		 return $string;
		}
	    }
	}
    }
    
    
 // Funktion erstellt eine Auswahlbox mit allen in der Datenbank vorhandenen Flüssigkeiten
 function create_liquidselection($id,$name)
    {
     // Überprüft, ob entweder die übergebene Flüssigkeitsl-ID leer ist oder eine Zahl ist
     if ($id == "" || ctype_digit($id) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("mixer");
	 
	 // Überprüft, ob beim Verbinden kein Fehler aufgetreten ist
         if ($conresult == true)
	    {
	     // Sendet eine SELECT-Anweisung an die Datenbank
	     $sqlresult = mysql_query("SELECT liquid_id, liquid_name FROM liquids ORDER BY liquid_name ASC;");
	     
	     // Überprüft, ob es keinen Fehler bei der Abfrage der Flüssigkeiten gab
	     if ($sqlresult == true)
	        {
		 // Leert die Stringvariable
		 $string = "";
		 
		 // Startet die Auswahlbox
		 $string .= "<select class=\"standard\" style=\"width:240px;\" size=\"1\" name=\"$name\">";
		 
		 // Erzeugt ein leere Auswahloption
		 $string .= " <option value=\"\">&nbsp;</option>";
		 
		 // Setzt den Standardwert der 'selected'-Variable
		 $selected = "";
		 
		 // Liest die Flüssigkeits-ID und den Flüssigkeitsnamen aus der Datenbank aus
		 while ($row = mysql_fetch_array($sqlresult))
		    {
		     // Überprüf, ob die übergebene Flüssigkeits-ID gleich der aus der Datenbank ausgelesenen ist
		     if ($id == $row[liquid_id])
		        {
			 // Schreib in die 'selected'-Variable
			 $selected = " selected";
			}
		
		     // Erzeugt eine Auswahloption mit der aus der Datenbank ausgelesenen Flüssigkeiten
		     $string .= " <option value=\"$row[liquid_id]\"$selected>$row[liquid_name]</option>";
		     
		     // Setzt die 'selected'-Variable wieder auf den Standardwert
		     $selected = "";
		    }
		    
		 // Beendet die Auswahlbox
		 $string .= "</select>";
		 
		 // Gibt die fertig erzeugte Auswahlbox mit allen in der Datenbank vorhanden Flüssigkeiten zurück
		 return $string;
		}
	    }
	}
    }
    
 
 // Funktion erstellt eine Auswahlbox mit allen in der Datenbank vorhandenen Benutzer
 function create_userselection($id,$name)
    {
     // Überprüft, ob entweder die übergebene Benutzer-ID leer ist oder eine Zahl ist
     if ($id == "" || ctype_digit($id) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
         $conresult = db_connect("commerce");
	 
	 // Überprüft, ob beim Verbinden kein Fehler aufgetreten ist
         if ($conresult == true)
	    {
	     // Sendet eine SELECT-Anweisung an die Datenbank
	     $sqlresult = mysql_query("SELECT user_id, user_firstname, user_lastname FROM users ORDER BY user_lastname ASC, user_firstname ASC;");
	     
	     // Überprüft, ob es keinen Fehler bei der Abfrage der Benutzer gab
	     if ($sqlresult == true)
	        {
		 // Leert die Stringvariable
		 $string = "";
		 
		 // Startet die Auswahlbox
		 $string .= "<select class=\"standard\" style=\"width:240px;\" size=\"1\" name=\"$name\">";
		 
		 // Erzeugt ein leere Auswahloption
		 $string .= " <option value=\"\">&nbsp;</option>";
		 
		 // Setzt den Standardwert der 'selected'-Variable
		 $selected = "";
		 
		 // Liest die Benutzers-ID und den Vor- und Nachnamen des Benutzers aus der Datenbank aus
		 while ($row = mysql_fetch_array($sqlresult))
		    {
		     // Überprüf, ob die übergebene Benutzer-ID gleich der aus der Datenbank ausgelesenen ist
		     if ($id == $row[user_id])
		        {
			 // Schreib in die 'selected'-Variable
			 $selected = " selected";
			}
		
		     // Erzeugt eine Auswahloption mit der aus der Datenbank ausgelesenen Benutzer
		     $string .= " <option value=\"$row[user_id]\"$selected>$row[user_firstname] $row[user_lastname]</option>";
		     
		     // Setzt die 'selected'-Variable wieder auf den Standardwert
		     $selected = "";
		    }
		    
		 // Beendet die Auswahlbox
		 $string .= "</select>";
		 
		 // Gibt die fertig erzeugte Auswahlbox mit allen in der Datenbank vorhanden Benutzer zurück
		 return $string;
		}
	    }
	}
    }
    
  
 // Funktion ermittelt die Anzahl der Tanks in der Maschine
 function count_tanks()
    {
     // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
     $conresult = db_connect("mixer");
     
     // Überprüft, ob beim Verbinden kein Fehler aufgetreten ist
     if ($conresult == true)
	{
	 // Sendet eine SELECT-Anweisung an die Datenbank
	 $sqlresult = mysql_query("SELECT COUNT('') AS tank_count FROM tanks LIMIT 1;");
	 
	 // Überprüft, ob es keinen Fehler bei der Abfrage der Anzahl von Tanks gab
	 if ($sqlresult == true)
	    {
	     // Liest die Anzahl der Tanks aus
	     $row = mysql_fetch_array($sqlresult);
	     
	     // Gibt die Anzahl der Tanks zurück
	     return $row[tank_count];
	    }
	 else
	    {
	     // Gibt einen leeren String zurück
	     return "";
	    }
	}
     else
        {
	 // Gibt einen leeren String zurück
	 return "";
	}
    }
?>