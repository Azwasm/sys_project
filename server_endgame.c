int endGame(int c)
{
        const int NOD=8;

        int x,y,player,d,i;
        int dx[]={1,1,0,-1,-1,-1,0,1};
        int dy[]={0,1,1,1,0,-1,-1,-1};
		for (x = 0; x < WIDTH; x++)
		{
			for (y = 0; y < HEIGHT; y++) 
			{
				player = board[x][y];
				if (player == c) 
				{
					for (d = 0; d < NOD; d++)
					{
						i = 1;
						for (i = 1; i < 5; i++) 
						{
							int tx = x + (dx[d] * i);
							int ty = y + (dy[d] * i);
							if (board[tx][ty] != c)
								break;
						}
						if (i == 5)
							return END;
					}
				}
			}
		}
        return CONTINUE;
}