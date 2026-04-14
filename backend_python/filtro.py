inventario_tiendita = [
    {"id": 1, "nombre": "Coca Cola", "categoria": "Bebidas", "precio": 2.5},
    {"id": 2, "nombre": "Pan Tajado", "categoria": "Panaderia", "precio": 3.0},
    {"id": 3, "nombre": "Jugo de Naranja", "categoria": "Bebidas", "precio": 1.5},
    {"id": 4, "nombre": "Croissant", "categoria": "Panaderia", "precio": 2.0},
]


# Recuerda usar los parámetros, ¡no la variable global!
def filtrar_por_categoria(lista_productos, categoria_buscada):
    # 1. Crea una lista vacía llamada 'resultados' (usando corchetes [])
    resultado = []
    # 2. Haz un ciclo 'for' para recorrer 'lista_productos'
    for productos in lista_productos:
        if productos["categoria"] == categoria_buscada:
            resultado.append(productos)

    return resultado
    # 3. Adentro del for: Si la "categoria" del producto actual es igual a 'categoria_buscada':

    # 4. Agrega ese producto completo a la lista 'resultados'.
    #    (Pista: usa resultados.append(el_nombre_de_tu_variable_temporal))

    # 5. Afuera del for (cuidado con la sangría), retorna la lista 'resultados'.
    # Borra este pass y escribe tu código aquí


# --- ZONA DE PRUEBAS ---
bebidas_encontradas = filtrar_por_categoria(inventario_tiendita, "Bebidas")

print("Las bebidas disponibles en la tienda son:")
for bebida in bebidas_encontradas:
    print("-", bebida["nombre"], "a $", bebida["precio"])
