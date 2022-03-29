int writeGraphToFile(graph_t graph, char* name){
    FILE *fptr;
    int row, col, nodeNum;
    node_t tempNode;
    fptr = fopen(name, "w");
    fprintf(fptr,"%d %d\n",graph.cols,graph.rows);
    for(row = 0; row< graph.rows; row++){
        for(col = 0; col < graph.cols; col++){
            nodeNum =row*graph.cols+col ;
            tempNode= graph->nodes + nodeNum;
            fprintf(fptr,"   ");
            if(tempNode->left != EMPTY){
                fprintf(fptr,"  %d :%f",nodeNum-1, tempNode->left);
            }
            if(tempNode->right != EMPTY){
                fprintf(fptr,"  %d :%f",nodeNum+1, tempNode->right);
            }
            if(tempNode->up != EMPTY){
                fprintf(fptr,"  %d :%f",nodeNum-graph.cols, tempNode->up);
            }
            if(tempNode->down != EMPTY){
                fprintf(fptr,"  %d :%f",nodeNum+graph.cols, tempNode->down);
            }
            fprintf(fptr,"\n");
            
        }
    }
    fclose(fptr);
    return 0;
}