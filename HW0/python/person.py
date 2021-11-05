from typing import Tuple, List


class Person:

    def __init__(self, _id: int, state: int) -> None:
        self._id = _id
        self.state = state

        # Nodo padre correspondiente al árbol
        self.parent = None

        # Nodo cabeza y cola correspondiente a la lista ligada-nodos hijos
        self.head = None
        self.tail = None

        # Nodo anterior y siguiente correspondiente a los nodos hermanos
        self.prev = None
        self._next = None

    def append_contact(self, other_id: int, state: int):
        """ 
        Inserta una nueva persona como nodo hijo al final de la lista ligada
        """
        
        # Nuevo nodo con id dado y padre self
        new = Person(other_id, state)
        new.parent = self
        
        # insertar nodo al final de la lista
        if not self.head:
            self.head = new
        else:
            new.prev = self.tail
            self.tail._next = new
        self.tail = new

        return new

    def search_contact(self, _id: int):
        """ 
        Busca el nodo hijo con id dado 
        """
        current = self.head
        while current:
            if current._id == _id:
                return current
            current = current._next
        return None
    
    def recursive_inform(self, depth: int, output_file):
        output_file.write("    "*depth + f"{self._id}:{self.state}\n")
        current = self.head
        while current:
             current.recursive_inform(depth + 1, output_file)
             current = current._next
        