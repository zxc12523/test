#include <stdio.h>
#include <string.h>

int a[501];

int main()
{
    char size[10];
    scanf("%s", &size);

    int r = size[0] - '0';
    int c = size[2] - '0';

    char row[r];
    char col[c];
    char table[r][c];
    char flag;

    for (int j = 0; j < c; j++)
        scanf(" %c", &col[j]);

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j <= c; j++)
        {
            if (j == 0)
                scanf(" %c", &row[i]);
            else
                scanf(" %c", &table[i][j - 1]);
        }
    }

    //     for(int j=0;j<c;j++) printf("%c ", col[j]);
    //     printf("\n");
    //     for(int i=0;i<r;i++) printf("%c ", row[i]);
    //     printf("\n");

    // for (int i = 0; i < r; i++)
    // {
    //     for (int j = 0; j < c; j++)
    //     {
    //         printf("%c ", &table[i][j]);
    //     }
    //     printf("\n");
    // }

    scanf(" %c\n", &flag);
    if (flag == 'D')
    {
        char str[256];
        scanf("%s", &str);
        printf("%d\n", strlen(str) / 2);
        for (int id = 0; id < strlen(str); id += 2)
        {
            int x, y;
            for (int i = 0; i < r; i++)
            {
                if (row[i] == str[id])
                    x = i;
            }
            for (int j = 0; j < c; j++)
            {
                if (col[j] == str[id + 1])
                    y = j;
            }
            printf("%c", table[x][y]);
        }
    }
    else
    {
        char str[256];
        scanf("%s", &str);
        printf("%d\n", strlen(str) * 2);

        for (int id = 0; id < strlen(str); id++)
        {
            for (int i = 0; i < r; i++)
            {
                for (int j = 0; j < c; j++)
                {
                    if (table[i][j] == str[id])
                    {
                        printf("%c", row[i]);
                        printf("%c", col[j]);
                    }
                }
            }
        }
    }
    printf("\n");
}
