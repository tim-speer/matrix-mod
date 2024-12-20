import itertools
import numpy as np
import math

from ring import Ring
from ring import display_percent
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
        self._data['clean_decomps'] = None
        self._data['strongly_clean_decomps'] = None
        self._data['is_clean'] = None
        self._data['is_strongly_clean'] = None
        self._data['ntorsion_clean_decomps'] = {}
        self._data['strongly_ntorsion_clean_decomps'] = {}
        self._data['is_ntorsion_clean'] = {} 
        self._data['is_strongly_ntorsion_clean'] = {}

    def __str__(self):
                   
        out = f"{self._size}x{self._size} Matrix Ring over Z_{self._modulus}\n"
        spacing = '-' * len(out) + '\n'
        out = '\n' + spacing + out + spacing 
        keys = ['order', 'units', 'idempotents', 'is_clean', 'is_strongly_clean',
                'is_ntorsion_clean', 'is_strongly_ntorsion_clean']
        
        for key in keys:
            out += self._data_str(key)
  
        return out

    def _prop_unit(self, elem):
        if math.gcd(self._modulus, elem.det()) == 1:
            return True

        return False

    def _data_str(self, key):
        out = ''
        value = self._data[key]
        out += f'{key.title().replace('_', ' ')}: '            
        
        if value is None:
            out += '?'
        elif isinstance(value, list):
            out += str(len(value))
        else:
            out += str(value)

        return out + '\n'

    def identity_matrix(self):
        identity_array = np.identity(self._size, dtype=int)
        return MatrixMod(identity_array, self._modulus, self._size)

    def clean_decomps(self, strong=False):
        key = ''
        if strong:
            key = 'strongly_clean_decomps'
        else:
            key = 'clean_decomps'       

        if ((strong and self._data[key] == None) or
           (not strong and self._data[key] == None)): 
            
            decomps = {} 
            idems = self.idempotents()
            unit_group = self.units()
            total = len(idems) * len(unit_group)

            print(f'Calculating {' '.join(key.split('_'))}')

            count = 1
            for idem in idems:
                for unit in unit_group:
                    display_percent(count, total)
                    if not strong:
                        add_decomp(decomps, idem, unit)
                    elif idem * unit == unit * idem:
                        add_decomp(decomps, idem, unit)
                    count += 1

            self._data[key] = decomps
            
            print()

        return self._data[key]

    def is_clean(self):
        if self._data['is_clean'] == None:
            self._data['is_clean'] = (len(self) == 
                                      len(self.clean_decomps()))
        return self._data['is_clean']    

    def is_strongly_clean(self):
        if self._data['is_strongly_clean'] == None:
            self._data['is_strongly_clean'] = (len(self) ==
                                               len(self.clean_decomps(strong=True)))
        return self._data['is_strongly_clean']

    def ntorsion_clean_decomps(self, n, strong=False):
        data_key = ''
        if strong:
            data_key = 'strongly_ntorsion_clean_decomps'
            if self._data['is_strongly_clean'] is None:
                self.is_strongly_clean()
        else:
            data_key = 'ntorsion_clean_decomps'
            if self._data['is_clean'] is None:
                self.is_clean() 
        
        if not n in self._data[data_key]:

            ntorsion_decomps = {}
            clean_decomps = self.clean_decomps(strong=strong)
            total = sum([len(clean_decomps[key]) for key in clean_decomps])            

            print(f'Calculating {' '.join(data_key.split('_'))}')
            
            count = 1
            for key, decomps in clean_decomps.items():
                for decomp in decomps:
                    display_percent(count, total)
                    if decomp[1] ** n == self.identity_matrix():
                        add_decomp(ntorsion_decomps, 
                                   decomp[0], 
                                   decomp[1])          
                    count += 1

            self._data[data_key][n] = ntorsion_decomps

            print()

        return self._data[data_key][n]

    def is_ntorsion_clean(self, n):
        if not n in self._data['is_ntorsion_clean']:
            self._data['is_ntorsion_clean'][n] = (len(self._elements) == 
                                                  len(self.ntorsion_clean_decomps(n)))
        return self._data['is_ntorsion_clean'][n]

    def is_strongly_ntorsion_clean(self, n):
        if not n in self._data['is_strongly_ntorsion_clean']:
            self._data['is_strongly_ntorsion_clean'][n] = (len(self._elements) ==
                                    len(self.ntorsion_clean_decomps(n, strong=True)))
        return self._data['is_strongly_ntorsion_clean'][n]

    def ntorsion_clean_search(self):
        pass

    def strongly_ntorsiont_clean_search(self):
        pass

def add_decomp(decomps, idem, unit):
    decomp = idem + unit
    try:
        decomps[decomp.to_tuple()].append((idem, unit))
    except KeyError:
        decomps[decomp.to_tuple()] = [(idem, unit)]                 

