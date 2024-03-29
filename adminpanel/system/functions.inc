<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 26.12.2004
 // �nderungsdatum: 08.04.2004
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 

 // Funktion stellt eine Verbindung zur angegebenen Datenbank her
 function db_connect($database)
    {
     // Stellt eine Verbindung zum Datenbankserver her
     $conresult = @mysql_connect("","","");
     
     // W�hlt die richtige Datenbank aus
     $selectresult = mysql_select_db($database);
     
     // Gibt den Erfolgstatus der Aktionen zur�ck
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
     
     // Gibt die formatierte Systemmeldung zur�ck
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
     
     // Gibt den HTML-Kopf zur�ck
     return $string;
    }
    
    
 // Funktion erzeugt den HTML-Fu�
 function create_htmlfoot()
    {
     // Leert die Stringvariable
     $string = "";
     
     $string .= " </body>\n";
     $string .= "</html>\n";
     
     // Gibt den HTML-Fu� zur�ck
     return $string;
    }
    
 
 // Funktion erzeugt das Men� auf der Webseite
 function create_sitemenu($entries,$modes)
    {
     // �berpr�ft, ob die Men�punktvariable genausoviele Elemente hat wie die Modusvariable
     if (sizeof($entries) == sizeof($modes) && (sizeof($entries) > 0 && sizeof($modes) > 0))
        {
	 // Setzt die Z�hlervariable auf 0
	 $count = 0;
	 
	 // Leert die Stringvariable
	 $string = "";
	 
	 $string .= "<table>\n";
	 $string .= " <tr>\n";
	 
	 while (sizeof($entries) > $count)
	    {
	     $string.= "<td class=\"sitemenu\"><a class=\"sitemenu\" href=\"$_SERVER[PHP_SELF]?mode=$modes[$count]\">$entries[$count]</a></td>\n";
	     
	     // Erh�ht die Z�hlervariable um 1
	     $count++;
	    }
	 
	 $string .= " <tr>\n";
	 $string .= "</table>\n";
	    
	 // Gibt das generierte Seitenmenu zur�ck
	 return $string;
	}
     else
        {
	 // Gibt eine Fehlermeldung zur�ck
	 return show_systemmessage("Das Men� konnte leider aus technischen Gr�nden nicht erzeugt werden","error");
	 
	 // Beendet die Ausf�hrung der Funktion
	 exit();
	}
    }
    
    
 // Funktion erstellt eine Liste von Fehlern bei der Daten�berpr�fung
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
     // �berpr�ft, ob entweder die �bergebene Kategorie-ID leer ist oder eine Zahl ist
     if ($id == "" || ctype_digit($id) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und w�hlt die richtige Datenbank aus
         $conresult = db_connect("mixer");
	 
	 // �berpr�ft, ob beim Verbinden kein Fehler aufgetreten ist
         if ($conresult == true)
	    {
	     // Sendet eine SELECT-Anweisung an die Datenbank
	     $sqlresult = mysql_query("SELECT category_id, category_name FROM categories ORDER BY category_name ASC;");
	     
	     // �berpr�ft, ob es keinen Fehler bei der Abfrage der Cocktailkategorien gab
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
		     // �berpr�f, ob die �bergebene Kategorie-ID gleich der aus der Datenbank ausgelesenen ist
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
		 
		 // Gibt die fertig erzeugte Auswahlbox mit allen in der Datenbank vorhanden Cocktailkategorien zur�ck
		 return $string;
		}
	    }
	}
    }
    
    
 // Funktion erstellt eine Auswahlbox mit allen in der Datenbank vorhandenen Cocktails
 function create_cocktailselection($id,$name)
    {
     // �berpr�ft, ob entweder die �bergebene Cocktail-ID leer ist oder eine Zahl ist
     if ($id == "" || ctype_digit($id) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und w�hlt die richtige Datenbank aus
         $conresult = db_connect("mixer");
	 
	 // �berpr�ft, ob beim Verbinden kein Fehler aufgetreten ist
         if ($conresult == true)
	    {
	     // Sendet eine SELECT-Anweisung an die Datenbank
	     $sqlresult = mysql_query("SELECT cocktail_id, cocktail_name FROM cocktails ORDER BY cocktail_name ASC;");
	     
	     // �berpr�ft, ob es keinen Fehler bei der Abfrage der Cocktails gab
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
		     // �berpr�f, ob die �bergebene Cocktail-ID gleich der aus der Datenbank ausgelesenen ist
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
		 
		 // Gibt die fertig erzeugte Auswahlbox mit allen in der Datenbank vorhanden Cocktails zur�ck
		 return $string;
		}
	    }
	}
    }
    
    
 // Funktion erstellt eine Auswahlbox mit allen in der Datenbank vorhandenen Fl�ssigkeiten
 function create_liquidselection($id,$name)
    {
     // �berpr�ft, ob entweder die �bergebene Fl�ssigkeitsl-ID leer ist oder eine Zahl ist
     if ($id == "" || ctype_digit($id) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und w�hlt die richtige Datenbank aus
         $conresult = db_connect("mixer");
	 
	 // �berpr�ft, ob beim Verbinden kein Fehler aufgetreten ist
         if ($conresult == true)
	    {
	     // Sendet eine SELECT-Anweisung an die Datenbank
	     $sqlresult = mysql_query("SELECT liquid_id, liquid_name FROM liquids ORDER BY liquid_name ASC;");
	     
	     // �berpr�ft, ob es keinen Fehler bei der Abfrage der Fl�ssigkeiten gab
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
		 
		 // Liest die Fl�ssigkeits-ID und den Fl�ssigkeitsnamen aus der Datenbank aus
		 while ($row = mysql_fetch_array($sqlresult))
		    {
		     // �berpr�f, ob die �bergebene Fl�ssigkeits-ID gleich der aus der Datenbank ausgelesenen ist
		     if ($id == $row[liquid_id])
		        {
			 // Schreib in die 'selected'-Variable
			 $selected = " selected";
			}
		
		     // Erzeugt eine Auswahloption mit der aus der Datenbank ausgelesenen Fl�ssigkeiten
		     $string .= " <option value=\"$row[liquid_id]\"$selected>$row[liquid_name]</option>";
		     
		     // Setzt die 'selected'-Variable wieder auf den Standardwert
		     $selected = "";
		    }
		    
		 // Beendet die Auswahlbox
		 $string .= "</select>";
		 
		 // Gibt die fertig erzeugte Auswahlbox mit allen in der Datenbank vorhanden Fl�ssigkeiten zur�ck
		 return $string;
		}
	    }
	}
    }
    
 
 // Funktion erstellt eine Auswahlbox mit allen in der Datenbank vorhandenen Benutzer
 function create_userselection($id,$name)
    {
     // �berpr�ft, ob entweder die �bergebene Benutzer-ID leer ist oder eine Zahl ist
     if ($id == "" || ctype_digit($id) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und w�hlt die richtige Datenbank aus
         $conresult = db_connect("commerce");
	 
	 // �berpr�ft, ob beim Verbinden kein Fehler aufgetreten ist
         if ($conresult == true)
	    {
	     // Sendet eine SELECT-Anweisung an die Datenbank
	     $sqlresult = mysql_query("SELECT user_id, user_firstname, user_lastname FROM users ORDER BY user_lastname ASC, user_firstname ASC;");
	     
	     // �berpr�ft, ob es keinen Fehler bei der Abfrage der Benutzer gab
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
		     // �berpr�f, ob die �bergebene Benutzer-ID gleich der aus der Datenbank ausgelesenen ist
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
		 
		 // Gibt die fertig erzeugte Auswahlbox mit allen in der Datenbank vorhanden Benutzer zur�ck
		 return $string;
		}
	    }
	}
    }
    
  
 // Funktion ermittelt die Anzahl der Tanks in der Maschine
 function count_tanks()
    {
     // Stellt eine Verbindung zum Datenbankserver her und w�hlt die richtige Datenbank aus
     $conresult = db_connect("mixer");
     
     // �berpr�ft, ob beim Verbinden kein Fehler aufgetreten ist
     if ($conresult == true)
	{
	 // Sendet eine SELECT-Anweisung an die Datenbank
	 $sqlresult = mysql_query("SELECT COUNT('') AS tank_count FROM tanks LIMIT 1;");
	 
	 // �berpr�ft, ob es keinen Fehler bei der Abfrage der Anzahl von Tanks gab
	 if ($sqlresult == true)
	    {
	     // Liest die Anzahl der Tanks aus
	     $row = mysql_fetch_array($sqlresult);
	     
	     // Gibt die Anzahl der Tanks zur�ck
	     return $row[tank_count];
	    }
	 else
	    {
	     // Gibt einen leeren String zur�ck
	     return "";
	    }
	}
     else
        {
	 // Gibt einen leeren String zur�ck
	 return "";
	}
    }
?>