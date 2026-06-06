# Esta es la lista de compras del cliente
carrito_cliente = [
    {"nombre": "Laptop", "precio": 1500.0, "cantidad": 1},
    {"nombre": "Mouse", "precio": 25.0, "cantidad": 2},  # Ojo, lleva 2 mouses
    {"nombre": "Teclado", "precio": 80.0, "cantidad": 1},
]


def cobrar_carrito(lista_compras):

    total = 0

    for productos in lista_compras:
        resultado = productos["precio"] * productos["cantidad"]
        total += resultado



    return total




total_a_pagar = cobrar_carrito(carrito_cliente)
print("El cliente debe pagar un total de: $", total_a_pagar)

