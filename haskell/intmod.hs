module IntMod where

data IntMod = IntMod { value :: Int, modulus :: Int } | Invalid
  deriving (Show)

instance Num IntMod where
  x + y | modulus x == modulus y = reduceIntMod $ IntMod (value x + value y) (modulus x)
        | otherwise = Invalid
  x * y | modulus x == modulus y = reduceIntMod $ IntMod (value x * value y) (modulus x)
        | otherwise = Invalid 
  abs x = reduceIntMod x
  signum x = Invalid
  fromInteger x = Invalid
  negate Invalid = Invalid
  negate (IntMod value modulus) = reduceIntMod $ IntMod (-value) modulus

instance Eq IntMod where
  x == y = (modulus x == modulus y) && (mod (value x - value y) (modulus x) == 0) 

reduceIntMod :: IntMod -> IntMod
reduceIntMod Invalid = Invalid
reduceIntMod (IntMod value modulus) 
  | modulus >= 2  = IntMod (mod value modulus) modulus
  | otherwise = Invalid
