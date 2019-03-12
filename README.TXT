Servidor de fichaje para una empresa.
Se compone de un servidor, un cliente que se instala en los puntos de fichaje y un cliente administrador con el que se pueden ver los estados de los fichajes y editarlos.

La base de datos esta en postgres
Los programas estan en c++ con QT
La comunicacion se hace a traves de websocket y json

El administrador actualmente no esta terminado y solo permite crear usuarios.


Antes de empezar:

Si vas a compliar release:
Exporta solo la extructura de la base de datos
Elimina comentarios de debug en mainWindow de cliente y administrador.
Asegurate de que la ruta  es correcta para los archivos de configuracion en mainwindow de cliente y administrador.
Verifica los datos del archivo de configuracion y coloca el host y puertos correctos.

Si vas a debugear o probar algo.
Exporta la base de datos completa.
Pon los config dentro de la build de cada programa.
