import sys
from typing import Tuple, List
from world import World


def fscanf(string: str) -> Tuple[str, str]:
    """
    Función para leer parcialmente una línea.
    Esta función permite hacer una equivalencia
    más directa con la función 'fscanf' de C
    y no es necesario que la reescriban.
    Ejemplo de uso:
    a, b = fscanf("hola como estas")
    a -> "hola"
    b -> "como estas"
    """
    space = string.find(' ')
    if space == -1:
        return string, ''
    else:
        return string[:space], string[space+1:]


def check_arguments(argc: int, argv: List[str]):
    if argc != 3:
        print(f"Modo de uso: python3 {argv[0]} INPUT OUTPUT")
        print("Donde:")
        print("\tINPUT es la ruta del archivo de input")
        print("\tOUTPUT es la ruta del archivo de output")
        return False
    return True


# Programa principal

if __name__ == "__main__":

    # Si los parámetros del programa son inválidos
    if not check_arguments(len(sys.argv), sys.argv):
        # Salimos del programa indicando que no terminó correctamente
        sys.exit(1)

    # Abrimos el archivo de input
    input_file = open(sys.argv[1], 'r')

    # Abrimos archivo de output
    output_file = open(sys.argv[2], 'w')

    # Leemos la cantidad de paises y regiones
    countries, regions = fscanf(input_file.readline().strip())

    # Creamos el mundo
    world = World(int(countries))

    # Poblaremos los paises del mundo con sus regiones
    for i in range(int(countries)):

        # Obtenemos el comando
        q_regions, regions = fscanf(regions)

        # Poblamos cada pais
        world.create_region(i, int(q_regions))

    # Número de líneas a leer
    n_lines = int(input_file.readline().strip())

    # Mientras existan líneas
    while n_lines > 0:

        # Disminuímos el número de líneas por leer en 1
        n_lines -= 1

        # Leemos la línea
        line = input_file.readline().strip()

        # Obtenemos el comando
        command, line = fscanf(line)

        # Instrucciones
        if command == "ADD_CONTACTS":
            # leemos los datos del input
            country_idx, line = fscanf(line)
            region_idx, line = fscanf(line)
            depth, line = fscanf(line)
            depth = int(depth)
            route = [None for _ in range(depth)]
            for r in range(depth):
                person_id, line = fscanf(line)
                route[r] = int(person_id)
            n_contacts, line = fscanf(line)
            country_idx, region_idx, n_contacts = int(country_idx), int(region_idx), int(n_contacts)
            # agregamos los contactos
            world.add_contacts(country_idx, region_idx, depth, route, n_contacts)

        
        elif command == "INFORM":
            country_idx, line = fscanf(line)
            region_idx, line = fscanf(line)
            world.inform(int(country_idx), int(region_idx), output_file)

        elif command == "POSITIVE":
            pass

        elif command == "NEGATIVE":
            pass

        elif command == "RECOVERED":
            pass

        elif command == "CORRECT":
            pass

        elif command == "STADISTICS":
            pass

    # Cerramos archivo de lectura
    input_file.close()

    # Cerramos archivo de escritura
    output_file.close()
