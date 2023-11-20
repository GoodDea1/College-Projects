vector<GraphVertex*> Graph::searchDFS(int start) {

    /*
     Create a Stack<Node> of nodes to visit;
     Add v to the stack;
     while (The stack is not empty) {
     Pop a node from the stack, let it be u;
     if (u has been visited) continue;
     Add u to the visited set;
     for (Node w connected to u)
     Push w onto the stack;
     }
     */

    vector<GraphVertex*> returnVector;
    stack<GraphVertex*> nodeStack;
    bool vertexExists = false;
    int currentIndex = 0;
    GraphVertex* u = nullptr;

    for (int i=start; i<STARTSIZE; i++) {
    	if (edgeArray[i].first->Value == start) {
    		currentIndex = i;
    		vertexExists = true;
    		break;
    	}//if
    	else {}
    }//for

    if (vertexExists == false) {
    	return returnVector;
    }//if
    else {
    	nodeStack.push(edgeArray[currentIndex].first);
    	while (nodeStack.size() != 0) {
    		u = nodeStack.top();
    		nodeStack.pop();
    		if (u->Visited == false) {
    			u->Visited = true;
    			returnVector.push_back(u);
    			for (GraphVertex* w: *(edgeArray[currentIndex].second)) {
    				nodeStack.push(w);
    			}//for
    		}//if
    		else {}
    		for (int i=start; i<STARTSIZE; i++) {
    			if (nodeStack.size() != 0 && edgeArray[i].first->Value == nodeStack.top()->Value) {
    				currentIndex = i;
    				break;
    			}//if
    			else{}
    		}//for
    	}//while
    }//else

    u = nullptr;
    clearAllVisited();
    return returnVector;
}//searchDFS

vector<GraphVertex*> Graph::searchBFS(int start) {

    /*
     Create a Queue<Node> of nodes to visit;
     Add v to the stack;
     while (The stack is not empty) {
     Pop a node from the stack, let it be u;
     if (u has been visited) continue;
     Add u to the visited set;
     for (Node w connected to u)
     Push w onto the stack;
     }
     */

    vector<GraphVertex*> returnVector;
    queue<GraphVertex*> nodeQueue;
    bool vertexExists = false;
    int currentIndex = 0;
    GraphVertex* u = nullptr;

    for (int i=start; i<STARTSIZE; i++) {
    	if (edgeArray[i].first->Value == start) {
    		currentIndex = i;
    		vertexExists = true;
    		break;
    	}//if
    	else {}
    }//for

    if (vertexExists == false) {
    	return returnVector;
    }//if
    else {
    	nodeQueue.push(edgeArray[currentIndex].first);
    	while (nodeQueue.size() != 0) {
    		u = nodeQueue.front();
    		nodeQueue.pop();
    		if (u->Visited == false) {
    			u->Visited = true;
    			returnVector.push_back(u);
    			for (GraphVertex* w: *(edgeArray[currentIndex].second)) {
    				nodeQueue.push(w);
    			}//for
    		}//if
    		else {}
    		for (int i=start; i<STARTSIZE; i++) {
    			if (nodeQueue.size() != 0 && edgeArray[i].first->Value == nodeQueue.front()->Value) {
    				currentIndex = i;
    				break;
    			}//if
    			else{}
    		}//for
    	}//while
    }//else

    u = nullptr;
    clearAllVisited();
    return returnVector;
}//searchBFS
