#include "Editor.h"

	void Editor::insertLine(){
	
	LinkedNode<Line>* tmp = lines.getNodeAt(cursor);
	Line emptyline;
	lines.insertNode(tmp, emptyline);
	Line * currentline = tmp->getData();
	int linecursor = currentline->getCursorPosition();

	history.push(Action(INSERT_LINE, cursor, linecursor,  'a'));
	cursor = cursor+1;
}

	void Editor::insertChar(char c){

	LinkedNode<Line>* tmp = lines.getNodeAt(cursor);
	Line * currentline = tmp->getData();
	currentline->insert(c);
	int linecursor = currentline->getCursorPosition();
	
	history.push(Action(INSERT_CHAR, cursor, linecursor, c));
}

	void Editor::del(){

	LinkedNode<Line>* tmp = lines.getNodeAt(cursor);
	Line * currentline = tmp->getData();
	int linecursor = currentline->getCursorPosition();
	
	if(linecursor!=currentline->getLength())
	{
	history.push(Action(DEL, cursor, linecursor, currentline->getCharAt(linecursor) ));
	currentline->del();
	}
}




	void Editor::backspace(){

	LinkedNode<Line>* tmp = lines.getNodeAt(cursor);
	Line * currentline = tmp->getData();
	int linecursor = currentline->getCursorPosition();
	if(linecursor!=0)
	{
	history.push(Action(BACKSPACE, cursor, linecursor-1, currentline->getCharAt(linecursor-1) ));
	currentline->backspace();
	}
}




	void Editor::undo(){

	if(!history.empty()){

	Action lastAc = history.top();
	ActionType at = lastAc.getType();
	cursor = lastAc.getRow();
	int linecursor = lastAc.getCol();

	LinkedNode<Line>* tmp = lines.getNodeAt(lastAc.getRow());
	Line * currentline = tmp->getData();

	switch(at)
	{
		case INSERT_CHAR: 
		currentline->moveCursorTo(linecursor);
		currentline->backspace();
	break;

		case DEL:
		currentline->moveCursorTo(linecursor);
		currentline->insert(lastAc.getParam());
		currentline->moveCursorTo(linecursor);
	break;
		case BACKSPACE:
		currentline->moveCursorTo(linecursor);
		currentline->insert(lastAc.getParam());
	break;
		case INSERT_LINE:
		lines.deleteNode(tmp->getNext());

	break;
	}
	history.pop();

	}
}


	void Editor::moveCursorUp(){
	if(cursor)
	{
	cursor = cursor-1;
	}
}


	void Editor::moveCursorDown(){
	LinkedNode<Line>* tmp = lines.getNodeAt(cursor);
	
	if(tmp->getNext())
	{
	cursor = cursor+1;
	}

}

	void Editor::moveCursorLeft(){

	LinkedNode<Line>* tmp = lines.getNodeAt(cursor);
	Line * currentline = tmp->getData();
	int linecursor = currentline->getCursorPosition();

	if(linecursor!=0){
	currentline->moveCursorLeft();
	}
}


	void Editor::moveCursorRight(){

	LinkedNode<Line>* tmp = lines.getNodeAt(cursor);
	Line * currentline = tmp->getData();
	int linecursor = currentline->getCursorPosition();
	
	if(linecursor!=(currentline->getLength())){
	currentline->moveCursorRight();
	}


}	


	int Editor::getCursorRow() const{
	return cursor;
}


	int Editor::getCursorCol() const{

	LinkedNode<Line>* tmp = lines.getNodeAt(cursor);
	Line * currentline = tmp->getData();

	int linecursor = currentline->getCursorPosition();
	return linecursor;
}

	int Editor::getLength() const{
	LinkedNode<Line>* tmp = lines.getHead();
	if(tmp == NULL)
		{return 0;}
	tmp = tmp->getNext();
	int length = 1;
	while(tmp!=NULL)
		{
		tmp = tmp->getNext();
		length++;
		}
	return length;

}

	std::string Editor::getLine(int idx) const{

	LinkedNode<Line>* tmp = lines.getNodeAt(idx);
	Line  *currentline = tmp->getData();
	std::string linecontent = std::string();

	for(int i=0; i<currentline->getLength(); i++){
		linecontent.append(1,currentline->getCharAt(i)) ;
	}
	
	return linecontent;

	
}
