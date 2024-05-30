# Pastram functia din C
def MinOfTwo(a,b)
    if ab
        return a
    else
        return b
def NrMinimOperatii(regula,fragment_cod)
    n=len(regula)
    m=len(fragment_cod)
    dp = [[0]  (m+1) for _ in range(n+1)]
    # Initializam prima linie si prima coloana a matricei dp
    # Pentru transformarea unui sir vid costul este 1
    for i in range(n+1)
        dp[i][0]=i
    for j in range (m+1)
        dp[0][j]=j
    for i in range (n)
        for j in range(m)
            if regula[i]==fragment_cod[j]
                dp[i+1][j+1]=dp[i][j]
            else
                 insert_cost=dp[i+1][j]+1
                 delete_cost=dp[i][j+1]+1
                 replace_cost=dp[i][j]+1
                 if regula[i-1]==fragment_cod[j] and regula[i]==fragment_cod[j-1]
                      swap_cost=dp[i-1][j-1]+1
                      replace_cost=MinOfTwo(replace_cost,swap_cost)
                 dp[i+1][j+1]=MinOfTwo(MinOfTwo(insert_cost,delete_cost),replace_cost)
    return dp[n][m]
regula=input(Introduceti regula care va defini sintaxa valida )
fragment_cod=input(Introduceti fragmentul de cod )
nr=NrMinimOperatii(regula,fragment_cod)
print(nr)
