#!/usr/bin/env python3



import base64
import subprocess
import os
import time
import queue
import threading
import gzip
import sys
import os.path

Q = queue.Queue()

keeplooping=True
def threadFunc(so):
    while keeplooping:
        ln = ""
        while True:
            b = so.read(1)
            if len(b) == 0:
                return
            elif b == b"\n":
                break
            else:
                ln += b.decode(errors="ignore")
        print(ln)
        Q.put(ln)
   
def compare( ew,eh,edata, aw,ah,adata):
    if ew != aw or eh != ah:
        print("BAD: Dimension mismatch")
        return
        
    ei=0
    ai=0
    for y in range(ah):
        for x in range(aw):
            ar = adata[ai]
            ai+=1
            ag = adata[ai]
            ai+=1
            ab = adata[ai]
            ai+=1
            er = edata[ei]
            ei+=1
            eg = edata[ei]
            ei+=1
            eb = edata[ei]
            ei+=1
            if ar != er or ag != eg or ab != eb:
                return False, x,y,ar,ag,ab,er,eg,eb
    return True,None
                
                
def main():
    make = os.getenv("MAKE_3701","make")
    P = subprocess.Popen([make],stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    si = P.stdin
    thr = threading.Thread(target=threadFunc, args=(P.stdout,))
    thr.start()

    si.write(b"\x1b" b"c")
    si.flush()
    
    global keeplooping
    
    while keeplooping:
        si.write(b"info registers\n")
        si.flush()
        while True:
            li = Q.get(timeout=4)
            if "SMM=0 HLT=" in li:
                if "HLT=0" in li:
                    print("...")
                    time.sleep(0.5)
                    break
                elif "HLT=1" in li:
                    si.write(b"screendump x\nquit\n")
                    si.flush()
                    P.wait()
                    keeplooping=False
                    break
    
    with gzip.GzipFile(os.path.join(sys.path[0],"color.ppm.gz")) as fp:
        cw,ch,cdata = ppmdecode(fp)

    with gzip.GzipFile(os.path.join(sys.path[0],"nocolor.ppm.gz")) as fp:
        ncw,nch,ncdata = ppmdecode(fp)
    
    with open("x","rb") as fp:
        aw,ah,adata = ppmdecode(fp)
    
    ret = compare(cw,ch,cdata, aw,ah,adata)
    if ret[0]:
        print("OK: Bonus!")
    else:
        ret = compare(ncw,nch,ncdata, aw,ah,adata)
        if ret[0]:
            print("OK: No bonus")
        else:
            _,x,y,ar,ag,ab,er,eg,eb = ret
            print("Bad: At",x,y,": Expected",er,eg,eb,"but got",ar,ag,ab)
    
    print("Press 'enter' to quit")
    z=input()
    
def ppmdecode(fp):
    def line():
        x = fp.readline()
        if x[0] == b"#":
            return line()
        return x
        
    p6 = line()
    assert p6.strip() == b"P6"
    size = line()
    w,h = [int(q) for q in size.split()]
    maxccv = line()
    data = fp.read()
    return (w,h,data)
        
        
main()
