void printTree(Node* root) 
{
    int treeHeight = 3;
    if (root)  return;
    else {
        queue<Node*> q;//Queue* q = createQueue((int)pow(2, treeHeight));
        int i, line_len = 62;
        int first_skip = line_len, in_between_skip;

        if (!q)   return;
        q.push(root);//insertIntoQueue(q, tree->root);
        for (i = 0; i treeHeight; i++) {
            int j = 1 << i, k, l;
            in_between_skip = first_skip;
            first_skip = (first_skip - 2) / 2;
            for (k = 0; k < first_skip; k++) putchar(' ');
            for (k = 0; k < j; k++) {
                Node* btn = q.front();//BinTreeNode* btn = (BinTreeNode*)removeFromQueue(q);
                q.pop();
                if (btn) {
                    q.push(btn->left);//insertIntoQueue(q, btn->left);
                    q.push(btn->right);//insertIntoQueue(q, btn->right);
                }
                else {
                    q.push(nullptr);//insertIntoQueue(q, 0);
                    q.push(nullptr);//insertIntoQueue(q, 0);
                }
                if (btn)  printf("%2d", btn->key);
                else       printf("  ");
                for (l = 0; l < in_between_skip; l++) putchar(' ');
            }
            cout << endl;//putchar('\n');
            cout << endl;//putchar('\n');
        }
        //eraseQueue(q);
    }
}
