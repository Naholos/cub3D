# aoteo-be@student.42madrid.com

# Para ejecutar las pruebas sobre los bonus agregar la opción "bonus" al ejecutar
# El script.

# Como paso previo se genera un fichero sin permisos de lectura en el momento.
# Esto se hace por comodidad, ya que sino al copiar la carpeta se pide una
# clave de administrador.

cp ./maps/Player_NO.cub ./maps/No_readable.cub
chmod -r ./maps/No_readable.cub  

clear

if [ "$1" == "bonus" ]; then
	echo "*********************************************************************"
	echo "*                 Tests bonus proyecto cub3D.                       *"
	echo "*********************************************************************"

	echo "$(tput setaf 3)*****************************************************"
	echo "*    Ejecución de makefile con la :opción bonus.     *"
	echo "*****************************************************"
	
	echo "$(tput setaf 10)1) Se ejecuta make"
	echo "$(tput setaf 9)\c"
	make bonus
	read foo

	echo "$(tput setaf 10)2) Se ejecuta make de nuevo"
 	echo "$(tput setaf 9)\c"
 	make bonus
 	read foo
 
 	echo "$(tput setaf 10)3) Se ejecuta make re"
 	echo "$(tput setaf 9)\c"
 	make re
 	read foo
 
 	echo "$(tput setaf 10)3) Se ejecuta make clean"
 	echo "$(tput setaf 9)\c"
 	make clean
 	read foo
 
 	echo "$(tput setaf 10)4) Se ejecuta make fclean"
	echo "$(tput setaf 9)\c"
	make fclean
	read foo

	echo "$(tput setaf 10)5) Se ejecuta make una vez más para comenzar las pruebas"
	echo "$(tput setaf 9)\c"
 	make bonus

else
	echo "*********************************************************************"
	echo "*                 Tests proyecto cub3D.                             *"
	echo "*********************************************************************"

	echo "$(tput setaf 3)*****************************************************"
	echo "*             Pruebas de Makefie                    *"
	echo "*****************************************************"

	echo "$(tput setaf 10)1) Se ejecuta make"
	echo "$(tput setaf 9)\c"
	make
	read foo

	echo "$(tput setaf 10)2) Se ejecuta make de nuevo"
	echo "$(tput setaf 9)\c"
	make
	read foo

	echo "$(tput setaf 10)3) Se ejecuta make re"
	echo "$(tput setaf 9)\c"
	make re
	read foo

	echo "$(tput setaf 10)4) Se ejecuta make clean"
	echo "$(tput setaf 9)\c"
	make clean
	read foo

	echo "$(tput setaf 10)5) Se ejecuta make fclean"
	echo "$(tput setaf 9)\c"
	make fclean
	read foo

	echo "$(tput setaf 10)6) Se ejecuta make una vez más para comenzar las pruebas"
	echo "$(tput setaf 9)\c"
	make
	read foo
fi		

echo "$(tput setaf 3)*****************************************************"
echo "*             Pruebas de la norma                   *"
echo "*****************************************************"

echo "$(tput setaf 10)1) Sobre ficheros fuente"
echo "$(tput setaf 9)\c"
norminette *.c
read foo

