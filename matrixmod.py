import numpy as np
import math
from intmod import IntMod
from intmod import check_modulus


class MatrixMod(np.ndarray):

    def __new__(cls, entries=None, modulus=2, size=2):
        check_modulus(modulus)
        check_modulus(size)

        if entries is None:
            entries = np.zeros((size, size), int)
        else:
            check_entries(entries, size)

        matrix = np.ndarray.__new__(cls, 
                                    shape=(size, size), 
                                    dtype=IntMod)
       
        for i in range(size):
            for j in range(size):
                matrix[i][j] = IntMod(int(entries[i][j]), 
                                      modulus)
        
        return matrix

    def __init__(self, entries=None, modulus=2, size=2):
        self._modulus = modulus
        self._size = size    

    def __mul__(self, matrix_mod):
        product = self.__matmul__(matrix_mod)
        return MatrixMod(product.entry_values(), 
                         self._modulus, 
                         self._size)

    def __pow__(self, exp):
        check_exp(exp)        

        identity = np.identity(self._size, dtype=int)
        iden_matrix = MatrixMod(identity, self._modulus, self._size)
        product = iden_matrix
 
        for i in range(exp):
            product = product * self
        return product

    def __str__(self):
        return str(self.entry_values()) 

    def __eq__(self, matrix_mod):
        return bool((self.__array__() == matrix_mod.__array__()).all())
    
    def entry_values(self):
        values = [entry._value for row in self for entry in row]
        values_array = np.array(values)
        values_array.shape = self.shape

        return values_array

    def to_tuple(self):
        return tuple(self.entry_values().flatten())

    def is_idempotent(self):
        return self * self  == self


def check_exp(exp):
    if not isinstance(exp, int):
        raise TypeError('exp should be an int')
    elif not exp >= 0:
        raise ValueError('exp should be >= 0')


def check_entries(entries, size):
    if not isinstance(entries, np.ndarray):
        raise TypeError('entries must be an ndarray')
    elif not entries.shape == (size, size):
        raise ValueError('entries has the wrong shape')
    elif not entries.dtype == int:
        raise ValueError('entries must have dtype int') 
