#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

int main( )
{
	//Variáveis
	int i, j, k;						// Iteradores
	int num;							// Variável que recebe o número aleatório
	int cartelas[ 10 * 24 ];			// Variavel que montam as cartelas
	bool repetido = false;				// Variavel que controla se encontramos um valor repetido
	bool swapped = false;				// Variavel para otimização da ordenação
	int resultado[ 99 ];				// Array dos números do sorteio
	int verificacao[ 10 ] = { 0 };		// Array de verificação das tabelas
	int num_ganhadores = 0;				// Controla se alguém já ganhou
	int index1, index2;					// Valores para embaralhar os números do sorteio
	int temp;							// Variável temporária
	int input;							// Variável para pegar input do usuário
	
	// Inicializa a seed do rand( )
	srand( time( NULL ) );

	// Itera as cartelas e gera os números
	for ( i = 0; i < 10; i++ )
	{
		// Sub loop que itera os números de cada cartela
		for ( j = 0; j < 24; j++ )
		{
			// Loop infinito para gerar os números sem repetição
			while ( true )
			{
				// Resetar a flag e pegar um número aleatório
				repetido = false;
				num = rand( ) % 99 + 1;

				// Checar se o número está repetido
				// O loop vai de 0, até o número atual - 1 (j - 1)
				for ( k = 0; k < j; k++ )
				{
					if ( cartelas[ i * 24 + k ] == num ) // Se estiver repetido, seta a flag e quebra o loop
					{
						repetido = true;
						break;
					}
				}

				// Se não encontramos um valor repetido, adicionamos na cartela atual
				if ( !repetido )
				{
					cartelas[ i * 24 + j ] = num;
					break;
				}
			}
		}


		// Ordena a tabela ( bubble sort )
		for ( j = 0; j < 24; j++ )
		{
			// Reseta a flag
			swapped = false;
			
			for ( k = 0; k < 24 - j - 1; k++ )
			{
				if ( cartelas[ i * 24 + k ] > cartelas[ i * 24 + k + 1 ] )
				{
					temp = cartelas[ i * 24 + k ];
					cartelas[ i * 24 + k ] = cartelas[ i * 24 + k + 1 ];
					cartelas[ i * 24 + k + 1 ] = temp;

					swapped = true;
				}
			}

			// Se não houver uma troca, a array já está otimizada
			if ( !swapped )
				break;
		}

		// Verifica se alguma tabela é igual a atual
		for ( j = 0; j < i; j++ ) // Loop de cartelas anteriores
		{
			for ( k = 0; k < 24; k++ ) // Loop dos números das cartelas
			{
				if ( cartelas[ i * 24 + k ] != cartelas[ j * 24 + k ] ) // Se os números forem diferentes, sabemos que as cartelas são diferentes
				{
					break;
				}

				// Se chegou aqui, as cartelas são iguais
				// Nesse caso, decrementamos o i para gerar uma nova cartela
				i--;
			}
		}
	}
	
	
	// Mostra as cartelas na tela
	for ( i = 0; i < 10; i++ )
	{
		printf( "Cartela %d:", i + 1 );

		for ( j = 0; j < 24; j++ )
		{
			if ( j % 6 == 0 )
				printf( "\n" );

			if ( cartelas[ i * 24 + j ] < 10 )
				printf( "0" );

			printf( "%d ", cartelas[ i * 24 + j ] );
		}

		printf( "\n\n" );
	}

	// Inicializa a array do resultado
	for ( i = 0; i < 99; i++ )
		resultado[ i ] = i + 1;

	// Embaralhar a array
	// O limite é um número arbitrário de vezes
	// Quanto maior, mais aleatório
	for ( i = 0; i < 500; i++ )
	{
		index1 = rand( ) % 99;
		index2 = rand( ) % 99;

		temp = resultado[ index1 ];
		resultado[ index1 ] = resultado[ index2 ];
		resultado[ index2 ] = temp;
	}

	// Pegar a opção do usuário
	input = 0;
	printf( "Escolha uma opcao:\n" );
	printf( "[1] Sorteio completo\n" );
	printf( "[2] Sorteio numero a numero\n" );
	printf( "Opcao: " );
	scanf_s( "%d", &input );
	printf( "\n" );

	if ( input == 1 || input == 2 )
	{
		for ( i = 0; i < 99; i++ )										// Iterar a array dos resultados
		{
			if ( input == 2 )
			{
				for ( j = 0; j < 30; j++ )
				{
					printf( "=" );
				}
				
				//printf( "\n          Rodada %d:\n\n", i );
				printf( "\n%16s %d:\n\n", "Rodada", i );
					
				printf( "Numero sorteado: %d\n", resultado[ i ] );
			}

			for ( j = 0; j < 10; j++ )									// Itera as cartelas
			{
				for ( k = 0; k < 24; k++ )								// Itera os números das cartelas
				{
					if ( resultado[ i ] == cartelas[ j * 24 + k ] )		// Verifica se o resultado está presente na cartela
					{
						verificacao[ j ]++;								// Soma 1 na array de verificação

						if ( verificacao[ j ] == 24 )					// Se a cartela atual ganhar, adicionamos um ganhador
							num_ganhadores++;
					}
				}

				if ( input == 2 )
					printf( "A cartela %d marcou %d numero%s\n", j + 1, verificacao[ j ], verificacao[ j ] == 1 ? "" : "s" );
			}
			
			if ( input == 2 )
			{
				system( "pause" );
				printf( "\n" );
			}

			// Se há um ganhador
			if ( num_ganhadores )
			{
				printf( "Numeros sorteados: " );

				for ( j = 0; j <= i; j++ )
				{
					printf( "%d ", resultado[ j ] );
				}

				printf( "\n\nNumero de ganhadores: %d\n\n", num_ganhadores );

				printf( "Cartelas vencedoras:\n\n" );

				for ( j = 0; j < 10; j++ )
				{
					if ( verificacao[ j ] == 24 )
					{
						printf( "Cartela %d:", j + 1 );

						for ( k = 0; k < 24; k++ )
						{
							if ( k % 6 == 0 )
								printf( "\n" );

							if ( cartelas[ j * 24 + k ] < 10 )
								printf( "0" );

							printf( "%d ", cartelas[ j * 24 + k ] );
						}

						printf( "\n\n" );
					}
				}

				break;
			}
		}
	}

	system( "pause>nul" );
	return 0;
}
