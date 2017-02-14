
module HW2(FeatureStruct, FeatureTerm(Simple, Struct), emptyfs, getpath, addpath, delpath, union, intersect) where

data FeatureTerm = Simple String | Struct FeatureStruct
data FeatureStruct = FS [(String, FeatureTerm)]
 
emptyfs     :: FeatureStruct
getpath     :: FeatureStruct -> [String] -> Maybe FeatureTerm
addpath     :: FeatureStruct -> [String] -> FeatureTerm -> FeatureStruct
delpath     :: FeatureStruct -> [String] -> FeatureStruct
union       :: FeatureStruct -> FeatureStruct -> Maybe FeatureStruct
intersect   :: FeatureStruct -> FeatureStruct -> FeatureStruct

-- DO NOT MODIFT ABOVE

instance Show FeatureTerm where
	show (Simple word) =  show word 
	show (Struct fese) = "[" ++ kek fese ++ "]"

instance Show FeatureStruct where
	show (FS []) = "[]"
	show (FS ((a, Simple term):xs)) = "[" ++ kek (FS ((a, Simple term):xs)) ++ "]"
	show (FS ((a, Struct fese):xs))	= "[" ++ kek (FS ((a, Struct fese):xs)) ++ "]"

instance Eq FeatureStruct where
	(==) (FS []) (FS []) = True
	(==) (FS []) _ = False
	(==) _ (FS []) = False
	(==) (FS ((a,b):xs1)) (FS ((c,d):xs2)) = if (a == c) && (b==d)
												then  (FS xs1) == (FS xs2)
											else False
	(/=) (FS []) (FS []) = False
	(/=) (FS []) _ = True
	(/=) _ (FS []) = True
	(/=) (FS ((a,b):xs1)) (FS ((c,d):xs2)) = not( (FS ((a,b):xs1)) == (FS ((c,d):xs2)))


instance Eq FeatureTerm where
	(==) (Simple a) (Simple b) = a==b
	(==) (Struct a) (Struct b) = a==b
	(==) (Simple a) (Struct b) = False
	(==) (Struct a) (Simple b) = False




emptyfs = FS []

kek (FS []) = []
kek (FS [(a, Simple term)]) = a ++"=" ++ show term
kek (FS [(a, Struct fese)]) = a ++ "=>[" ++  kek  fese ++"]"
kek (FS ((a, Simple term):xs)) = a ++"=" ++ show  term++", " ++ kek (FS xs)
kek (FS ((a, Struct fese):xs))	= a ++ "=>[" ++  kek fese ++"]" ++", "++ kek (FS xs)




addpath (FS []) [p] toadd = FS [(p, toadd)]
addpath (FS []) (p:ps) toadd = FS [(p, Struct (helper emptyfs (ps) toadd ))]
addpath (FS ((a,b):ls)) [p] toadd = FS (edpet (FS ((a,b):ls)) [p] toadd)
addpath (FS ((a,b):ls)) (p:ps) toadd = FS (edpet (FS ((a,b):ls)) (p:ps) toadd)


helper (FS []) []  toadd = FS []
helper (FS []) [p]  toadd  = FS (edpet emptyfs [p] toadd)
helper (FS []) (p:ps)  toadd  = FS [(p, Struct (helper emptyfs ps toadd))]



edpet (FS []) [p] toadd = [(p, toadd)]
edpet (FS []) (p:ps) toadd = [(p, Struct (helper emptyfs (ps) toadd ))]
edpet (FS ((a,b):ls)) [p] toadd = if a > p
											then (p, toadd): (a,b) : ls
											else if a == p
											then (p, toadd) : ls
											else (a,b) : edpet (FS(ls)) [p] toadd 


edpet (FS ((a,b):ls)) (p:ps) toadd = if a > p
										then (p, Struct (helper emptyfs (ps) toadd )) : (a,b) : ls
									else if a == p
										then if kolay(b)
											 	then (a, Struct (helper emptyfs (ps) toadd )) : ls
										   	else 
												[(a, convert2( FS (edpet (convert b) ps toadd)))] ++ ls									
									else (a, b) : edpet (FS(ls)) (p:ps) toadd											
kolay (Simple b) = True
kolay (Struct b) = False
convert (Struct b) = (b)
convert2 (x) = Struct x
convert3 (x) = FS (x)


getpath _ [] = Nothing
getpath (FS []) _ = Nothing

getpath (FS ((a,b):ls)) (p:[]) = if a==p
									then Just b
									else if a>p
										then Nothing
									else 
										getpath (FS (ls)) (p:[])



getpath (FS ((a,b):ls)) (p:ps) = if a==p
									then if kolay(b)
										then Nothing
										else
										getpath (convert b) (ps) 
								else if a>p
									then Nothing
								else
									getpath (FS (ls)) (p:ps)				

delpath (FS x) [] = FS x
delpath (FS []) _ = FS []

