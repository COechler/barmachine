<?php
 // Autor: Christian Oechler
 // Erstellungsdatum: 01.04.2005
 // �nderungsdatum: 01.04.2005
 // Version 0.0.1
 // Copyright: 2005 Christian Oechler
 // Lizenz: GPL Version 2
 
 // F�gt die Funktionsbibliotheken ein
 include("../system/functions.inc");
 include("functions.inc");
 
 // Erzeugt den HTML-Kopf
 echo create_htmlheader("Lichtsteuerung");
 
 // �ndert den Status des angegebenen Lichtmoduls
 change_lightmodulstatus();
 
 // Zeigt den aktuellen Status des Lichtmoduls an
 show_lightmodulstatus();
 
 // Erzeugt den HTML-Fu�   
 echo create_htmlfoot();
?> 
