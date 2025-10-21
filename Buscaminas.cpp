// Buscaminas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define ARRAY_MAX_X 11
#define ARRAY_MAX_Y 11

int main()
{
    int height = 1;
    int width = 1;
    int minas = 0;
    int board[ARRAY_MAX_X][ARRAY_MAX_Y]{};
    int boardHide[ARRAY_MAX_X][ARRAY_MAX_Y]{};
    int boardMinas[ARRAY_MAX_X][ARRAY_MAX_Y]{};
	char charA = 'a';
    int slotX = 0;
    int slotY = 0;
    char slotYcharA = 'a';
	int minasClose = 0;
	bool win = true;

    //generador de seeds
    srand(time(NULL));

    //inicio del juego
    do
    {
        if ((width > 10) || (width <= 0) || (height > 10) || (height <= 0))
        {
            std::cout << "--Tu tablero es demasiado grande!--\n\n";
        }
        else if (minas >= width * height)
        {
            std::cout << "--Demasiadas minas para el tamaño de tu tablero!--\n\n";
        }
        else
        {
            std::cout << "--Bienvenido a Buscaminas!--\n\n";
        }
        std::cout << "Introduce la longitud de la tabla: (max 10, min 1)\n";
        std::cin >> width;
        std::cout << "Introduce la altura de la tabla: (max 10, min 1)\n";
        std::cin >> height;
        std::cout << "Introduce la dificultad de las minas: \n";
        std::cin >> minas;

        system("cls");
    } while ((width > 10) || (width <= 0) || (height > 10) || (height <= 0) || (minas >= width * height));
    
    //configurar tablero
    for (size_t y = 0; y < (height + 1); y++)
    {
        for (size_t x = 0; x < (width + 1); x++)
        {
            if ((x || y) != 0)
            {
                board[x][y] = 0;
                boardHide[x][y] = 1;
            }
            else
            {
                board[x][y] = 3;
                boardHide[x][y] = 0;
            }
        }
    }

    //repartir minas
    for (int i = 0; i < minas; i++)
    {
        //usa temporalmente slot X e Y para elegir la casilla de la mina, si no esta vacio vuelve a intentar
        slotX = 1 + rand() % width;
        slotY = 1 + rand() % height;
        if (board[slotX][slotY] == 0)
        {
            board[slotX][slotY] = 1;
        }
        else
        {
            i--;
        }
    }

	//añadir los numeros de proximidad
    for (size_t y = 0; y < (height + 1); y++)
    {
        for (size_t x = 0; x < (width + 1); x++)
        {
			minasClose = 0;
            //mirar casillas cercanas
            for (int SUBy = y - 1; SUBy <= y + 1; SUBy++)
            {
                for (int SUBx = x - 1; SUBx <= x + 1; SUBx++)
                {
                    if (SUBy >= 1 && SUBy <= height && SUBx >= 1 && SUBx <= width)
                    {
                        if (board[SUBx][SUBy] == 1)
                        {
                            minasClose++;
                        }
                    }
                }
            }

			boardMinas[x][y] = minasClose;
            if (board[x][y] == 1)
            {
                continue;
            }
            else if (minasClose >= 1)
            {
                board[x][y] = 2;
            }
        }
    }

    //creacion del tablero
    do
    {
        do
        {
            //dibujar tablero
            std::cout << " __--BUSCAMINAS--__   | Minas: " << minas << " | Longitud: " << width << " | Altura: " << height << " |\n";
            for (size_t y = 0; y < (height + 1); y++)
            {
                std::cout << "\n";
                for (size_t x = 0; x < (width + 1); x++)
                {

                    if (y == 0)
                    {
                        if (x == 0)
                        {
                            std::cout << "  ";
                        }
                        else
                        {
                            std::cout << x - 1 << " ";
                        }
                    }
                    else if (x == 0)
                    {
                        //std::cout << y << " ";
                        std::cout << static_cast<char>(charA + y - 1) << " ";
                    }

                    //relleno del tablero
                    else if (boardHide[x][y] == 1)
                    {
                        std::cout << "# ";
                    }
                    else if (boardHide[x][y] == 0)
                    {
                        if (board[x][y] == 0)
                        {
                            std::cout << ". ";
                        }
                        else if (board[x][y] == 1)
                        {
                            std::cout << "* ";
                        }
                        else if (board[x][y] == 2)
                        {
                            std::cout << boardMinas[x][y] << " ";
                        }
                    }
                }
            }


            //esto es para reactivar lo de ganar
            win = true;

            std::cout << "\n\n";
            std::cout << "-- Ingresa un valor por Columna y fila! --\n";
            std::cout << "En que COLUMNA quieres cavar? (Numero):\n";
            std::cin >> slotX;
            std::cout << "En que FILA quieres cavar? (Letra):\n";
            std::cin >> slotYcharA;

            slotY = slotYcharA - 'a' + 1;
            //especificar INT para evitar bugs
            slotX = (int)slotX - slotX + 1;

            system("cls");
        } while ((slotX > width) || (slotY > height) || (slotX < 0) || (slotY < 0));
        


		//accion del usuario
        switch (board[slotX][slotY])
        {
        case 0:
            //exponer las casillas cercanas
            if (boardHide[slotX][slotY] == 1)
            {
                for (int y = slotY - 1; y <= slotY + 1; y++)
                {
                    for (int x = slotX - 1; x <= slotX + 1; x++)
                    {
                        if (board[slotX][slotY] == 0)
                        {
                            boardHide[x][y] = 0;
                        }
                        else if (board[slotX][slotY] == 1)
                        {
                            boardHide[x][y] = 1;
                        }
                    }
                }
            }
            break;
        case 1:
            //PISAR EN MINA
            boardHide[slotX][slotY] = 0;
            win = false;
            break;
        case 2:
            //cavar una casilla de numero
            boardHide[slotX][slotY] = 0;
            break;
        default:
            break;
        }

		//ganar si se han cavado todas las casillas
        for (int y = 1; y < (height + 1); y++)
        {
            for (int x = 1; x < (width + 1); x++)
            {

                ////CAZA DE BUGS
                //std::cout << "\nx = " << x;
                //std::cout << "\ny = " << y;
                //std::cout << "\nboardHide = " << boardHide[x][y];
                //std::cout << "\nboard = " << board[x][y];
                //std::cout << "\nwin = " << win;
                //std::cout << "\n";
                ////tablero
                //for (size_t SUBy = 0; SUBy < (height + 1); SUBy++)
                //{
                //    std::cout << "\n";
                //    for (size_t SUBx = 0; SUBx < (width + 1); SUBx++)
                //    {

                //        if (SUBy == 0)
                //        {
                //            if (SUBx == 0)
                //            {
                //                std::cout << "  ";
                //            }
                //            else
                //            {
                //                std::cout << SUBx << " ";
                //            }
                //        }
                //        else if (SUBx == 0)
                //        {
                //            //std::cout << y << " ";
                //            std::cout << static_cast<char>(charA + SUBy - 1) << " ";
                //        }

                //        //relleno del tablero
                //        else if (SUBy != y || SUBx != x)
                //        {
                //            std::cout << "# ";
                //        }
                //        else if (SUBy == y && SUBx == x)
                //        {
                //            std::cout << "X ";
                //        }
                //    }
                //}


                if (win == true)
                {
                    if (board[x][y] == 0 || board[x][y] == 2)
                    {
                        if (boardHide[x][y] == 0)
                        {
                            win = true;
                        }
                        else
                        {
                            win = false;
                        }
                        
                    }
                }

            }
        }


        if (win == true)
        {
            board[slotX][slotY] = 1;
        }

        system("cls");
    } while (board[slotX][slotY] != 1);


	//FIN DE LA PARTIDA

    for (size_t y = 0; y < (height + 1); y++)
    {
        for (size_t x = 0; x < (width + 1); x++)
        {
			boardHide[x][y] = 0;
        }
    }


    std::cout << " __--BUSCAMINAS--__   | Minas: " << minas << " | Longitud: " << width << " | Altura: " << height << " |\n";
    for (size_t y = 0; y < (height + 1); y++)
    {
        std::cout << "\n";
        for (size_t x = 0; x < (width + 1); x++)
        {

            if (y == 0)
            {
                if (x == 0)
                {
                    std::cout << "  ";
                }
                else
                {
                    std::cout << x - 1 << " ";
                }
            }
            else if (x == 0)
            {
                //std::cout << y << " ";
                std::cout << static_cast<char>(charA + y - 1) << " ";
            }

            //relleno del tablero
            else if (boardHide[x][y] == 1)
            {
                std::cout << "# ";
            }
            else if (boardHide[x][y] == 0)
            {
                if (board[x][y] == 0)
                {
                    std::cout << ". ";
                }
                else if (board[x][y] == 1)
                {
                    if (x == slotX && y == slotY)
                    {
                        std::cout << ". ";
                    }
                    else
                    {
                        std::cout << "* ";
                    }
                    
                }
                else if (board[x][y] == 2)
                {
                    std::cout << boardMinas[x][y] << " ";
                }
            }
        }
    }

    std::cout << "\n\n";

    if (win == true)
    {
        std::cout << "-- Felicidades!!!! Has ganado!!!! --\n";
    }
    else if (win == false)
    {
        std::cout << "-- Vaya... Parece que has pardido! --\n";
    }
}