delpath (FS ((a,b):ls)) (p:[]) = if a==p
									then (FS (ls))
									else if a>p
										then (FS ((a,b):ls))
									else 
										cokyabistir (FS[(a,b)]) (delpath (FS (ls)) (p:[]))

delpath (FS ((a,b):ls)) (p:ps) =  if a==p
									then if kolay(b)
										then (FS ls)
									 else cokyabistir ( FS [(a, Struct (delpath (convert b) (ps)) )]) (FS ls)
									else if a>p
										then (FS ((a,b):ls))
									else
										cokyabistir (FS[(a,b)]) (delpath (FS (ls)) (p:ps))

cokyabistir (FS x) (FS y) = FS (x++y)


union (FS []) (FS []) = Just emptyfs
union (FS []) (FS y) = Just (FS y)
union (FS x) (FS []) = Just (FS x)
union (FS ((a,b):ls1)) (FS ((c,d):ls2)) = if (FS ((a,b):ls1)) == (FS ((c,d):ls2))
											then check (FS ((a,b):ls1))
											else if (checkhelper result result)
												then check result
												else
												Nothing 
											where result = (uni (FS ((a,b):ls1)) (FS ((c,d):ls2)) emptyfs)

check (FS []) = Nothing
check (FS x) = Just (FS x)

uni (FS []) (FS []) (FS z)= (FS z)
uni (FS []) (FS y) (FS z)= cokyabistir (FS z) (FS y)
uni (FS x) (FS []) (FS z)= cokyabistir (FS z) (FS x)

uni (FS ((a,b):ls1)) (FS [(c,d)]) (FS z) = if [(a,b)] == [(c,d)]
												then  uni (FS ls1) emptyfs (cokyabistir (FS z) (FS[(a,b)]))
											else if  a==c && b/=d
												then shortcut (FS ((a,b):ls1)) (FS [(c,d)]) (FS z)
											else
												if a>c
													then uni (FS((a,b):ls1)) emptyfs (cokyabistir (FS z) (FS[(c,d)]))
												else if a==c
													then cokyabistir (uni (convert b) (convert d) (FS z)) (FS(ls1))
												else
													uni (FS(ls1)) (FS[(c,d)]) (cokyabistir (FS z) (FS[(a,b)]))


uni (FS ((a,b):ls1)) (FS ((c,d):ls2)) (FS z) =   uni ( uni (FS ((a,b):ls1)) (FS [(c,d)]) (FS z))  (FS ls2) emptyfs

checkhelper (FS []) (FS x) = True

checkhelper (FS ((a,b):ls1)) (FS x)  = if b == (Struct emptyfs)
													then False
										else if kolay b
											then checkhelper (FS ls1) (FS x)
										else checkhelper (FS ls1) (FS x) && checkhelper (convert b)	(FS x)											--

shortcut (FS ((a,b):ls1)) (FS [(c,d)]) (FS z) =	 if not(kolay(b)) && not(kolay(d)) && a==c && b/=d
												 	then cokyabistir (FS z ) (cokyabistir (FS [(a, Struct (uni (convert b) (convert d) emptyfs) )]) (FS ls1))
												else emptyfs
intersect (FS []) (FS []) = emptyfs
intersect(FS []) (FS y) = emptyfs
intersect (FS x) (FS []) = emptyfs
intersect (FS ((a,b):ls1)) (FS [(c,d)]) =  miniintersect (FS ((a,b):ls1)) (FS [(c,d)]) emptyfs
intersect (FS ((a,b):ls1)) (FS ((c,d):ls2)) =  miniintersect (FS ((a,b):ls1)) (FS ((c,d):ls2))  emptyfs


miniintersect (FS []) (FS []) (FS z ) = (FS z )
miniintersect(FS []) (FS y) (FS z ) = (FS z )
miniintersect (FS x) (FS []) (FS z ) = (FS z )
miniintersect (FS ((a,b):ls1)) (FS [(c,d)]) (FS z ) = if a == c
											then interhelper (FS ((a,b):ls1)) (FS [(c,d)]) (FS z )
										else
											miniintersect (FS ls1) (FS [(c,d)]) (FS z)

miniintersect (FS ((a,b):ls1)) (FS ((c,d):ls2)) (FS z ) =  miniintersect (FS ((a,b):ls1)) (FS ls2)  ( miniintersect (FS ((a,b):ls1)) (FS [(c,d)]) (FS z ) )  


interhelper (FS []) (FS []) (FS z ) = (FS z )
interhelper (FS []) (FS y) (FS z ) = (FS z )
interhelper (FS x) (FS []) (FS z ) = (FS z )
interhelper (FS ((a,b):ls1)) (FS [(c,d)]) (FS z) = if (not(kolay b)) && (not(kolay d)) 
													then cokyabistir (FS z) (FS [(a, Struct (intersect (convert b) (convert d)))])
													else if (kolay b) && (kolay d) && b==d
														then cokyabistir (FS z) (FS [(a,b)])
													else
														cokyabistir (FS z) (FS [(a, Struct emptyfs)])
