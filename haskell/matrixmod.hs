module MatrixMod where

import IntMod hiding (modulus)

data MatrixMod = MatrixMod { dim :: Int, modulus :: Int, entries :: [IntMod] }
  deriving (Show)

createMatrixMod :: Int -> Int -> [Int] -> MatrixMod
createMatrixMod dim modulus entries
  | dim >= 1 && 
    modulus >= 2 &&
    length entries == dim^2 = MatrixMod dim modulus (map convert entries) 
  | otherwise = createMatrixMod 2 2 [0, 0, 0, 0]
  where convert = (\v -> createIntMod v modulus)

addMatrixMod :: MatrixMod -> MatrixMod -> MatrixMod
addMatrixMod left right
  | dim m1 == dim m2 &&
    modulus m1 == modulus m2 = MatrixMod (dim m1) (modulus m1) (zipWith (addIntMod) (entries m1) (entries m2)) 
  | otherwise = createMatrixMod 0 0 []
  where m1 = ensureValidMatrix left 
        m2 = ensureValidMatrix right

mulMatrixMod :: MatrixMod -> MatrixMod -> MatrixMod
mulMatrixMod left right
  | dim m1 == dim m2 &&
    modulus m1 == modulus m2 = 
  createMatrixMod (dim m1) 
                  (modulus m1) 
                  [innerProduct (row i m1) (column j m2) | i <- [0..dim m1 - 1], j <- [0..dim m1 - 1]]
  | otherwise = createMatrixMod 0 0 []
  where m1 = ensureValidMatrix left 
        m2 = ensureValidMatrix right
        xs = map modToInt (entries m1)
        ys = map modToInt (entries m2)

row :: Int -> MatrixMod -> [Int]
row i (MatrixMod dim _ entries) =
  take dim (drop (i*dim) (map modToInt entries)) 
  
column :: Int -> MatrixMod -> [Int]
column i (MatrixMod dim _ entries) =
 [es !! k | k <- [i, i + dim..(i + dim)*(dim-1)]]
 where es = map modToInt entries 

modToInt :: IntMod -> Int
modToInt (IntMod v _) = v

ensureValidMatrix :: MatrixMod -> MatrixMod
ensureValidMatrix matrix = 
  createMatrixMod (dim matrix) (modulus matrix) (map modToInt (entries matrix))

innerProduct :: [Int] -> [Int] -> Int
innerProduct xs ys 
  | length xs == length ys = sum (zipWith (*) xs ys)
  | otherwise = 0

