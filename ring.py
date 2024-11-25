class Ring:

    def __init__(self, elements, element_type):
        self._elements = elements
        self._element_type = element_type
        self._data = ring_data()

        for elem in elements:
            elem._data = ring_element_data()

    def __contains__(self, elem):
        if not isinstance(elem, self._element_type):
            raise TypeError(f'elem needs type {self._element_type}')
       
        return elem in self._elements

    def __getitem__(self, index):
        return self._elements[index]

    def _element_has_property(self, elem, prop, prop_name):
        if elem in self:
            if elem._data[prop_name] is None:
                elem._data[prop_name] = prop(elem)
    
            return elem._data[prop_name]
 
        raise ValueError('elem is not in ring')

    def _prop_idempotent(self, elem):
        return elem * elem == elem

    def _prop_mul_identity(self, elem):
        for member in self:
            if not (member * elem == elem * member == member):
                return False

        self._data['has_mul_identity'] = True
        self._data['mul_identity'] = elem

        return True 

    def _prop_unit(self, elem):
        for member in self:
            if (member * elem == elem * member == 
                self._data['mul_identity']):
                return True

        return False 

    def is_idempotent(self, elem):
        return self._element_has_property(elem,
                                          self._prop_idempotent,
                                          'is_idempotent')

    def is_mul_identity(self, elem):
        return self._element_has_property(elem,
                                          self._prop_mul_identity,
                                          'is_mul_identity')

    def is_unit(self, elem):
        if not self.has_mul_identity():
            msg = 'Ring does not have multiplicative identity'
            raise ValueError(msg)

        return self._element_has_property(elem,
                                          self._prop_unit,
                                          'is_unit')

    def has_mul_identity(self):
        if self._data['has_mul_identity'] is None:
            for elem in self:
                if self.is_mul_identity(elem):
                    return True

            self._data['has_mul_identity'] = False

        return self._data['has_mul_identity']

    def idempotents(self):
        if self._data['idempotents'] is None:
            idems = []
            for elem in self:
                if self.is_idempotent(elem):
                    idems.append(elem)

            self._data['idempotents'] = idems
        
        return self._data['idempotents']

    def units(self):
        if self._data['units'] is None:
            unit_list = []
            for elem in self:
                if self.is_unit(elem):
                    unit_list.append(elem)

            self._data['units'] = unit_list

        return self._data['units']


def ring_data():
    data = {}
    data['has_mul_identity'] = None
    data['mul_identity'] = None
    data['is_commutative'] = None
    data['idempotents'] = None
    data['units'] = None

    return data


def ring_element_data():
    data = {}
    data['is_idempotent'] = None
    data['is_mul_identity'] = None
    data['is_unit'] = None

    return data
