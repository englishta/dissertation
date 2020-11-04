<script async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.0/MathJax.js?config=TeX-AMS_CHTML"></script>
<script type="text/x-mathjax-config">
 MathJax.Hub.Config({
 tex2jax: {
 inlineMath: [["\\(","\\)"] ],
 displayMath: [ ['$$','$$'], ["\\[","\\]"] ]
 }
 });
</script>
Nim言語でABC181を解いたコードと解説を載せていきます。  
[https://atcoder.jp/contests/abc181:embed:cite]  
## A問題 [Heavy Rotation](https://atcoder.jp/contests/abc181/tasks/abc181_a)  

**問題文**  
高橋くんは今、白い服を着ています。
高橋くんは、白い服を着た次の日には黒い服を、黒い服を着た次の日には白い服を着ます。
N 日後には何色の服を着るでしょうか？  
**制約**  
Nは整数である  
\\(1\leq N \leq 30\\)  

```nim
import strutils
let read = iterator: string {.closure.} =
  while true:
    for s in stdin.readLine.split:
      yield s

let N = read().parseInt

if N mod 2 == 0:
    echo "White"
else:
    echo "Black"
```
**解説**  
上5行はおまじないです。興味があったら調べてみてください。以下のコードではこの5行を省略します。
偶数と奇数で場合分けする。nimでは、x mod yでxをyで割った余りが求められます。

## B問題 [Trapezoid Sum](https://atcoder.jp/contests/abc181/tasks/abc181_b)  
解答のコードは以下の通りです。ただし、マクロの部分のコードを省略しています。  
```nim
var sum = 0
let N = read().parseInt

for i in 0..<N:
    let a, b = read().parseInt
    sum += (a+b)*(b-a+1)div 2
echo sum
```
**解説**  
等差数列の和の公式、a:初項、b:末項、N=(b-a+1):項数にあてはめます。  
$$ S_{N}=\frac{(a+b)*N}{2} $$
for i in 0..<N:は, for(int i=0; i<N; i++)と同じような意味です。また、div 2は２で割った時に小数点以下を切り捨てて、整数にする演算です。Pythonで言うところの//になります。



