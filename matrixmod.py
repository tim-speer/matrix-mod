import numpy as np
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


def check_entries(entries, size):
    if not isinstance(entries, np.ndarray):
        raise TypeError('entries must be an ndarray')
    elif not entries.shape == (size, size):
        raise ValueError('entries has the wrong shape')
    elif not entries.dtype == int:
        raise ValueError('entries must have dtype int') 
