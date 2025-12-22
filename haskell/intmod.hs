data IntMod = IntMod { value :: Int, modulus :: Int }
  deriving (Show)

reduceIntMod :: IntMod -> IntMod
reduceIntMod (IntMod value modulus) = IntMod (mod value modulus) modulus 
