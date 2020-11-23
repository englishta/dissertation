import sequtils, strutils, strformat, algorithm, math, sugar
let inps = iterator: string {.closure.} =
  while true: (for s in stdin.readLine.split: yield s)
proc inp: int{.used.} = inps().parseInt()
template newSeqWith(y, x: int, p: untyped): untyped{.used.} =
  newSeqWith(y, newSeqWith(x, p))
{.warning[UnusedImport]: off.}

const pi = 3.141592
var one_sycle = 2*pi*420
var le = 2*pi*420*2000/60 
var pm=120*le/(0.00022*2*1e3)
var be = 350*60/(le*0.0001)
var netu_critu = le/((350/60)*42000)
var v_eff = (2200e-6*2000)/6.0

echo "one_sycle ", one_sycle
echo "le ", le
echo "pm ", pm 
echo "be ", be 
echo "netu_critu ", netu_critu 
echo "v_eff", v_eff 
