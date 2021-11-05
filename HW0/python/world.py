from typing import List
from person import Person


class World:

    def __init__(self, n_countries):
        self.n_countries = n_countries
        # Número de regiones por país
        self.n_regions_countries = [0 for _ in range(n_countries)]
        # Cada país
        self.countries = [None for _ in range(n_countries)]
        # Arreglo para guardar numero de personas 
        self.people_count = [[] for _ in range(n_countries)]
            
    
    def create_region(self, idx: int, amount: int) -> None:
        '''
        Funcion que define la lista de regiones por país
        '''
        self.n_regions_countries[idx] = amount

        # cada región empieza con un contacto contagiado
        self.countries[idx] = [Person(0, 2) for _ in range(amount)]
        self.people_count[idx] = [1 for _ in range(amount)]

    def search(self, country_idx: int, region_idx: int, depth: int, route: List):
        """
        Busca un nodo persona a partir de una ruta con profundidad 'depth'
        """
        person = self.countries[country_idx][region_idx]
        for idx in range(depth):
            person = person.search_contact(route[idx])
        return person
    
    def add_contact(self, person, new_id: int):
        """
        Crea una nueva persona con id new_id como nodo hijo de person
        """
        # si el nodo padre está contagiado (2) el estado es sospechoso en espera (1), 
        # en otro caso es sospechoso (0)
        if person.state == 2:
            state = 1
        else:
            state = 0
        
        person.append_contact(new_id, state)
        return person
    
    def add_contacts(self, country_idx: int, region_idx: int, depth: int, route: List, n_contacts: int) -> None:
        """
        Agrega los contactos estrechos de la persona encontrada con la ruta
        """
        person = self.search(country_idx, region_idx, depth, route)

        for _ in range(n_contacts):
            new_id = self.people_count[country_idx][region_idx]
            self.add_contact(person, new_id)
            self.people_count[country_idx][region_idx] += 1

    def inform(self, country_idx: int, region_idx: int, output_file: int) -> None:
        """
        Imprime el árbol del país y región indicado
        """
        output_file.write(f"INFORM {country_idx} {region_idx}\n")
        first = self.countries[country_idx][region_idx]
        first.recursive_inform(0, output_file)
