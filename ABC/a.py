def solve():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))

    ans = 1
    for x in a:
        ans *= x
        if len(str(ans)) > k:
            ans = 1
    print(ans)

if __name__ == "__main__":
    solve()