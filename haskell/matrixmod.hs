import IntMod

data MatrixMod = MatrixMod { size :: Int, modulus :: Int, entries :: [[IntMod]] } | Invalid
  deriving (Show, Eq)
