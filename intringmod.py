import math
from ring import Ring
from intmod import IntMod
from intmod import check_modulus
from intmod import check_int_mod


class IntRingMod(Ring):

    def __init__(self, modulus):
        check_modulus(modulus)

        elements = [IntMod(i, modulus) for i in range(modulus)]
        super().__init__(elements, IntMod)
        self._modulus = modulus

    def _prop_unit(self, elem):
        return math.gcd(self._modulus, elem._value) == 1
