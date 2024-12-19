import itertools
import numpy as np
from ring import Ring
from intmod import check_modulus
from matrixmod import MatrixMod


class MatrixRingMod(Ring):

    def __init__(self, modulus=2, size=2):
        check_modulus(modulus)
        check_modulus(size)

        self._modulus = modulus
        self._size = size
        
        elements = []
        entry_values = [i for i in range(modulus)]
        entries_list = itertools.product(entry_values, repeat=(size ** 2))
        
        for entries in entries_list:
            entries = np.array(entries)
            entries.shape = (size, size)
            matrix_mod = MatrixMod(entries, modulus, size)
            elements.append(matrix_mod)

        super().__init__(elements, MatrixMod)
        self._data['has_mul_identity'] = True
        self._data['mul_identity'] = self.identity_matrix()

    def __str__(self):
        title = f"|{self._size}x{self._size} Matrix Ring over Z_{self._modulus}|" 
        order = f"\n#Elements: {len(self)}"
        
        units = f"\n#Units: "
        if self._data['units'] is None:
            units += f'?'
        else:
            units += f'{len(self._data["units"])}' 
        
        idems = f"\n#Idempotents: "
        if self._data['idempotents'] is None:
            idems += f'?'
        else:
            idems += f'{len(self._data["idempotents"])}'
        
        out = title + order + units + idems
        return out

    def identity_matrix(self):
        identity_array = np.identity(self._size, dtype=int)
        return MatrixMod(identity_array, self._modulus, self._size)

    def clean_decomps(self, strong=False):
        decomps = {} 
        idems = self.idempotents()
        unit_group = self.units()
        for idem in idems:
            for unit in unit_group:
                if not strong:
                    add_decomp(decomps, idem, unit)
                elif idem * unit == unit * idem:
                    add_decomp(decomps, idem, unit)

        return decomps

    def ntorsion_clean_decomps(self, n, strong=False):
        ntorsion_decomps = {}
        for key, decomps in self.clean_decomps(strong=strong).items():
            for decomp in decomps:
                if decomp[1] ** n == self.identity_matrix():
                    add_decomp(ntorsion_decomps, 
                               decomp[0], 
                               decomp[1])          

        return ntorsion_decomps

    def is_ntorsion_clean(self, n, strong=False):
        return (len(self._elements) == 
                len(self.ntorsion_clean_decomps(n, strong=strong)))


def add_decomp(decomps, idem, unit):
    decomp = idem + unit
    try:
        decomps[decomp.to_tuple()].append((idem, unit))
    except KeyError:
        decomps[decomp.to_tuple()] = [(idem, unit)]                 

