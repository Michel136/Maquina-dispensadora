#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#define NUM_DENOMINACIONES 5
#define MAX_MONEDAS 50

// Estructura para representar las denominaciones de las monedas
struct Moneda {
    int valor;
    int cantidad;
};

// Estructura para representar los productos
struct Producto {
    char id[4];
    int precio;
    int stock;
};

// Funci�n para devolver las monedas ingresadas
void devolverMonedas(int monedasIngresadas[], int totalInsertado) {
    printf("Devolviendo las monedas ingresadas:\n");
    for (int i = 0; i < totalInsertado; i++) {
        printf("Devolviendo 1 moneda de %d pesos\n", monedasIngresadas[i]);
    }
}

// Funci�n para devolver el cambio
int devolverCambio(int cambio, struct Moneda monedas[]) {
    printf("Intentando devolver cambio: %d pesos\n", cambio);
    for (int i = 0; i < NUM_DENOMINACIONES; i++) {
        while (cambio >= monedas[i].valor && monedas[i].cantidad > 0) {
            cambio -= monedas[i].valor;
            monedas[i].cantidad--;
            printf("Devolviendo 1 moneda de %d pesos\n", monedas[i].valor);
        }
    }

    if (cambio > 0) {
        printf("No se puede devolver el cambio total. Cambio restante: %d pesos\n", cambio);
        return 0;
    }
    return 1;
}

// Funci�n para calcular el total del fondo de cambio
int calcularTotalFondo(struct Moneda monedas[]) {
    int totalFondo = 0;
    for (int i = 0; i < NUM_DENOMINACIONES; i++) {
        totalFondo += monedas[i].valor * monedas[i].cantidad;
    }
    return totalFondo;
}

// Funci�n para mostrar y manejar el men� de reabastecimiento
void menuReabastecimiento(struct Producto productos[], int totalProductos, struct Moneda monedas[]) {
    int opcion, nuevoStock, nuevaCantidad, i;
    char productoID[4];

    while (1) {
        system("cls");
        printf("=== MENU DE REABASTECIMIENTO ===\n");
        printf("1. Rellenar stock de productos\n");
        printf("2. Agregar monedas al fondo de cambio\n");
        printf("3. Regresar al sistema\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingresa el ID del producto que deseas reabastecer: ");
                scanf("%s", productoID);
                for (i = 0; i < totalProductos; i++) {
                    if (strcmp(productos[i].id, productoID) == 0) {
                        printf("Producto %s encontrado. Stock actual: %d\n", productos[i].id, productos[i].stock);
                        printf("Ingresa el nuevo stock: ");
                        scanf("%d", &nuevoStock);
                        productos[i].stock = nuevoStock;
                        printf("Stock de %s actualizado a %d\n", productos[i].id, productos[i].stock);
                        break;
                    }
                }
                if (i == totalProductos) {
                    printf("Producto no encontrado.\n");
                }
                break;

            case 2:
                printf("Denominaciones disponibles:\n");
                for (i = 0; i < NUM_DENOMINACIONES; i++) {
                    printf("%d pesos: %d monedas\n", monedas[i].valor, monedas[i].cantidad);
                }
                printf("Ingresa la denominacion de moneda que deseas agregar: ");
                int denom;
                scanf("%d", &denom);
                printf("Ingresa la cantidad a agregar: ");
                scanf("%d", &nuevaCantidad);
                for (i = 0; i < NUM_DENOMINACIONES; i++) {
                    if (monedas[i].valor == denom) {
                        monedas[i].cantidad += nuevaCantidad;
                        printf("Cantidad de monedas de %d pesos actualizada a %d\n", denom, monedas[i].cantidad);
                        break;
                    }
                }
                if (i == NUM_DENOMINACIONES) {
                    printf("Denominacion no valida.\n");
                }
                break;

            case 3:
            	system("cls");
                return;
                

            default:
                printf("Opcion no valida.\n");
        }
        Sleep(2000);
          
    }
}

