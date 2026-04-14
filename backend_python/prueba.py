# Esta es la lista de compras del cliente
carrito_cliente = [
    {"nombre": "Laptop", "precio": 1500.0, "cantidad": 1},
    {"nombre": "Mouse", "precio": 25.0, "cantidad": 2},  # Ojo, lleva 2 mouses
    {"nombre": "Teclado", "precio": 80.0, "cantidad": 1},
]


def cobrar_carrito(lista_compras):
    # 1. Crea una variable llamada 'total' y ponla en 0.
    total = 0
    # 2. Haz un ciclo 'for' para recorrer los productos en 'lista_compras'
    for productos in lista_compras:
        resultado = productos["precio"] * productos["cantidad"]
        total += resultado
    # 3. Adentro del for: Calcula cuánto cuesta este producto en específico
    #    (multiplicando su "precio" por su "cantidad").

    # 4. Súmale ese resultado a tu variable 'total'.
    return total
    # 5. Afuera del for (cuidado con la sangría), haz un 'return' de la variable 'total'.
    # Borra este pass y escribe tu código aquí


# --- ZONA DE PRUEBAS ---
total_a_pagar = cobrar_carrito(carrito_cliente)
print("El cliente debe pagar un total de: $", total_a_pagar)
# El resultado correcto en la consola debería ser: 1630.0
