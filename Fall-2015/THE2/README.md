WordNet is a lexical database for the English language. It groups English words into sets of syn-
onyms called synsets. All synsets are connected to other synsets by means of semantic relations.
There are several different relations between synsets. In WordNet, nouns are organized into hierar-
chies, defined by hypernym or IS A relationships. Opposite of hypernymy is hyponymy. A hyponym
shares a type-of relationship with its hypernym. For example, pigeon, crow, eagle and seagull are
all hyponyms of bird (their hypernym); which, in turn, is a hyponym of animal. In this implementation
only worked with these relations and built small WordNet’s with IS A relations. These relations are called superclass and subclass relations and used to perform the following operations on these simple WordNet’s:

BuildWordnet
Takes a filename containing the relations as its argument and builds a tree for the WordNet.

HandleTask
Takes a string as its argument will perform following tasks on the WordNet. 

	PrintWordNet
	It prints the wordnet in depth first manner.

	PrintSubclasses
	It prints the subclasses (node, its children and all descendants) of a given class in
	the breadth first order.

	PrintSuperclasses
	PrintSuperclasses task prints the superclasses (node, its parent and all ancestors) of a given node.

	PrintIntermediateClasses
	It prints the classes between two given nodes.
