module IntMod where

data IntMod = IntMod { value :: Int, modulus :: Int }
  deriving (Show)

createIntMod :: Int -> Int -> IntMod
createIntMod value modulus 
  | modulus >= 2 = IntMod (mod value modulus) modulus
  | otherwise = IntMod 0 2

addIntMod :: IntMod -> IntMod -> IntMod
addIntMod (IntMod vx mx) (IntMod vy my) 
  | mx == my = createIntMod (vx + vy) mx
  | otherwise = IntMod 0 2

mulIntMod :: IntMod -> IntMod -> IntMod
mulIntMod (IntMod vx mx) (IntMod vy my)
  | mx == my = createIntMod (vx * vy) mx
  | otherwise = IntMod 0 2

enumIntMod :: Int -> [IntMod]
enumIntMod modulus = enumIntMod' modulus 0

enumIntMod' :: Int -> Int -> [IntMod]
enumIntMod' modulus n 
  | modulus < 2 = []
  | n == modulus = []
  | otherwise = IntMod n modulus : enumIntMod' modulus (n+1) 
