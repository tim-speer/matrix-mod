import itertools
import numpy as np
from intmod import check_modulus
from matrixmod import MatrixMod


class MatrixRingMod():

    def __init__(self, modulus=2, size=2):
        check_modulus(modulus)
        check_modulus(size)

        self._elements = []
        entry_values = [i for i in range(modulus)]
        entries_list = itertools.product(entry_values, repeat=(size ** 2))
        
        for entries in entries_list:
            entries = np.array(entries)
            entries.shape = (size, size)
            matrix_mod = MatrixMod(entries, modulus, size)
            self._elements.append(matrix_mod)

    def idempotents(self):
        idems = []
        for matrix in self._elements:
            if matrix.is_idempotent():
                idems.append(matrix)
        return idems

    def units(self):
        units = []
        for matrix in self._elements:
            if matrix.is_unit():
                units.append(matrix)
        return units
