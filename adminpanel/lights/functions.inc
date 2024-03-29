<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 31.12.2004
 // �nderungsdatum: 18.04.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 
 // Funktion erzeugt eine Eingabemaske f�r Lichtmoduldaten
 function create_inputmasklightmoduls()
    {
     // �berpr�ft, ob eine Lichtmodul-ID vorliegt und der Modus "edit" ausgew�hlt wurde
     if ($_GET[id] != "" && $_GET[mode] == "edit")
        {
	 // Stellt eine Verbindung zum Datenbankserver her und w�hlt die richtige Datenbank aus
         $conresult = db_connect("lights");
     
         // �berpr�ft, ob beim Verbinden ein Fehler aufgetreten ist
         if ($conresult == false)
	    {
	     // Gibt eine Fehlermeldung zur�ck
	     return show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten","error");
	     
	     // Beendet die Ausf�hrung der Funktion
	     exit();
	    }
         else
            {
	     // Sendet eine SELECT-Anweisung an die Datenbank
	     $sqlresult = mysql_query("SELECT lightmodul_id, lightmodul_name, lightmodul_description FROM lightmoduls WHERE lightmodul_id='$_GET[id]' LIMIT 1;");
	     
	     if ($sqlresult == false)
	        {
	         // Gibt eine Fehlermeldung zur�ck
	         return show_systemmessage("Es ist ein Fehler bei der Erzeugung der Bearbeitungsmaske aufgetreten","error");
	     
	         // Beendet die ge�ffnete Verbindung zum Datenbankserver
	         mysql_close($conresult);
	     
	         // Beendet die Ausf�hrung der Funktion
	         exit();
	        }
	     else
	        {
		 // �berpr�ft ob wirklich nur die Daten von einem Lichtmodul abgefragt worden sind
		 if (mysql_num_rows($sqlresult) == 1)
		    {
		     // Liest die Werte zu dem angegebenen Lichtmodul aus 
		     $row = mysql_fetch_array($sqlresult);     
		     
		     // Schreibt sie in die richtige Variable
		     $id = $row[lightmodul_id];
		     $name = $row[lightmodul_name];
		     $description = $row[lightmodul_description];
		    }
		 else
		    {
		     // Gibt eine Fehlermeldung zur�ck
	             return show_systemmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten","error");
	     
	             // Beendet die ge�ffnete Verbindung zum Datenbankserver
	             mysql_close($conresult);
	     
	             // Beendet die Ausf�hrung der Funktion
	             exit();
		    }
		}
	    }
	}
     else
        {
	 // Schreibt die �ber die Post-Variablen �bergebenen Werte in die richtige Variablen
	 $id = $_POST[id];
	 $name = $_POST[name];
	 $description = $_POST[description];
	}
	
     // W�hlt die richtige Beschriftung f�r den Sendeknopf aus
     if	($_GET[id] != "" && $_GET[mode] == "edit")
        {
	 // Schreibt den Bildnamen f�r den Button in die entsprechende Variable
	 $imagename = "update.png";
	}
     else
        {
	 // Schreibt den Bildnamen f�r den Button in die entsprechende Variable
	 $imagename = "insert.png";
	}
	
     // Leert die Stringvariable
     $string = "";
     
     $string .= "<table>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">ID:&nbsp;&nbsp;(1 bis 3)</td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\"><input class=\"standard\" type=\"text\" name=\"id\" value=\"$id\" maxlength=\"1\"></td>\n";
     $string .= " </tr>\n";
     $string .= " <tr>\n";
     $string .= " <td class=\"standard\">&nbsp;</td>\n";
     $string .= " </tr>\n";
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
     $string .= " <td class=\"standard\">Beschreibung:&nbsp;&nbsp;(max. 65535 Zeichen)</td>\n";
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
     
     // Gibt die fertige Eingabemaske zur�ck
     return $string;
    }
 
    
 // Funktion �berpr�ft die Daten f�r das eingegebene Lichtmodul
 function check_lightmoduldatas()
    {
     // �berpr�ft ob alle Inhalte der Eingabemaske gesendet wurden
     if (isset($_POST[id]) == true && isset($_POST[name]) == true && isset($_POST[description]) == true)
        {
	 // Setzt die Fehlerzahlvariable auf 0
	 $errorcount = 0;
	 
	 // �berpr�ft, dass alle Pflichtangaben gemacht worden sind
	 if ($_POST[id] == "") {$errorcount++; $error[$errorcount] = "Die Lichtmodul-ID wurde nicht eingegeben!";}
	 if ($_POST[name] == "") {$errorcount++; $error[$errorcount] = "Der Lichtmodul Name wurde nicht eingegeben!";}
	 
	 // �berpr�ft, dass die Eingaben nicht zu lang sind
	 if (strlen($_POST[id]) > 1) {$errorcount++; $error[$errorcount] = "Die eingegebene Lichtmodul-ID ist zu lang!";}
	 if (strlen($_POST[name]) > 30) {$errorcount++; $error[$errorcount] = "Der eingegebene Lichtmodul-Name ist zu lang!";}
	 if (strlen($_POST[description]) > 65535) {$errorcount++; $error[$errorcount] = "Die eingegebene Lichtmodul-Beschreibung ist zu lang!";}
	 
	 // �berpr�ft, ob die ID im g�ltigen Rahmen ist
	 if ($_POST[id] < 1 || $_POST[id] > 3) {$errorcount++; $error[$errorcount] = "Die eingegebene Lichtmodul-ID ist zu ung�ltig!";}
	 
	 // Stellt eine Verbindung zum Datenbankserver her und w�hlt die richtige Datenbank aus
         $conresult = db_connect("lights");
     
         // �berpr�ft, ob beim Verbinden ein Fehler aufgetreten ist
         if ($conresult == false)
	    {
	     // Zeigt eine Fehlermeldung an
	     echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten","error");
	     
	     // Beendet die Ausf�hrung der Funktion
	     exit();
	    }
	 else
	    {
	     // F�hrt die Codeteile nur aus, wenn nicht der Bearbeitungsmodus ausgew�hlt worden ist
	     if ($_GET[mode] != "edit")
	        {
	         // �berpr�ft, ob die ID nicht schon vergeben ist
	         if (mysql_num_rows(mysql_query("SELECT NULL FROM lightmoduls WHERE lightmodul_id = TRIM('$_POST[id]');")) > 0) {$errorcount++; $error[$errorcount] = "Die eingegebene Lichtmodul-ID ist schon belegt!";}
	 
	         // �berpr�ft, ob der Name nicht schon vergeben ist
	         if (mysql_num_rows(mysql_query("SELECT NULL FROM lightmoduls WHERE lightmodul_name=TRIM('$_POST[name]');")) > 0) {$errorcount++; $error[$errorcount] = "Der eingegebene Lichtmodul-Name ist schon belegt!";}
	     
	         // Beendet die Verbindung zum Datenbankserver
	         mysql_close($conresult);
		}
	    }
	 
	 // �berpr�ft, ob mindestens ein Fehler bei der �berpr�fung der Daten aufgetreten ist
	 if ($errorcount == 0)
	    {
	     // Es wird 'true' zur�ck gegebenen, da kein Fehler aufgetreten ist
	     return true;
	    }
	 else
	    {
	     // Gibt eine Liste mit Fehlermeldungen aus
	     create_errorlist($error);
	     
	     // Gibt 'false' zur�ck
	     return false;
	    } 
	}
     else
        {
	 // Gibt 'false' zur�ck
	 return false;
	}
    }
 
     

 
    
 
    
    
 
    
    
 // Funktion listet alle vorhanden Lichtmodule inklusive ihres Statuses auf
 function list_lightmoduls()
    {
     // Stellt eine Verbindung zum Datenbankserver her und w�hlt die richtige Datenbank aus
     $conresult = db_connect("lights");
	 
     // �berpr�ft, ob beim Verbinden ein Fehler aufgetreten ist
     if ($conresult == false)
	{
	 // Gibt eine Fehlermeldung zur�ck
	 return show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten","error");
	     
	 // Beendet die Ausf�hrung der Funktion
	 exit();
	}
     else
        {
	 // Sendet eine SELECT-Anweisung an die Datenbank
	 $sqlresult = mysql_query("SELECT lightmodul_id, lightmodul_name, lightmodul_description FROM lightmoduls ORDER BY lightmodul_id ASC LIMIT 12;");
	 
	 if ($sqlresult == false)
	    {
	     // Gibt eine Fehlermeldung zur�ck
	     return show_systemmessage("Es ist ein Fehler bei der Abfrage der Lichtmodule aus der Datenbank aufgetreten","error");
	     
	     // Beendet die ge�ffnete Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Beendet die Ausf�hrung der Funktion
	     exit();
	    }
	 else
	    {
	     // Leert die Stringvariable
	     $string = "";
	     
	     // �berpr�ft, ob mindestens ein Lichtmodul vorhanden ist
	     if (mysql_num_rows($sqlresult) > 0)
	        {
		 $string .= "<table style=\"width:800px;\">\n";
		 
		 $string .= " <tr>\n";
		 $string .= "  <td class=\"head\">ID</td>\n";
		 $string .= "  <td class=\"head\">Name</td>\n";
		 $string .= "  <td class=\"head\">Beschreibung</td>\n";
		 $string .= "  <td class=\"head\" colspan=\"2\"><b>Aktionen</b></td>\n";
		 $string .= " </tr>\n";
		 
		 // Setzt die Anfangshintergrundfarbe
		 $color = "#E6E6E6";
		 
		 // Liest alle Werte der Lichtmodule aus der Datenbank aus
		 while ($row = mysql_fetch_array($sqlresult))
		    {
		     $string .= " <tr style=\"background-color:$color;\">\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:center;width:50px;\">$row[lightmodul_id]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:left;width:200px;\">$row[lightmodul_name]</td>\n";
		     $string .= "  <td class=\"standard\" style=\"text-align:left;\">$row[lightmodul_description]</td>\n";
		     $string .= "  <td class=\"action\"><a href=\"$_SERVER[PHP_SELF]?mode=edit&id=$row[lightmodul_id]\"><img class=\"action\" src=\"../system/edit.png\" alt=\"&Auml;;ndert das Lichtmodul\"></a></td>\n";
		     $string .= "  <td class=\"action\"><a href=\"$_SERVER[PHP_SELF]?mode=delete&id=$row[lightmodul_id]\" onclick=\"return confirm('Soll das Lichtmodul wirklich gel�scht werden?')\"><img class=\"action\" src=\"../system/delete.png\" alt=\"L&ouml;scht das Lichtmodul\"></a></td>\n";
		     $string .= " </tr>\n";
		     
		     // Sorgt f�r eine immer wechselnde Hinterhintergrundfarbe der Zeilen
		     if ($color == "#E6E6E6") {$color = "#D5D6D5";} else {$color = "#E6E6E6";}
		    }
		    
		 $string .= "</table>\n";
		 
		 return $string;
		}
	     else
	        {
		 // Gibt eine Hinweismeldung zur�ck
	         return show_systemmessage("Es sind keine Lichtmodule vorhanden!","info");
		}
	    }
	}
    }
    
    
    
    
    
    
    
    
    
    
    
    

    
    
    
    
 // Funktion erstellt ein neues Lichtmodul
 function new_lightmodul()
    {
     // Stellt eine Verbindung zum Datenbankserver her und w�hlt die richtige Datenbank aus
     $conresult = db_connect("lights");
     
     // �berpr�ft, ob beim Verbinden ein Fehler aufgetreten ist
     if ($conresult == false)
	{
	 // Zeigt eine Fehlermeldung an, dass ein Fehler beim Verbinden zur Datenbank aufgetreten ist
	 echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten!","error");
	     
	 // Gibt 'false' zur�ck
	 return false;
	     
	 // Beendet die Ausf�hrung der Funktion
	 exit();
	}
     else
        {
	 // Sendet eine INSERT-Anweisung an die Datenbank
	 $sqlresult = mysql_query("INSERT INTO lightmoduls (lightmodul_id, lightmodul_name, lightmodul_description) VALUES (TRIM('$_POST[id]'),TRIM('$_POST[name]'),TRIM('$_POST[description]'));");
	 
	 // �berpr�ft, ob es einen Fehler bei der Erstellung eines neuen Lichtmoduls gab
	 if ($sqlresult == false)
	    {
	     // Zeigt eine Fehlermeldung an, dass das neue Lichtmodul nicht in die Datenbank eingetragen werden konnte
	     echo show_systemmessage("Beim Erstellen des Lichtmoduls ist leider ein Fehler aufgetreten!","error");
	     
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Gibt 'false' zur�ck
	     return false;
	     
	     // Beendet die Ausf�hrung der Funktion
	     exit();
	    }
	 else
	    {
	     // Zeigt eine Erfolgsmeldung an, dass das neue Lichtmodul erfolgreich in die Datenbank eingetragen worde
	     echo show_systemmessage("Das Lichtmodul wurde erfolgreich erstellt!","success");
	     
	     // Beendet die Verbindung zum Datenbankserver
	     mysql_close($conresult);
	     
	     // Gibt 'true' zur�ck
	     return true;
	    }
	}
    }
        
    
 // Funktion l�scht das angegebene Lichtmodul
 function delete_lightmodul()
    {
     // �berpr�ft, ob die angegebene Lichtmodul-ID eine Zahl ist
     if (ctype_digit($_GET[id]) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und w�hlt die richtige Datenbank aus
	 $conresult = db_connect("lights");
	 
	 // �berpr�ft, ob beim Verbinden ein Fehler aufgetreten ist
	 if ($conresult == false)
	    {
	     // Zeigt eine Fehlermeldung an, dass ein Fehler beim Verbinden zur Datenbank aufgetreten ist
	     echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten!","error");
	     
	     // Gibt 'false' zur�ck
	     return false;
	     
	     // Beendet die Ausf�hrung der Funktion
	     exit();
	    }
	 else
	    {
	     // Sendet eine DELETE-Anweisung an die Datenbank
	     $sqlresult = mysql_query("DELETE FROM lightmoduls WHERE lightmodul_id='$_GET[id]' LIMIT 1;");
	     
	     // �berpr�ft, ob es einen Fehler beim L�schen des Lichtmoduls gab
	     if ($sqlresult == false)
	        {
		 // Zeigt eine Fehlermeldung an, dass das angegebene Lichtmodul nicht gel�scht worden konnte
		 echo show_systemmessage("Beim L�schen des Lichtmoduls ist leider ein Fehler aufgetreten","error");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zur�ck
		 return false; 
	    	}
	     else
	        {
		 // Zeigt eine Erfolgsmeldung an, dass das angegebene Lichtmodul erfolgreich gel�scht worden ist
		 echo show_systemmessage("Das Lichtmodul wurde erfolgreich gel�scht","success");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'true' zur�ck
		 return true;
		}
	    }
	}
     else
        {
	 // Gibt eine Fehlermeldung an, dass ein interner Verarbeitungsfehler aufgetreten
	 echo show_sysetmmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten","error");
	  
	 // Gibt 'false' zur�ck
	 return false;
	  
	 // Beendet die Ausf�hrung der Funktion
	 exit();
	}
    }    
 
 
 // Funktion zeigt den aktuellen Status des Lichtmoduls an
 function show_lightmodulstatus()
    {
     // Stellt eine Verbindung zum Datenbankserver her und w�hlt die richtige Datenbank aus
     $conresult = db_connect("lights");
      
      // �berpr�ft, ob beim Verbinden ein Fehler aufgetreten ist
      if ($conresult == false)
	 {
	  // Zeigt eine Fehlermeldung an, dass ein Fehler beim Verbinden zur Datenbank aufgetreten ist
	  echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten!","error");
	     
	  // Gibt 'false' zur�ck
	  return false;
	     
	  // Beendet die Ausf�hrung der Funktion
	  exit();
	 }
     else
	 {
	  // Sendet eine SELECT-Anweisung an die Datenbank
	  $sqlresult = mysql_query("SELECT lightmodul_id, lightmodul_name, lightmodul_status FROM lightmoduls ORDER BY lightmodul_id ASC;");
	  
	  // �berpr�ft, ob es einen Fehler beim Aktualisieren des Lichtmoduls gab
	  if ($sqlresult == false)
	     {
	      // Zeigt eine Fehlermeldung an, dass das angegebene Lichtmodul nicht aktualisiert worden konnte
	      echo show_systemmessage("Beim Auslesen der Lichtmodule und deren Status ist leider ein Fehler aufgetreten!","error");
	      
	      // Beendet die Verbindung zum Datenbankserver
	      mysql_close($conresult);
	       
	      // Gibt 'false' zur�ck
	      return false;
	      
	      // Beendet die Ausf�hrung der Funktion
	      exit();
	     }
	  else
	     {
	      // �berpr�ft, ob mindestens ein Lichtmodul vorhanden ist
	      if (mysql_num_rows($sqlresult) > 0)
	         {
		  echo "<table  style=\"width:800px;\">\n";
		  echo " <tr>";
		  
		  // Setzt die Startwert der Z�hlervariable
		  $count = 1;
		  
		  while ($row = mysql_fetch_array($sqlresult))
		     {
		      echo "<td class=\"standard\" style=\"text-align:center;width:200px;\">";
		      
		      echo $row[lightmodul_name]."<br>";
		      
		      if ($row[lightmodul_status] == "on")
		         {
			  echo "<img src=\"../system/lighton.png\"><br><br>";
			  echo "<a href=\"$_SERVER[PHP_SELF]?id=$row[lightmodul_id]\"><img class=\"button\" src=\"../system/switchoff.png\"></a>";
			 }
		      else
		         {
			  echo "<img src=\"../system/lightoff.png\"><br><br>";
			  echo "<a href=\"$_SERVER[PHP_SELF]?id=$row[lightmodul_id]\"><img class=\"button\" src=\"../system/switchon.png\"></a>";
			 }

		      echo "</td>\n";
		      
		      if (($count % 3) == 0)
		         {
			  echo "</tr>\n";
			  
			  echo "<tr>\n";
			  echo " <td>&nbsp;</td>\n";
			  echo "</tr>\n";
			  
			  echo "<tr>\n";
			 }
		 
		 // Erh�ht den Wert der Z�hlervariable um 1
		 $count++;
		     }
		     
		  echo " </tr>\n";
		  echo "</table>\n";
		 }
	      else
	         {
		  // Gibt eine Hinweismeldung zur�ck, dass keine Lichtmodule in der Datenbank vorhanden ist
		  echo show_systemmessage("Es liegen keine Lichtmodule vor","info");
		  
		  // Gibt 'true' zur�ck
		  return true;
		 }
	     }
	 }
    }
 
 
 // Funktion �ndert den Status des angegebenen Lichtmoduls
 function change_lightmodulstatus()
    {
     // �berpr�ft, ob die angegebene Lichtmodul-ID eine Zahl ist
     if (ctype_digit($_GET[id]) == true && $_GET[id] != "" && isset($_GET[id]) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und w�hlt die richtige Datenbank aus
	 $conresult = db_connect("lights");
	 
	 // �berpr�ft, ob beim Verbinden ein Fehler aufgetreten ist
	 if ($conresult == false)
	    {
	     // Zeigt eine Fehlermeldung an, dass ein Fehler beim Verbinden zur Datenbank aufgetreten ist
	     echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten!","error");
	     
	     // Gibt 'false' zur�ck
	     return false;
	     
	     // Beendet die Ausf�hrung der Funktion
	     exit();
	    }
	 else
	    {
	     // Sendet eine UPDATE-Anweisung an die Datenbank um den Status des Lichtmoduls zu �ndern
	     $sqlresult = mysql_query("UPDATE lightmoduls SET lightmodul_status = IF(lightmodul_status = 'on','off','on') WHERE lightmodul_id='$_GET[id]';");
	     
	     // �berpr�ft, ob es einen Fehler beim �ndern des Status des Lichtmoduls gab
	     if ($sqlresult == false)
	        {
		 // Zeigt eine Fehlermeldung an, dass der Status des angegebenen Lichtmoduls nicht ge�ndert werden konnte
		 echo show_systemmessage("Beim �ndern des Status des Lichtmoduls ist leider ein Fehler aufgetreten!","error");
	 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zur�ck
		 return false;
		 
		 // Beendet die Ausf�hrung der Funktion
		 exit();
		}
	    }
	}
    }
 
    
 // Funktion aktualisiert das angegebene Lichtmodul
 function update_lightmodul()
    {
     // �berpr�ft, ob die angegebene Lichtmodul-ID eine Zahl ist
     if (ctype_digit($_GET[id]) == true)
        {
	 // Stellt eine Verbindung zum Datenbankserver her und w�hlt die richtige Datenbank aus
	 $conresult = db_connect("lights");
	 
	 // �berpr�ft, ob beim Verbinden ein Fehler aufgetreten ist
	 if ($conresult == false)
	    {
	     // Zeigt eine Fehlermeldung an, dass ein Fehler beim Verbinden zur Datenbank aufgetreten ist
	     echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten!","error");
	     
	     // Gibt 'false' zur�ck
	     return false;
	     
	     // Beendet die Ausf�hrung der Funktion
	     exit();
	    }
	 else
	    {
	     // Sendet eine UPDATE-Anweisung an die Datenbank
	     $sqlresult = mysql_query("UPDATE lightmoduls SET lightmodul_id = TRIM('$_POST[id]'), lightmodul_name = TRIM('$_POST[name]'), lightmodul_description = TRIM('$_POST[description]') WHERE lightmodul_id = '$_GET[id]' LIMIT 1;");
	     
	     // �berpr�ft, ob es einen Fehler beim Aktualisieren des Lichtmoduls gab
	     if ($sqlresult == false)
	        {
		 // Zeigt eine Fehlermeldung an, dass das angegebene Lichtmodul nicht aktualisiert worden konnte
		 echo show_systemmessage("Beim Aktualisieren des Lichtmoduls ist leider ein Fehler aufgetreten!","error");
	 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'false' zur�ck
		 return false;
		 
		 // Beendet die Ausf�hrung der Funktion
		 exit();
		}
	     else
	        {
		 // Zeigt eine Erfolgsmeldung an, dass das angegebene Lichtmodul erfolgreich aktualisiert worden ist
		 echo show_systemmessage("Das Lichtmodul wurde erfolgreich aktualisiert!","success");
		 
		 // Beendet die Verbindung zum Datenbankserver
		 mysql_close($conresult);
		 
		 // Gibt 'true' zur�ck
		 return true;
		}
	     }
	 }
      else
         {
	  // Gibt eine Fehlermeldung an, dass ein interner Verarbeitungsfehler aufgetreten
	  echo show_sysetmmessage("Es ist leider ein interner Verarbeitungsfehler aufgetreten","error");
	  
	  // Gibt 'false' zur�ck
	  return false;
	  
	  // Beendet die Ausf�hrung der Funktion
	  exit();
	 }
     }
?> 