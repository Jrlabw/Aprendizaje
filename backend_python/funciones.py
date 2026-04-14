productos_db = [
    {"id": 101, "nombre": "laptop", "precio": 1500.00, "stock": 5},
    {"id": 102, "nombre": "mouse", "precio": 25.00, "stock": 50},
    {"id": 103, "nombre": "tecldo", "precio": 80.00, "stock": 10},
]


def buscar_por_id(id_buscado):
    for buscado in productos_db:
        if buscado["id"] == id_buscado:
            return buscado

    return None


resultado = buscar_por_id(102)

if resultado != None:
    print("exito, encontre el ", resultado["nombre"])
else:
    print("error no encontre el valor")
