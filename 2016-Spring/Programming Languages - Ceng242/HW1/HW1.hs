module HW1 where

--Data
------

type RealName = String
type UserName = String
type GroupName = String
type Message = String

data Post    = Post UserName Message deriving (Show, Eq)
data To 	 = UserID UserName | GroupID GroupName deriving (Show, Eq)
data User    = User UserName RealName [UserName] [Post] deriving (Show, Eq)
data Group   = Group GroupName [UserName] [Post] deriving (Show, Eq)
data DB		 = DB [User] [Group] deriving (Show, Eq)

--1. Commands

newUser      :: DB -> User -> DB
addFriend    :: DB -> UserName -> UserName -> DB
sendPost 	 :: DB -> UserName -> Message -> [To] -> DB
newGroup 	 :: DB -> GroupName -> DB
addMember 	 :: DB -> GroupName -> UserName -> DB
removeMember :: DB -> GroupName -> UserName -> DB

--2. Queries

getFriendNames :: DB -> UserName -> [RealName]
getPosts 	   :: DB -> To -> [Post]
listGroups 	   :: DB -> UserName -> [Group]
suggestFriends :: DB -> User -> Int -> [User]
---- IMPLEMENTATIONS ----

newUser (DB u g) n  = DB (n:u) g


addFriend (DB u g) u2 u3 = DB (miniFriend u u2 u3 ++ miniFriend u u3 u2 ++ unamelist (unamelist u u2) u3  ) g


miniFriend ((User u1 r1 f1 p1):u) ux uy | u1 == ux = [(User u1 r1 (uy:f1) p1)]
				        | otherwise = miniFriend u ux uy
unamelist [] _= []
unamelist ((User u1 r1 f1 p1):u) ux = if ux == u1
					then u
					else (User u1 r1 f1 p1):(unamelist u ux)


--sendPost (DB u g) su m ((UserID rs):r) =  DB (kekpost su m u ((UserID rs):r) )  g
--sendPost (DB u g) su m ((GroupID rs):r) =  DB (findgroups su m u g ((GroupID rs):r) )  g








--kekpost senderuser message ((User u1 r1 f1 p1):u) [UserID rs] =  addpost senderuser message ((User u1 r1 f1 p1):u) [UserID rs] 
--kekpost senderuser message ((User u1 r1 f1 p1):u) ((UserID rs):r) = kekpost senderuser message (addpost senderuser message ((User u1 r1 f1 p1):u) [(UserID rs)]) r



--addpost senderuser message u [] = u
--addpost senderuser message ((User u1 r1 f1 p1):u) ((UserID rs):r) = if u1 == rs
--												then (User u1 r1 f1 ((Post senderuser message ):p1) ):u
--												else addpost senderuser message (u++[User u1 r1 f1 p1]) ([UserID rs])
sendPost (DB u g) su m [] = (DB u g)
sendPost (DB u g) su m ((UserID rs):r) = sendPost (DB (posttoman su m u [rs]) g) su m r
sendPost (DB u g) su m ((GroupID rs):r) = sendPost (DB (posttogroup su m u g [rs]) (updategroup su m g [rs]) ) su m r

updategroup su m ((Group g gu gp):gl) [rs] =  if g == rs
						then (Group g gu (((Post su m):( postfilter         gp    su m     ))  ):gl)
						else updategroup su m (gl++[(Group g gu gp)]) [rs]

posttoman su m [] [rs] = []

posttoman su m ((User u1 r1 f1 p1):u) [rs] =  if u1 == rs
						then (User u1 r1 f1 (((Post su m ):( postfilter     p1   su m )) ) ):u
						else (User u1 r1 f1 p1):(	posttoman su m u [rs])
posttoman su m u (rs:r) = posttoman su m (posttoman su m u [rs]) r

posttogroup su m u ((Group g gu gp):gl) [rs] = if g == rs
						then posttoman su m u gu
						else posttogroup su m u (gl++[(Group g gu gp)]) [rs]
posttogroup su m u ((Group g gu gp):gl) (rs:r) = posttogroup su m (posttogroup su m u ((Group g gu gp):gl) [rs]) ((Group g gu gp):gl) r

getPosts (DB ((User u1 r1 f1 p1):u) g) (UserID adam) =  if u1 == adam
													then  p1
													else getPosts ( DB (u++[User u1 r1 f1 p1]) g ) (UserID adam) 
 