// Funci�n para mostrar advertencias de stock o fondo bajo
void verificarAdvertencias(struct Producto productos[], int totalProductos, struct Moneda monedas[]) {
    int totalFondo = calcularTotalFondo(monedas);
    int advertencia = 0;

    if (totalFondo < 20) {
        printf("ADVERTENCIA: El fondo de cambio es bajo (%d pesos).\n", totalFondo);
        advertencia = 1;
    }
    for (int i = 0; i < totalProductos; i++) {
        if (productos[i].stock == 1) {
            printf("ADVERTENCIA: Stock bajo para el producto %s.\n", productos[i].id);
            advertencia = 1;
        }
    }

    if (advertencia) {
    		
        printf("Presiona 'M' para entrar al menu de reabastecimiento o cualquier otra tecla para continuar.\n");
        char opcion = getch();
        if (opcion == 'M' || opcion == 'm') {
            menuReabastecimiento(productos, totalProductos, monedas);
        }
        system("cls");
    }
}
//INICIO DEL MAIN 
int main() {
    struct Producto productos[] = {
        {"C01", 10, 5},
        {"C02", 15, 3},
        {"C03", 20, 2},
        {"C04", 25, 2},  
        {"C05", 30, 7}
    };

    struct Moneda monedas[NUM_DENOMINACIONES] = {
        {20, 2},
        {10, 1},
        {5, 0},
        {2, 0},
        {1, 0}
    };

     int totalProductos = 5;
    int totalInsertado = 0; 
    int moneda;
    char entrada[4];
    int i, encontrado = 0;

    // Almacenar las monedas ingresadas
    int monedasIngresadas[MAX_MONEDAS];
    int totalMonedasIngresadas = 0;
    
    while (1) {
        system("cls");
        printf("=== SISTEMA DISPENSADOR DE PRODUCTOS ===\n");
        verificarAdvertencias(productos, 5, monedas);

        // L�gica principal para ingresar monedas y seleccionar productos
        char entrada[10];
        int encontrado = 0;
        printf("Total insertado: %d pesos\n", totalInsertado);
        printf("Fondo de cambio disponible:\n");
        int totalFondo = calcularTotalFondo(monedas);  // Calcular el total del fondo
        for (int i = 0; i < NUM_DENOMINACIONES; i++) {
            printf("%d pesos: %d monedas\n", monedas[i].valor, monedas[i].cantidad);
        }
        printf("Total en el fondo: %d pesos\n", totalFondo);
        printf("\n");

        printf("Inserta monedas de (1, 2, 5, 10, 20) pesos o selecciona un producto.\n");
        printf("Ingresa 'salir' para cancelar y devolver las monedas.\n");

        // Mostrar productos
        printf("            PRODUCTOS\n");
        for (int i = 0; i < 5; i++) {
            printf("%s - Precio: %d pesos - Stock: %d\n", productos[i].id, productos[i].precio, productos[i].stock);
        }
        printf("\n");

        // Leer la entrada del usuario
        printf("Ingresa el valor de la moneda, el ID del producto o 'salir': ");
        scanf("%s", entrada);

         // Verificar si el usuario ingres� 'salir'
        if (strcmp(entrada, "salir") == 0) {
            printf("Proceso cancelado. Devolviendo monedas...\n");
            devolverMonedas(monedasIngresadas, totalMonedasIngresadas); // Llamar a la funci�n para devolver las monedas
            totalInsertado = 0; 
            totalMonedasIngresadas = 0; // Reiniciar el contador de monedas
            Sleep(4000);
            continue;
        }

        // Verificar si el usuario ingres� una moneda v�lida
        if (sscanf(entrada, "%d", &moneda) == 1) {
            if (moneda == 1 || moneda == 2 || moneda == 5 || moneda == 10 || moneda == 20) {
                totalInsertado += moneda; 
                monedasIngresadas[totalMonedasIngresadas] = moneda; // Almacenar la moneda ingresada
                totalMonedasIngresadas++; // Incrementar el contador de monedas ingresadas

                printf("Moneda aceptada: %d pesos. Total insertado: %d pesos.\n", moneda, totalInsertado);
                Sleep(3000);
            } else {
                printf("Moneda no valida. Solo se aceptan monedas de 1, 2, 5, 10 y 20 pesos.\n");
                Sleep(3000);
            }
        } else {
            encontrado = 0;
            for (i = 0; i < totalProductos; i++) {
                if (strcmp(productos[i].id, entrada) == 0) {
                    encontrado = 1;
                    if (productos[i].stock > 0) {
                        if (totalInsertado >= productos[i].precio) {
                            printf("Has seleccionado el producto %s. Precio: %d pesos\n", productos[i].id, productos[i].precio);
                            
                            // Verificar si se puede devolver el cambio antes de reducir el stock
                            if (!devolverCambio(totalInsertado - productos[i].precio, monedas)) {
                                printf("No hay suficiente cambio disponible para completar la transacci�n.\n");
                                printf("Por favor, ingresa la cantidad correcta del producto.\n");
                            
                                devolverMonedas(monedasIngresadas, totalMonedasIngresadas);
                                totalInsertado = 0; 
                                totalMonedasIngresadas = 0; 
                            } else {
                                productos[i].stock--; 
                                printf("Compra exitosa. El nuevo stock de %s es: %d\n", productos[i].id, productos[i].stock);
                                
                                // Aqu� se suman las monedas ingresadas al fondo solo si se pudo devolver el cambio
                                for (int j = 0; j < totalMonedasIngresadas; j++) {
                                    for (int k = 0; k < NUM_DENOMINACIONES; k++) {
                                        if (monedas[k].valor == monedasIngresadas[j]) {
                                            monedas[k].cantidad++; // Aumentar la cantidad de monedas de esa denominaci�n
                                            break;
                                        }
                                    }
                                }

                                totalInsertado = 0; 
                                totalMonedasIngresadas = 0; 
                            }
                            Sleep(5000);
                        } else {
                            printf("Dinero insuficiente. Necesitas %d pesos y tienes %d pesos.\n", productos[i].precio, totalInsertado);
                            Sleep(3000);
                        }
                    } else {
                        printf("Lo siento, el producto %s est� agotado.\n", productos[i].id);
                        Sleep(2000);
                    }
                    break;
                }
            }
            if (!encontrado) {
                printf("Producto no encontrado. Por favor, selecciona un producto v�lido.\n");
                Sleep(2000);
            }
        }
    }
    return 0;
}

