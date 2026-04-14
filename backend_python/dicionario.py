producto = {
    "id": 101,
    "nombre": "juanchito",
    "edad": 15,
    "pedido": "laptop",
    "precio": 1500.00,
    "stock": 5,
}

print("el comprador es:", producto["nombre"], " y su edad es: ", producto["edad"])
print("el producto pedido es:", producto["pedido"])


# ==========================================
# TU MISIÓN PARA MAÑANA:
# 1. El producto entró en descuento. Modifica el 'precio' a 1200.00
#    (Pista: Se asigna igualito que como se lee, usando el signo =)
# 2. El gerente ordenó restar 1 al 'stock' porque se acaba de vender uno.
# 3. Imprime un mensaje final que diga:
#    "Se vendió una Laptop Pro. Nuevo precio: 1200.0. Stock restante: 4"
# ==========================================
# 1
producto["precio"] = 1200.00
producto["stock"] = producto["stock"] - 1
print(
    "se vendio",
    producto["pedido"],
    "nuevo precio",
    producto["precio"],
    "stock restante",
    producto["stock"],
)

# Escribe tu código aquí abajo cuando retomes:
