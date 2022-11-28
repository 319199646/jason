#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
//void create_jaso(Invoice* voice, char* filenae)

typedef struct
{
    char nombre[32];
    int semestre;
    float promedio;
} Alumno;

typedef struct
{
    char profesor[32];
    int grupo;
    char semestre[8];
    int anio;
    bool finalizado;
    Alumno alumnos[10];
} Grupo;

typedef struct Product
{
    int barcode;
    char name[32];
    double price;
}Product;

typedef struct Item
{
    Product product;
    int quantity;
}Item;

typedef struct Invoice
{
    char buyer[32];
    char date[11];
    Item items[5];
    double subtotal;
    double vat;
    double total;
    bool payment;
}Invoice;

#define MAX_ALUMS 5
int main()
{

    Invoice factura={
    .buyer="Skock",
    .date="27-11-2022",
    .items[0]={.product.barcode=1199, .product.name="jabon",    .product.price=15.89, .quantity=3},
    .items[1]={.product.barcode=3682, .product.name="guantes",   .product.price=90.5, .quantity=2},
    .items[2]={.product.barcode=1302, .product.name="leche"   , .product.price=15.89, .quantity=4},
    .items[3]={.product.barcode=1820, .product.name="galletas", .product.price=15.89, .quantity=1},
    .items[4]={.product.barcode=7921, .product.name="arroz",    .product.price=15.89, .quantity=3},
    .vat=1.16,
    .payment=false
    };
    factura.subtotal=0;
    for (size_t i = 0; i < 5; i++)
        factura.subtotal+=(factura.items[i].product.price)*factura.items[i].quantity;
    factura.total+=(factura.subtotal)*factura.vat;
   
    Grupo g03 = {
        .profesor = "Fco",
        .grupo = 3,
        .semestre = "2022-2",
        .anio = 2022,
        .finalizado = false,
        .alumnos[0] = {.nombre = "Xocas", .semestre = 3, .promedio = 6.1},
        .alumnos[1] = {.nombre = "Liza", .semestre = 2, .promedio = 10.0},
        .alumnos[2] = {.nombre = "Milhouse", .semestre = 3, .promedio = 9.5},
    };
    FILE *json_output = fopen("factura.json", "w");
    if (!json_output)
    {
        printf("Error abriendo el archivo\n");
        exit(1);
    }
    fprintf(json_output, "{\n");
    fprintf(json_output, "\"Comprador\": \"%s\",\n", factura.buyer);
    fprintf(json_output, "\"fecha\": \"%s\",\n", factura.date);
    fprintf(json_output, "\"subtotal\": \"%.2f\",\n", factura.subtotal);
    fprintf(json_output, "\"IVA\": \"%.2f\",\n", factura.vat);
    fprintf(json_output, "\"total\": \"%.2f\",\n", factura.total);
    fprintf(json_output, "\"productos\": [\n");
    for (size_t i = 0; i < MAX_ALUMS; ++i)
    {
        if (i > 0)
            fprintf(json_output, ",\n");
        fprintf(json_output, "{ ");
        fprintf(json_output, "\"name\": \"%s\", \"barcode\": %d, \"price\": %0.2f,\"quantity\": %d",factura.items[i].product.name,factura.items[i].product.barcode,factura.items[i].product.price ,factura.items[i].quantity);
        fprintf(json_output, " }");
        // la ',' separadora de registros se inserta al principio del ciclo; // la ',' separadora NO se inserta en el último registro
    }
    fprintf(json_output, "\n]"); // fprintf( json_output, ",\n" ); // descomentar cuando este arreglo NO sea el último elemento
    fprintf(json_output, "\n}");
    fclose(json_output);
}