getPosts (DB u ((Group g gu gp):gl)) (GroupID grup) = if g == grup
													then  gp
													else getPosts (DB u (gl++[(Group g gu gp)]) ) (GroupID grup) 

postfilter [] u2 m2 = []
postfilter ((Post u1 m1):pl) u2 m2 = if u1==u2 && m1 == m2
									then pl
									else (Post u1 m1): postfilter pl u2 m2




newGroup (DB u g) n = DB u ((Group n [] []):g)

addMember (DB u ((Group g gu gp):gl) ) g1 u1 = if g==g1
												then  DB u ((Group g (u1:gu) gp):gl) 
											else addMember (DB u (gl++[(Group g gu gp)]) ) g1 u1

removeMember (DB u ((Group g gu gp):gl) ) g1 u1 = if g==g1
												then  DB u ((Group g (remomem gu u1) gp):gl)			
												else removeMember (DB u (gl++[(Group g gu gp)]) ) g1 u1

remomem (gus:gu) u1 =  if gus == u1
						then gu
						else remomem (gu++[gus]) u1

getFriendNames ( DB ((User u1 r1 f1 p1):u) g ) u2 = if u1 == u2 
													then realn ((User u1 r1 f1 p1):u) f1 
													else getFriendNames ( DB (u++[User u1 r1 f1 p1]) g ) u2
realn u [] = []
realn ((User u1 r1 f1 p1):u) (fx:f) = if u1==fx
									then r1: (realn u f )
									else realn (u++[User u1 r1 f1 p1]) (fx:f) 	
listGroups ( DB u [] ) u2 = []	
listGroups ( DB u ((Group g gu gp):gl) ) u2	= if u2 `elem` gu 
												then (Group g gu gp) : (listGroups ( DB u gl) u2)
												else  listGroups ( DB u gl) u2

--suggestFriends ( DB ((User u1 r1 f1 p1):u) g ) (User u2 r2 f2 p2) x = if u1 == u2 
--													then findfriends x ((User u1 r1 f1 p1):u) (findfriends x ((User u1 r1 f1 p1):u) f1 )
--													else suggestFriends ( DB (u++[(User u1 r1 f1 p1)]) g ) (User u2 r2 f2 p2) x

--findfriends n u [] = []
--findfriends n [] _ = []
--findfriends n ((User u1 r1 f1 p1):u) [fx] = if u1==fx
--											then [u1]:(findfriends n u [fx] )
--											else findfriends n (u++[(User u1 r1 f1 p1)]) [fx]

--findfriends n ((User u1 r1 f1 p1):u) (fx:f) =  (findfriends n ((User u1 r1 f1 p1):u) [fx] ) : (findfriends n ((User u1 r1 f1 p1):u) f)
suggestFriends	(DB u g ) u2  n	 = minisuggestFriends	(DB u g ) (u2:[] ) n	
minisuggestFriends	(DB u g ) [u2]  n	=  sonfilter 0 n ( getme (friendfilter u2 (sugFriends n (DB u g ) (sugFriends n (DB u g ) [u2]) ))) (friendfilter u2 (sugFriends n (DB u g ) (sugFriends n (DB u g ) [u2]  ) )) []

getme (x:xs) = x


sugFriends	n (DB ((User u1 r1 f1 p1):u) g ) []  =[]
sugFriends	n (DB ((User u1 r1 f1 p1):u) g ) [User u2 r2 f2 p2]  =	if u1 == u2 
													then usern ((User u1 r1 f1 p1):u) f1 
													else sugFriends n ( DB (u++[User u1 r1 f1 p1]) g ) [User u2 r2 f2 p2]
sugFriends	n (DB u g ) ((User u2 r2 f2 p2) :p) = (sugFriends	n (DB u g ) [User u2 r2 f2 p2] ) ++ ( sugFriends	n (DB u g ) p)




usern u [] = []
usern ((User u1 r1 f1 p1):u) (fx:f) = if u1==fx
									then (User u1 r1 f1 p1): (usern u f )
									else usern (u++[User u1 r1 f1 p1]) (fx:f) 			

friendfilter u2 list = filter (/= u2) list



sonfilter count n u1 [] l1 =if count>= n
							then u1 :l1
							else l1


sonfilter count n u1 (u2:u3) l1 = if u1==u2
							then sonfilter (count+1) n u1 u3 l1
							else if count>= n
							then u1: (sonfilter 1 n u2 u3 l1)
							else sonfilter 1 n u2 u3 l1
