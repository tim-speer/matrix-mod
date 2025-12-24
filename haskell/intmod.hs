module IntMod where

data IntMod = IntMod { value :: Int, modulus :: Int }
  deriving (Show)

instance Eq IntMod where
  IntMod v1 m1 == IntMod v2 m2 = m1 == m2 && 
                                 (mod (v1-v2) m1) == 0

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
