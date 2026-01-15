module MatrixMod where

import IntMod hiding (modulus)

data MatrixMod = MatrixMod { dim :: Int, modulus :: Int, entries :: [IntMod] }
  deriving (Show, Eq)

createMatrixMod :: Int -> Int -> [Int] -> MatrixMod
createMatrixMod dim modulus entries
  | dim >= 1 && 
    modulus >= 2 &&
    length entries == dim^2 = MatrixMod dim modulus (map convert entries) 
  where convert = (\v -> createIntMod v modulus)

addMatrixMod :: MatrixMod -> MatrixMod -> MatrixMod
addMatrixMod left right
  | dim m1 == dim m2 &&
    modulus m1 == modulus m2 = MatrixMod (dim m1) (modulus m1) (zipWith (addIntMod) (entries m1) (entries m2)) 
  where m1 = ensureValidMatrix left 
        m2 = ensureValidMatrix right

mulMatrixMod :: MatrixMod -> MatrixMod -> MatrixMod
mulMatrixMod left right
  | dim m1 == dim m2 &&
    modulus m1 == modulus m2 = 
  createMatrixMod (dim m1) 
                  (modulus m1) 
                  [innerProduct (row i m1) (column j m2) | i <- [0..dim m1 - 1], j <- [0..dim m1 - 1]]
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

squareMatrixMod :: MatrixMod -> MatrixMod
squareMatrixMod matrix = mulMatrixMod matrix matrix

isIdempotent :: MatrixMod -> Bool
isIdempotent matrix = squareMatrixMod matrix == matrix

subMatrixEntries :: Int -> Int -> Int -> [Int] -> [Int]
subMatrixEntries i j dim entries = subMatrixEntries' 0 i j dim entries
  
subMatrixEntries' :: Int -> Int -> Int -> Int -> [Int] -> [Int]
subMatrixEntries' index i j dim [] = []
subMatrixEntries' index i j dim (e:es) =
  if row == i || column == j then
    subMatrixEntries' (index+1) i j dim es 
  else
    e : subMatrixEntries' (index+1) i j dim es
  where row = div index dim 
        column = mod index dim  

determinant :: MatrixMod -> IntMod
determinant (MatrixMod dim modulus entries) 
  | dim == 1 = entries !! 0
