class Solution {
public:
    bool isSafe(int row,int col,vector<string> board,int n)
    {
        int rowi,coli;
        rowi=row;
        coli=col;


        while(rowi>=0 && coli>=0)
        {
            if(board[rowi][coli]=='Q')
            {
                return false;
            }
            rowi--;
            coli--;
        }

        rowi=row;
        coli=col;

        while(coli>=0)
        {
            if(board[rowi][coli]=='Q'){
                return false;
            }
            coli--;
        }


        rowi=row;
        coli=col;

        while(rowi<n && coli>=0)
        {
            if(board[rowi][coli]=='Q'){
                return false;
            }
            rowi++;
            coli--;
        }
        return true;
    }
    void solve(int col,vector<string> &baord,vector<vector<string>> &ans,int n)
    {
        if(col==n){
            ans.push_back(baord);
        }

        for(int row=0;row<n;row++)
        {
            if(isSafe(row,col,baord,n))
            {
                baord[row][col]='Q';
                solve(col+1,baord,ans,n);
                baord[row][col]='.';
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) 
    {
        vector<vector<string>> ans;
        vector<string> board(n);
        string s(n,'.');
        for(int i=0;i<n;i++)
        {
            board[i]=s;
        }
        solve(0,board,ans,n);
        return ans;
    }
};