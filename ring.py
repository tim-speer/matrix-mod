class Ring:

    def __init__(self, elements, element_type):
        self._elements = elements
        self._element_type = element_type

    def __contains__(self, elem):
        if not isinstance(elem, self._element_type):
            raise TypeError(f'elem needs type {self._element_type}')
       
        return elem in self._elements

    def __getitem__(self, index):
        return self._elements[index]

    def _element_has_property(self, elem, prop):
        if elem in self:
            return prop(elem)
 
        raise ValueError('elem is not in ring')

    def _prop_idempotent(self, elem):
        return elem * elem == elem

    def _prop_identity(self, elem):
        for member in self:
            if not (member * elem == elem * member == member):
                return False

        return True 

    def _prop_unit(self, elem):
        pass

    def is_idempotent(self, elem):
        return self._element_has_property(elem,
                                          self._prop_idempotent)

    def is_identity(self, elem):
        return self._element_has_property(elem,
                                          self._prop_identity)

    def is_unit(self, elem):
        return self._element_has_property(elem,
                                          self._prop_unit)
