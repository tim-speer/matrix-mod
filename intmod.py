class IntMod:

    def __init__(self, value, modulus):
        check_value(value)
        check_modulus(modulus)

        self._value = value % modulus
        self._modulus = modulus

    def __add__(self, int_mod):
        check_valid_op(self, int_mod)
         
        value = (self._value + int_mod._value) % self._modulus
        modulus = self._modulus

        return IntMod(value, modulus)

    def __mul__(self, int_mod):
        check_valid_op(self, int_mod)

        value = (self._value * int_mod._value) % self._modulus
        modulus = self._modulus

        return IntMod(value, modulus)

    def __str__(self):
        return str(self._value)


def check_int(arg):
    if not isinstance(arg, int):
        raise TypeError('arg should be an int')


def check_ge_2(arg):
    if arg < 2:
        raise ValueError('arg should be >= 2')


def check_value(value):
    check_int(value)


def check_modulus(modulus):
    check_int(modulus)
    check_ge_2(modulus)


def check_int_mod(int_mod):
    if not isinstance(int_mod, IntMod):
        raise TypeError('int_mod should have type IntMod')

 
def check_eq_modulus(modulus1, modulus2):
    if not modulus1 == modulus2:
        raise ValueError('moduli should be equal')


def check_valid_op(int_mod1, int_mod2):
    check_int_mod(int_mod2)
    check_eq_modulus(int_mod1._modulus, int_mod2._modulus)        
