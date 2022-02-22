<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 01.01.2005
 // Änderungsdatum: 08.04.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 
 // Fügt die Funktionsbibliotheken ein
 include("../system/functions.inc");
 include("functions.inc");
 
 // Erzeugt den HTML-Kopf
 echo create_htmlheader("Tankübersicht");
 
 // Aktualisiert die Inhalte der Tanks
 if (isset($_POST[liquidname1]) == true && isset($_POST[tankamount1]) == true) {echo update_tank(1,$_POST[liquidname1],$_POST[tankamount1]);}
 if (isset($_POST[liquidname2]) == true && isset($_POST[tankamount2]) == true) {echo update_tank(2,$_POST[liquidname2],$_POST[tankamount2]);}
 if (isset($_POST[liquidname3]) == true && isset($_POST[tankamount3]) == true) {echo update_tank(3,$_POST[liquidname3],$_POST[tankamount3]);}
 if (isset($_POST[liquidname4]) == true && isset($_POST[tankamount4]) == true) {echo update_tank(4,$_POST[liquidname4],$_POST[tankamount4]);}
 if (isset($_POST[liquidname5]) == true && isset($_POST[tankamount5]) == true) {echo update_tank(5,$_POST[liquidname5],$_POST[tankamount5]);}
 if (isset($_POST[liquidname6]) == true && isset($_POST[tankamount6]) == true) {echo update_tank(6,$_POST[liquidname6],$_POST[tankamount6]);}
 
 // Stellt eine Verbindung zum Datenbankserver her und wählt die richtige Datenbank aus
 $conresult = db_connect("mixer");
	 
 // Überprüft, ob beim Verbinden ein Fehler aufgetreten ist
 if ($conresult == false)
    {
     // Gibt eine Fehlermeldung zurück
     echo show_systemmessage("Es ist ein Fehler bei der Verbindung zur Datenbank aufgetreten","error");
	     
     // Beendet die Ausführung der Funktion
     exit();
    }
 else
    {
     // Sendet eine SELECT-Anweisung an die Datenbank
     $sqlresult = mysql_query("SELECT tank_id, liquid_id, tank_volume FROM tanks");
     
     // Überprüft, ob die SELECT-Anweisung erfolgreich ausgeführt worden ist
     if ($sqlresult == false)
	{
	 // Gibt eine Fehlermeldung zurück
	 echo show_systemmessage("Es ist ein Fehler bei der Abfrage der Tanks aufgetreten","error");
	     
	 // Beendet die geöffnete Verbindung zum Datenbankserver
	 mysql_close();
	     
	 // Beendet die Ausführung der Funktion
	 exit();
	}
     else
	{
	 // Ermittel die Anzahl der vorhandenen Tanks
	 $tankcount = mysql_result(mysql_query("SELECT COUNT(tank_id) FROM tanks LIMIT 1"),0);
	 
	 // Überprüft, ob mindestens ein Tank vorliegt
	 if (mysql_num_rows($sqlresult) > 0)
	    {
	     echo "<table  style=\"width:800px;\">\n";
	     echo " <tr>";
	     
	     // Setzt die Startwert der Zählervariable
	     $count = 1;
	     
	     while ($row = mysql_fetch_array($sqlresult))
	        {
		 echo "<td class=\"standard\" style=\"text-align:center;width:200px;\">";
		 echo "Tank ".$row[tank_id]."<br>";
		 echo "<img src=\"tank.php?id=$row[tank_id]\">";
		 echo "<form action=\"$_SERVER[PHP_SELF]\" method=\"post\">\n";
		 echo create_liquidselection1($row[tank_id],$row[liquid_id])."<br><input  class=\"standard\" style=\"width:40px;\" type=\"text\" name=\"tankamount$row[tank_id]\" value=\"$row[tank_volume]\" maxlength=\"4\">&nbsp;ml<br><br><input type=\"image\" src=\"../system/update.png\">";
		 echo "  </form>\n";
		 echo "</td>";
		 
		 if (($count % 3) == 0)
		    {
		     echo "</tr>\n";
		     
		     echo "<tr>\n";
		     echo " <td>&nbsp;</td>\n";
		     echo "</tr>\n";
		     
		     echo "<tr>\n";
		    }
		 
		 // Erhöht den Wert der Zählervariable um 1
		 $count++;
		}

             echo " </tr>\n";
	     echo "</table>\n";
	    }
	 else
	    {
	     // Gibt eine Hinweismeldung zurück
	     echo show_systemmessage("Die Barmaschine hat zur Zeit keine Tanks","info");
	    }
	}
    }
 
 // Erzeugt den HTML-Fuß   
 echo create_htmlfoot();
?>  
 
