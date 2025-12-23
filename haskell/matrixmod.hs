module MatrixMod where

import IntMod

data MatrixMod = MatrixMod { dim :: Int, modulus :: Int, entries :: [IntMod] }
  deriving (Show)

createMatrixMod :: Int -> Int -> [Int] -> MatrixMod
createMatrixMod dim modulus entries
  | dim >= 1 && 
    modulus >= 2 &&
    length entries == dim^2 = MatrixMod dim modulus (map convert entries) 
  | otherwise = createMatrixMod 2 2 [0, 0, 0, 0]
  where convert = (\v -> createIntMod v modulus)

tuples :: Int -> Int -> [[Int]]
tuples _ 0 = []
tuples items 1 = [[x] | x <- [0..items-1]]
tuples items len = [x : y | x <- [0..items-1], y <- tuples items (len-1)]

matrixRing :: Int -> Int -> [[Int]]
matrixRing modulus dim = tuples modulus (dim^2)