echo "$(tput setaf 10)2) Sobre ficheros cabecera"
echo "$(tput setaf 9)\c"
norminette ./includes/*.h
read foo

echo "$(tput setaf 3)*****************************************************"
echo "*            Errores en uso del programa.           *"
echo "*****************************************************"

echo "$(tput setaf 10)\n1) Prueba sin parámetro de entrada: ./cub3D"
echo "$(tput setaf 9)\c"
./cub3D
read foo

echo "$(tput setaf 10)\n2) Prueba con número de parámetros de entrada erróneo: ./cub3D ./maps/subject.cub ./maps/subject2.cub"
echo "$(tput setaf 9)\c"
./cub3D ./maps/NO_player.cub ./maps/XX_player.cub
read foo

echo "$(tput setaf 3)*****************************************************"
echo "*            Errores de fichero en general.         *"
echo "*****************************************************"

echo "$(tput setaf 10)\n1) Prueba con fichero de entrada inexistente: ./cub3D ./maps/inexistent_map.cub"
echo "$(tput setaf 9)\c"
./cub3D ./maps/Inexistent_map.cub
read foo

echo "$(tput setaf 10)\n2) Prueba con ruta errónea (1): ./objs/NO_player.cub"
echo "$(tput setaf 9)\c"
./cub3D ./objs/NO_player.cub
read foo

echo "$(tput setaf 10)\n3) Prueba con ruta errónea (2): ./cub3D/NO_player.cub"
echo "$(tput setaf 9)\c"
./cub3D ./cub3D/NO_player.cub
read foo

echo "$(tput setaf 10)\n4) Prueba sin permiso de lectura: ./cub3D ./maps/No_readablemap.cub"
echo "$(tput setaf 9)\c"
./cub3D ./maps/No_readablemap.cub
read foo

echo "$(tput setaf 3)*****************************************************"
echo "*           Errores de fichero de mapa              *"
echo "*****************************************************"

echo "$(tput setaf 10)\n1) Prueba con fichero de entrada sin extensión: ./cub3D ./maps/NO_player"
echo "$(tput setaf 9)\c"
./cub3D ./maps/NO_player
read foo

echo "$(tput setaf 10)\n2) Prueba con fichero de entrada con extensión errónea: ./cub3D ./maps/NO_player.txt"
echo "$(tput setaf 9)\c"
./cub3D ./maps/NO_player.txt
read foo

echo "$(tput setaf 10)\n3) Prueba con fichero de entrada vacío: ./cub3D ./maps/Empty.cub"
echo "$(tput setaf 9)\c"
./cub3D ./maps/Empty.cub
read foo

echo "$(tput setaf 10)\n4) Prueba con fichero sin NO: ./cub3D ./maps/NO_missing.cub"
echo "$(tput setaf 7)\c"
cat ./maps/NO_missing.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/NO_missing.cub
read foo

echo "$(tput setaf 10)\n5) Prueba con fichero sin SO: ./cub3D ./maps/SO_missing.cub"
echo "$(tput setaf 7)\c"
cat ./maps/SO_missing.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/SO_missing.cub
read foo

echo "$(tput setaf 10)\n6) Prueba con fichero sin WE: ./cub3D ./maps/WE_missing.cub"
echo "$(tput setaf 7)\c"
cat ./maps/WE_missing.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/WE_missing.cub
read foo

echo "$(tput setaf 10)\n7) Prueba con fichero sin EA: ./cub3D ./maps/EA_missing.cub"
echo "$(tput setaf 7)\c"
cat ./maps/EA_missing.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/EA_missing.cub
read foo

echo "$(tput setaf 10)\n8) Prueba con fichero sin F: ./cub3D ./maps/F_missing.cub"
echo "$(tput setaf 7)\c"
cat ./maps/F_missing.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/F_missing.cub
read foo

echo "$(tput setaf 10)\n9) Prueba con fichero sin C: ./cub3D ./maps/C_missing.cub"
echo "$(tput setaf 7)\c"
cat ./maps/C_missing.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/C_missing.cub
read foo

echo "$(tput setaf 10)\n10) Prueba con fichero con NO duplicado: ./cub3D ./maps/NO_duplicated.cub"
echo "$(tput setaf 7)\c"
cat ./maps/NO_duplicated.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/NO_duplicated.cub
read fo

echo "$(tput setaf 10)\n11) Prueba con fichero con SO duplicado: ./cub3D ./maps/SO_duplicated.cub"
echo "$(tput setaf 7)\c"
cat ./maps/SO_duplicated.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/SO_duplicated.cub
read foo

echo "$(tput setaf 10)\n12) Prueba con fichero con WE duplicado: ./cub3D ./maps/WE_duplicated.cub"
echo "$(tput setaf 7)\c"
cat ./maps/WE_duplicated.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/WE_duplicated.cub
read foo

echo "$(tput setaf 10)\n13) Prueba con fichero con EA duplicado: ./cub3D ./maps/EA_duplicated.cub"
echo "$(tput setaf 7)\c"
cat ./maps/EA_duplicated.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/EA_duplicated.cub
read foo

echo "$(tput setaf 10)\n14) Prueba con fichero con F duplicado: ./cub3D ./maps/F_duplicated.cub"
echo "$(tput setaf 7)\c"
cat ./maps/F_duplicated.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/F_duplicated.cub
read foo

echo "$(tput setaf 10)\n15) Prueba con fichero con C duplicado: ./cub3D ./maps/C_duplicated.cub"
echo "$(tput setaf 7)\c"
cat ./maps/C_duplicated.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/C_duplicated.cub
read foo

echo "$(tput setaf 10)\n16) Prueba con fichero con parámetro desconocido: ./cub3D ./maps/Unknown_symbol.cub"
echo "$(tput setaf 7)\c"
cat ./maps/unknown_symbol.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/unknown_symbol.cub
read foo

echo "$(tput setaf 10)\n17) Prueba de mapa sin posición inicial del jugador: .cub3D ./maps/No_player.cub"
echo "$(tput setaf 7)\c"
cat ./maps/No_player.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/No_player.cub
read foo

echo "$(tput setaf 10)\n18) Prueba de mapa con símbolo del jugador desconocido: .cub3D ./maps/unknown_player.cub"
echo "$(tput setaf 7)\c"
cat ./maps/unknown_player.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/Unknown_player.cub
read foo

echo "$(tput setaf 10)\n19) Prueba de mapa con más de un jugador: .cub3D ./maps/Two_players.cub"
echo "$(tput setaf 7)\c"
cat ./maps/Two_players.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/Two_players.cub
read foo

echo "$(tput setaf 10)\n20) Prueba con perímetro sin cerrar (1): .cub3D ./maps/Open_walls1.cub"
echo "$(tput setaf 7)\c"
cat ./maps/Open_walls1.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/Open_walls1.cub
read foo

echo "$(tput setaf 10)\n21) Prueba con perímetro sin cerrar (2): .cub3D ./maps/Open_walls2.cub"
echo "$(tput setaf 7)\c"
cat ./maps/Open_walls2.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/Open_walls2.cub
read foo

echo "$(tput setaf 10)\n22) Prueba con perímetro sin cerrar (3): .cub3D ./maps/Open_walls3.cub"
echo "$(tput setaf 7)\c"
cat ./maps/Open_walls3.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/Open_walls3.cub
read foo

echo "$(tput setaf 10)\n23) Prueba con perímetro sin cerrar (4): .cub3D ./maps/Open_walls4.cub"
echo "$(tput setaf 7)\c"
echo "\n"
cat ./maps/Open_walls4.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/Open_walls4.cub
read foo

echo "$(tput setaf 10)\n24) Prueba de mapa con fila intermedia vacía: .cub3D ./maps/Empty_line.cub"
echo "$(tput setaf 7)\c"
cat ./maps/Empty_line.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/Empty_line.cub
read foo

echo "$(tput setaf 3)*****************************************************"
echo "*  Comprobación de no utilización de mlx_put_pixel *"
echo "*****************************************************"

echo "$(tput setaf 10)\n1) Búsqueda de mlx_pixel_put con 'grep mlx_put_pixel *.c'"
echo "$(tput setaf 9)\c"
grep "mlx_pixel_put" *.c
echo "\n"
read foo

echo "$(tput setaf 3)*****************************************************"
echo "*           Pruebas sobre mapas correctos            *"
echo "*****************************************************"

echo "$(tput setaf 10)\n1) Prueba de mapa correcto con usuario mirando al norte: .cub3D ./maps/NO_player.cub"
echo "$(tput setaf 7)\c"
cat ./maps/Player_NO.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/Player_NO.cub
read foo

echo "$(tput setaf 10)\n2) Prueba de mapa correcto con usuario mirando al sur: .cub3D ./maps/Player_SO.cub"
echo "$(tput setaf 7)\c"
cat ./maps/Player_SO.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/Player_SO.cub
read foo

echo "$(tput setaf 10)\n3) Prueba de mapa correcto con usuario mirando al oeste: .cub3D ./maps/Player_WE.cub"
echo "$(tput setaf 7)\c"
cat ./maps/Player_WE.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/Player_WE.cub
read foo

echo "$(tput setaf 10)\n4) Prueba de mapa correcto con usuario mirando al este: .cub3D ./maps/Player_EA.cub"
echo "$(tput setaf 7)\c"
cat ./maps/Player_EA.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/Player_EA.cub
read foo

echo "$(tput setaf 10)\n5) Prueba de mapa correcto con líneas entre los parámetros iniciales: .cub3D ./maps/Empty_lines_on_header.cub"
echo "$(tput setaf 7)\c"
cat ./maps/Empty_lines_on_header.cub
echo "\n$(tput setaf 9)\c"
./cub3D ./maps/Empty_lines_on_header.cub
read foo

# Como paso final se genera borra el fichero sin permisos de lectura en el momento, para evitar el problema
# mencionado al principio.

rm  ./maps/No_readable.cub
